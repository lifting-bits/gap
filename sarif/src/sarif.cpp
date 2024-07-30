// Copyright (c) 2024-present, Trail of Bits, Inc.

#include <gap/sarif/sarif.hpp>

namespace gap::sarif {
    void from_json(const json &j, property_bag &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "tags" ) {
                val.get_to(o.tags);
                continue;
            }
            val.get_to(o.additional_properties[key]);
        }
    }
    void to_json(json &j, const property_bag &o) {
        if ( !o.tags.empty() ) {
            j["tags"] = o.tags;
        }
        for ( auto &[key, val] : o.additional_properties.items() ) {
            j[key] = val;
        }
    }
    void from_json(const json &j, root &o) {
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
                std::forward_list< external_properties > field;
                val.get_to(field);
                o.inlineExternalProperties = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const root &o) {
        j["version"] = o.version;
        j["runs"] = o.runs;
        if ( !o.inlineExternalProperties.empty() ) {
            j["inlineExternalProperties"] = o.inlineExternalProperties;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, address &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "absoluteAddress" ) {
                val.get_to(o.absoluteAddress);
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
                val.get_to(o.index);
                continue;
            }
            if ( key == "parentIndex" ) {
                val.get_to(o.parentIndex);
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const address &o) {
        if ( o.absoluteAddress != -1 ) {
            j["absoluteAddress"] = o.absoluteAddress;
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
        if ( o.index != -1 ) {
            j["index"] = o.index;
        }
        if ( o.parentIndex != -1 ) {
            j["parentIndex"] = o.parentIndex;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, message &o) {
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
                val.get_to(o.arguments);
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const message &o) {
        if ( o.text.has_value() ) {
            j["text"] = *o.text;
        }
        if ( o.markdown.has_value() ) {
            j["markdown"] = *o.markdown;
        }
        if ( o.id.has_value() ) {
            j["id"] = *o.id;
        }
        if ( !o.arguments.empty() ) {
            j["arguments"] = o.arguments;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, artifact_location &o) {
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
                val.get_to(o.index);
                continue;
            }
            if ( key == "description" ) {
                message field;
                val.get_to(field);
                o.description = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const artifact_location &o) {
        if ( o.uri.has_value() ) {
            j["uri"] = *o.uri;
        }
        if ( o.uriBaseId.has_value() ) {
            j["uriBaseId"] = *o.uriBaseId;
        }
        if ( o.index != -1 ) {
            j["index"] = o.index;
        }
        if ( o.description.has_value() ) {
            j["description"] = *o.description;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, multiformat_message_string &o) {
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
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const multiformat_message_string &o) {
        j["text"] = o.text;
        if ( o.markdown.has_value() ) {
            j["markdown"] = *o.markdown;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, artifact_content &o) {
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
                multiformat_message_string field;
                val.get_to(field);
                o.rendered = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const artifact_content &o) {
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
    void from_json(const json &j, artifact &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "description" ) {
                message field;
                val.get_to(field);
                o.description = field;
                continue;
            }
            if ( key == "location" ) {
                artifact_location field;
                val.get_to(field);
                o.location = field;
                continue;
            }
            if ( key == "parentIndex" ) {
                val.get_to(o.parentIndex);
                continue;
            }
            if ( key == "offset" ) {
                int64_t field;
                val.get_to(field);
                o.offset = field;
                continue;
            }
            if ( key == "length" ) {
                val.get_to(o.length);
                continue;
            }
            if ( key == "roles" ) {
                val.get_to(o.roles);
                continue;
            }
            if ( key == "mimeType" ) {
                std::string field;
                val.get_to(field);
                o.mimeType = field;
                continue;
            }
            if ( key == "contents" ) {
                artifact_content field;
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
                std::unordered_map< std::string, std::string > field;
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
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const artifact &o) {
        if ( o.description.has_value() ) {
            j["description"] = *o.description;
        }
        if ( o.location.has_value() ) {
            j["location"] = *o.location;
        }
        if ( o.parentIndex != -1 ) {
            j["parentIndex"] = o.parentIndex;
        }
        if ( o.offset.has_value() ) {
            j["offset"] = *o.offset;
        }
        if ( o.length != -1 ) {
            j["length"] = o.length;
        }
        if ( !o.roles.empty() ) {
            j["roles"] = o.roles;
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
    void from_json(const json &j, artifact_change &o) {
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
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const artifact_change &o) {
        j["artifactLocation"] = o.artifactLocation;
        j["replacements"] = o.replacements;
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, attachment &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "description" ) {
                message field;
                val.get_to(field);
                o.description = field;
                continue;
            }
            if ( key == "artifactLocation" ) {
                val.get_to(o.artifactLocation);
                continue;
            }
            if ( key == "regions" ) {
                val.get_to(o.regions);
                continue;
            }
            if ( key == "rectangles" ) {
                val.get_to(o.rectangles);
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const attachment &o) {
        if ( o.description.has_value() ) {
            j["description"] = *o.description;
        }
        j["artifactLocation"] = o.artifactLocation;
        if ( !o.regions.empty() ) {
            j["regions"] = o.regions;
        }
        if ( !o.rectangles.empty() ) {
            j["rectangles"] = o.rectangles;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, code_flow &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "message" ) {
                message field;
                val.get_to(field);
                o.message = field;
                continue;
            }
            if ( key == "threadFlows" ) {
                val.get_to(o.threadFlows);
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const code_flow &o) {
        if ( o.message.has_value() ) {
            j["message"] = *o.message;
        }
        j["threadFlows"] = o.threadFlows;
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, reporting_configuration &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "enabled" ) {
                val.get_to(o.enabled);
                continue;
            }
            if ( key == "level" ) {
                val.get_to(o.level);
                continue;
            }
            if ( key == "rank" ) {
                val.get_to(o.rank);
                continue;
            }
            if ( key == "parameters" ) {
                property_bag field;
                val.get_to(field);
                o.parameters = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const reporting_configuration &o) {
        if ( o.enabled != true ) {
            j["enabled"] = o.enabled;
        }
        if ( o.level != ::gap::sarif::level::kWarning ) {
            j["level"] = o.level;
        }
        if ( o.rank != -1.0 ) {
            j["rank"] = o.rank;
        }
        if ( o.parameters.has_value() ) {
            j["parameters"] = *o.parameters;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, tool_component_reference &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "name" ) {
                std::string field;
                val.get_to(field);
                o.name = field;
                continue;
            }
            if ( key == "index" ) {
                val.get_to(o.index);
                continue;
            }
            if ( key == "guid" ) {
                std::string field;
                val.get_to(field);
                o.guid = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const tool_component_reference &o) {
        if ( o.name.has_value() ) {
            j["name"] = *o.name;
        }
        if ( o.index != -1 ) {
            j["index"] = o.index;
        }
        if ( o.guid.has_value() ) {
            j["guid"] = *o.guid;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, reporting_descriptor_reference &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "id" ) {
                std::string field;
                val.get_to(field);
                o.id = field;
                continue;
            }
            if ( key == "index" ) {
                val.get_to(o.index);
                continue;
            }
            if ( key == "guid" ) {
                std::string field;
                val.get_to(field);
                o.guid = field;
                continue;
            }
            if ( key == "toolComponent" ) {
                tool_component_reference field;
                val.get_to(field);
                o.toolComponent = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const reporting_descriptor_reference &o) {
        if ( o.id.has_value() ) {
            j["id"] = *o.id;
        }
        if ( o.index != -1 ) {
            j["index"] = o.index;
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
    void from_json(const json &j, configuration_override &o) {
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
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const configuration_override &o) {
        j["configuration"] = o.configuration;
        j["descriptor"] = o.descriptor;
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, translation_metadata &o) {
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
                multiformat_message_string field;
                val.get_to(field);
                o.shortDescription = field;
                continue;
            }
            if ( key == "fullDescription" ) {
                multiformat_message_string field;
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
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const translation_metadata &o) {
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
    void from_json(const json &j, tool_component &o) {
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
                multiformat_message_string field;
                val.get_to(field);
                o.shortDescription = field;
                continue;
            }
            if ( key == "fullDescription" ) {
                multiformat_message_string field;
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
                std::unordered_map< std::string, multiformat_message_string > field;
                val.get_to(field);
                o.globalMessageStrings = field;
                continue;
            }
            if ( key == "notifications" ) {
                val.get_to(o.notifications);
                continue;
            }
            if ( key == "rules" ) {
                val.get_to(o.rules);
                continue;
            }
            if ( key == "taxa" ) {
                val.get_to(o.taxa);
                continue;
            }
            if ( key == "locations" ) {
                val.get_to(o.locations);
                continue;
            }
            if ( key == "language" ) {
                val.get_to(o.language);
                continue;
            }
            if ( key == "contents" ) {
                val.get_to(o.contents);
                continue;
            }
            if ( key == "isComprehensive" ) {
                val.get_to(o.isComprehensive);
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
                tool_component_reference field;
                val.get_to(field);
                o.associatedComponent = field;
                continue;
            }
            if ( key == "translationMetadata" ) {
                translation_metadata field;
                val.get_to(field);
                o.translationMetadata = field;
                continue;
            }
            if ( key == "supportedTaxonomies" ) {
                val.get_to(o.supportedTaxonomies);
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const tool_component &o) {
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
        if ( !o.notifications.empty() ) {
            j["notifications"] = o.notifications;
        }
        if ( !o.rules.empty() ) {
            j["rules"] = o.rules;
        }
        if ( !o.taxa.empty() ) {
            j["taxa"] = o.taxa;
        }
        if ( !o.locations.empty() ) {
            j["locations"] = o.locations;
        }
        if ( o.language != "en-US" ) {
            j["language"] = o.language;
        }
        if ( o.contents != decltype(o.contents){ ::gap::sarif::contents::kLocalizedData, ::gap::sarif::contents::kNonLocalizedData } ) {
            j["contents"] = o.contents;
        }
        if ( o.isComprehensive != false ) {
            j["isComprehensive"] = o.isComprehensive;
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
        if ( !o.supportedTaxonomies.empty() ) {
            j["supportedTaxonomies"] = o.supportedTaxonomies;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, tool &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "driver" ) {
                val.get_to(o.driver);
                continue;
            }
            if ( key == "extensions" ) {
                val.get_to(o.extensions);
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const tool &o) {
        j["driver"] = o.driver;
        if ( !o.extensions.empty() ) {
            j["extensions"] = o.extensions;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, invocation &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "commandLine" ) {
                std::string field;
                val.get_to(field);
                o.commandLine = field;
                continue;
            }
            if ( key == "arguments" ) {
                std::forward_list< std::string > field;
                val.get_to(field);
                o.arguments = field;
                continue;
            }
            if ( key == "responseFiles" ) {
                std::forward_list< artifact_location > field;
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
                val.get_to(o.ruleConfigurationOverrides);
                continue;
            }
            if ( key == "notificationConfigurationOverrides" ) {
                val.get_to(o.notificationConfigurationOverrides);
                continue;
            }
            if ( key == "toolExecutionNotifications" ) {
                val.get_to(o.toolExecutionNotifications);
                continue;
            }
            if ( key == "toolConfigurationNotifications" ) {
                val.get_to(o.toolConfigurationNotifications);
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
                artifact_location field;
                val.get_to(field);
                o.executableLocation = field;
                continue;
            }
            if ( key == "workingDirectory" ) {
                artifact_location field;
                val.get_to(field);
                o.workingDirectory = field;
                continue;
            }
            if ( key == "environmentVariables" ) {
                std::unordered_map< std::string, std::string > field;
                val.get_to(field);
                o.environmentVariables = field;
                continue;
            }
            if ( key == "stdin" ) {
                artifact_location field;
                val.get_to(field);
                o.stdin = field;
                continue;
            }
            if ( key == "stdout" ) {
                artifact_location field;
                val.get_to(field);
                o.stdout = field;
                continue;
            }
            if ( key == "stderr" ) {
                artifact_location field;
                val.get_to(field);
                o.stderr = field;
                continue;
            }
            if ( key == "stdoutStderr" ) {
                artifact_location field;
                val.get_to(field);
                o.stdoutStderr = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const invocation &o) {
        if ( o.commandLine.has_value() ) {
            j["commandLine"] = *o.commandLine;
        }
        if ( !o.arguments.empty() ) {
            j["arguments"] = o.arguments;
        }
        if ( !o.responseFiles.empty() ) {
            j["responseFiles"] = o.responseFiles;
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
        if ( !o.ruleConfigurationOverrides.empty() ) {
            j["ruleConfigurationOverrides"] = o.ruleConfigurationOverrides;
        }
        if ( !o.notificationConfigurationOverrides.empty() ) {
            j["notificationConfigurationOverrides"] = o.notificationConfigurationOverrides;
        }
        if ( !o.toolExecutionNotifications.empty() ) {
            j["toolExecutionNotifications"] = o.toolExecutionNotifications;
        }
        if ( !o.toolConfigurationNotifications.empty() ) {
            j["toolConfigurationNotifications"] = o.toolConfigurationNotifications;
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
    void from_json(const json &j, conversion &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "tool" ) {
                val.get_to(o.tool);
                continue;
            }
            if ( key == "invocation" ) {
                invocation field;
                val.get_to(field);
                o.invocation = field;
                continue;
            }
            if ( key == "analysisToolLogFiles" ) {
                val.get_to(o.analysisToolLogFiles);
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const conversion &o) {
        j["tool"] = o.tool;
        if ( o.invocation.has_value() ) {
            j["invocation"] = *o.invocation;
        }
        if ( !o.analysisToolLogFiles.empty() ) {
            j["analysisToolLogFiles"] = o.analysisToolLogFiles;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, edge &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "id" ) {
                val.get_to(o.id);
                continue;
            }
            if ( key == "label" ) {
                message field;
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
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const edge &o) {
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
    void from_json(const json &j, edge_traversal &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "edgeId" ) {
                val.get_to(o.edgeId);
                continue;
            }
            if ( key == "message" ) {
                message field;
                val.get_to(field);
                o.message = field;
                continue;
            }
            if ( key == "finalState" ) {
                std::unordered_map< std::string, multiformat_message_string > field;
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
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const edge_traversal &o) {
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
    void from_json(const json &j, stack &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "message" ) {
                message field;
                val.get_to(field);
                o.message = field;
                continue;
            }
            if ( key == "frames" ) {
                val.get_to(o.frames);
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const stack &o) {
        if ( o.message.has_value() ) {
            j["message"] = *o.message;
        }
        j["frames"] = o.frames;
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, exception &o) {
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
                stack field;
                val.get_to(field);
                o.stack = field;
                continue;
            }
            if ( key == "innerExceptions" ) {
                val.get_to(o.innerExceptions);
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const exception &o) {
        if ( o.kind.has_value() ) {
            j["kind"] = *o.kind;
        }
        if ( o.message.has_value() ) {
            j["message"] = *o.message;
        }
        if ( o.stack.has_value() ) {
            j["stack"] = *o.stack;
        }
        if ( !o.innerExceptions.empty() ) {
            j["innerExceptions"] = o.innerExceptions;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, external_properties &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "schema" ) {
                std::string field;
                val.get_to(field);
                o.schema = field;
                continue;
            }
            if ( key == "version" ) {
                version field;
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
                conversion field;
                val.get_to(field);
                o.conversion = field;
                continue;
            }
            if ( key == "graphs" ) {
                val.get_to(o.graphs);
                continue;
            }
            if ( key == "externalizedProperties" ) {
                property_bag field;
                val.get_to(field);
                o.externalizedProperties = field;
                continue;
            }
            if ( key == "artifacts" ) {
                std::forward_list< artifact > field;
                val.get_to(field);
                o.artifacts = field;
                continue;
            }
            if ( key == "invocations" ) {
                val.get_to(o.invocations);
                continue;
            }
            if ( key == "logicalLocations" ) {
                val.get_to(o.logicalLocations);
                continue;
            }
            if ( key == "threadFlowLocations" ) {
                val.get_to(o.threadFlowLocations);
                continue;
            }
            if ( key == "results" ) {
                val.get_to(o.results);
                continue;
            }
            if ( key == "taxonomies" ) {
                val.get_to(o.taxonomies);
                continue;
            }
            if ( key == "driver" ) {
                tool_component field;
                val.get_to(field);
                o.driver = field;
                continue;
            }
            if ( key == "extensions" ) {
                val.get_to(o.extensions);
                continue;
            }
            if ( key == "policies" ) {
                val.get_to(o.policies);
                continue;
            }
            if ( key == "translations" ) {
                val.get_to(o.translations);
                continue;
            }
            if ( key == "addresses" ) {
                val.get_to(o.addresses);
                continue;
            }
            if ( key == "webRequests" ) {
                val.get_to(o.webRequests);
                continue;
            }
            if ( key == "webResponses" ) {
                val.get_to(o.webResponses);
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const external_properties &o) {
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
        if ( !o.graphs.empty() ) {
            j["graphs"] = o.graphs;
        }
        if ( o.externalizedProperties.has_value() ) {
            j["externalizedProperties"] = *o.externalizedProperties;
        }
        if ( !o.artifacts.empty() ) {
            j["artifacts"] = o.artifacts;
        }
        if ( !o.invocations.empty() ) {
            j["invocations"] = o.invocations;
        }
        if ( !o.logicalLocations.empty() ) {
            j["logicalLocations"] = o.logicalLocations;
        }
        if ( !o.threadFlowLocations.empty() ) {
            j["threadFlowLocations"] = o.threadFlowLocations;
        }
        if ( !o.results.empty() ) {
            j["results"] = o.results;
        }
        if ( !o.taxonomies.empty() ) {
            j["taxonomies"] = o.taxonomies;
        }
        if ( o.driver.has_value() ) {
            j["driver"] = *o.driver;
        }
        if ( !o.extensions.empty() ) {
            j["extensions"] = o.extensions;
        }
        if ( !o.policies.empty() ) {
            j["policies"] = o.policies;
        }
        if ( !o.translations.empty() ) {
            j["translations"] = o.translations;
        }
        if ( !o.addresses.empty() ) {
            j["addresses"] = o.addresses;
        }
        if ( !o.webRequests.empty() ) {
            j["webRequests"] = o.webRequests;
        }
        if ( !o.webResponses.empty() ) {
            j["webResponses"] = o.webResponses;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, external_property_file_reference &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "location" ) {
                artifact_location field;
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
                val.get_to(o.itemCount);
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const external_property_file_reference &o) {
        if ( o.location.has_value() ) {
            j["location"] = *o.location;
        }
        if ( o.guid.has_value() ) {
            j["guid"] = *o.guid;
        }
        if ( o.itemCount != -1 ) {
            j["itemCount"] = o.itemCount;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, external_property_file_references &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "conversion" ) {
                external_property_file_reference field;
                val.get_to(field);
                o.conversion = field;
                continue;
            }
            if ( key == "graphs" ) {
                val.get_to(o.graphs);
                continue;
            }
            if ( key == "externalizedProperties" ) {
                external_property_file_reference field;
                val.get_to(field);
                o.externalizedProperties = field;
                continue;
            }
            if ( key == "artifacts" ) {
                val.get_to(o.artifacts);
                continue;
            }
            if ( key == "invocations" ) {
                val.get_to(o.invocations);
                continue;
            }
            if ( key == "logicalLocations" ) {
                val.get_to(o.logicalLocations);
                continue;
            }
            if ( key == "threadFlowLocations" ) {
                val.get_to(o.threadFlowLocations);
                continue;
            }
            if ( key == "results" ) {
                val.get_to(o.results);
                continue;
            }
            if ( key == "taxonomies" ) {
                val.get_to(o.taxonomies);
                continue;
            }
            if ( key == "addresses" ) {
                val.get_to(o.addresses);
                continue;
            }
            if ( key == "driver" ) {
                external_property_file_reference field;
                val.get_to(field);
                o.driver = field;
                continue;
            }
            if ( key == "extensions" ) {
                val.get_to(o.extensions);
                continue;
            }
            if ( key == "policies" ) {
                val.get_to(o.policies);
                continue;
            }
            if ( key == "translations" ) {
                val.get_to(o.translations);
                continue;
            }
            if ( key == "webRequests" ) {
                val.get_to(o.webRequests);
                continue;
            }
            if ( key == "webResponses" ) {
                val.get_to(o.webResponses);
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const external_property_file_references &o) {
        if ( o.conversion.has_value() ) {
            j["conversion"] = *o.conversion;
        }
        if ( !o.graphs.empty() ) {
            j["graphs"] = o.graphs;
        }
        if ( o.externalizedProperties.has_value() ) {
            j["externalizedProperties"] = *o.externalizedProperties;
        }
        if ( !o.artifacts.empty() ) {
            j["artifacts"] = o.artifacts;
        }
        if ( !o.invocations.empty() ) {
            j["invocations"] = o.invocations;
        }
        if ( !o.logicalLocations.empty() ) {
            j["logicalLocations"] = o.logicalLocations;
        }
        if ( !o.threadFlowLocations.empty() ) {
            j["threadFlowLocations"] = o.threadFlowLocations;
        }
        if ( !o.results.empty() ) {
            j["results"] = o.results;
        }
        if ( !o.taxonomies.empty() ) {
            j["taxonomies"] = o.taxonomies;
        }
        if ( !o.addresses.empty() ) {
            j["addresses"] = o.addresses;
        }
        if ( o.driver.has_value() ) {
            j["driver"] = *o.driver;
        }
        if ( !o.extensions.empty() ) {
            j["extensions"] = o.extensions;
        }
        if ( !o.policies.empty() ) {
            j["policies"] = o.policies;
        }
        if ( !o.translations.empty() ) {
            j["translations"] = o.translations;
        }
        if ( !o.webRequests.empty() ) {
            j["webRequests"] = o.webRequests;
        }
        if ( !o.webResponses.empty() ) {
            j["webResponses"] = o.webResponses;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, fix &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "description" ) {
                message field;
                val.get_to(field);
                o.description = field;
                continue;
            }
            if ( key == "artifactChanges" ) {
                val.get_to(o.artifactChanges);
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const fix &o) {
        if ( o.description.has_value() ) {
            j["description"] = *o.description;
        }
        j["artifactChanges"] = o.artifactChanges;
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, graph &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "description" ) {
                message field;
                val.get_to(field);
                o.description = field;
                continue;
            }
            if ( key == "nodes" ) {
                val.get_to(o.nodes);
                continue;
            }
            if ( key == "edges" ) {
                val.get_to(o.edges);
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const graph &o) {
        if ( o.description.has_value() ) {
            j["description"] = *o.description;
        }
        if ( !o.nodes.empty() ) {
            j["nodes"] = o.nodes;
        }
        if ( !o.edges.empty() ) {
            j["edges"] = o.edges;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, graph_traversal &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "runGraphIndex" ) {
                val.get_to(o.runGraphIndex);
                continue;
            }
            if ( key == "resultGraphIndex" ) {
                val.get_to(o.resultGraphIndex);
                continue;
            }
            if ( key == "description" ) {
                message field;
                val.get_to(field);
                o.description = field;
                continue;
            }
            if ( key == "initialState" ) {
                std::unordered_map< std::string, multiformat_message_string > field;
                val.get_to(field);
                o.initialState = field;
                continue;
            }
            if ( key == "immutableState" ) {
                std::unordered_map< std::string, multiformat_message_string > field;
                val.get_to(field);
                o.immutableState = field;
                continue;
            }
            if ( key == "edgeTraversals" ) {
                val.get_to(o.edgeTraversals);
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const graph_traversal &o) {
        if ( o.runGraphIndex != -1 ) {
            j["runGraphIndex"] = o.runGraphIndex;
        }
        if ( o.resultGraphIndex != -1 ) {
            j["resultGraphIndex"] = o.resultGraphIndex;
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
        if ( !o.edgeTraversals.empty() ) {
            j["edgeTraversals"] = o.edgeTraversals;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, region &o) {
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
                val.get_to(o.charOffset);
                continue;
            }
            if ( key == "charLength" ) {
                int64_t field;
                val.get_to(field);
                o.charLength = field;
                continue;
            }
            if ( key == "byteOffset" ) {
                val.get_to(o.byteOffset);
                continue;
            }
            if ( key == "byteLength" ) {
                int64_t field;
                val.get_to(field);
                o.byteLength = field;
                continue;
            }
            if ( key == "snippet" ) {
                artifact_content field;
                val.get_to(field);
                o.snippet = field;
                continue;
            }
            if ( key == "message" ) {
                message field;
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
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const region &o) {
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
        if ( o.charOffset != -1 ) {
            j["charOffset"] = o.charOffset;
        }
        if ( o.charLength.has_value() ) {
            j["charLength"] = *o.charLength;
        }
        if ( o.byteOffset != -1 ) {
            j["byteOffset"] = o.byteOffset;
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
    void from_json(const json &j, physical_location &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "address" ) {
                address field;
                val.get_to(field);
                o.address = field;
                continue;
            }
            if ( key == "artifactLocation" ) {
                artifact_location field;
                val.get_to(field);
                o.artifactLocation = field;
                continue;
            }
            if ( key == "region" ) {
                region field;
                val.get_to(field);
                o.region = field;
                continue;
            }
            if ( key == "contextRegion" ) {
                region field;
                val.get_to(field);
                o.contextRegion = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const physical_location &o) {
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
    void from_json(const json &j, location &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "id" ) {
                val.get_to(o.id);
                continue;
            }
            if ( key == "physicalLocation" ) {
                physical_location field;
                val.get_to(field);
                o.physicalLocation = field;
                continue;
            }
            if ( key == "logicalLocations" ) {
                val.get_to(o.logicalLocations);
                continue;
            }
            if ( key == "message" ) {
                message field;
                val.get_to(field);
                o.message = field;
                continue;
            }
            if ( key == "annotations" ) {
                val.get_to(o.annotations);
                continue;
            }
            if ( key == "relationships" ) {
                val.get_to(o.relationships);
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const location &o) {
        if ( o.id != -1 ) {
            j["id"] = o.id;
        }
        if ( o.physicalLocation.has_value() ) {
            j["physicalLocation"] = *o.physicalLocation;
        }
        if ( !o.logicalLocations.empty() ) {
            j["logicalLocations"] = o.logicalLocations;
        }
        if ( o.message.has_value() ) {
            j["message"] = *o.message;
        }
        if ( !o.annotations.empty() ) {
            j["annotations"] = o.annotations;
        }
        if ( !o.relationships.empty() ) {
            j["relationships"] = o.relationships;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, location_relationship &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "target" ) {
                val.get_to(o.target);
                continue;
            }
            if ( key == "kinds" ) {
                val.get_to(o.kinds);
                continue;
            }
            if ( key == "description" ) {
                message field;
                val.get_to(field);
                o.description = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const location_relationship &o) {
        j["target"] = o.target;
        if ( o.kinds != decltype(o.kinds){ "relevant" } ) {
            j["kinds"] = o.kinds;
        }
        if ( o.description.has_value() ) {
            j["description"] = *o.description;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, logical_location &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "name" ) {
                std::string field;
                val.get_to(field);
                o.name = field;
                continue;
            }
            if ( key == "index" ) {
                val.get_to(o.index);
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
                val.get_to(o.parentIndex);
                continue;
            }
            if ( key == "kind" ) {
                std::string field;
                val.get_to(field);
                o.kind = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const logical_location &o) {
        if ( o.name.has_value() ) {
            j["name"] = *o.name;
        }
        if ( o.index != -1 ) {
            j["index"] = o.index;
        }
        if ( o.fullyQualifiedName.has_value() ) {
            j["fullyQualifiedName"] = *o.fullyQualifiedName;
        }
        if ( o.decoratedName.has_value() ) {
            j["decoratedName"] = *o.decoratedName;
        }
        if ( o.parentIndex != -1 ) {
            j["parentIndex"] = o.parentIndex;
        }
        if ( o.kind.has_value() ) {
            j["kind"] = *o.kind;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, node &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "id" ) {
                val.get_to(o.id);
                continue;
            }
            if ( key == "label" ) {
                message field;
                val.get_to(field);
                o.label = field;
                continue;
            }
            if ( key == "location" ) {
                location field;
                val.get_to(field);
                o.location = field;
                continue;
            }
            if ( key == "children" ) {
                val.get_to(o.children);
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const node &o) {
        j["id"] = o.id;
        if ( o.label.has_value() ) {
            j["label"] = *o.label;
        }
        if ( o.location.has_value() ) {
            j["location"] = *o.location;
        }
        if ( !o.children.empty() ) {
            j["children"] = o.children;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, notification &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "locations" ) {
                val.get_to(o.locations);
                continue;
            }
            if ( key == "message" ) {
                val.get_to(o.message);
                continue;
            }
            if ( key == "level" ) {
                val.get_to(o.level);
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
                exception field;
                val.get_to(field);
                o.exception = field;
                continue;
            }
            if ( key == "descriptor" ) {
                reporting_descriptor_reference field;
                val.get_to(field);
                o.descriptor = field;
                continue;
            }
            if ( key == "associatedRule" ) {
                reporting_descriptor_reference field;
                val.get_to(field);
                o.associatedRule = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const notification &o) {
        if ( !o.locations.empty() ) {
            j["locations"] = o.locations;
        }
        j["message"] = o.message;
        if ( o.level != ::gap::sarif::level::kWarning ) {
            j["level"] = o.level;
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
    void from_json(const json &j, rectangle &o) {
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
                message field;
                val.get_to(field);
                o.message = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const rectangle &o) {
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
    void from_json(const json &j, replacement &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "deletedRegion" ) {
                val.get_to(o.deletedRegion);
                continue;
            }
            if ( key == "insertedContent" ) {
                artifact_content field;
                val.get_to(field);
                o.insertedContent = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const replacement &o) {
        j["deletedRegion"] = o.deletedRegion;
        if ( o.insertedContent.has_value() ) {
            j["insertedContent"] = *o.insertedContent;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, reporting_descriptor &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "id" ) {
                val.get_to(o.id);
                continue;
            }
            if ( key == "deprecatedIds" ) {
                std::forward_list< std::string > field;
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
                std::forward_list< std::string > field;
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
                std::forward_list< std::string > field;
                val.get_to(field);
                o.deprecatedNames = field;
                continue;
            }
            if ( key == "shortDescription" ) {
                multiformat_message_string field;
                val.get_to(field);
                o.shortDescription = field;
                continue;
            }
            if ( key == "fullDescription" ) {
                multiformat_message_string field;
                val.get_to(field);
                o.fullDescription = field;
                continue;
            }
            if ( key == "messageStrings" ) {
                std::unordered_map< std::string, multiformat_message_string > field;
                val.get_to(field);
                o.messageStrings = field;
                continue;
            }
            if ( key == "defaultConfiguration" ) {
                reporting_configuration field;
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
                multiformat_message_string field;
                val.get_to(field);
                o.help = field;
                continue;
            }
            if ( key == "relationships" ) {
                val.get_to(o.relationships);
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const reporting_descriptor &o) {
        j["id"] = o.id;
        if ( !o.deprecatedIds.empty() ) {
            j["deprecatedIds"] = o.deprecatedIds;
        }
        if ( o.guid.has_value() ) {
            j["guid"] = *o.guid;
        }
        if ( !o.deprecatedGuids.empty() ) {
            j["deprecatedGuids"] = o.deprecatedGuids;
        }
        if ( o.name.has_value() ) {
            j["name"] = *o.name;
        }
        if ( !o.deprecatedNames.empty() ) {
            j["deprecatedNames"] = o.deprecatedNames;
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
        if ( !o.relationships.empty() ) {
            j["relationships"] = o.relationships;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, reporting_descriptor_relationship &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "target" ) {
                val.get_to(o.target);
                continue;
            }
            if ( key == "kinds" ) {
                val.get_to(o.kinds);
                continue;
            }
            if ( key == "description" ) {
                message field;
                val.get_to(field);
                o.description = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const reporting_descriptor_relationship &o) {
        j["target"] = o.target;
        if ( o.kinds != decltype(o.kinds){ "relevant" } ) {
            j["kinds"] = o.kinds;
        }
        if ( o.description.has_value() ) {
            j["description"] = *o.description;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, result_provenance &o) {
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
                val.get_to(o.invocationIndex);
                continue;
            }
            if ( key == "conversionSources" ) {
                val.get_to(o.conversionSources);
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const result_provenance &o) {
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
        if ( o.invocationIndex != -1 ) {
            j["invocationIndex"] = o.invocationIndex;
        }
        if ( !o.conversionSources.empty() ) {
            j["conversionSources"] = o.conversionSources;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, web_request &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "index" ) {
                val.get_to(o.index);
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
                std::unordered_map< std::string, std::string > field;
                val.get_to(field);
                o.headers = field;
                continue;
            }
            if ( key == "parameters" ) {
                std::unordered_map< std::string, std::string > field;
                val.get_to(field);
                o.parameters = field;
                continue;
            }
            if ( key == "body" ) {
                artifact_content field;
                val.get_to(field);
                o.body = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const web_request &o) {
        if ( o.index != -1 ) {
            j["index"] = o.index;
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
    void from_json(const json &j, web_response &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "index" ) {
                val.get_to(o.index);
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
                std::unordered_map< std::string, std::string > field;
                val.get_to(field);
                o.headers = field;
                continue;
            }
            if ( key == "body" ) {
                artifact_content field;
                val.get_to(field);
                o.body = field;
                continue;
            }
            if ( key == "noResponseReceived" ) {
                val.get_to(o.noResponseReceived);
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const web_response &o) {
        if ( o.index != -1 ) {
            j["index"] = o.index;
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
        if ( o.noResponseReceived != false ) {
            j["noResponseReceived"] = o.noResponseReceived;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, result &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "ruleId" ) {
                std::string field;
                val.get_to(field);
                o.ruleId = field;
                continue;
            }
            if ( key == "ruleIndex" ) {
                val.get_to(o.ruleIndex);
                continue;
            }
            if ( key == "rule" ) {
                reporting_descriptor_reference field;
                val.get_to(field);
                o.rule = field;
                continue;
            }
            if ( key == "kind" ) {
                val.get_to(o.kind);
                continue;
            }
            if ( key == "level" ) {
                val.get_to(o.level);
                continue;
            }
            if ( key == "message" ) {
                val.get_to(o.message);
                continue;
            }
            if ( key == "analysisTarget" ) {
                artifact_location field;
                val.get_to(field);
                o.analysisTarget = field;
                continue;
            }
            if ( key == "locations" ) {
                val.get_to(o.locations);
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
                std::unordered_map< std::string, std::string > field;
                val.get_to(field);
                o.partialFingerprints = field;
                continue;
            }
            if ( key == "fingerprints" ) {
                std::unordered_map< std::string, std::string > field;
                val.get_to(field);
                o.fingerprints = field;
                continue;
            }
            if ( key == "stacks" ) {
                val.get_to(o.stacks);
                continue;
            }
            if ( key == "codeFlows" ) {
                val.get_to(o.codeFlows);
                continue;
            }
            if ( key == "graphs" ) {
                val.get_to(o.graphs);
                continue;
            }
            if ( key == "graphTraversals" ) {
                val.get_to(o.graphTraversals);
                continue;
            }
            if ( key == "relatedLocations" ) {
                val.get_to(o.relatedLocations);
                continue;
            }
            if ( key == "suppressions" ) {
                std::forward_list< suppression > field;
                val.get_to(field);
                o.suppressions = field;
                continue;
            }
            if ( key == "baselineState" ) {
                baseline_state field;
                val.get_to(field);
                o.baselineState = field;
                continue;
            }
            if ( key == "rank" ) {
                val.get_to(o.rank);
                continue;
            }
            if ( key == "attachments" ) {
                val.get_to(o.attachments);
                continue;
            }
            if ( key == "hostedViewerUri" ) {
                std::string field;
                val.get_to(field);
                o.hostedViewerUri = field;
                continue;
            }
            if ( key == "workItemUris" ) {
                std::forward_list< std::string > field;
                val.get_to(field);
                o.workItemUris = field;
                continue;
            }
            if ( key == "provenance" ) {
                result_provenance field;
                val.get_to(field);
                o.provenance = field;
                continue;
            }
            if ( key == "fixes" ) {
                val.get_to(o.fixes);
                continue;
            }
            if ( key == "taxa" ) {
                val.get_to(o.taxa);
                continue;
            }
            if ( key == "webRequest" ) {
                web_request field;
                val.get_to(field);
                o.webRequest = field;
                continue;
            }
            if ( key == "webResponse" ) {
                web_response field;
                val.get_to(field);
                o.webResponse = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const result &o) {
        if ( o.ruleId.has_value() ) {
            j["ruleId"] = *o.ruleId;
        }
        if ( o.ruleIndex != -1 ) {
            j["ruleIndex"] = o.ruleIndex;
        }
        if ( o.rule.has_value() ) {
            j["rule"] = *o.rule;
        }
        if ( o.kind != ::gap::sarif::kind::kFail ) {
            j["kind"] = o.kind;
        }
        if ( o.level != ::gap::sarif::level::kWarning ) {
            j["level"] = o.level;
        }
        j["message"] = o.message;
        if ( o.analysisTarget.has_value() ) {
            j["analysisTarget"] = *o.analysisTarget;
        }
        if ( !o.locations.empty() ) {
            j["locations"] = o.locations;
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
        if ( !o.stacks.empty() ) {
            j["stacks"] = o.stacks;
        }
        if ( !o.codeFlows.empty() ) {
            j["codeFlows"] = o.codeFlows;
        }
        if ( !o.graphs.empty() ) {
            j["graphs"] = o.graphs;
        }
        if ( !o.graphTraversals.empty() ) {
            j["graphTraversals"] = o.graphTraversals;
        }
        if ( !o.relatedLocations.empty() ) {
            j["relatedLocations"] = o.relatedLocations;
        }
        if ( !o.suppressions.empty() ) {
            j["suppressions"] = o.suppressions;
        }
        if ( o.baselineState.has_value() ) {
            j["baselineState"] = *o.baselineState;
        }
        if ( o.rank != -1.0 ) {
            j["rank"] = o.rank;
        }
        if ( !o.attachments.empty() ) {
            j["attachments"] = o.attachments;
        }
        if ( o.hostedViewerUri.has_value() ) {
            j["hostedViewerUri"] = *o.hostedViewerUri;
        }
        if ( !o.workItemUris.empty() ) {
            j["workItemUris"] = o.workItemUris;
        }
        if ( o.provenance.has_value() ) {
            j["provenance"] = *o.provenance;
        }
        if ( !o.fixes.empty() ) {
            j["fixes"] = o.fixes;
        }
        if ( !o.taxa.empty() ) {
            j["taxa"] = o.taxa;
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
    void from_json(const json &j, run_automation_details &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "description" ) {
                message field;
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
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const run_automation_details &o) {
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
    void from_json(const json &j, special_locations &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "displayBase" ) {
                artifact_location field;
                val.get_to(field);
                o.displayBase = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const special_locations &o) {
        if ( o.displayBase.has_value() ) {
            j["displayBase"] = *o.displayBase;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, run &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "tool" ) {
                val.get_to(o.tool);
                continue;
            }
            if ( key == "invocations" ) {
                val.get_to(o.invocations);
                continue;
            }
            if ( key == "conversion" ) {
                conversion field;
                val.get_to(field);
                o.conversion = field;
                continue;
            }
            if ( key == "language" ) {
                val.get_to(o.language);
                continue;
            }
            if ( key == "versionControlProvenance" ) {
                val.get_to(o.versionControlProvenance);
                continue;
            }
            if ( key == "originalUriBaseIds" ) {
                std::unordered_map< std::string, artifact_location > field;
                val.get_to(field);
                o.originalUriBaseIds = field;
                continue;
            }
            if ( key == "artifacts" ) {
                std::forward_list< artifact > field;
                val.get_to(field);
                o.artifacts = field;
                continue;
            }
            if ( key == "logicalLocations" ) {
                val.get_to(o.logicalLocations);
                continue;
            }
            if ( key == "graphs" ) {
                val.get_to(o.graphs);
                continue;
            }
            if ( key == "results" ) {
                std::forward_list< result > field;
                val.get_to(field);
                o.results = field;
                continue;
            }
            if ( key == "automationDetails" ) {
                run_automation_details field;
                val.get_to(field);
                o.automationDetails = field;
                continue;
            }
            if ( key == "runAggregates" ) {
                val.get_to(o.runAggregates);
                continue;
            }
            if ( key == "baselineGuid" ) {
                std::string field;
                val.get_to(field);
                o.baselineGuid = field;
                continue;
            }
            if ( key == "redactionTokens" ) {
                val.get_to(o.redactionTokens);
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
                val.get_to(o.newlineSequences);
                continue;
            }
            if ( key == "columnKind" ) {
                column_kind field;
                val.get_to(field);
                o.columnKind = field;
                continue;
            }
            if ( key == "externalPropertyFileReferences" ) {
                external_property_file_references field;
                val.get_to(field);
                o.externalPropertyFileReferences = field;
                continue;
            }
            if ( key == "threadFlowLocations" ) {
                val.get_to(o.threadFlowLocations);
                continue;
            }
            if ( key == "taxonomies" ) {
                val.get_to(o.taxonomies);
                continue;
            }
            if ( key == "addresses" ) {
                val.get_to(o.addresses);
                continue;
            }
            if ( key == "translations" ) {
                val.get_to(o.translations);
                continue;
            }
            if ( key == "policies" ) {
                val.get_to(o.policies);
                continue;
            }
            if ( key == "webRequests" ) {
                val.get_to(o.webRequests);
                continue;
            }
            if ( key == "webResponses" ) {
                val.get_to(o.webResponses);
                continue;
            }
            if ( key == "specialLocations" ) {
                special_locations field;
                val.get_to(field);
                o.specialLocations = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const run &o) {
        j["tool"] = o.tool;
        if ( !o.invocations.empty() ) {
            j["invocations"] = o.invocations;
        }
        if ( o.conversion.has_value() ) {
            j["conversion"] = *o.conversion;
        }
        if ( o.language != "en-US" ) {
            j["language"] = o.language;
        }
        if ( !o.versionControlProvenance.empty() ) {
            j["versionControlProvenance"] = o.versionControlProvenance;
        }
        if ( o.originalUriBaseIds.has_value() ) {
            j["originalUriBaseIds"] = *o.originalUriBaseIds;
        }
        if ( !o.artifacts.empty() ) {
            j["artifacts"] = o.artifacts;
        }
        if ( !o.logicalLocations.empty() ) {
            j["logicalLocations"] = o.logicalLocations;
        }
        if ( !o.graphs.empty() ) {
            j["graphs"] = o.graphs;
        }
        if ( !o.results.empty() ) {
            j["results"] = o.results;
        }
        if ( o.automationDetails.has_value() ) {
            j["automationDetails"] = *o.automationDetails;
        }
        if ( !o.runAggregates.empty() ) {
            j["runAggregates"] = o.runAggregates;
        }
        if ( o.baselineGuid.has_value() ) {
            j["baselineGuid"] = *o.baselineGuid;
        }
        if ( !o.redactionTokens.empty() ) {
            j["redactionTokens"] = o.redactionTokens;
        }
        if ( o.defaultEncoding.has_value() ) {
            j["defaultEncoding"] = *o.defaultEncoding;
        }
        if ( o.defaultSourceLanguage.has_value() ) {
            j["defaultSourceLanguage"] = *o.defaultSourceLanguage;
        }
        if ( o.newlineSequences != decltype(o.newlineSequences){ "\r\n", "\n" } ) {
            j["newlineSequences"] = o.newlineSequences;
        }
        if ( o.columnKind.has_value() ) {
            j["columnKind"] = *o.columnKind;
        }
        if ( o.externalPropertyFileReferences.has_value() ) {
            j["externalPropertyFileReferences"] = *o.externalPropertyFileReferences;
        }
        if ( !o.threadFlowLocations.empty() ) {
            j["threadFlowLocations"] = o.threadFlowLocations;
        }
        if ( !o.taxonomies.empty() ) {
            j["taxonomies"] = o.taxonomies;
        }
        if ( !o.addresses.empty() ) {
            j["addresses"] = o.addresses;
        }
        if ( !o.translations.empty() ) {
            j["translations"] = o.translations;
        }
        if ( !o.policies.empty() ) {
            j["policies"] = o.policies;
        }
        if ( !o.webRequests.empty() ) {
            j["webRequests"] = o.webRequests;
        }
        if ( !o.webResponses.empty() ) {
            j["webResponses"] = o.webResponses;
        }
        if ( o.specialLocations.has_value() ) {
            j["specialLocations"] = *o.specialLocations;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, stack_frame &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "location" ) {
                location field;
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
                val.get_to(o.parameters);
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const stack_frame &o) {
        if ( o.location.has_value() ) {
            j["location"] = *o.location;
        }
        if ( o.module.has_value() ) {
            j["module"] = *o.module;
        }
        if ( o.threadId.has_value() ) {
            j["threadId"] = *o.threadId;
        }
        if ( !o.parameters.empty() ) {
            j["parameters"] = o.parameters;
        }
        if ( o.properties.has_value() ) {
            j["properties"] = *o.properties;
        }
    }
    void from_json(const json &j, suppression &o) {
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
                state field;
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
                location field;
                val.get_to(field);
                o.location = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const suppression &o) {
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
    void from_json(const json &j, thread_flow &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "id" ) {
                std::string field;
                val.get_to(field);
                o.id = field;
                continue;
            }
            if ( key == "message" ) {
                message field;
                val.get_to(field);
                o.message = field;
                continue;
            }
            if ( key == "initialState" ) {
                std::unordered_map< std::string, multiformat_message_string > field;
                val.get_to(field);
                o.initialState = field;
                continue;
            }
            if ( key == "immutableState" ) {
                std::unordered_map< std::string, multiformat_message_string > field;
                val.get_to(field);
                o.immutableState = field;
                continue;
            }
            if ( key == "locations" ) {
                val.get_to(o.locations);
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const thread_flow &o) {
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
    void from_json(const json &j, thread_flow_location &o) {
        for( auto &[key, val] : j.items() ) {
            if ( key == "index" ) {
                val.get_to(o.index);
                continue;
            }
            if ( key == "location" ) {
                location field;
                val.get_to(field);
                o.location = field;
                continue;
            }
            if ( key == "stack" ) {
                stack field;
                val.get_to(field);
                o.stack = field;
                continue;
            }
            if ( key == "kinds" ) {
                val.get_to(o.kinds);
                continue;
            }
            if ( key == "taxa" ) {
                val.get_to(o.taxa);
                continue;
            }
            if ( key == "module" ) {
                std::string field;
                val.get_to(field);
                o.module = field;
                continue;
            }
            if ( key == "state" ) {
                std::unordered_map< std::string, multiformat_message_string > field;
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
                val.get_to(o.executionOrder);
                continue;
            }
            if ( key == "executionTimeUtc" ) {
                std::string field;
                val.get_to(field);
                o.executionTimeUtc = field;
                continue;
            }
            if ( key == "importance" ) {
                val.get_to(o.importance);
                continue;
            }
            if ( key == "webRequest" ) {
                web_request field;
                val.get_to(field);
                o.webRequest = field;
                continue;
            }
            if ( key == "webResponse" ) {
                web_response field;
                val.get_to(field);
                o.webResponse = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const thread_flow_location &o) {
        if ( o.index != -1 ) {
            j["index"] = o.index;
        }
        if ( o.location.has_value() ) {
            j["location"] = *o.location;
        }
        if ( o.stack.has_value() ) {
            j["stack"] = *o.stack;
        }
        if ( !o.kinds.empty() ) {
            j["kinds"] = o.kinds;
        }
        if ( !o.taxa.empty() ) {
            j["taxa"] = o.taxa;
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
        if ( o.executionOrder != -1 ) {
            j["executionOrder"] = o.executionOrder;
        }
        if ( o.executionTimeUtc.has_value() ) {
            j["executionTimeUtc"] = *o.executionTimeUtc;
        }
        if ( o.importance != ::gap::sarif::importance::kImportant ) {
            j["importance"] = o.importance;
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
    void from_json(const json &j, version_control_details &o) {
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
                artifact_location field;
                val.get_to(field);
                o.mappedTo = field;
                continue;
            }
            if ( key == "properties" ) {
                property_bag field;
                val.get_to(field);
                o.properties = field;
                continue;
            }
        }
    }
    void to_json(json &j, const version_control_details &o) {
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
} // namespace gap::sarif
