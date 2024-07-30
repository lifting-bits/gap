// Copyright (c) 2024-present, Trail of Bits, Inc.

#include <doctest/doctest.h>
#include <gap/sarif/sarif.hpp>

namespace gap::sarif {
    TEST_CASE("Struct to JSON roundtrip") {
        // Sample SARIF output from https://github.com/microsoft/sarif-tutorials/blob/main/docs/1-Introduction.md
        root obj{
            .version = version::k2_1_0,
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
                            .level = level::kError,
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

        json obj_json = obj;
        root deser = obj;
        json deser_json = deser;

        CHECK_EQ(obj_json, deser_json);
    }

    TEST_CASE("JSON to struct roundtrip") {
        auto j = json::parse(R"({
  "version": "2.1.0",
  "runs": [
    {
      "tool": {
        "driver": {
          "name": "ESLint",
          "informationUri": "https://eslint.org",
          "rules": [
            {
              "id": "no-unused-vars",
              "shortDescription": {
                "text": "disallow unused variables"
              },
              "helpUri": "https://eslint.org/docs/rules/no-unused-vars",
              "properties": {
                "category": "Variables"
              }
            }
          ]
        }
      },
      "artifacts": [
        {
          "location": {
            "uri": "file:///C:/dev/sarif/sarif-tutorials/samples/Introduction/simple-example.js"
          }
        }
      ],
      "results": [
        {
          "level": "error",
          "message": {
            "text": "'x' is assigned a value but never used."
          },
          "locations": [
            {
              "physicalLocation": {
                "artifactLocation": {
                  "uri": "file:///C:/dev/sarif/sarif-tutorials/samples/Introduction/simple-example.js",
                  "index": 0
                },
                "region": {
                  "startLine": 1,
                  "startColumn": 5
                }
              }
            }
          ],
          "ruleId": "no-unused-vars",
          "ruleIndex": 0
        }
      ]
    }
  ]
})");

        root root = j;

        json j2 = root;

        CHECK_EQ(j, j2);
    }
}