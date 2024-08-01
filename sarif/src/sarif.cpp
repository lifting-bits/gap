// Copyright (c) 2024-present, Trail of Bits, Inc.

#include <gap/sarif/sarif.hpp>

namespace nlohmann {
    template<typename T>
    struct adl_serializer< std::optional<T> > {
        static void from_json(const json& j, std::optional<T>& opt) {
            opt = std::optional<T>{ j.get<T>() };
        }
    };
}

namespace gap::sarif {
    void from_json(const json &j, property_bag &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "tags" ) {
                val.get_to(o.tags);
            } else {
                val.get_to(o.additional_properties[key]);
            }
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
    void from_json(const json &j, multiformat_message_string &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "text" ) {
                val.get_to(o.text);
            } else if ( key == "markdown" ) {
                val.get_to(o.markdown);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, reporting_configuration &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "enabled" ) {
                val.get_to(o.enabled);
            } else if ( key == "level" ) {
                val.get_to(o.level);
            } else if ( key == "rank" ) {
                val.get_to(o.rank);
            } else if ( key == "parameters" ) {
                val.get_to(o.parameters);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
        for( const auto &[key, val] : j.items() ) {
            if ( key == "name" ) {
                val.get_to(o.name);
            } else if ( key == "index" ) {
                val.get_to(o.index);
            } else if ( key == "guid" ) {
                val.get_to(o.guid);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
        for( const auto &[key, val] : j.items() ) {
            if ( key == "id" ) {
                val.get_to(o.id);
            } else if ( key == "index" ) {
                val.get_to(o.index);
            } else if ( key == "guid" ) {
                val.get_to(o.guid);
            } else if ( key == "toolComponent" ) {
                val.get_to(o.toolComponent);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, message &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "text" ) {
                val.get_to(o.text);
            } else if ( key == "markdown" ) {
                val.get_to(o.markdown);
            } else if ( key == "id" ) {
                val.get_to(o.id);
            } else if ( key == "arguments" ) {
                val.get_to(o.arguments);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, reporting_descriptor_relationship &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "target" ) {
                val.get_to(o.target);
            } else if ( key == "kinds" ) {
                val.get_to(o.kinds);
            } else if ( key == "description" ) {
                val.get_to(o.description);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, reporting_descriptor &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "id" ) {
                val.get_to(o.id);
            } else if ( key == "deprecatedIds" ) {
                val.get_to(o.deprecatedIds);
            } else if ( key == "guid" ) {
                val.get_to(o.guid);
            } else if ( key == "deprecatedGuids" ) {
                val.get_to(o.deprecatedGuids);
            } else if ( key == "name" ) {
                val.get_to(o.name);
            } else if ( key == "deprecatedNames" ) {
                val.get_to(o.deprecatedNames);
            } else if ( key == "shortDescription" ) {
                val.get_to(o.shortDescription);
            } else if ( key == "fullDescription" ) {
                val.get_to(o.fullDescription);
            } else if ( key == "messageStrings" ) {
                val.get_to(o.messageStrings);
            } else if ( key == "defaultConfiguration" ) {
                val.get_to(o.defaultConfiguration);
            } else if ( key == "helpUri" ) {
                val.get_to(o.helpUri);
            } else if ( key == "help" ) {
                val.get_to(o.help);
            } else if ( key == "relationships" ) {
                val.get_to(o.relationships);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, artifact_location &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "uri" ) {
                val.get_to(o.uri);
            } else if ( key == "uriBaseId" ) {
                val.get_to(o.uriBaseId);
            } else if ( key == "index" ) {
                val.get_to(o.index);
            } else if ( key == "description" ) {
                val.get_to(o.description);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, translation_metadata &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "name" ) {
                val.get_to(o.name);
            } else if ( key == "fullName" ) {
                val.get_to(o.fullName);
            } else if ( key == "shortDescription" ) {
                val.get_to(o.shortDescription);
            } else if ( key == "fullDescription" ) {
                val.get_to(o.fullDescription);
            } else if ( key == "downloadUri" ) {
                val.get_to(o.downloadUri);
            } else if ( key == "informationUri" ) {
                val.get_to(o.informationUri);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
        for( const auto &[key, val] : j.items() ) {
            if ( key == "guid" ) {
                val.get_to(o.guid);
            } else if ( key == "name" ) {
                val.get_to(o.name);
            } else if ( key == "organization" ) {
                val.get_to(o.organization);
            } else if ( key == "product" ) {
                val.get_to(o.product);
            } else if ( key == "productSuite" ) {
                val.get_to(o.productSuite);
            } else if ( key == "shortDescription" ) {
                val.get_to(o.shortDescription);
            } else if ( key == "fullDescription" ) {
                val.get_to(o.fullDescription);
            } else if ( key == "fullName" ) {
                val.get_to(o.fullName);
            } else if ( key == "version" ) {
                val.get_to(o.version);
            } else if ( key == "semanticVersion" ) {
                val.get_to(o.semanticVersion);
            } else if ( key == "dottedQuadFileVersion" ) {
                val.get_to(o.dottedQuadFileVersion);
            } else if ( key == "releaseDateUtc" ) {
                val.get_to(o.releaseDateUtc);
            } else if ( key == "downloadUri" ) {
                val.get_to(o.downloadUri);
            } else if ( key == "informationUri" ) {
                val.get_to(o.informationUri);
            } else if ( key == "globalMessageStrings" ) {
                val.get_to(o.globalMessageStrings);
            } else if ( key == "notifications" ) {
                val.get_to(o.notifications);
            } else if ( key == "rules" ) {
                val.get_to(o.rules);
            } else if ( key == "taxa" ) {
                val.get_to(o.taxa);
            } else if ( key == "locations" ) {
                val.get_to(o.locations);
            } else if ( key == "language" ) {
                val.get_to(o.language);
            } else if ( key == "contents" ) {
                val.get_to(o.contents);
            } else if ( key == "isComprehensive" ) {
                val.get_to(o.isComprehensive);
            } else if ( key == "localizedDataSemanticVersion" ) {
                val.get_to(o.localizedDataSemanticVersion);
            } else if ( key == "minimumRequiredLocalizedDataSemanticVersion" ) {
                val.get_to(o.minimumRequiredLocalizedDataSemanticVersion);
            } else if ( key == "associatedComponent" ) {
                val.get_to(o.associatedComponent);
            } else if ( key == "translationMetadata" ) {
                val.get_to(o.translationMetadata);
            } else if ( key == "supportedTaxonomies" ) {
                val.get_to(o.supportedTaxonomies);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
        for( const auto &[key, val] : j.items() ) {
            if ( key == "driver" ) {
                val.get_to(o.driver);
            } else if ( key == "extensions" ) {
                val.get_to(o.extensions);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, configuration_override &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "configuration" ) {
                val.get_to(o.configuration);
            } else if ( key == "descriptor" ) {
                val.get_to(o.descriptor);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, address &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "absoluteAddress" ) {
                val.get_to(o.absoluteAddress);
            } else if ( key == "relativeAddress" ) {
                val.get_to(o.relativeAddress);
            } else if ( key == "length" ) {
                val.get_to(o.length);
            } else if ( key == "kind" ) {
                val.get_to(o.kind);
            } else if ( key == "name" ) {
                val.get_to(o.name);
            } else if ( key == "fullyQualifiedName" ) {
                val.get_to(o.fullyQualifiedName);
            } else if ( key == "offsetFromParent" ) {
                val.get_to(o.offsetFromParent);
            } else if ( key == "index" ) {
                val.get_to(o.index);
            } else if ( key == "parentIndex" ) {
                val.get_to(o.parentIndex);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, artifact_content &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "text" ) {
                val.get_to(o.text);
            } else if ( key == "binary" ) {
                val.get_to(o.binary);
            } else if ( key == "rendered" ) {
                val.get_to(o.rendered);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, region &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "startLine" ) {
                val.get_to(o.startLine);
            } else if ( key == "startColumn" ) {
                val.get_to(o.startColumn);
            } else if ( key == "endLine" ) {
                val.get_to(o.endLine);
            } else if ( key == "endColumn" ) {
                val.get_to(o.endColumn);
            } else if ( key == "charOffset" ) {
                val.get_to(o.charOffset);
            } else if ( key == "charLength" ) {
                val.get_to(o.charLength);
            } else if ( key == "byteOffset" ) {
                val.get_to(o.byteOffset);
            } else if ( key == "byteLength" ) {
                val.get_to(o.byteLength);
            } else if ( key == "snippet" ) {
                val.get_to(o.snippet);
            } else if ( key == "message" ) {
                val.get_to(o.message);
            } else if ( key == "sourceLanguage" ) {
                val.get_to(o.sourceLanguage);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
        for( const auto &[key, val] : j.items() ) {
            if ( key == "address" ) {
                val.get_to(o.address);
            } else if ( key == "artifactLocation" ) {
                val.get_to(o.artifactLocation);
            } else if ( key == "region" ) {
                val.get_to(o.region);
            } else if ( key == "contextRegion" ) {
                val.get_to(o.contextRegion);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, logical_location &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "name" ) {
                val.get_to(o.name);
            } else if ( key == "index" ) {
                val.get_to(o.index);
            } else if ( key == "fullyQualifiedName" ) {
                val.get_to(o.fullyQualifiedName);
            } else if ( key == "decoratedName" ) {
                val.get_to(o.decoratedName);
            } else if ( key == "parentIndex" ) {
                val.get_to(o.parentIndex);
            } else if ( key == "kind" ) {
                val.get_to(o.kind);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, location_relationship &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "target" ) {
                val.get_to(o.target);
            } else if ( key == "kinds" ) {
                val.get_to(o.kinds);
            } else if ( key == "description" ) {
                val.get_to(o.description);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, location &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "id" ) {
                val.get_to(o.id);
            } else if ( key == "physicalLocation" ) {
                val.get_to(o.physicalLocation);
            } else if ( key == "logicalLocations" ) {
                val.get_to(o.logicalLocations);
            } else if ( key == "message" ) {
                val.get_to(o.message);
            } else if ( key == "annotations" ) {
                val.get_to(o.annotations);
            } else if ( key == "relationships" ) {
                val.get_to(o.relationships);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, stack_frame &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "location" ) {
                val.get_to(o.location);
            } else if ( key == "module" ) {
                val.get_to(o.module);
            } else if ( key == "threadId" ) {
                val.get_to(o.threadId);
            } else if ( key == "parameters" ) {
                val.get_to(o.parameters);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, stack &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "message" ) {
                val.get_to(o.message);
            } else if ( key == "frames" ) {
                val.get_to(o.frames);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
        for( const auto &[key, val] : j.items() ) {
            if ( key == "kind" ) {
                val.get_to(o.kind);
            } else if ( key == "message" ) {
                val.get_to(o.message);
            } else if ( key == "stack" ) {
                val.get_to(o.stack);
            } else if ( key == "innerExceptions" ) {
                val.get_to(o.innerExceptions);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, notification &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "locations" ) {
                val.get_to(o.locations);
            } else if ( key == "message" ) {
                val.get_to(o.message);
            } else if ( key == "level" ) {
                val.get_to(o.level);
            } else if ( key == "threadId" ) {
                val.get_to(o.threadId);
            } else if ( key == "timeUtc" ) {
                val.get_to(o.timeUtc);
            } else if ( key == "exception" ) {
                val.get_to(o.exception);
            } else if ( key == "descriptor" ) {
                val.get_to(o.descriptor);
            } else if ( key == "associatedRule" ) {
                val.get_to(o.associatedRule);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, invocation &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "commandLine" ) {
                val.get_to(o.commandLine);
            } else if ( key == "arguments" ) {
                val.get_to(o.arguments);
            } else if ( key == "responseFiles" ) {
                val.get_to(o.responseFiles);
            } else if ( key == "startTimeUtc" ) {
                val.get_to(o.startTimeUtc);
            } else if ( key == "endTimeUtc" ) {
                val.get_to(o.endTimeUtc);
            } else if ( key == "exitCode" ) {
                val.get_to(o.exitCode);
            } else if ( key == "ruleConfigurationOverrides" ) {
                val.get_to(o.ruleConfigurationOverrides);
            } else if ( key == "notificationConfigurationOverrides" ) {
                val.get_to(o.notificationConfigurationOverrides);
            } else if ( key == "toolExecutionNotifications" ) {
                val.get_to(o.toolExecutionNotifications);
            } else if ( key == "toolConfigurationNotifications" ) {
                val.get_to(o.toolConfigurationNotifications);
            } else if ( key == "exitCodeDescription" ) {
                val.get_to(o.exitCodeDescription);
            } else if ( key == "exitSignalName" ) {
                val.get_to(o.exitSignalName);
            } else if ( key == "exitSignalNumber" ) {
                val.get_to(o.exitSignalNumber);
            } else if ( key == "processStartFailureMessage" ) {
                val.get_to(o.processStartFailureMessage);
            } else if ( key == "executionSuccessful" ) {
                val.get_to(o.executionSuccessful);
            } else if ( key == "machine" ) {
                val.get_to(o.machine);
            } else if ( key == "account" ) {
                val.get_to(o.account);
            } else if ( key == "processId" ) {
                val.get_to(o.processId);
            } else if ( key == "executableLocation" ) {
                val.get_to(o.executableLocation);
            } else if ( key == "workingDirectory" ) {
                val.get_to(o.workingDirectory);
            } else if ( key == "environmentVariables" ) {
                val.get_to(o.environmentVariables);
            } else if ( key == "stdin" ) {
                val.get_to(o.stdin);
            } else if ( key == "stdout" ) {
                val.get_to(o.stdout);
            } else if ( key == "stderr" ) {
                val.get_to(o.stderr);
            } else if ( key == "stdoutStderr" ) {
                val.get_to(o.stdoutStderr);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
        for( const auto &[key, val] : j.items() ) {
            if ( key == "tool" ) {
                val.get_to(o.tool);
            } else if ( key == "invocation" ) {
                val.get_to(o.invocation);
            } else if ( key == "analysisToolLogFiles" ) {
                val.get_to(o.analysisToolLogFiles);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, version_control_details &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "repositoryUri" ) {
                val.get_to(o.repositoryUri);
            } else if ( key == "revisionId" ) {
                val.get_to(o.revisionId);
            } else if ( key == "branch" ) {
                val.get_to(o.branch);
            } else if ( key == "revisionTag" ) {
                val.get_to(o.revisionTag);
            } else if ( key == "asOfTimeUtc" ) {
                val.get_to(o.asOfTimeUtc);
            } else if ( key == "mappedTo" ) {
                val.get_to(o.mappedTo);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, artifact &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "description" ) {
                val.get_to(o.description);
            } else if ( key == "location" ) {
                val.get_to(o.location);
            } else if ( key == "parentIndex" ) {
                val.get_to(o.parentIndex);
            } else if ( key == "offset" ) {
                val.get_to(o.offset);
            } else if ( key == "length" ) {
                val.get_to(o.length);
            } else if ( key == "roles" ) {
                val.get_to(o.roles);
            } else if ( key == "mimeType" ) {
                val.get_to(o.mimeType);
            } else if ( key == "contents" ) {
                val.get_to(o.contents);
            } else if ( key == "encoding" ) {
                val.get_to(o.encoding);
            } else if ( key == "sourceLanguage" ) {
                val.get_to(o.sourceLanguage);
            } else if ( key == "hashes" ) {
                val.get_to(o.hashes);
            } else if ( key == "lastModifiedTimeUtc" ) {
                val.get_to(o.lastModifiedTimeUtc);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, node &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "id" ) {
                val.get_to(o.id);
            } else if ( key == "label" ) {
                val.get_to(o.label);
            } else if ( key == "location" ) {
                val.get_to(o.location);
            } else if ( key == "children" ) {
                val.get_to(o.children);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, edge &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "id" ) {
                val.get_to(o.id);
            } else if ( key == "label" ) {
                val.get_to(o.label);
            } else if ( key == "sourceNodeId" ) {
                val.get_to(o.sourceNodeId);
            } else if ( key == "targetNodeId" ) {
                val.get_to(o.targetNodeId);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, graph &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "description" ) {
                val.get_to(o.description);
            } else if ( key == "nodes" ) {
                val.get_to(o.nodes);
            } else if ( key == "edges" ) {
                val.get_to(o.edges);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, web_request &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "index" ) {
                val.get_to(o.index);
            } else if ( key == "protocol" ) {
                val.get_to(o.protocol);
            } else if ( key == "version" ) {
                val.get_to(o.version);
            } else if ( key == "target" ) {
                val.get_to(o.target);
            } else if ( key == "method" ) {
                val.get_to(o.method);
            } else if ( key == "headers" ) {
                val.get_to(o.headers);
            } else if ( key == "parameters" ) {
                val.get_to(o.parameters);
            } else if ( key == "body" ) {
                val.get_to(o.body);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
        for( const auto &[key, val] : j.items() ) {
            if ( key == "index" ) {
                val.get_to(o.index);
            } else if ( key == "protocol" ) {
                val.get_to(o.protocol);
            } else if ( key == "version" ) {
                val.get_to(o.version);
            } else if ( key == "statusCode" ) {
                val.get_to(o.statusCode);
            } else if ( key == "reasonPhrase" ) {
                val.get_to(o.reasonPhrase);
            } else if ( key == "headers" ) {
                val.get_to(o.headers);
            } else if ( key == "body" ) {
                val.get_to(o.body);
            } else if ( key == "noResponseReceived" ) {
                val.get_to(o.noResponseReceived);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, thread_flow_location &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "index" ) {
                val.get_to(o.index);
            } else if ( key == "location" ) {
                val.get_to(o.location);
            } else if ( key == "stack" ) {
                val.get_to(o.stack);
            } else if ( key == "kinds" ) {
                val.get_to(o.kinds);
            } else if ( key == "taxa" ) {
                val.get_to(o.taxa);
            } else if ( key == "module" ) {
                val.get_to(o.module);
            } else if ( key == "state" ) {
                val.get_to(o.state);
            } else if ( key == "nestingLevel" ) {
                val.get_to(o.nestingLevel);
            } else if ( key == "executionOrder" ) {
                val.get_to(o.executionOrder);
            } else if ( key == "executionTimeUtc" ) {
                val.get_to(o.executionTimeUtc);
            } else if ( key == "importance" ) {
                val.get_to(o.importance);
            } else if ( key == "webRequest" ) {
                val.get_to(o.webRequest);
            } else if ( key == "webResponse" ) {
                val.get_to(o.webResponse);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, thread_flow &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "id" ) {
                val.get_to(o.id);
            } else if ( key == "message" ) {
                val.get_to(o.message);
            } else if ( key == "initialState" ) {
                val.get_to(o.initialState);
            } else if ( key == "immutableState" ) {
                val.get_to(o.immutableState);
            } else if ( key == "locations" ) {
                val.get_to(o.locations);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, code_flow &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "message" ) {
                val.get_to(o.message);
            } else if ( key == "threadFlows" ) {
                val.get_to(o.threadFlows);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, edge_traversal &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "edgeId" ) {
                val.get_to(o.edgeId);
            } else if ( key == "message" ) {
                val.get_to(o.message);
            } else if ( key == "finalState" ) {
                val.get_to(o.finalState);
            } else if ( key == "stepOverEdgeCount" ) {
                val.get_to(o.stepOverEdgeCount);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, graph_traversal &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "runGraphIndex" ) {
                val.get_to(o.runGraphIndex);
            } else if ( key == "resultGraphIndex" ) {
                val.get_to(o.resultGraphIndex);
            } else if ( key == "description" ) {
                val.get_to(o.description);
            } else if ( key == "initialState" ) {
                val.get_to(o.initialState);
            } else if ( key == "immutableState" ) {
                val.get_to(o.immutableState);
            } else if ( key == "edgeTraversals" ) {
                val.get_to(o.edgeTraversals);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, suppression &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "guid" ) {
                val.get_to(o.guid);
            } else if ( key == "kind" ) {
                val.get_to(o.kind);
            } else if ( key == "state" ) {
                val.get_to(o.state);
            } else if ( key == "justification" ) {
                val.get_to(o.justification);
            } else if ( key == "location" ) {
                val.get_to(o.location);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, rectangle &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "top" ) {
                val.get_to(o.top);
            } else if ( key == "left" ) {
                val.get_to(o.left);
            } else if ( key == "bottom" ) {
                val.get_to(o.bottom);
            } else if ( key == "right" ) {
                val.get_to(o.right);
            } else if ( key == "message" ) {
                val.get_to(o.message);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, attachment &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "description" ) {
                val.get_to(o.description);
            } else if ( key == "artifactLocation" ) {
                val.get_to(o.artifactLocation);
            } else if ( key == "regions" ) {
                val.get_to(o.regions);
            } else if ( key == "rectangles" ) {
                val.get_to(o.rectangles);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, result_provenance &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "firstDetectionTimeUtc" ) {
                val.get_to(o.firstDetectionTimeUtc);
            } else if ( key == "lastDetectionTimeUtc" ) {
                val.get_to(o.lastDetectionTimeUtc);
            } else if ( key == "firstDetectionRunGuid" ) {
                val.get_to(o.firstDetectionRunGuid);
            } else if ( key == "lastDetectionRunGuid" ) {
                val.get_to(o.lastDetectionRunGuid);
            } else if ( key == "invocationIndex" ) {
                val.get_to(o.invocationIndex);
            } else if ( key == "conversionSources" ) {
                val.get_to(o.conversionSources);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, replacement &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "deletedRegion" ) {
                val.get_to(o.deletedRegion);
            } else if ( key == "insertedContent" ) {
                val.get_to(o.insertedContent);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, artifact_change &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "artifactLocation" ) {
                val.get_to(o.artifactLocation);
            } else if ( key == "replacements" ) {
                val.get_to(o.replacements);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, fix &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "description" ) {
                val.get_to(o.description);
            } else if ( key == "artifactChanges" ) {
                val.get_to(o.artifactChanges);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, result &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "ruleId" ) {
                val.get_to(o.ruleId);
            } else if ( key == "ruleIndex" ) {
                val.get_to(o.ruleIndex);
            } else if ( key == "rule" ) {
                val.get_to(o.rule);
            } else if ( key == "kind" ) {
                val.get_to(o.kind);
            } else if ( key == "level" ) {
                val.get_to(o.level);
            } else if ( key == "message" ) {
                val.get_to(o.message);
            } else if ( key == "analysisTarget" ) {
                val.get_to(o.analysisTarget);
            } else if ( key == "locations" ) {
                val.get_to(o.locations);
            } else if ( key == "guid" ) {
                val.get_to(o.guid);
            } else if ( key == "correlationGuid" ) {
                val.get_to(o.correlationGuid);
            } else if ( key == "occurrenceCount" ) {
                val.get_to(o.occurrenceCount);
            } else if ( key == "partialFingerprints" ) {
                val.get_to(o.partialFingerprints);
            } else if ( key == "fingerprints" ) {
                val.get_to(o.fingerprints);
            } else if ( key == "stacks" ) {
                val.get_to(o.stacks);
            } else if ( key == "codeFlows" ) {
                val.get_to(o.codeFlows);
            } else if ( key == "graphs" ) {
                val.get_to(o.graphs);
            } else if ( key == "graphTraversals" ) {
                val.get_to(o.graphTraversals);
            } else if ( key == "relatedLocations" ) {
                val.get_to(o.relatedLocations);
            } else if ( key == "suppressions" ) {
                val.get_to(o.suppressions);
            } else if ( key == "baselineState" ) {
                val.get_to(o.baselineState);
            } else if ( key == "rank" ) {
                val.get_to(o.rank);
            } else if ( key == "attachments" ) {
                val.get_to(o.attachments);
            } else if ( key == "hostedViewerUri" ) {
                val.get_to(o.hostedViewerUri);
            } else if ( key == "workItemUris" ) {
                val.get_to(o.workItemUris);
            } else if ( key == "provenance" ) {
                val.get_to(o.provenance);
            } else if ( key == "fixes" ) {
                val.get_to(o.fixes);
            } else if ( key == "taxa" ) {
                val.get_to(o.taxa);
            } else if ( key == "webRequest" ) {
                val.get_to(o.webRequest);
            } else if ( key == "webResponse" ) {
                val.get_to(o.webResponse);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
        for( const auto &[key, val] : j.items() ) {
            if ( key == "description" ) {
                val.get_to(o.description);
            } else if ( key == "id" ) {
                val.get_to(o.id);
            } else if ( key == "guid" ) {
                val.get_to(o.guid);
            } else if ( key == "correlationGuid" ) {
                val.get_to(o.correlationGuid);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, external_property_file_reference &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "location" ) {
                val.get_to(o.location);
            } else if ( key == "guid" ) {
                val.get_to(o.guid);
            } else if ( key == "itemCount" ) {
                val.get_to(o.itemCount);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
        for( const auto &[key, val] : j.items() ) {
            if ( key == "conversion" ) {
                val.get_to(o.conversion);
            } else if ( key == "graphs" ) {
                val.get_to(o.graphs);
            } else if ( key == "externalizedProperties" ) {
                val.get_to(o.externalizedProperties);
            } else if ( key == "artifacts" ) {
                val.get_to(o.artifacts);
            } else if ( key == "invocations" ) {
                val.get_to(o.invocations);
            } else if ( key == "logicalLocations" ) {
                val.get_to(o.logicalLocations);
            } else if ( key == "threadFlowLocations" ) {
                val.get_to(o.threadFlowLocations);
            } else if ( key == "results" ) {
                val.get_to(o.results);
            } else if ( key == "taxonomies" ) {
                val.get_to(o.taxonomies);
            } else if ( key == "addresses" ) {
                val.get_to(o.addresses);
            } else if ( key == "driver" ) {
                val.get_to(o.driver);
            } else if ( key == "extensions" ) {
                val.get_to(o.extensions);
            } else if ( key == "policies" ) {
                val.get_to(o.policies);
            } else if ( key == "translations" ) {
                val.get_to(o.translations);
            } else if ( key == "webRequests" ) {
                val.get_to(o.webRequests);
            } else if ( key == "webResponses" ) {
                val.get_to(o.webResponses);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, special_locations &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "displayBase" ) {
                val.get_to(o.displayBase);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
        for( const auto &[key, val] : j.items() ) {
            if ( key == "tool" ) {
                val.get_to(o.tool);
            } else if ( key == "invocations" ) {
                val.get_to(o.invocations);
            } else if ( key == "conversion" ) {
                val.get_to(o.conversion);
            } else if ( key == "language" ) {
                val.get_to(o.language);
            } else if ( key == "versionControlProvenance" ) {
                val.get_to(o.versionControlProvenance);
            } else if ( key == "originalUriBaseIds" ) {
                val.get_to(o.originalUriBaseIds);
            } else if ( key == "artifacts" ) {
                val.get_to(o.artifacts);
            } else if ( key == "logicalLocations" ) {
                val.get_to(o.logicalLocations);
            } else if ( key == "graphs" ) {
                val.get_to(o.graphs);
            } else if ( key == "results" ) {
                val.get_to(o.results);
            } else if ( key == "automationDetails" ) {
                val.get_to(o.automationDetails);
            } else if ( key == "runAggregates" ) {
                val.get_to(o.runAggregates);
            } else if ( key == "baselineGuid" ) {
                val.get_to(o.baselineGuid);
            } else if ( key == "redactionTokens" ) {
                val.get_to(o.redactionTokens);
            } else if ( key == "defaultEncoding" ) {
                val.get_to(o.defaultEncoding);
            } else if ( key == "defaultSourceLanguage" ) {
                val.get_to(o.defaultSourceLanguage);
            } else if ( key == "newlineSequences" ) {
                val.get_to(o.newlineSequences);
            } else if ( key == "columnKind" ) {
                val.get_to(o.columnKind);
            } else if ( key == "externalPropertyFileReferences" ) {
                val.get_to(o.externalPropertyFileReferences);
            } else if ( key == "threadFlowLocations" ) {
                val.get_to(o.threadFlowLocations);
            } else if ( key == "taxonomies" ) {
                val.get_to(o.taxonomies);
            } else if ( key == "addresses" ) {
                val.get_to(o.addresses);
            } else if ( key == "translations" ) {
                val.get_to(o.translations);
            } else if ( key == "policies" ) {
                val.get_to(o.policies);
            } else if ( key == "webRequests" ) {
                val.get_to(o.webRequests);
            } else if ( key == "webResponses" ) {
                val.get_to(o.webResponses);
            } else if ( key == "specialLocations" ) {
                val.get_to(o.specialLocations);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, external_properties &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "schema" ) {
                val.get_to(o.schema);
            } else if ( key == "version" ) {
                val.get_to(o.version);
            } else if ( key == "guid" ) {
                val.get_to(o.guid);
            } else if ( key == "runGuid" ) {
                val.get_to(o.runGuid);
            } else if ( key == "conversion" ) {
                val.get_to(o.conversion);
            } else if ( key == "graphs" ) {
                val.get_to(o.graphs);
            } else if ( key == "externalizedProperties" ) {
                val.get_to(o.externalizedProperties);
            } else if ( key == "artifacts" ) {
                val.get_to(o.artifacts);
            } else if ( key == "invocations" ) {
                val.get_to(o.invocations);
            } else if ( key == "logicalLocations" ) {
                val.get_to(o.logicalLocations);
            } else if ( key == "threadFlowLocations" ) {
                val.get_to(o.threadFlowLocations);
            } else if ( key == "results" ) {
                val.get_to(o.results);
            } else if ( key == "taxonomies" ) {
                val.get_to(o.taxonomies);
            } else if ( key == "driver" ) {
                val.get_to(o.driver);
            } else if ( key == "extensions" ) {
                val.get_to(o.extensions);
            } else if ( key == "policies" ) {
                val.get_to(o.policies);
            } else if ( key == "translations" ) {
                val.get_to(o.translations);
            } else if ( key == "addresses" ) {
                val.get_to(o.addresses);
            } else if ( key == "webRequests" ) {
                val.get_to(o.webRequests);
            } else if ( key == "webResponses" ) {
                val.get_to(o.webResponses);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
    void from_json(const json &j, root &o) {
        for( const auto &[key, val] : j.items() ) {
            if ( key == "version" ) {
                val.get_to(o.version);
            } else if ( key == "runs" ) {
                val.get_to(o.runs);
            } else if ( key == "inlineExternalProperties" ) {
                val.get_to(o.inlineExternalProperties);
            } else if ( key == "properties" ) {
                val.get_to(o.properties);
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
} // namespace gap::sarif
