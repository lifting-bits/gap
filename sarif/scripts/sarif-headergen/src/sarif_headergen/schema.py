from typing import TypedDict, NotRequired, Union
from enum import Enum


class Type(str, Enum):
    null = "null"
    boolean = "boolean"
    object = "object"
    array = "array"
    number = "number"
    string = "string"
    integer = "integer"


Schema = TypedDict(
    "Schema",
    {
        "title": NotRequired[str],
        "description": NotRequired[str],
        "type": NotRequired[Type],
        "$ref": NotRequired[str],
        "items": NotRequired["Schema"],
        "properties": NotRequired[dict[str, "Schema"]],
        "additionalProperties": NotRequired[Union["Schema", bool]],
        "definitions": NotRequired[dict[str, "Schema"]],
        "enum": NotRequired[list[str]],
        "required": NotRequired[list[str]],
        "default": NotRequired[str | int | float | bool | list],
    },
)
