// Copyright (c) 2024-present, Trail of Bits, Inc.

#include <doctest/doctest.h>
#include <gap/sarif/definitions.hpp>

namespace gap::sarif::definitions {
    TEST_CASE("Roundtrip") {
        // Sample SARIF output from https://github.com/microsoft/sarif-tutorials/blob/main/docs/1-Introduction.md
        root_struct root{
            .version = version_enum::k2_1_0,
            .runs = {
                {
                    .tool = {
                        .driver = {
                            .name = "ESLint",
                            .informationUri = "https://eslint.org",
                            .rules = {{
                                {
                                    .id = "no-unused-vars",
                                    .shortDescription = {{
                                        .text = "disallow unused variables",
                                    }},
                                    .helpUri = "https://eslint.org/docs/rules/no-unused-vars",
                                    .properties = {{
                                        .additional_properties = {
                                            {"category", "Variable"},
                                        },
                                    }},
                                }
                            }},
                        },
                    },
                    .artifacts = {{
                        {
                            .location = {{
                                .uri = "file:///C:/dev/sarif/sarif-tutorials/samples/Introduction/simple-example.js",
                            }},
                        },
                    }},
                    .results = {{
                        {
                            .ruleId = "no-unused-vars",
                            .ruleIndex = 0,
                            .level = level_enum::kError,
                            .message = {
                                .text = "'x' is assigned a value but never used.",
                            },
                            .locations = {{
                                {
                                    .physicalLocation = {{
                                        .artifactLocation = {{
                                            .uri = "file:///C:/dev/sarif/sarif-tutorials/samples/Introduction/simple-example.js",
                                            .index = 0,
                                        }},
                                    }},
                                    .properties = {{
                                        .additional_properties = {
                                            {"region", {
                                                {"startLine", 1},
                                                {"startColumn", 5},
                                            }},
                                        },
                                    }},
                                },
                            }},
                        },
                    }},
                }
            },
        };

        nlohmann::json root_json = root;
        root_struct deser = root;
        nlohmann::json deser_json = deser;

        CHECK(root_json == deser_json);
    }
}