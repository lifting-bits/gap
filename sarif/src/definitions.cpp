// Copyright (c) 2024-present, Trail of Bits, Inc.

#include <gap/sarif/definitions.hpp>

namespace gap::sarif {
    void from_json(const json &j, property_bag_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "tags" ) {
                std::forward_list<std::string> field;
                val.get_to(field);
                o.tags = field;
                continue;
            }
            val.get_to(o.additional_properties[key]);
        }
    }
    void to_json(json &j, const property_bag_struct &o) {
        if ( o.tags.has_value() ) {
            j["tags"] = *o.tags;
        }
        for ( auto &[key, val] : o.additional_properties ) {
            j[key] = val;
        }
    }
    void from_json(const json &j, root_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "version" ) {
                val.get_to(o.version);
                continue;
            }
            if ( key == "runs" ) {
                val.get_to(o.runs);
                continue;
            }
            if ( key == "inlineExternalProperties" ) {
                std::forward_list<external_properties_struct> field;
                val.get_to(field);
                o.inlineExternalProperties = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const root_struct &o) {
        j["version"] = o.version;
        j["runs"] = o.runs;
        if ( o.inlineExternalProperties.has_value() ) {
            j["inlineExternalProperties"] = *o.inlineExternalProperties;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, address_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "absoluteAddress" ) {
                int64_t field;
                val.get_to(field);
                o.absoluteAddress = field;
                continue;
            }
            if ( key == "relativeAddress" ) {
                int64_t field;
                val.get_to(field);
                o.relativeAddress = field;
                continue;
            }
            if ( key == "length" ) {
                int64_t field;
                val.get_to(field);
                o.length = field;
                continue;
            }
            if ( key == "kind" ) {
                std::string field;
                val.get_to(field);
                o.kind = field;
                continue;
            }
            if ( key == "name" ) {
                std::string field;
                val.get_to(field);
                o.name = field;
                continue;
            }
            if ( key == "fullyQualifiedName" ) {
                std::string field;
                val.get_to(field);
                o.fullyQualifiedName = field;
                continue;
            }
            if ( key == "offsetFromParent" ) {
                int64_t field;
                val.get_to(field);
                o.offsetFromParent = field;
                continue;
            }
            if ( key == "index" ) {
                int64_t field;
                val.get_to(field);
                o.index = field;
                continue;
            }
            if ( key == "parentIndex" ) {
                int64_t field;
                val.get_to(field);
                o.parentIndex = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const address_struct &o) {
        if ( o.absoluteAddress.has_value() ) {
            j["absoluteAddress"] = *o.absoluteAddress;
        }
        if ( o.relativeAddress.has_value() ) {
            j["relativeAddress"] = *o.relativeAddress;
        }
        if ( o.length.has_value() ) {
            j["length"] = *o.length;
        }
        if ( o.kind.has_value() ) {
            j["kind"] = *o.kind;
        }
        if ( o.name.has_value() ) {
            j["name"] = *o.name;
        }
        if ( o.fullyQualifiedName.has_value() ) {
            j["fullyQualifiedName"] = *o.fullyQualifiedName;
        }
        if ( o.offsetFromParent.has_value() ) {
            j["offsetFromParent"] = *o.offsetFromParent;
        }
        if ( o.index.has_value() ) {
            j["index"] = *o.index;
        }
        if ( o.parentIndex.has_value() ) {
            j["parentIndex"] = *o.parentIndex;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, message_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "text" ) {
                std::string field;
                val.get_to(field);
                o.text = field;
                continue;
            }
            if ( key == "markdown" ) {
                std::string field;
                val.get_to(field);
                o.markdown = field;
                continue;
            }
            if ( key == "id" ) {
                std::string field;
                val.get_to(field);
                o.id = field;
                continue;
            }
            if ( key == "arguments" ) {
                std::forward_list<std::string> field;
                val.get_to(field);
                o.arguments = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const message_struct &o) {
        if ( o.text.has_value() ) {
            j["text"] = *o.text;
        }
        if ( o.markdown.has_value() ) {
            j["markdown"] = *o.markdown;
        }
        if ( o.id.has_value() ) {
            j["id"] = *o.id;
        }
        if ( o.arguments.has_value() ) {
            j["arguments"] = *o.arguments;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, artifact_location_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "uri" ) {
                std::string field;
                val.get_to(field);
                o.uri = field;
                continue;
            }
            if ( key == "uriBaseId" ) {
                std::string field;
                val.get_to(field);
                o.uriBaseId = field;
                continue;
            }
            if ( key == "index" ) {
                int64_t field;
                val.get_to(field);
                o.index = field;
                continue;
            }
            if ( key == "description" ) {
                message_struct field;
                val.get_to(field);
                o.description = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const artifact_location_struct &o) {
        if ( o.uri.has_value() ) {
            j["uri"] = *o.uri;
        }
        if ( o.uriBaseId.has_value() ) {
            j["uriBaseId"] = *o.uriBaseId;
        }
        if ( o.index.has_value() ) {
            j["index"] = *o.index;
        }
        if ( o.description.has_value() ) {
            j["description"] = *o.description;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, multiformat_message_string_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "text" ) {
                val.get_to(o.text);
                continue;
            }
            if ( key == "markdown" ) {
                std::string field;
                val.get_to(field);
                o.markdown = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const multiformat_message_string_struct &o) {
        j["text"] = o.text;
        if ( o.markdown.has_value() ) {
            j["markdown"] = *o.markdown;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, artifact_content_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "text" ) {
                std::string field;
                val.get_to(field);
                o.text = field;
                continue;
            }
            if ( key == "binary" ) {
                std::string field;
                val.get_to(field);
                o.binary = field;
                continue;
            }
            if ( key == "rendered" ) {
                multiformat_message_string_struct field;
                val.get_to(field);
                o.rendered = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const artifact_content_struct &o) {
        if ( o.text.has_value() ) {
            j["text"] = *o.text;
        }
        if ( o.binary.has_value() ) {
            j["binary"] = *o.binary;
        }
        if ( o.rendered.has_value() ) {
            j["rendered"] = *o.rendered;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, artifact_hashes_struct &o) {
        for( auto &[key, val] : j.items() ) {
            val.get_to(o.additional_properties[key]);
        }
    }
    void to_json(json &j, const artifact_hashes_struct &o) {
        for ( auto &[key, val] : o.additional_properties ) {
            j[key] = val;
        }
    }
    void from_json(const json &j, artifact_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "description" ) {
                message_struct field;
                val.get_to(field);
                o.description = field;
                continue;
            }
            if ( key == "location" ) {
                artifact_location_struct field;
                val.get_to(field);
                o.location = field;
                continue;
            }
            if ( key == "parentIndex" ) {
                int64_t field;
                val.get_to(field);
                o.parentIndex = field;
                continue;
            }
            if ( key == "offset" ) {
                int64_t field;
                val.get_to(field);
                o.offset = field;
                continue;
            }
            if ( key == "length" ) {
                int64_t field;
                val.get_to(field);
                o.length = field;
                continue;
            }
            if ( key == "roles" ) {
                std::forward_list<roles_enum> field;
                val.get_to(field);
                o.roles = field;
                continue;
            }
            if ( key == "mimeType" ) {
                std::string field;
                val.get_to(field);
                o.mimeType = field;
                continue;
            }
            if ( key == "contents" ) {
                artifact_content_struct field;
                val.get_to(field);
                o.contents = field;
                continue;
            }
            if ( key == "encoding" ) {
                std::string field;
                val.get_to(field);
                o.encoding = field;
                continue;
            }
            if ( key == "sourceLanguage" ) {
                std::string field;
                val.get_to(field);
                o.sourceLanguage = field;
                continue;
            }
            if ( key == "hashes" ) {
                artifact_hashes_struct field;
                val.get_to(field);
                o.hashes = field;
                continue;
            }
            if ( key == "lastModifiedTimeUtc" ) {
                std::string field;
                val.get_to(field);
                o.lastModifiedTimeUtc = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const artifact_struct &o) {
        if ( o.description.has_value() ) {
            j["description"] = *o.description;
        }
        if ( o.location.has_value() ) {
            j["location"] = *o.location;
        }
        if ( o.parentIndex.has_value() ) {
            j["parentIndex"] = *o.parentIndex;
        }
        if ( o.offset.has_value() ) {
            j["offset"] = *o.offset;
        }
        if ( o.length.has_value() ) {
            j["length"] = *o.length;
        }
        if ( o.roles.has_value() ) {
            j["roles"] = *o.roles;
        }
        if ( o.mimeType.has_value() ) {
            j["mimeType"] = *o.mimeType;
        }
        if ( o.contents.has_value() ) {
            j["contents"] = *o.contents;
        }
        if ( o.encoding.has_value() ) {
            j["encoding"] = *o.encoding;
        }
        if ( o.sourceLanguage.has_value() ) {
            j["sourceLanguage"] = *o.sourceLanguage;
        }
        if ( o.hashes.has_value() ) {
            j["hashes"] = *o.hashes;
        }
        if ( o.lastModifiedTimeUtc.has_value() ) {
            j["lastModifiedTimeUtc"] = *o.lastModifiedTimeUtc;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, artifact_change_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "artifactLocation" ) {
                val.get_to(o.artifactLocation);
                continue;
            }
            if ( key == "replacements" ) {
                val.get_to(o.replacements);
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const artifact_change_struct &o) {
        j["artifactLocation"] = o.artifactLocation;
        j["replacements"] = o.replacements;
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, attachment_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "description" ) {
                message_struct field;
                val.get_to(field);
                o.description = field;
                continue;
            }
            if ( key == "artifactLocation" ) {
                val.get_to(o.artifactLocation);
                continue;
            }
            if ( key == "regions" ) {
                std::forward_list<region_struct> field;
                val.get_to(field);
                o.regions = field;
                continue;
            }
            if ( key == "rectangles" ) {
                std::forward_list<rectangle_struct> field;
                val.get_to(field);
                o.rectangles = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const attachment_struct &o) {
        if ( o.description.has_value() ) {
            j["description"] = *o.description;
        }
        j["artifactLocation"] = o.artifactLocation;
        if ( o.regions.has_value() ) {
            j["regions"] = *o.regions;
        }
        if ( o.rectangles.has_value() ) {
            j["rectangles"] = *o.rectangles;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, code_flow_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "message" ) {
                message_struct field;
                val.get_to(field);
                o.message = field;
                continue;
            }
            if ( key == "threadFlows" ) {
                val.get_to(o.threadFlows);
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const code_flow_struct &o) {
        if ( o.message.has_value() ) {
            j["message"] = *o.message;
        }
        j["threadFlows"] = o.threadFlows;
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, reporting_configuration_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "enabled" ) {
                bool field;
                val.get_to(field);
                o.enabled = field;
                continue;
            }
            if ( key == "level" ) {
                level_enum field;
                val.get_to(field);
                o.level = field;
                continue;
            }
            if ( key == "rank" ) {
                double field;
                val.get_to(field);
                o.rank = field;
                continue;
            }
            if ( key == "parameters" ) {
                property_bag_struct field;
                val.get_to(field);
                o.parameters = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const reporting_configuration_struct &o) {
        if ( o.enabled.has_value() ) {
            j["enabled"] = *o.enabled;
        }
        if ( o.level.has_value() ) {
            j["level"] = *o.level;
        }
        if ( o.rank.has_value() ) {
            j["rank"] = *o.rank;
        }
        if ( o.parameters.has_value() ) {
            j["parameters"] = *o.parameters;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, tool_component_reference_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "name" ) {
                std::string field;
                val.get_to(field);
                o.name = field;
                continue;
            }
            if ( key == "index" ) {
                int64_t field;
                val.get_to(field);
                o.index = field;
                continue;
            }
            if ( key == "guid" ) {
                std::string field;
                val.get_to(field);
                o.guid = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const tool_component_reference_struct &o) {
        if ( o.name.has_value() ) {
            j["name"] = *o.name;
        }
        if ( o.index.has_value() ) {
            j["index"] = *o.index;
        }
        if ( o.guid.has_value() ) {
            j["guid"] = *o.guid;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, reporting_descriptor_reference_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "id" ) {
                std::string field;
                val.get_to(field);
                o.id = field;
                continue;
            }
            if ( key == "index" ) {
                int64_t field;
                val.get_to(field);
                o.index = field;
                continue;
            }
            if ( key == "guid" ) {
                std::string field;
                val.get_to(field);
                o.guid = field;
                continue;
            }
            if ( key == "toolComponent" ) {
                tool_component_reference_struct field;
                val.get_to(field);
                o.toolComponent = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const reporting_descriptor_reference_struct &o) {
        if ( o.id.has_value() ) {
            j["id"] = *o.id;
        }
        if ( o.index.has_value() ) {
            j["index"] = *o.index;
        }
        if ( o.guid.has_value() ) {
            j["guid"] = *o.guid;
        }
        if ( o.toolComponent.has_value() ) {
            j["toolComponent"] = *o.toolComponent;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, configuration_override_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "configuration" ) {
                val.get_to(o.configuration);
                continue;
            }
            if ( key == "descriptor" ) {
                val.get_to(o.descriptor);
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const configuration_override_struct &o) {
        j["configuration"] = o.configuration;
        j["descriptor"] = o.descriptor;
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, tool_component_global_message_strings_struct &o) {
        for( auto &[key, val] : j.items() ) {
            val.get_to(o.additional_properties[key]);
        }
    }
    void to_json(json &j, const tool_component_global_message_strings_struct &o) {
        for ( auto &[key, val] : o.additional_properties ) {
            j[key] = val;
        }
    }
    void from_json(const json &j, translation_metadata_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "name" ) {
                val.get_to(o.name);
                continue;
            }
            if ( key == "fullName" ) {
                std::string field;
                val.get_to(field);
                o.fullName = field;
                continue;
            }
            if ( key == "shortDescription" ) {
                multiformat_message_string_struct field;
                val.get_to(field);
                o.shortDescription = field;
                continue;
            }
            if ( key == "fullDescription" ) {
                multiformat_message_string_struct field;
                val.get_to(field);
                o.fullDescription = field;
                continue;
            }
            if ( key == "downloadUri" ) {
                std::string field;
                val.get_to(field);
                o.downloadUri = field;
                continue;
            }
            if ( key == "informationUri" ) {
                std::string field;
                val.get_to(field);
                o.informationUri = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const translation_metadata_struct &o) {
        j["name"] = o.name;
        if ( o.fullName.has_value() ) {
            j["fullName"] = *o.fullName;
        }
        if ( o.shortDescription.has_value() ) {
            j["shortDescription"] = *o.shortDescription;
        }
        if ( o.fullDescription.has_value() ) {
            j["fullDescription"] = *o.fullDescription;
        }
        if ( o.downloadUri.has_value() ) {
            j["downloadUri"] = *o.downloadUri;
        }
        if ( o.informationUri.has_value() ) {
            j["informationUri"] = *o.informationUri;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, tool_component_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "guid" ) {
                std::string field;
                val.get_to(field);
                o.guid = field;
                continue;
            }
            if ( key == "name" ) {
                val.get_to(o.name);
                continue;
            }
            if ( key == "organization" ) {
                std::string field;
                val.get_to(field);
                o.organization = field;
                continue;
            }
            if ( key == "product" ) {
                std::string field;
                val.get_to(field);
                o.product = field;
                continue;
            }
            if ( key == "productSuite" ) {
                std::string field;
                val.get_to(field);
                o.productSuite = field;
                continue;
            }
            if ( key == "shortDescription" ) {
                multiformat_message_string_struct field;
                val.get_to(field);
                o.shortDescription = field;
                continue;
            }
            if ( key == "fullDescription" ) {
                multiformat_message_string_struct field;
                val.get_to(field);
                o.fullDescription = field;
                continue;
            }
            if ( key == "fullName" ) {
                std::string field;
                val.get_to(field);
                o.fullName = field;
                continue;
            }
            if ( key == "version" ) {
                std::string field;
                val.get_to(field);
                o.version = field;
                continue;
            }
            if ( key == "semanticVersion" ) {
                std::string field;
                val.get_to(field);
                o.semanticVersion = field;
                continue;
            }
            if ( key == "dottedQuadFileVersion" ) {
                std::string field;
                val.get_to(field);
                o.dottedQuadFileVersion = field;
                continue;
            }
            if ( key == "releaseDateUtc" ) {
                std::string field;
                val.get_to(field);
                o.releaseDateUtc = field;
                continue;
            }
            if ( key == "downloadUri" ) {
                std::string field;
                val.get_to(field);
                o.downloadUri = field;
                continue;
            }
            if ( key == "informationUri" ) {
                std::string field;
                val.get_to(field);
                o.informationUri = field;
                continue;
            }
            if ( key == "globalMessageStrings" ) {
                tool_component_global_message_strings_struct field;
                val.get_to(field);
                o.globalMessageStrings = field;
                continue;
            }
            if ( key == "notifications" ) {
                std::forward_list<reporting_descriptor_struct> field;
                val.get_to(field);
                o.notifications = field;
                continue;
            }
            if ( key == "rules" ) {
                std::forward_list<reporting_descriptor_struct> field;
                val.get_to(field);
                o.rules = field;
                continue;
            }
            if ( key == "taxa" ) {
                std::forward_list<reporting_descriptor_struct> field;
                val.get_to(field);
                o.taxa = field;
                continue;
            }
            if ( key == "locations" ) {
                std::forward_list<artifact_location_struct> field;
                val.get_to(field);
                o.locations = field;
                continue;
            }
            if ( key == "language" ) {
                std::string field;
                val.get_to(field);
                o.language = field;
                continue;
            }
            if ( key == "contents" ) {
                std::forward_list<contents_enum> field;
                val.get_to(field);
                o.contents = field;
                continue;
            }
            if ( key == "isComprehensive" ) {
                bool field;
                val.get_to(field);
                o.isComprehensive = field;
                continue;
            }
            if ( key == "localizedDataSemanticVersion" ) {
                std::string field;
                val.get_to(field);
                o.localizedDataSemanticVersion = field;
                continue;
            }
            if ( key == "minimumRequiredLocalizedDataSemanticVersion" ) {
                std::string field;
                val.get_to(field);
                o.minimumRequiredLocalizedDataSemanticVersion = field;
                continue;
            }
            if ( key == "associatedComponent" ) {
                tool_component_reference_struct field;
                val.get_to(field);
                o.associatedComponent = field;
                continue;
            }
            if ( key == "translationMetadata" ) {
                translation_metadata_struct field;
                val.get_to(field);
                o.translationMetadata = field;
                continue;
            }
            if ( key == "supportedTaxonomies" ) {
                std::forward_list<tool_component_reference_struct> field;
                val.get_to(field);
                o.supportedTaxonomies = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const tool_component_struct &o) {
        if ( o.guid.has_value() ) {
            j["guid"] = *o.guid;
        }
        j["name"] = o.name;
        if ( o.organization.has_value() ) {
            j["organization"] = *o.organization;
        }
        if ( o.product.has_value() ) {
            j["product"] = *o.product;
        }
        if ( o.productSuite.has_value() ) {
            j["productSuite"] = *o.productSuite;
        }
        if ( o.shortDescription.has_value() ) {
            j["shortDescription"] = *o.shortDescription;
        }
        if ( o.fullDescription.has_value() ) {
            j["fullDescription"] = *o.fullDescription;
        }
        if ( o.fullName.has_value() ) {
            j["fullName"] = *o.fullName;
        }
        if ( o.version.has_value() ) {
            j["version"] = *o.version;
        }
        if ( o.semanticVersion.has_value() ) {
            j["semanticVersion"] = *o.semanticVersion;
        }
        if ( o.dottedQuadFileVersion.has_value() ) {
            j["dottedQuadFileVersion"] = *o.dottedQuadFileVersion;
        }
        if ( o.releaseDateUtc.has_value() ) {
            j["releaseDateUtc"] = *o.releaseDateUtc;
        }
        if ( o.downloadUri.has_value() ) {
            j["downloadUri"] = *o.downloadUri;
        }
        if ( o.informationUri.has_value() ) {
            j["informationUri"] = *o.informationUri;
        }
        if ( o.globalMessageStrings.has_value() ) {
            j["globalMessageStrings"] = *o.globalMessageStrings;
        }
        if ( o.notifications.has_value() ) {
            j["notifications"] = *o.notifications;
        }
        if ( o.rules.has_value() ) {
            j["rules"] = *o.rules;
        }
        if ( o.taxa.has_value() ) {
            j["taxa"] = *o.taxa;
        }
        if ( o.locations.has_value() ) {
            j["locations"] = *o.locations;
        }
        if ( o.language.has_value() ) {
            j["language"] = *o.language;
        }
        if ( o.contents.has_value() ) {
            j["contents"] = *o.contents;
        }
        if ( o.isComprehensive.has_value() ) {
            j["isComprehensive"] = *o.isComprehensive;
        }
        if ( o.localizedDataSemanticVersion.has_value() ) {
            j["localizedDataSemanticVersion"] = *o.localizedDataSemanticVersion;
        }
        if ( o.minimumRequiredLocalizedDataSemanticVersion.has_value() ) {
            j["minimumRequiredLocalizedDataSemanticVersion"] = *o.minimumRequiredLocalizedDataSemanticVersion;
        }
        if ( o.associatedComponent.has_value() ) {
            j["associatedComponent"] = *o.associatedComponent;
        }
        if ( o.translationMetadata.has_value() ) {
            j["translationMetadata"] = *o.translationMetadata;
        }
        if ( o.supportedTaxonomies.has_value() ) {
            j["supportedTaxonomies"] = *o.supportedTaxonomies;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, tool_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "driver" ) {
                val.get_to(o.driver);
                continue;
            }
            if ( key == "extensions" ) {
                std::forward_list<tool_component_struct> field;
                val.get_to(field);
                o.extensions = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const tool_struct &o) {
        j["driver"] = o.driver;
        if ( o.extensions.has_value() ) {
            j["extensions"] = *o.extensions;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, invocation_environment_variables_struct &o) {
        for( auto &[key, val] : j.items() ) {
            val.get_to(o.additional_properties[key]);
        }
    }
    void to_json(json &j, const invocation_environment_variables_struct &o) {
        for ( auto &[key, val] : o.additional_properties ) {
            j[key] = val;
        }
    }
    void from_json(const json &j, invocation_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "commandLine" ) {
                std::string field;
                val.get_to(field);
                o.commandLine = field;
                continue;
            }
            if ( key == "arguments" ) {
                std::forward_list<std::string> field;
                val.get_to(field);
                o.arguments = field;
                continue;
            }
            if ( key == "responseFiles" ) {
                std::forward_list<artifact_location_struct> field;
                val.get_to(field);
                o.responseFiles = field;
                continue;
            }
            if ( key == "startTimeUtc" ) {
                std::string field;
                val.get_to(field);
                o.startTimeUtc = field;
                continue;
            }
            if ( key == "endTimeUtc" ) {
                std::string field;
                val.get_to(field);
                o.endTimeUtc = field;
                continue;
            }
            if ( key == "exitCode" ) {
                int64_t field;
                val.get_to(field);
                o.exitCode = field;
                continue;
            }
            if ( key == "ruleConfigurationOverrides" ) {
                std::forward_list<configuration_override_struct> field;
                val.get_to(field);
                o.ruleConfigurationOverrides = field;
                continue;
            }
            if ( key == "notificationConfigurationOverrides" ) {
                std::forward_list<configuration_override_struct> field;
                val.get_to(field);
                o.notificationConfigurationOverrides = field;
                continue;
            }
            if ( key == "toolExecutionNotifications" ) {
                std::forward_list<notification_struct> field;
                val.get_to(field);
                o.toolExecutionNotifications = field;
                continue;
            }
            if ( key == "toolConfigurationNotifications" ) {
                std::forward_list<notification_struct> field;
                val.get_to(field);
                o.toolConfigurationNotifications = field;
                continue;
            }
            if ( key == "exitCodeDescription" ) {
                std::string field;
                val.get_to(field);
                o.exitCodeDescription = field;
                continue;
            }
            if ( key == "exitSignalName" ) {
                std::string field;
                val.get_to(field);
                o.exitSignalName = field;
                continue;
            }
            if ( key == "exitSignalNumber" ) {
                int64_t field;
                val.get_to(field);
                o.exitSignalNumber = field;
                continue;
            }
            if ( key == "processStartFailureMessage" ) {
                std::string field;
                val.get_to(field);
                o.processStartFailureMessage = field;
                continue;
            }
            if ( key == "executionSuccessful" ) {
                val.get_to(o.executionSuccessful);
                continue;
            }
            if ( key == "machine" ) {
                std::string field;
                val.get_to(field);
                o.machine = field;
                continue;
            }
            if ( key == "account" ) {
                std::string field;
                val.get_to(field);
                o.account = field;
                continue;
            }
            if ( key == "processId" ) {
                int64_t field;
                val.get_to(field);
                o.processId = field;
                continue;
            }
            if ( key == "executableLocation" ) {
                artifact_location_struct field;
                val.get_to(field);
                o.executableLocation = field;
                continue;
            }
            if ( key == "workingDirectory" ) {
                artifact_location_struct field;
                val.get_to(field);
                o.workingDirectory = field;
                continue;
            }
            if ( key == "environmentVariables" ) {
                invocation_environment_variables_struct field;
                val.get_to(field);
                o.environmentVariables = field;
                continue;
            }
            if ( key == "stdin" ) {
                artifact_location_struct field;
                val.get_to(field);
                o.stdin = field;
                continue;
            }
            if ( key == "stdout" ) {
                artifact_location_struct field;
                val.get_to(field);
                o.stdout = field;
                continue;
            }
            if ( key == "stderr" ) {
                artifact_location_struct field;
                val.get_to(field);
                o.stderr = field;
                continue;
            }
            if ( key == "stdoutStderr" ) {
                artifact_location_struct field;
                val.get_to(field);
                o.stdoutStderr = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const invocation_struct &o) {
        if ( o.commandLine.has_value() ) {
            j["commandLine"] = *o.commandLine;
        }
        if ( o.arguments.has_value() ) {
            j["arguments"] = *o.arguments;
        }
        if ( o.responseFiles.has_value() ) {
            j["responseFiles"] = *o.responseFiles;
        }
        if ( o.startTimeUtc.has_value() ) {
            j["startTimeUtc"] = *o.startTimeUtc;
        }
        if ( o.endTimeUtc.has_value() ) {
            j["endTimeUtc"] = *o.endTimeUtc;
        }
        if ( o.exitCode.has_value() ) {
            j["exitCode"] = *o.exitCode;
        }
        if ( o.ruleConfigurationOverrides.has_value() ) {
            j["ruleConfigurationOverrides"] = *o.ruleConfigurationOverrides;
        }
        if ( o.notificationConfigurationOverrides.has_value() ) {
            j["notificationConfigurationOverrides"] = *o.notificationConfigurationOverrides;
        }
        if ( o.toolExecutionNotifications.has_value() ) {
            j["toolExecutionNotifications"] = *o.toolExecutionNotifications;
        }
        if ( o.toolConfigurationNotifications.has_value() ) {
            j["toolConfigurationNotifications"] = *o.toolConfigurationNotifications;
        }
        if ( o.exitCodeDescription.has_value() ) {
            j["exitCodeDescription"] = *o.exitCodeDescription;
        }
        if ( o.exitSignalName.has_value() ) {
            j["exitSignalName"] = *o.exitSignalName;
        }
        if ( o.exitSignalNumber.has_value() ) {
            j["exitSignalNumber"] = *o.exitSignalNumber;
        }
        if ( o.processStartFailureMessage.has_value() ) {
            j["processStartFailureMessage"] = *o.processStartFailureMessage;
        }
        j["executionSuccessful"] = o.executionSuccessful;
        if ( o.machine.has_value() ) {
            j["machine"] = *o.machine;
        }
        if ( o.account.has_value() ) {
            j["account"] = *o.account;
        }
        if ( o.processId.has_value() ) {
            j["processId"] = *o.processId;
        }
        if ( o.executableLocation.has_value() ) {
            j["executableLocation"] = *o.executableLocation;
        }
        if ( o.workingDirectory.has_value() ) {
            j["workingDirectory"] = *o.workingDirectory;
        }
        if ( o.environmentVariables.has_value() ) {
            j["environmentVariables"] = *o.environmentVariables;
        }
        if ( o.stdin.has_value() ) {
            j["stdin"] = *o.stdin;
        }
        if ( o.stdout.has_value() ) {
            j["stdout"] = *o.stdout;
        }
        if ( o.stderr.has_value() ) {
            j["stderr"] = *o.stderr;
        }
        if ( o.stdoutStderr.has_value() ) {
            j["stdoutStderr"] = *o.stdoutStderr;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, conversion_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "tool" ) {
                val.get_to(o.tool);
                continue;
            }
            if ( key == "invocation" ) {
                invocation_struct field;
                val.get_to(field);
                o.invocation = field;
                continue;
            }
            if ( key == "analysisToolLogFiles" ) {
                std::forward_list<artifact_location_struct> field;
                val.get_to(field);
                o.analysisToolLogFiles = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const conversion_struct &o) {
        j["tool"] = o.tool;
        if ( o.invocation.has_value() ) {
            j["invocation"] = *o.invocation;
        }
        if ( o.analysisToolLogFiles.has_value() ) {
            j["analysisToolLogFiles"] = *o.analysisToolLogFiles;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, edge_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "id" ) {
                val.get_to(o.id);
                continue;
            }
            if ( key == "label" ) {
                message_struct field;
                val.get_to(field);
                o.label = field;
                continue;
            }
            if ( key == "sourceNodeId" ) {
                val.get_to(o.sourceNodeId);
                continue;
            }
            if ( key == "targetNodeId" ) {
                val.get_to(o.targetNodeId);
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const edge_struct &o) {
        j["id"] = o.id;
        if ( o.label.has_value() ) {
            j["label"] = *o.label;
        }
        j["sourceNodeId"] = o.sourceNodeId;
        j["targetNodeId"] = o.targetNodeId;
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, edge_traversal_final_state_struct &o) {
        for( auto &[key, val] : j.items() ) {
            val.get_to(o.additional_properties[key]);
        }
    }
    void to_json(json &j, const edge_traversal_final_state_struct &o) {
        for ( auto &[key, val] : o.additional_properties ) {
            j[key] = val;
        }
    }
    void from_json(const json &j, edge_traversal_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "edgeId" ) {
                val.get_to(o.edgeId);
                continue;
            }
            if ( key == "message" ) {
                message_struct field;
                val.get_to(field);
                o.message = field;
                continue;
            }
            if ( key == "finalState" ) {
                edge_traversal_final_state_struct field;
                val.get_to(field);
                o.finalState = field;
                continue;
            }
            if ( key == "stepOverEdgeCount" ) {
                int64_t field;
                val.get_to(field);
                o.stepOverEdgeCount = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const edge_traversal_struct &o) {
        j["edgeId"] = o.edgeId;
        if ( o.message.has_value() ) {
            j["message"] = *o.message;
        }
        if ( o.finalState.has_value() ) {
            j["finalState"] = *o.finalState;
        }
        if ( o.stepOverEdgeCount.has_value() ) {
            j["stepOverEdgeCount"] = *o.stepOverEdgeCount;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, stack_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "message" ) {
                message_struct field;
                val.get_to(field);
                o.message = field;
                continue;
            }
            if ( key == "frames" ) {
                val.get_to(o.frames);
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const stack_struct &o) {
        if ( o.message.has_value() ) {
            j["message"] = *o.message;
        }
        j["frames"] = o.frames;
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, exception_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "kind" ) {
                std::string field;
                val.get_to(field);
                o.kind = field;
                continue;
            }
            if ( key == "message" ) {
                std::string field;
                val.get_to(field);
                o.message = field;
                continue;
            }
            if ( key == "stack" ) {
                stack_struct field;
                val.get_to(field);
                o.stack = field;
                continue;
            }
            if ( key == "innerExceptions" ) {
                std::forward_list<exception_struct> field;
                val.get_to(field);
                o.innerExceptions = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const exception_struct &o) {
        if ( o.kind.has_value() ) {
            j["kind"] = *o.kind;
        }
        if ( o.message.has_value() ) {
            j["message"] = *o.message;
        }
        if ( o.stack.has_value() ) {
            j["stack"] = *o.stack;
        }
        if ( o.innerExceptions.has_value() ) {
            j["innerExceptions"] = *o.innerExceptions;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, external_properties_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "schema" ) {
                std::string field;
                val.get_to(field);
                o.schema = field;
                continue;
            }
            if ( key == "version" ) {
                version_enum field;
                val.get_to(field);
                o.version = field;
                continue;
            }
            if ( key == "guid" ) {
                std::string field;
                val.get_to(field);
                o.guid = field;
                continue;
            }
            if ( key == "runGuid" ) {
                std::string field;
                val.get_to(field);
                o.runGuid = field;
                continue;
            }
            if ( key == "conversion" ) {
                conversion_struct field;
                val.get_to(field);
                o.conversion = field;
                continue;
            }
            if ( key == "graphs" ) {
                std::forward_list<graph_struct> field;
                val.get_to(field);
                o.graphs = field;
                continue;
            }
            if ( key == "externalizedProperties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.externalizedProperties = field;
                continue;
            }
            if ( key == "artifacts" ) {
                std::forward_list<artifact_struct> field;
                val.get_to(field);
                o.artifacts = field;
                continue;
            }
            if ( key == "invocations" ) {
                std::forward_list<invocation_struct> field;
                val.get_to(field);
                o.invocations = field;
                continue;
            }
            if ( key == "logicalLocations" ) {
                std::forward_list<logical_location_struct> field;
                val.get_to(field);
                o.logicalLocations = field;
                continue;
            }
            if ( key == "threadFlowLocations" ) {
                std::forward_list<thread_flow_location_struct> field;
                val.get_to(field);
                o.threadFlowLocations = field;
                continue;
            }
            if ( key == "results" ) {
                std::forward_list<result_struct> field;
                val.get_to(field);
                o.results = field;
                continue;
            }
            if ( key == "taxonomies" ) {
                std::forward_list<tool_component_struct> field;
                val.get_to(field);
                o.taxonomies = field;
                continue;
            }
            if ( key == "driver" ) {
                tool_component_struct field;
                val.get_to(field);
                o.driver = field;
                continue;
            }
            if ( key == "extensions" ) {
                std::forward_list<tool_component_struct> field;
                val.get_to(field);
                o.extensions = field;
                continue;
            }
            if ( key == "policies" ) {
                std::forward_list<tool_component_struct> field;
                val.get_to(field);
                o.policies = field;
                continue;
            }
            if ( key == "translations" ) {
                std::forward_list<tool_component_struct> field;
                val.get_to(field);
                o.translations = field;
                continue;
            }
            if ( key == "addresses" ) {
                std::forward_list<address_struct> field;
                val.get_to(field);
                o.addresses = field;
                continue;
            }
            if ( key == "webRequests" ) {
                std::forward_list<web_request_struct> field;
                val.get_to(field);
                o.webRequests = field;
                continue;
            }
            if ( key == "webResponses" ) {
                std::forward_list<web_response_struct> field;
                val.get_to(field);
                o.webResponses = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const external_properties_struct &o) {
        if ( o.schema.has_value() ) {
            j["schema"] = *o.schema;
        }
        if ( o.version.has_value() ) {
            j["version"] = *o.version;
        }
        if ( o.guid.has_value() ) {
            j["guid"] = *o.guid;
        }
        if ( o.runGuid.has_value() ) {
            j["runGuid"] = *o.runGuid;
        }
        if ( o.conversion.has_value() ) {
            j["conversion"] = *o.conversion;
        }
        if ( o.graphs.has_value() ) {
            j["graphs"] = *o.graphs;
        }
        if ( o.externalizedProperties.has_value() ) {
            j["externalizedProperties"] = *o.externalizedProperties;
        }
        if ( o.artifacts.has_value() ) {
            j["artifacts"] = *o.artifacts;
        }
        if ( o.invocations.has_value() ) {
            j["invocations"] = *o.invocations;
        }
        if ( o.logicalLocations.has_value() ) {
            j["logicalLocations"] = *o.logicalLocations;
        }
        if ( o.threadFlowLocations.has_value() ) {
            j["threadFlowLocations"] = *o.threadFlowLocations;
        }
        if ( o.results.has_value() ) {
            j["results"] = *o.results;
        }
        if ( o.taxonomies.has_value() ) {
            j["taxonomies"] = *o.taxonomies;
        }
        if ( o.driver.has_value() ) {
            j["driver"] = *o.driver;
        }
        if ( o.extensions.has_value() ) {
            j["extensions"] = *o.extensions;
        }
        if ( o.policies.has_value() ) {
            j["policies"] = *o.policies;
        }
        if ( o.translations.has_value() ) {
            j["translations"] = *o.translations;
        }
        if ( o.addresses.has_value() ) {
            j["addresses"] = *o.addresses;
        }
        if ( o.webRequests.has_value() ) {
            j["webRequests"] = *o.webRequests;
        }
        if ( o.webResponses.has_value() ) {
            j["webResponses"] = *o.webResponses;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, external_property_file_reference_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "location" ) {
                artifact_location_struct field;
                val.get_to(field);
                o.location = field;
                continue;
            }
            if ( key == "guid" ) {
                std::string field;
                val.get_to(field);
                o.guid = field;
                continue;
            }
            if ( key == "itemCount" ) {
                int64_t field;
                val.get_to(field);
                o.itemCount = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const external_property_file_reference_struct &o) {
        if ( o.location.has_value() ) {
            j["location"] = *o.location;
        }
        if ( o.guid.has_value() ) {
            j["guid"] = *o.guid;
        }
        if ( o.itemCount.has_value() ) {
            j["itemCount"] = *o.itemCount;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, external_property_file_references_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "conversion" ) {
                external_property_file_reference_struct field;
                val.get_to(field);
                o.conversion = field;
                continue;
            }
            if ( key == "graphs" ) {
                std::forward_list<external_property_file_reference_struct> field;
                val.get_to(field);
                o.graphs = field;
                continue;
            }
            if ( key == "externalizedProperties" ) {
                external_property_file_reference_struct field;
                val.get_to(field);
                o.externalizedProperties = field;
                continue;
            }
            if ( key == "artifacts" ) {
                std::forward_list<external_property_file_reference_struct> field;
                val.get_to(field);
                o.artifacts = field;
                continue;
            }
            if ( key == "invocations" ) {
                std::forward_list<external_property_file_reference_struct> field;
                val.get_to(field);
                o.invocations = field;
                continue;
            }
            if ( key == "logicalLocations" ) {
                std::forward_list<external_property_file_reference_struct> field;
                val.get_to(field);
                o.logicalLocations = field;
                continue;
            }
            if ( key == "threadFlowLocations" ) {
                std::forward_list<external_property_file_reference_struct> field;
                val.get_to(field);
                o.threadFlowLocations = field;
                continue;
            }
            if ( key == "results" ) {
                std::forward_list<external_property_file_reference_struct> field;
                val.get_to(field);
                o.results = field;
                continue;
            }
            if ( key == "taxonomies" ) {
                std::forward_list<external_property_file_reference_struct> field;
                val.get_to(field);
                o.taxonomies = field;
                continue;
            }
            if ( key == "addresses" ) {
                std::forward_list<external_property_file_reference_struct> field;
                val.get_to(field);
                o.addresses = field;
                continue;
            }
            if ( key == "driver" ) {
                external_property_file_reference_struct field;
                val.get_to(field);
                o.driver = field;
                continue;
            }
            if ( key == "extensions" ) {
                std::forward_list<external_property_file_reference_struct> field;
                val.get_to(field);
                o.extensions = field;
                continue;
            }
            if ( key == "policies" ) {
                std::forward_list<external_property_file_reference_struct> field;
                val.get_to(field);
                o.policies = field;
                continue;
            }
            if ( key == "translations" ) {
                std::forward_list<external_property_file_reference_struct> field;
                val.get_to(field);
                o.translations = field;
                continue;
            }
            if ( key == "webRequests" ) {
                std::forward_list<external_property_file_reference_struct> field;
                val.get_to(field);
                o.webRequests = field;
                continue;
            }
            if ( key == "webResponses" ) {
                std::forward_list<external_property_file_reference_struct> field;
                val.get_to(field);
                o.webResponses = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const external_property_file_references_struct &o) {
        if ( o.conversion.has_value() ) {
            j["conversion"] = *o.conversion;
        }
        if ( o.graphs.has_value() ) {
            j["graphs"] = *o.graphs;
        }
        if ( o.externalizedProperties.has_value() ) {
            j["externalizedProperties"] = *o.externalizedProperties;
        }
        if ( o.artifacts.has_value() ) {
            j["artifacts"] = *o.artifacts;
        }
        if ( o.invocations.has_value() ) {
            j["invocations"] = *o.invocations;
        }
        if ( o.logicalLocations.has_value() ) {
            j["logicalLocations"] = *o.logicalLocations;
        }
        if ( o.threadFlowLocations.has_value() ) {
            j["threadFlowLocations"] = *o.threadFlowLocations;
        }
        if ( o.results.has_value() ) {
            j["results"] = *o.results;
        }
        if ( o.taxonomies.has_value() ) {
            j["taxonomies"] = *o.taxonomies;
        }
        if ( o.addresses.has_value() ) {
            j["addresses"] = *o.addresses;
        }
        if ( o.driver.has_value() ) {
            j["driver"] = *o.driver;
        }
        if ( o.extensions.has_value() ) {
            j["extensions"] = *o.extensions;
        }
        if ( o.policies.has_value() ) {
            j["policies"] = *o.policies;
        }
        if ( o.translations.has_value() ) {
            j["translations"] = *o.translations;
        }
        if ( o.webRequests.has_value() ) {
            j["webRequests"] = *o.webRequests;
        }
        if ( o.webResponses.has_value() ) {
            j["webResponses"] = *o.webResponses;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, fix_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "description" ) {
                message_struct field;
                val.get_to(field);
                o.description = field;
                continue;
            }
            if ( key == "artifactChanges" ) {
                val.get_to(o.artifactChanges);
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const fix_struct &o) {
        if ( o.description.has_value() ) {
            j["description"] = *o.description;
        }
        j["artifactChanges"] = o.artifactChanges;
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, graph_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "description" ) {
                message_struct field;
                val.get_to(field);
                o.description = field;
                continue;
            }
            if ( key == "nodes" ) {
                std::forward_list<node_struct> field;
                val.get_to(field);
                o.nodes = field;
                continue;
            }
            if ( key == "edges" ) {
                std::forward_list<edge_struct> field;
                val.get_to(field);
                o.edges = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const graph_struct &o) {
        if ( o.description.has_value() ) {
            j["description"] = *o.description;
        }
        if ( o.nodes.has_value() ) {
            j["nodes"] = *o.nodes;
        }
        if ( o.edges.has_value() ) {
            j["edges"] = *o.edges;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, graph_traversal_initial_state_struct &o) {
        for( auto &[key, val] : j.items() ) {
            val.get_to(o.additional_properties[key]);
        }
    }
    void to_json(json &j, const graph_traversal_initial_state_struct &o) {
        for ( auto &[key, val] : o.additional_properties ) {
            j[key] = val;
        }
    }
    void from_json(const json &j, graph_traversal_immutable_state_struct &o) {
        for( auto &[key, val] : j.items() ) {
            val.get_to(o.additional_properties[key]);
        }
    }
    void to_json(json &j, const graph_traversal_immutable_state_struct &o) {
        for ( auto &[key, val] : o.additional_properties ) {
            j[key] = val;
        }
    }
    void from_json(const json &j, graph_traversal_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "runGraphIndex" ) {
                int64_t field;
                val.get_to(field);
                o.runGraphIndex = field;
                continue;
            }
            if ( key == "resultGraphIndex" ) {
                int64_t field;
                val.get_to(field);
                o.resultGraphIndex = field;
                continue;
            }
            if ( key == "description" ) {
                message_struct field;
                val.get_to(field);
                o.description = field;
                continue;
            }
            if ( key == "initialState" ) {
                graph_traversal_initial_state_struct field;
                val.get_to(field);
                o.initialState = field;
                continue;
            }
            if ( key == "immutableState" ) {
                graph_traversal_immutable_state_struct field;
                val.get_to(field);
                o.immutableState = field;
                continue;
            }
            if ( key == "edgeTraversals" ) {
                std::forward_list<edge_traversal_struct> field;
                val.get_to(field);
                o.edgeTraversals = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const graph_traversal_struct &o) {
        if ( o.runGraphIndex.has_value() ) {
            j["runGraphIndex"] = *o.runGraphIndex;
        }
        if ( o.resultGraphIndex.has_value() ) {
            j["resultGraphIndex"] = *o.resultGraphIndex;
        }
        if ( o.description.has_value() ) {
            j["description"] = *o.description;
        }
        if ( o.initialState.has_value() ) {
            j["initialState"] = *o.initialState;
        }
        if ( o.immutableState.has_value() ) {
            j["immutableState"] = *o.immutableState;
        }
        if ( o.edgeTraversals.has_value() ) {
            j["edgeTraversals"] = *o.edgeTraversals;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, region_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "startLine" ) {
                int64_t field;
                val.get_to(field);
                o.startLine = field;
                continue;
            }
            if ( key == "startColumn" ) {
                int64_t field;
                val.get_to(field);
                o.startColumn = field;
                continue;
            }
            if ( key == "endLine" ) {
                int64_t field;
                val.get_to(field);
                o.endLine = field;
                continue;
            }
            if ( key == "endColumn" ) {
                int64_t field;
                val.get_to(field);
                o.endColumn = field;
                continue;
            }
            if ( key == "charOffset" ) {
                int64_t field;
                val.get_to(field);
                o.charOffset = field;
                continue;
            }
            if ( key == "charLength" ) {
                int64_t field;
                val.get_to(field);
                o.charLength = field;
                continue;
            }
            if ( key == "byteOffset" ) {
                int64_t field;
                val.get_to(field);
                o.byteOffset = field;
                continue;
            }
            if ( key == "byteLength" ) {
                int64_t field;
                val.get_to(field);
                o.byteLength = field;
                continue;
            }
            if ( key == "snippet" ) {
                artifact_content_struct field;
                val.get_to(field);
                o.snippet = field;
                continue;
            }
            if ( key == "message" ) {
                message_struct field;
                val.get_to(field);
                o.message = field;
                continue;
            }
            if ( key == "sourceLanguage" ) {
                std::string field;
                val.get_to(field);
                o.sourceLanguage = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const region_struct &o) {
        if ( o.startLine.has_value() ) {
            j["startLine"] = *o.startLine;
        }
        if ( o.startColumn.has_value() ) {
            j["startColumn"] = *o.startColumn;
        }
        if ( o.endLine.has_value() ) {
            j["endLine"] = *o.endLine;
        }
        if ( o.endColumn.has_value() ) {
            j["endColumn"] = *o.endColumn;
        }
        if ( o.charOffset.has_value() ) {
            j["charOffset"] = *o.charOffset;
        }
        if ( o.charLength.has_value() ) {
            j["charLength"] = *o.charLength;
        }
        if ( o.byteOffset.has_value() ) {
            j["byteOffset"] = *o.byteOffset;
        }
        if ( o.byteLength.has_value() ) {
            j["byteLength"] = *o.byteLength;
        }
        if ( o.snippet.has_value() ) {
            j["snippet"] = *o.snippet;
        }
        if ( o.message.has_value() ) {
            j["message"] = *o.message;
        }
        if ( o.sourceLanguage.has_value() ) {
            j["sourceLanguage"] = *o.sourceLanguage;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, physical_location_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "address" ) {
                address_struct field;
                val.get_to(field);
                o.address = field;
                continue;
            }
            if ( key == "artifactLocation" ) {
                artifact_location_struct field;
                val.get_to(field);
                o.artifactLocation = field;
                continue;
            }
            if ( key == "region" ) {
                region_struct field;
                val.get_to(field);
                o.region = field;
                continue;
            }
            if ( key == "contextRegion" ) {
                region_struct field;
                val.get_to(field);
                o.contextRegion = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const physical_location_struct &o) {
        if ( o.address.has_value() ) {
            j["address"] = *o.address;
        }
        if ( o.artifactLocation.has_value() ) {
            j["artifactLocation"] = *o.artifactLocation;
        }
        if ( o.region.has_value() ) {
            j["region"] = *o.region;
        }
        if ( o.contextRegion.has_value() ) {
            j["contextRegion"] = *o.contextRegion;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, location_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "id" ) {
                int64_t field;
                val.get_to(field);
                o.id = field;
                continue;
            }
            if ( key == "physicalLocation" ) {
                physical_location_struct field;
                val.get_to(field);
                o.physicalLocation = field;
                continue;
            }
            if ( key == "logicalLocations" ) {
                std::forward_list<logical_location_struct> field;
                val.get_to(field);
                o.logicalLocations = field;
                continue;
            }
            if ( key == "message" ) {
                message_struct field;
                val.get_to(field);
                o.message = field;
                continue;
            }
            if ( key == "annotations" ) {
                std::forward_list<region_struct> field;
                val.get_to(field);
                o.annotations = field;
                continue;
            }
            if ( key == "relationships" ) {
                std::forward_list<location_relationship_struct> field;
                val.get_to(field);
                o.relationships = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const location_struct &o) {
        if ( o.id.has_value() ) {
            j["id"] = *o.id;
        }
        if ( o.physicalLocation.has_value() ) {
            j["physicalLocation"] = *o.physicalLocation;
        }
        if ( o.logicalLocations.has_value() ) {
            j["logicalLocations"] = *o.logicalLocations;
        }
        if ( o.message.has_value() ) {
            j["message"] = *o.message;
        }
        if ( o.annotations.has_value() ) {
            j["annotations"] = *o.annotations;
        }
        if ( o.relationships.has_value() ) {
            j["relationships"] = *o.relationships;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, location_relationship_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "target" ) {
                val.get_to(o.target);
                continue;
            }
            if ( key == "kinds" ) {
                std::forward_list<std::string> field;
                val.get_to(field);
                o.kinds = field;
                continue;
            }
            if ( key == "description" ) {
                message_struct field;
                val.get_to(field);
                o.description = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const location_relationship_struct &o) {
        j["target"] = o.target;
        if ( o.kinds.has_value() ) {
            j["kinds"] = *o.kinds;
        }
        if ( o.description.has_value() ) {
            j["description"] = *o.description;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, logical_location_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "name" ) {
                std::string field;
                val.get_to(field);
                o.name = field;
                continue;
            }
            if ( key == "index" ) {
                int64_t field;
                val.get_to(field);
                o.index = field;
                continue;
            }
            if ( key == "fullyQualifiedName" ) {
                std::string field;
                val.get_to(field);
                o.fullyQualifiedName = field;
                continue;
            }
            if ( key == "decoratedName" ) {
                std::string field;
                val.get_to(field);
                o.decoratedName = field;
                continue;
            }
            if ( key == "parentIndex" ) {
                int64_t field;
                val.get_to(field);
                o.parentIndex = field;
                continue;
            }
            if ( key == "kind" ) {
                std::string field;
                val.get_to(field);
                o.kind = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const logical_location_struct &o) {
        if ( o.name.has_value() ) {
            j["name"] = *o.name;
        }
        if ( o.index.has_value() ) {
            j["index"] = *o.index;
        }
        if ( o.fullyQualifiedName.has_value() ) {
            j["fullyQualifiedName"] = *o.fullyQualifiedName;
        }
        if ( o.decoratedName.has_value() ) {
            j["decoratedName"] = *o.decoratedName;
        }
        if ( o.parentIndex.has_value() ) {
            j["parentIndex"] = *o.parentIndex;
        }
        if ( o.kind.has_value() ) {
            j["kind"] = *o.kind;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, node_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "id" ) {
                val.get_to(o.id);
                continue;
            }
            if ( key == "label" ) {
                message_struct field;
                val.get_to(field);
                o.label = field;
                continue;
            }
            if ( key == "location" ) {
                location_struct field;
                val.get_to(field);
                o.location = field;
                continue;
            }
            if ( key == "children" ) {
                std::forward_list<node_struct> field;
                val.get_to(field);
                o.children = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const node_struct &o) {
        j["id"] = o.id;
        if ( o.label.has_value() ) {
            j["label"] = *o.label;
        }
        if ( o.location.has_value() ) {
            j["location"] = *o.location;
        }
        if ( o.children.has_value() ) {
            j["children"] = *o.children;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, notification_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "locations" ) {
                std::forward_list<location_struct> field;
                val.get_to(field);
                o.locations = field;
                continue;
            }
            if ( key == "message" ) {
                val.get_to(o.message);
                continue;
            }
            if ( key == "level" ) {
                level_enum field;
                val.get_to(field);
                o.level = field;
                continue;
            }
            if ( key == "threadId" ) {
                int64_t field;
                val.get_to(field);
                o.threadId = field;
                continue;
            }
            if ( key == "timeUtc" ) {
                std::string field;
                val.get_to(field);
                o.timeUtc = field;
                continue;
            }
            if ( key == "exception" ) {
                exception_struct field;
                val.get_to(field);
                o.exception = field;
                continue;
            }
            if ( key == "descriptor" ) {
                reporting_descriptor_reference_struct field;
                val.get_to(field);
                o.descriptor = field;
                continue;
            }
            if ( key == "associatedRule" ) {
                reporting_descriptor_reference_struct field;
                val.get_to(field);
                o.associatedRule = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const notification_struct &o) {
        if ( o.locations.has_value() ) {
            j["locations"] = *o.locations;
        }
        j["message"] = o.message;
        if ( o.level.has_value() ) {
            j["level"] = *o.level;
        }
        if ( o.threadId.has_value() ) {
            j["threadId"] = *o.threadId;
        }
        if ( o.timeUtc.has_value() ) {
            j["timeUtc"] = *o.timeUtc;
        }
        if ( o.exception.has_value() ) {
            j["exception"] = *o.exception;
        }
        if ( o.descriptor.has_value() ) {
            j["descriptor"] = *o.descriptor;
        }
        if ( o.associatedRule.has_value() ) {
            j["associatedRule"] = *o.associatedRule;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, rectangle_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "top" ) {
                double field;
                val.get_to(field);
                o.top = field;
                continue;
            }
            if ( key == "left" ) {
                double field;
                val.get_to(field);
                o.left = field;
                continue;
            }
            if ( key == "bottom" ) {
                double field;
                val.get_to(field);
                o.bottom = field;
                continue;
            }
            if ( key == "right" ) {
                double field;
                val.get_to(field);
                o.right = field;
                continue;
            }
            if ( key == "message" ) {
                message_struct field;
                val.get_to(field);
                o.message = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const rectangle_struct &o) {
        if ( o.top.has_value() ) {
            j["top"] = *o.top;
        }
        if ( o.left.has_value() ) {
            j["left"] = *o.left;
        }
        if ( o.bottom.has_value() ) {
            j["bottom"] = *o.bottom;
        }
        if ( o.right.has_value() ) {
            j["right"] = *o.right;
        }
        if ( o.message.has_value() ) {
            j["message"] = *o.message;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, replacement_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "deletedRegion" ) {
                val.get_to(o.deletedRegion);
                continue;
            }
            if ( key == "insertedContent" ) {
                artifact_content_struct field;
                val.get_to(field);
                o.insertedContent = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const replacement_struct &o) {
        j["deletedRegion"] = o.deletedRegion;
        if ( o.insertedContent.has_value() ) {
            j["insertedContent"] = *o.insertedContent;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, reporting_descriptor_message_strings_struct &o) {
        for( auto &[key, val] : j.items() ) {
            val.get_to(o.additional_properties[key]);
        }
    }
    void to_json(json &j, const reporting_descriptor_message_strings_struct &o) {
        for ( auto &[key, val] : o.additional_properties ) {
            j[key] = val;
        }
    }
    void from_json(const json &j, reporting_descriptor_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "id" ) {
                val.get_to(o.id);
                continue;
            }
            if ( key == "deprecatedIds" ) {
                std::forward_list<std::string> field;
                val.get_to(field);
                o.deprecatedIds = field;
                continue;
            }
            if ( key == "guid" ) {
                std::string field;
                val.get_to(field);
                o.guid = field;
                continue;
            }
            if ( key == "deprecatedGuids" ) {
                std::forward_list<std::string> field;
                val.get_to(field);
                o.deprecatedGuids = field;
                continue;
            }
            if ( key == "name" ) {
                std::string field;
                val.get_to(field);
                o.name = field;
                continue;
            }
            if ( key == "deprecatedNames" ) {
                std::forward_list<std::string> field;
                val.get_to(field);
                o.deprecatedNames = field;
                continue;
            }
            if ( key == "shortDescription" ) {
                multiformat_message_string_struct field;
                val.get_to(field);
                o.shortDescription = field;
                continue;
            }
            if ( key == "fullDescription" ) {
                multiformat_message_string_struct field;
                val.get_to(field);
                o.fullDescription = field;
                continue;
            }
            if ( key == "messageStrings" ) {
                reporting_descriptor_message_strings_struct field;
                val.get_to(field);
                o.messageStrings = field;
                continue;
            }
            if ( key == "defaultConfiguration" ) {
                reporting_configuration_struct field;
                val.get_to(field);
                o.defaultConfiguration = field;
                continue;
            }
            if ( key == "helpUri" ) {
                std::string field;
                val.get_to(field);
                o.helpUri = field;
                continue;
            }
            if ( key == "help" ) {
                multiformat_message_string_struct field;
                val.get_to(field);
                o.help = field;
                continue;
            }
            if ( key == "relationships" ) {
                std::forward_list<reporting_descriptor_relationship_struct> field;
                val.get_to(field);
                o.relationships = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const reporting_descriptor_struct &o) {
        j["id"] = o.id;
        if ( o.deprecatedIds.has_value() ) {
            j["deprecatedIds"] = *o.deprecatedIds;
        }
        if ( o.guid.has_value() ) {
            j["guid"] = *o.guid;
        }
        if ( o.deprecatedGuids.has_value() ) {
            j["deprecatedGuids"] = *o.deprecatedGuids;
        }
        if ( o.name.has_value() ) {
            j["name"] = *o.name;
        }
        if ( o.deprecatedNames.has_value() ) {
            j["deprecatedNames"] = *o.deprecatedNames;
        }
        if ( o.shortDescription.has_value() ) {
            j["shortDescription"] = *o.shortDescription;
        }
        if ( o.fullDescription.has_value() ) {
            j["fullDescription"] = *o.fullDescription;
        }
        if ( o.messageStrings.has_value() ) {
            j["messageStrings"] = *o.messageStrings;
        }
        if ( o.defaultConfiguration.has_value() ) {
            j["defaultConfiguration"] = *o.defaultConfiguration;
        }
        if ( o.helpUri.has_value() ) {
            j["helpUri"] = *o.helpUri;
        }
        if ( o.help.has_value() ) {
            j["help"] = *o.help;
        }
        if ( o.relationships.has_value() ) {
            j["relationships"] = *o.relationships;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, reporting_descriptor_relationship_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "target" ) {
                val.get_to(o.target);
                continue;
            }
            if ( key == "kinds" ) {
                std::forward_list<std::string> field;
                val.get_to(field);
                o.kinds = field;
                continue;
            }
            if ( key == "description" ) {
                message_struct field;
                val.get_to(field);
                o.description = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const reporting_descriptor_relationship_struct &o) {
        j["target"] = o.target;
        if ( o.kinds.has_value() ) {
            j["kinds"] = *o.kinds;
        }
        if ( o.description.has_value() ) {
            j["description"] = *o.description;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, result_partial_fingerprints_struct &o) {
        for( auto &[key, val] : j.items() ) {
            val.get_to(o.additional_properties[key]);
        }
    }
    void to_json(json &j, const result_partial_fingerprints_struct &o) {
        for ( auto &[key, val] : o.additional_properties ) {
            j[key] = val;
        }
    }
    void from_json(const json &j, result_fingerprints_struct &o) {
        for( auto &[key, val] : j.items() ) {
            val.get_to(o.additional_properties[key]);
        }
    }
    void to_json(json &j, const result_fingerprints_struct &o) {
        for ( auto &[key, val] : o.additional_properties ) {
            j[key] = val;
        }
    }
    void from_json(const json &j, result_provenance_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "firstDetectionTimeUtc" ) {
                std::string field;
                val.get_to(field);
                o.firstDetectionTimeUtc = field;
                continue;
            }
            if ( key == "lastDetectionTimeUtc" ) {
                std::string field;
                val.get_to(field);
                o.lastDetectionTimeUtc = field;
                continue;
            }
            if ( key == "firstDetectionRunGuid" ) {
                std::string field;
                val.get_to(field);
                o.firstDetectionRunGuid = field;
                continue;
            }
            if ( key == "lastDetectionRunGuid" ) {
                std::string field;
                val.get_to(field);
                o.lastDetectionRunGuid = field;
                continue;
            }
            if ( key == "invocationIndex" ) {
                int64_t field;
                val.get_to(field);
                o.invocationIndex = field;
                continue;
            }
            if ( key == "conversionSources" ) {
                std::forward_list<physical_location_struct> field;
                val.get_to(field);
                o.conversionSources = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const result_provenance_struct &o) {
        if ( o.firstDetectionTimeUtc.has_value() ) {
            j["firstDetectionTimeUtc"] = *o.firstDetectionTimeUtc;
        }
        if ( o.lastDetectionTimeUtc.has_value() ) {
            j["lastDetectionTimeUtc"] = *o.lastDetectionTimeUtc;
        }
        if ( o.firstDetectionRunGuid.has_value() ) {
            j["firstDetectionRunGuid"] = *o.firstDetectionRunGuid;
        }
        if ( o.lastDetectionRunGuid.has_value() ) {
            j["lastDetectionRunGuid"] = *o.lastDetectionRunGuid;
        }
        if ( o.invocationIndex.has_value() ) {
            j["invocationIndex"] = *o.invocationIndex;
        }
        if ( o.conversionSources.has_value() ) {
            j["conversionSources"] = *o.conversionSources;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, web_request_headers_struct &o) {
        for( auto &[key, val] : j.items() ) {
            val.get_to(o.additional_properties[key]);
        }
    }
    void to_json(json &j, const web_request_headers_struct &o) {
        for ( auto &[key, val] : o.additional_properties ) {
            j[key] = val;
        }
    }
    void from_json(const json &j, web_request_parameters_struct &o) {
        for( auto &[key, val] : j.items() ) {
            val.get_to(o.additional_properties[key]);
        }
    }
    void to_json(json &j, const web_request_parameters_struct &o) {
        for ( auto &[key, val] : o.additional_properties ) {
            j[key] = val;
        }
    }
    void from_json(const json &j, web_request_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "index" ) {
                int64_t field;
                val.get_to(field);
                o.index = field;
                continue;
            }
            if ( key == "protocol" ) {
                std::string field;
                val.get_to(field);
                o.protocol = field;
                continue;
            }
            if ( key == "version" ) {
                std::string field;
                val.get_to(field);
                o.version = field;
                continue;
            }
            if ( key == "target" ) {
                std::string field;
                val.get_to(field);
                o.target = field;
                continue;
            }
            if ( key == "method" ) {
                std::string field;
                val.get_to(field);
                o.method = field;
                continue;
            }
            if ( key == "headers" ) {
                web_request_headers_struct field;
                val.get_to(field);
                o.headers = field;
                continue;
            }
            if ( key == "parameters" ) {
                web_request_parameters_struct field;
                val.get_to(field);
                o.parameters = field;
                continue;
            }
            if ( key == "body" ) {
                artifact_content_struct field;
                val.get_to(field);
                o.body = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const web_request_struct &o) {
        if ( o.index.has_value() ) {
            j["index"] = *o.index;
        }
        if ( o.protocol.has_value() ) {
            j["protocol"] = *o.protocol;
        }
        if ( o.version.has_value() ) {
            j["version"] = *o.version;
        }
        if ( o.target.has_value() ) {
            j["target"] = *o.target;
        }
        if ( o.method.has_value() ) {
            j["method"] = *o.method;
        }
        if ( o.headers.has_value() ) {
            j["headers"] = *o.headers;
        }
        if ( o.parameters.has_value() ) {
            j["parameters"] = *o.parameters;
        }
        if ( o.body.has_value() ) {
            j["body"] = *o.body;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, web_response_headers_struct &o) {
        for( auto &[key, val] : j.items() ) {
            val.get_to(o.additional_properties[key]);
        }
    }
    void to_json(json &j, const web_response_headers_struct &o) {
        for ( auto &[key, val] : o.additional_properties ) {
            j[key] = val;
        }
    }
    void from_json(const json &j, web_response_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "index" ) {
                int64_t field;
                val.get_to(field);
                o.index = field;
                continue;
            }
            if ( key == "protocol" ) {
                std::string field;
                val.get_to(field);
                o.protocol = field;
                continue;
            }
            if ( key == "version" ) {
                std::string field;
                val.get_to(field);
                o.version = field;
                continue;
            }
            if ( key == "statusCode" ) {
                int64_t field;
                val.get_to(field);
                o.statusCode = field;
                continue;
            }
            if ( key == "reasonPhrase" ) {
                std::string field;
                val.get_to(field);
                o.reasonPhrase = field;
                continue;
            }
            if ( key == "headers" ) {
                web_response_headers_struct field;
                val.get_to(field);
                o.headers = field;
                continue;
            }
            if ( key == "body" ) {
                artifact_content_struct field;
                val.get_to(field);
                o.body = field;
                continue;
            }
            if ( key == "noResponseReceived" ) {
                bool field;
                val.get_to(field);
                o.noResponseReceived = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const web_response_struct &o) {
        if ( o.index.has_value() ) {
            j["index"] = *o.index;
        }
        if ( o.protocol.has_value() ) {
            j["protocol"] = *o.protocol;
        }
        if ( o.version.has_value() ) {
            j["version"] = *o.version;
        }
        if ( o.statusCode.has_value() ) {
            j["statusCode"] = *o.statusCode;
        }
        if ( o.reasonPhrase.has_value() ) {
            j["reasonPhrase"] = *o.reasonPhrase;
        }
        if ( o.headers.has_value() ) {
            j["headers"] = *o.headers;
        }
        if ( o.body.has_value() ) {
            j["body"] = *o.body;
        }
        if ( o.noResponseReceived.has_value() ) {
            j["noResponseReceived"] = *o.noResponseReceived;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, result_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "ruleId" ) {
                std::string field;
                val.get_to(field);
                o.ruleId = field;
                continue;
            }
            if ( key == "ruleIndex" ) {
                int64_t field;
                val.get_to(field);
                o.ruleIndex = field;
                continue;
            }
            if ( key == "rule" ) {
                reporting_descriptor_reference_struct field;
                val.get_to(field);
                o.rule = field;
                continue;
            }
            if ( key == "kind" ) {
                kind_enum field;
                val.get_to(field);
                o.kind = field;
                continue;
            }
            if ( key == "level" ) {
                level_enum field;
                val.get_to(field);
                o.level = field;
                continue;
            }
            if ( key == "message" ) {
                val.get_to(o.message);
                continue;
            }
            if ( key == "analysisTarget" ) {
                artifact_location_struct field;
                val.get_to(field);
                o.analysisTarget = field;
                continue;
            }
            if ( key == "locations" ) {
                std::forward_list<location_struct> field;
                val.get_to(field);
                o.locations = field;
                continue;
            }
            if ( key == "guid" ) {
                std::string field;
                val.get_to(field);
                o.guid = field;
                continue;
            }
            if ( key == "correlationGuid" ) {
                std::string field;
                val.get_to(field);
                o.correlationGuid = field;
                continue;
            }
            if ( key == "occurrenceCount" ) {
                int64_t field;
                val.get_to(field);
                o.occurrenceCount = field;
                continue;
            }
            if ( key == "partialFingerprints" ) {
                result_partial_fingerprints_struct field;
                val.get_to(field);
                o.partialFingerprints = field;
                continue;
            }
            if ( key == "fingerprints" ) {
                result_fingerprints_struct field;
                val.get_to(field);
                o.fingerprints = field;
                continue;
            }
            if ( key == "stacks" ) {
                std::forward_list<stack_struct> field;
                val.get_to(field);
                o.stacks = field;
                continue;
            }
            if ( key == "codeFlows" ) {
                std::forward_list<code_flow_struct> field;
                val.get_to(field);
                o.codeFlows = field;
                continue;
            }
            if ( key == "graphs" ) {
                std::forward_list<graph_struct> field;
                val.get_to(field);
                o.graphs = field;
                continue;
            }
            if ( key == "graphTraversals" ) {
                std::forward_list<graph_traversal_struct> field;
                val.get_to(field);
                o.graphTraversals = field;
                continue;
            }
            if ( key == "relatedLocations" ) {
                std::forward_list<location_struct> field;
                val.get_to(field);
                o.relatedLocations = field;
                continue;
            }
            if ( key == "suppressions" ) {
                std::forward_list<suppression_struct> field;
                val.get_to(field);
                o.suppressions = field;
                continue;
            }
            if ( key == "baselineState" ) {
                baseline_state_enum field;
                val.get_to(field);
                o.baselineState = field;
                continue;
            }
            if ( key == "rank" ) {
                double field;
                val.get_to(field);
                o.rank = field;
                continue;
            }
            if ( key == "attachments" ) {
                std::forward_list<attachment_struct> field;
                val.get_to(field);
                o.attachments = field;
                continue;
            }
            if ( key == "hostedViewerUri" ) {
                std::string field;
                val.get_to(field);
                o.hostedViewerUri = field;
                continue;
            }
            if ( key == "workItemUris" ) {
                std::forward_list<std::string> field;
                val.get_to(field);
                o.workItemUris = field;
                continue;
            }
            if ( key == "provenance" ) {
                result_provenance_struct field;
                val.get_to(field);
                o.provenance = field;
                continue;
            }
            if ( key == "fixes" ) {
                std::forward_list<fix_struct> field;
                val.get_to(field);
                o.fixes = field;
                continue;
            }
            if ( key == "taxa" ) {
                std::forward_list<reporting_descriptor_reference_struct> field;
                val.get_to(field);
                o.taxa = field;
                continue;
            }
            if ( key == "webRequest" ) {
                web_request_struct field;
                val.get_to(field);
                o.webRequest = field;
                continue;
            }
            if ( key == "webResponse" ) {
                web_response_struct field;
                val.get_to(field);
                o.webResponse = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const result_struct &o) {
        if ( o.ruleId.has_value() ) {
            j["ruleId"] = *o.ruleId;
        }
        if ( o.ruleIndex.has_value() ) {
            j["ruleIndex"] = *o.ruleIndex;
        }
        if ( o.rule.has_value() ) {
            j["rule"] = *o.rule;
        }
        if ( o.kind.has_value() ) {
            j["kind"] = *o.kind;
        }
        if ( o.level.has_value() ) {
            j["level"] = *o.level;
        }
        j["message"] = o.message;
        if ( o.analysisTarget.has_value() ) {
            j["analysisTarget"] = *o.analysisTarget;
        }
        if ( o.locations.has_value() ) {
            j["locations"] = *o.locations;
        }
        if ( o.guid.has_value() ) {
            j["guid"] = *o.guid;
        }
        if ( o.correlationGuid.has_value() ) {
            j["correlationGuid"] = *o.correlationGuid;
        }
        if ( o.occurrenceCount.has_value() ) {
            j["occurrenceCount"] = *o.occurrenceCount;
        }
        if ( o.partialFingerprints.has_value() ) {
            j["partialFingerprints"] = *o.partialFingerprints;
        }
        if ( o.fingerprints.has_value() ) {
            j["fingerprints"] = *o.fingerprints;
        }
        if ( o.stacks.has_value() ) {
            j["stacks"] = *o.stacks;
        }
        if ( o.codeFlows.has_value() ) {
            j["codeFlows"] = *o.codeFlows;
        }
        if ( o.graphs.has_value() ) {
            j["graphs"] = *o.graphs;
        }
        if ( o.graphTraversals.has_value() ) {
            j["graphTraversals"] = *o.graphTraversals;
        }
        if ( o.relatedLocations.has_value() ) {
            j["relatedLocations"] = *o.relatedLocations;
        }
        if ( o.suppressions.has_value() ) {
            j["suppressions"] = *o.suppressions;
        }
        if ( o.baselineState.has_value() ) {
            j["baselineState"] = *o.baselineState;
        }
        if ( o.rank.has_value() ) {
            j["rank"] = *o.rank;
        }
        if ( o.attachments.has_value() ) {
            j["attachments"] = *o.attachments;
        }
        if ( o.hostedViewerUri.has_value() ) {
            j["hostedViewerUri"] = *o.hostedViewerUri;
        }
        if ( o.workItemUris.has_value() ) {
            j["workItemUris"] = *o.workItemUris;
        }
        if ( o.provenance.has_value() ) {
            j["provenance"] = *o.provenance;
        }
        if ( o.fixes.has_value() ) {
            j["fixes"] = *o.fixes;
        }
        if ( o.taxa.has_value() ) {
            j["taxa"] = *o.taxa;
        }
        if ( o.webRequest.has_value() ) {
            j["webRequest"] = *o.webRequest;
        }
        if ( o.webResponse.has_value() ) {
            j["webResponse"] = *o.webResponse;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, run_original_uri_base_ids_struct &o) {
        for( auto &[key, val] : j.items() ) {
            val.get_to(o.additional_properties[key]);
        }
    }
    void to_json(json &j, const run_original_uri_base_ids_struct &o) {
        for ( auto &[key, val] : o.additional_properties ) {
            j[key] = val;
        }
    }
    void from_json(const json &j, run_automation_details_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "description" ) {
                message_struct field;
                val.get_to(field);
                o.description = field;
                continue;
            }
            if ( key == "id" ) {
                std::string field;
                val.get_to(field);
                o.id = field;
                continue;
            }
            if ( key == "guid" ) {
                std::string field;
                val.get_to(field);
                o.guid = field;
                continue;
            }
            if ( key == "correlationGuid" ) {
                std::string field;
                val.get_to(field);
                o.correlationGuid = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const run_automation_details_struct &o) {
        if ( o.description.has_value() ) {
            j["description"] = *o.description;
        }
        if ( o.id.has_value() ) {
            j["id"] = *o.id;
        }
        if ( o.guid.has_value() ) {
            j["guid"] = *o.guid;
        }
        if ( o.correlationGuid.has_value() ) {
            j["correlationGuid"] = *o.correlationGuid;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, special_locations_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "displayBase" ) {
                artifact_location_struct field;
                val.get_to(field);
                o.displayBase = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const special_locations_struct &o) {
        if ( o.displayBase.has_value() ) {
            j["displayBase"] = *o.displayBase;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, run_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "tool" ) {
                val.get_to(o.tool);
                continue;
            }
            if ( key == "invocations" ) {
                std::forward_list<invocation_struct> field;
                val.get_to(field);
                o.invocations = field;
                continue;
            }
            if ( key == "conversion" ) {
                conversion_struct field;
                val.get_to(field);
                o.conversion = field;
                continue;
            }
            if ( key == "language" ) {
                std::string field;
                val.get_to(field);
                o.language = field;
                continue;
            }
            if ( key == "versionControlProvenance" ) {
                std::forward_list<version_control_details_struct> field;
                val.get_to(field);
                o.versionControlProvenance = field;
                continue;
            }
            if ( key == "originalUriBaseIds" ) {
                run_original_uri_base_ids_struct field;
                val.get_to(field);
                o.originalUriBaseIds = field;
                continue;
            }
            if ( key == "artifacts" ) {
                std::forward_list<artifact_struct> field;
                val.get_to(field);
                o.artifacts = field;
                continue;
            }
            if ( key == "logicalLocations" ) {
                std::forward_list<logical_location_struct> field;
                val.get_to(field);
                o.logicalLocations = field;
                continue;
            }
            if ( key == "graphs" ) {
                std::forward_list<graph_struct> field;
                val.get_to(field);
                o.graphs = field;
                continue;
            }
            if ( key == "results" ) {
                std::forward_list<result_struct> field;
                val.get_to(field);
                o.results = field;
                continue;
            }
            if ( key == "automationDetails" ) {
                run_automation_details_struct field;
                val.get_to(field);
                o.automationDetails = field;
                continue;
            }
            if ( key == "runAggregates" ) {
                std::forward_list<run_automation_details_struct> field;
                val.get_to(field);
                o.runAggregates = field;
                continue;
            }
            if ( key == "baselineGuid" ) {
                std::string field;
                val.get_to(field);
                o.baselineGuid = field;
                continue;
            }
            if ( key == "redactionTokens" ) {
                std::forward_list<std::string> field;
                val.get_to(field);
                o.redactionTokens = field;
                continue;
            }
            if ( key == "defaultEncoding" ) {
                std::string field;
                val.get_to(field);
                o.defaultEncoding = field;
                continue;
            }
            if ( key == "defaultSourceLanguage" ) {
                std::string field;
                val.get_to(field);
                o.defaultSourceLanguage = field;
                continue;
            }
            if ( key == "newlineSequences" ) {
                std::forward_list<std::string> field;
                val.get_to(field);
                o.newlineSequences = field;
                continue;
            }
            if ( key == "columnKind" ) {
                column_kind_enum field;
                val.get_to(field);
                o.columnKind = field;
                continue;
            }
            if ( key == "externalPropertyFileReferences" ) {
                external_property_file_references_struct field;
                val.get_to(field);
                o.externalPropertyFileReferences = field;
                continue;
            }
            if ( key == "threadFlowLocations" ) {
                std::forward_list<thread_flow_location_struct> field;
                val.get_to(field);
                o.threadFlowLocations = field;
                continue;
            }
            if ( key == "taxonomies" ) {
                std::forward_list<tool_component_struct> field;
                val.get_to(field);
                o.taxonomies = field;
                continue;
            }
            if ( key == "addresses" ) {
                std::forward_list<address_struct> field;
                val.get_to(field);
                o.addresses = field;
                continue;
            }
            if ( key == "translations" ) {
                std::forward_list<tool_component_struct> field;
                val.get_to(field);
                o.translations = field;
                continue;
            }
            if ( key == "policies" ) {
                std::forward_list<tool_component_struct> field;
                val.get_to(field);
                o.policies = field;
                continue;
            }
            if ( key == "webRequests" ) {
                std::forward_list<web_request_struct> field;
                val.get_to(field);
                o.webRequests = field;
                continue;
            }
            if ( key == "webResponses" ) {
                std::forward_list<web_response_struct> field;
                val.get_to(field);
                o.webResponses = field;
                continue;
            }
            if ( key == "specialLocations" ) {
                special_locations_struct field;
                val.get_to(field);
                o.specialLocations = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const run_struct &o) {
        j["tool"] = o.tool;
        if ( o.invocations.has_value() ) {
            j["invocations"] = *o.invocations;
        }
        if ( o.conversion.has_value() ) {
            j["conversion"] = *o.conversion;
        }
        if ( o.language.has_value() ) {
            j["language"] = *o.language;
        }
        if ( o.versionControlProvenance.has_value() ) {
            j["versionControlProvenance"] = *o.versionControlProvenance;
        }
        if ( o.originalUriBaseIds.has_value() ) {
            j["originalUriBaseIds"] = *o.originalUriBaseIds;
        }
        if ( o.artifacts.has_value() ) {
            j["artifacts"] = *o.artifacts;
        }
        if ( o.logicalLocations.has_value() ) {
            j["logicalLocations"] = *o.logicalLocations;
        }
        if ( o.graphs.has_value() ) {
            j["graphs"] = *o.graphs;
        }
        if ( o.results.has_value() ) {
            j["results"] = *o.results;
        }
        if ( o.automationDetails.has_value() ) {
            j["automationDetails"] = *o.automationDetails;
        }
        if ( o.runAggregates.has_value() ) {
            j["runAggregates"] = *o.runAggregates;
        }
        if ( o.baselineGuid.has_value() ) {
            j["baselineGuid"] = *o.baselineGuid;
        }
        if ( o.redactionTokens.has_value() ) {
            j["redactionTokens"] = *o.redactionTokens;
        }
        if ( o.defaultEncoding.has_value() ) {
            j["defaultEncoding"] = *o.defaultEncoding;
        }
        if ( o.defaultSourceLanguage.has_value() ) {
            j["defaultSourceLanguage"] = *o.defaultSourceLanguage;
        }
        if ( o.newlineSequences.has_value() ) {
            j["newlineSequences"] = *o.newlineSequences;
        }
        if ( o.columnKind.has_value() ) {
            j["columnKind"] = *o.columnKind;
        }
        if ( o.externalPropertyFileReferences.has_value() ) {
            j["externalPropertyFileReferences"] = *o.externalPropertyFileReferences;
        }
        if ( o.threadFlowLocations.has_value() ) {
            j["threadFlowLocations"] = *o.threadFlowLocations;
        }
        if ( o.taxonomies.has_value() ) {
            j["taxonomies"] = *o.taxonomies;
        }
        if ( o.addresses.has_value() ) {
            j["addresses"] = *o.addresses;
        }
        if ( o.translations.has_value() ) {
            j["translations"] = *o.translations;
        }
        if ( o.policies.has_value() ) {
            j["policies"] = *o.policies;
        }
        if ( o.webRequests.has_value() ) {
            j["webRequests"] = *o.webRequests;
        }
        if ( o.webResponses.has_value() ) {
            j["webResponses"] = *o.webResponses;
        }
        if ( o.specialLocations.has_value() ) {
            j["specialLocations"] = *o.specialLocations;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, stack_frame_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "location" ) {
                location_struct field;
                val.get_to(field);
                o.location = field;
                continue;
            }
            if ( key == "module" ) {
                std::string field;
                val.get_to(field);
                o.module = field;
                continue;
            }
            if ( key == "threadId" ) {
                int64_t field;
                val.get_to(field);
                o.threadId = field;
                continue;
            }
            if ( key == "parameters" ) {
                std::forward_list<std::string> field;
                val.get_to(field);
                o.parameters = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const stack_frame_struct &o) {
        if ( o.location.has_value() ) {
            j["location"] = *o.location;
        }
        if ( o.module.has_value() ) {
            j["module"] = *o.module;
        }
        if ( o.threadId.has_value() ) {
            j["threadId"] = *o.threadId;
        }
        if ( o.parameters.has_value() ) {
            j["parameters"] = *o.parameters;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, suppression_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "guid" ) {
                std::string field;
                val.get_to(field);
                o.guid = field;
                continue;
            }
            if ( key == "kind" ) {
                val.get_to(o.kind);
                continue;
            }
            if ( key == "state" ) {
                state_enum field;
                val.get_to(field);
                o.state = field;
                continue;
            }
            if ( key == "justification" ) {
                std::string field;
                val.get_to(field);
                o.justification = field;
                continue;
            }
            if ( key == "location" ) {
                location_struct field;
                val.get_to(field);
                o.location = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const suppression_struct &o) {
        if ( o.guid.has_value() ) {
            j["guid"] = *o.guid;
        }
        j["kind"] = o.kind;
        if ( o.state.has_value() ) {
            j["state"] = *o.state;
        }
        if ( o.justification.has_value() ) {
            j["justification"] = *o.justification;
        }
        if ( o.location.has_value() ) {
            j["location"] = *o.location;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, thread_flow_initial_state_struct &o) {
        for( auto &[key, val] : j.items() ) {
            val.get_to(o.additional_properties[key]);
        }
    }
    void to_json(json &j, const thread_flow_initial_state_struct &o) {
        for ( auto &[key, val] : o.additional_properties ) {
            j[key] = val;
        }
    }
    void from_json(const json &j, thread_flow_immutable_state_struct &o) {
        for( auto &[key, val] : j.items() ) {
            val.get_to(o.additional_properties[key]);
        }
    }
    void to_json(json &j, const thread_flow_immutable_state_struct &o) {
        for ( auto &[key, val] : o.additional_properties ) {
            j[key] = val;
        }
    }
    void from_json(const json &j, thread_flow_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "id" ) {
                std::string field;
                val.get_to(field);
                o.id = field;
                continue;
            }
            if ( key == "message" ) {
                message_struct field;
                val.get_to(field);
                o.message = field;
                continue;
            }
            if ( key == "initialState" ) {
                thread_flow_initial_state_struct field;
                val.get_to(field);
                o.initialState = field;
                continue;
            }
            if ( key == "immutableState" ) {
                thread_flow_immutable_state_struct field;
                val.get_to(field);
                o.immutableState = field;
                continue;
            }
            if ( key == "locations" ) {
                val.get_to(o.locations);
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const thread_flow_struct &o) {
        if ( o.id.has_value() ) {
            j["id"] = *o.id;
        }
        if ( o.message.has_value() ) {
            j["message"] = *o.message;
        }
        if ( o.initialState.has_value() ) {
            j["initialState"] = *o.initialState;
        }
        if ( o.immutableState.has_value() ) {
            j["immutableState"] = *o.immutableState;
        }
        j["locations"] = o.locations;
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, thread_flow_location_state_struct &o) {
        for( auto &[key, val] : j.items() ) {
            val.get_to(o.additional_properties[key]);
        }
    }
    void to_json(json &j, const thread_flow_location_state_struct &o) {
        for ( auto &[key, val] : o.additional_properties ) {
            j[key] = val;
        }
    }
    void from_json(const json &j, thread_flow_location_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "index" ) {
                int64_t field;
                val.get_to(field);
                o.index = field;
                continue;
            }
            if ( key == "location" ) {
                location_struct field;
                val.get_to(field);
                o.location = field;
                continue;
            }
            if ( key == "stack" ) {
                stack_struct field;
                val.get_to(field);
                o.stack = field;
                continue;
            }
            if ( key == "kinds" ) {
                std::forward_list<std::string> field;
                val.get_to(field);
                o.kinds = field;
                continue;
            }
            if ( key == "taxa" ) {
                std::forward_list<reporting_descriptor_reference_struct> field;
                val.get_to(field);
                o.taxa = field;
                continue;
            }
            if ( key == "module" ) {
                std::string field;
                val.get_to(field);
                o.module = field;
                continue;
            }
            if ( key == "state" ) {
                thread_flow_location_state_struct field;
                val.get_to(field);
                o.state = field;
                continue;
            }
            if ( key == "nestingLevel" ) {
                int64_t field;
                val.get_to(field);
                o.nestingLevel = field;
                continue;
            }
            if ( key == "executionOrder" ) {
                int64_t field;
                val.get_to(field);
                o.executionOrder = field;
                continue;
            }
            if ( key == "executionTimeUtc" ) {
                std::string field;
                val.get_to(field);
                o.executionTimeUtc = field;
                continue;
            }
            if ( key == "importance" ) {
                importance_enum field;
                val.get_to(field);
                o.importance = field;
                continue;
            }
            if ( key == "webRequest" ) {
                web_request_struct field;
                val.get_to(field);
                o.webRequest = field;
                continue;
            }
            if ( key == "webResponse" ) {
                web_response_struct field;
                val.get_to(field);
                o.webResponse = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const thread_flow_location_struct &o) {
        if ( o.index.has_value() ) {
            j["index"] = *o.index;
        }
        if ( o.location.has_value() ) {
            j["location"] = *o.location;
        }
        if ( o.stack.has_value() ) {
            j["stack"] = *o.stack;
        }
        if ( o.kinds.has_value() ) {
            j["kinds"] = *o.kinds;
        }
        if ( o.taxa.has_value() ) {
            j["taxa"] = *o.taxa;
        }
        if ( o.module.has_value() ) {
            j["module"] = *o.module;
        }
        if ( o.state.has_value() ) {
            j["state"] = *o.state;
        }
        if ( o.nestingLevel.has_value() ) {
            j["nestingLevel"] = *o.nestingLevel;
        }
        if ( o.executionOrder.has_value() ) {
            j["executionOrder"] = *o.executionOrder;
        }
        if ( o.executionTimeUtc.has_value() ) {
            j["executionTimeUtc"] = *o.executionTimeUtc;
        }
        if ( o.importance.has_value() ) {
            j["importance"] = *o.importance;
        }
        if ( o.webRequest.has_value() ) {
            j["webRequest"] = *o.webRequest;
        }
        if ( o.webResponse.has_value() ) {
            j["webResponse"] = *o.webResponse;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, version_control_details_struct &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "repositoryUri" ) {
                val.get_to(o.repositoryUri);
                continue;
            }
            if ( key == "revisionId" ) {
                std::string field;
                val.get_to(field);
                o.revisionId = field;
                continue;
            }
            if ( key == "branch" ) {
                std::string field;
                val.get_to(field);
                o.branch = field;
                continue;
            }
            if ( key == "revisionTag" ) {
                std::string field;
                val.get_to(field);
                o.revisionTag = field;
                continue;
            }
            if ( key == "asOfTimeUtc" ) {
                std::string field;
                val.get_to(field);
                o.asOfTimeUtc = field;
                continue;
            }
            if ( key == "mappedTo" ) {
                artifact_location_struct field;
                val.get_to(field);
                o.mappedTo = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag_struct field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const version_control_details_struct &o) {
        j["repositoryUri"] = o.repositoryUri;
        if ( o.revisionId.has_value() ) {
            j["revisionId"] = *o.revisionId;
        }
        if ( o.branch.has_value() ) {
            j["branch"] = *o.branch;
        }
        if ( o.revisionTag.has_value() ) {
            j["revisionTag"] = *o.revisionTag;
        }
        if ( o.asOfTimeUtc.has_value() ) {
            j["asOfTimeUtc"] = *o.asOfTimeUtc;
        }
        if ( o.mappedTo.has_value() ) {
            j["mappedTo"] = *o.mappedTo;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
}