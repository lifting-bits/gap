from typing import Literal
from functools import cache
from dataclasses import dataclass

from .schema import Schema

type FieldType = (
    Literal["string", "number", "boolean", "integer", "json"] | "Array" | "Struct" | "Enum" | "ForwardRef" | "Map"
)

@dataclass(frozen=True)
class Array:
    subtype: FieldType


@dataclass(frozen=True)
class Field:
    name: str
    type: FieldType
    description: str | None
    required: bool
    default: str | int | float | bool | list | None


@dataclass(frozen=True)
class Enum:
    name: str
    values: list[str]


@dataclass(frozen=True)
class Struct:
    name: str
    fields: list[Field]
    description: str | None
    additional_props: FieldType | None

@dataclass(frozen=True)
class ForwardRef:
    name: str

@dataclass(frozen=True)
class Map:
    subtype: FieldType


def get_structs(schema: Schema) -> list[Struct | Enum | ForwardRef]:
    assert "definitions" in schema

    res: list[Struct | Enum | ForwardRef] = []
    defs: dict[str, FieldType] = {}
    state: dict[str, Literal["visiting", "visited"]] = {}

    definitions = schema["definitions"]

    def get_field(name: str, field: Schema) -> FieldType:
        if "$ref" in field:
            return get_ref(field["$ref"])

        if "type" in field:
            if field["type"] in ("boolean", "number", "string", "integer"):
                return field["type"]
            if field["type"] == "array":
                items = field["items"]
                return Array(subtype=get_field(name, items))
            if field["type"] == "object":
                if "properties" not in field and "additionalProperties" in field and field["additionalProperties"] != False:
                    if field["additionalProperties"] != True:
                        return Map(subtype=get_field(name, field["additionalProperties"]))
                    else:
                        return "json"
                return make_struct(name, field)
            raise Exception("Invalid type")

        if "enum" in field:
            if name in defs:
                return defs[name]
            enum = Enum(name, field["enum"])
            res.append(enum)
            defs[name] = enum
            return enum

        raise Exception("Unknown field type")

    @cache
    def get_ref(ref: str) -> FieldType:
        assert ref.startswith("#/definitions/")
        name = ref[len("#/definitions/") :]
        if name in state:
            if state[name] == "visiting":
                if name in defs:
                    return defs[name]
                else:
                    fwd = ForwardRef(name)
                    res.append(fwd)
                    defs[name] = fwd
                    return fwd
            else:
                return defs[name]

        state[name] = "visiting"
        result = get_field(name, definitions[name])
        defs[name] = result
        state[name] = "visited"
        return result

    def make_struct(name: str, type: Schema):
        assert type["type"] == "object"
        additional_props: FieldType | None = None
        if "additionalProperties" in type:
            if type["additionalProperties"] == True:
                additional_props = "json"
            elif type["additionalProperties"] != False:
                additional_props = get_field("additional_properties", type["additionalProperties"])
        fields: list[Field] = []
        if "properties" in type:
            fields = [
                Field(
                    name=field_name,
                    type=get_field(field_name, field_type),
                    description=field_type.get("description", None),
                    required="required" in type and field_name in type["required"],
                    default=field_type.get("default", None),
                )
                for field_name, field_type in type["properties"].items()
                if field_name != "$schema"
            ]
        struct = Struct(
            name,
            fields=fields,
            description=type.get("description", None),
            additional_props=additional_props,
        )
        res.append(struct)
        defs[name] = struct
        return struct

    make_struct("root", schema)

    for name in schema["definitions"]:
        get_ref(f"#/definitions/{name}")

    return res
