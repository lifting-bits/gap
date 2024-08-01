import json
from .output import get_structs, Enum, Struct, ForwardRef, Array, FieldType, Map, Field
from .schema import Schema


def get_type_name(type: FieldType, field_names: set[str] = set()):
    def _get_type_name(type: FieldType):
        if isinstance(type, Enum):
            return to_snake_case(f"{type.name}")
        if isinstance(type, Struct):
            return to_snake_case(f"{type.name}")
        if isinstance(type, ForwardRef):
            return to_snake_case(f"{type.name}")
        if isinstance(type, Array):
            return f"std::vector< {get_type_name(type.subtype, field_names)} >"
        if isinstance(type, Map):
            return f"std::unordered_map< std::string, {get_type_name(type.subtype, field_names)} >"
        if type == "boolean":
            return "bool"
        if type == "number":
            return "double"
        if type == "integer":
            return "int64_t"
        if type == "string":
            return "std::string"
        if type == "json":
            return "json"
    name = _get_type_name(type)
    if name in field_names:
        return f"::gap::sarif::{name}"
    return name


def sanitize(name: str) -> str:
    return name.translate(str.maketrans({
        "-": "_",
        ".": "_",
        " ": "_",
    }))


def to_snake_case(name: str) -> str:
    tr = str.maketrans({
        letter: f"_{letter.lower()}" for letter in "QWERTYUIOPASDFGHJKLZXCVBNM"
    })
    return name.translate(tr)


def to_pascal_case(name: str) -> str:
    return name[0].upper() + name[1:]


def get_default_value(field: Field) -> str:
    def stringify(val):
        type = field.type
        if isinstance(type, Array):
            type = type.subtype

        if type == "string":
            val = val.translate(str.maketrans({
                '"': '\\"',
                "\r": "\\r",
                "\n": "\\n",
                "\\": "\\\\",
            }))
            return f'"{val}"'
        if isinstance(type, Enum):
            return f"{get_type_name(type, field.name)}::k{sanitize(to_pascal_case(val))}"
        elif isinstance(val, bool):
            return str(val).lower()
        else:
            return str(val)
    if isinstance(field.default, list):
        if len(field.default) == 0:
            return "{}"
        else:
            return f"{{ {', '.join(map(stringify, field.default))} }}"
    else:
        return stringify(field.default)


def print_struct(elem: Struct, file):
    elem_name = get_type_name(elem)

    print(file=file)
    print("    //", file=file)
    print(f"    // {elem.description}", file=file)
    print("    //", file=file)
    print(f"    struct {elem_name} {{", end="", file=file)
    field_names = set(field.name for field in elem.fields)
    for field in elem.fields:
        print(file=file)
        if field.description is not None:
            print("        //", file=file)
            print(f"        // {field.description}", file=file)
            print("        //", file=file)
        type_name = get_type_name(field.type, field_names)
        if field.required:
            print(f"        {type_name} {field.name};", file=file)
        elif field.default is not None:
            print(f"        {type_name} {field.name} = {get_default_value(field)};", file=file)
        elif isinstance(field.type, Array):
            print(f"        {type_name} {field.name} = {{}};", file=file)
        else:
            print(f"        std::optional< {type_name} > {field.name} = std::nullopt;", file=file)
    if elem.additional_props is not None:
        print(file=file)
        if elem.additional_props == "json":
            print("        json additional_properties;", file=file)
        else:
            print(f"        std::unordered_map< std::string, {get_type_name(elem.additional_props)} > additional_properties;", file=file)

    print("    };", file=file)
    print(file=file)
    print(f"    void to_json(json &, const {elem_name} &);", file=file)
    print(f"    void from_json(const json &, {elem_name} &);", file=file)


def print_enum(elem: Enum, file):
    elem_name = get_type_name(elem)

    print(file=file)
    print(f"    enum class {elem_name} {{", file=file)
    for value in elem.values:
        value_name = sanitize(to_pascal_case(value))
        print(f"        k{value_name},", file=file)
    print("    };", file=file)
    print(file=file)
    print(f"    NLOHMANN_JSON_SERIALIZE_ENUM({elem_name}, {{", file=file)
    for value in elem.values:
        value_name = sanitize(to_pascal_case(value))
        print(f"        {{ {elem_name}::k{value_name}, \"{value}\" }},", file=file)
    print("    })", file=file)


def print_from_json(elem: Struct, file):
    print(f"    void from_json(const json &j, {get_type_name(elem)} &o) {{", file=file)
    print("        for( const auto &[key, val] : j.items() ) {", file=file)
    is_first = True
    for field in elem.fields:
        if is_first:
            print(f"            if ( key == \"{field.name}\" ) {{", file=file)
            is_first = False
        else:
            print(f" else if ( key == \"{field.name}\" ) {{", file=file)
        print(f"                val.get_to(o.{field.name});", file=file)
        print("            }", end="", file=file)
    if elem.additional_props is not None:
        print(" else {", file=file)
        print("                val.get_to(o.additional_properties[key]);", file=file)
        print("            }", end="", file=file)
    print(file=file)
    print("        }", file=file)
    print("    }", file=file)


def print_to_json(elem: Struct, file):
    print(f"    void to_json(json &j, const {get_type_name(elem)} &o) {{", file=file)
    for field in elem.fields:
        if field.required:
            print(f"        j[\"{field.name}\"] = o.{field.name};", file=file)
        elif field.default is not None:
            if isinstance(field.default, list):
                if len(field.default) == 0:
                    print(f"        if ( !o.{field.name}.empty() ) {{", file=file)
                else:
                    print(f"        if ( o.{field.name} != decltype(o.{field.name}){get_default_value(field)} ) {{", file=file)
            else:
                print(f"        if ( o.{field.name} != {get_default_value(field)} ) {{", file=file)
            print(f"            j[\"{field.name}\"] = o.{field.name};", file=file)
            print("        }", file=file)
        elif isinstance(field.type, Array):
            print(f"        if ( !o.{field.name}.empty() ) {{", file=file)
            print(f"            j[\"{field.name}\"] = o.{field.name};", file=file)
            print("        }", file=file)
        else:
            print(f"        if ( o.{field.name}.has_value() ) {{", file=file)
            print(f"            j[\"{field.name}\"] = *o.{field.name};", file=file)
            print("        }", file=file)
    if elem.additional_props is not None:
        if elem.additional_props == "json":
            print("        for ( auto &[key, val] : o.additional_properties.items() ) {", file=file)
        else:
            print("        for ( auto &[key, val] : o.additional_properties ) {", file=file)
        print("            j[key] = val;", file=file)
        print("        }", file=file)
    print("    }", file=file)


if __name__ == "__main__":
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument("input_schema")
    parser.add_argument("output_header")
    parser.add_argument("output_source")

    args = parser.parse_args()

    with open(args.input_schema) as sarif:
        sarif: Schema = json.load(sarif)
        output = get_structs(sarif)
        with open(args.output_header, mode="w") as output_header:
            print("""// Copyright 2024-present, Trail of Bits, Inc.

#pragma once

//
// These definitions were generated from a JSON Schema description of SARIF
// found at https://github.com/microsoft/sarif-python-om/blob/7a84e8c2b2b9d8b9a8d25b1d376f039a0bf92a7c/sarif-schema-2.1.0.json
//
// The naming convention used is to convert all of the definition names from camelCase to snake_case,
// property names are kept as-is.
//
// Enum value names are converted from camelCase to PascalCase and prefixed with `k`.
//

#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include <nlohmann/json.hpp>

namespace gap::sarif
{
    using json = nlohmann::json;""", file=output_header)
            for elem in output:
                if isinstance(elem, ForwardRef):
                    print(f"    struct {get_type_name(elem)};", file=output_header)
                if isinstance(elem, Struct):
                    print_struct(elem, output_header)
                if isinstance(elem, Enum):
                    print_enum(elem, output_header)
            print("} // namespace gap::sarif", file=output_header)

        with open(args.output_source, mode="w") as output_source:
            print("""// Copyright (c) 2024-present, Trail of Bits, Inc.

#include <gap/sarif/sarif.hpp>

namespace nlohmann {
    template<typename T>
    struct adl_serializer< std::optional<T> > {
        static void from_json(const json& j, std::optional<T>& opt) {
            opt = std::optional<T>{ j.get<T>() };
        }
    };
}

namespace gap::sarif {""", file=output_source)
            for elem in output:
                if not isinstance(elem, Struct):
                    continue
                print_from_json(elem, output_source)
                print_to_json(elem, output_source)
            print("} // namespace gap::sarif", file=output_source)
