// Copyright 2024-present, Trail of Bits, Inc.

#pragma once

#include <cstdint>
#include <forward_list>
#include <optional>
#include <string>
#include <unordered_map>

#include <nlohmann/json.hpp>

namespace gap::sarif
{
    using json = nlohmann::json;

    enum class version_enum {
        k2_1_0,
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(version_enum, {
        { version_enum::k2_1_0, "2.1.0" },
    })
    struct run_struct;
    struct external_properties_struct;

    //
    // Key/value pairs that provide additional information about the object.
    //
    struct property_bag_struct {
        //
        // A set of distinct strings that provide additional information.
        //
        std::optional<std::forward_list<std::string>> tags = std::nullopt;

        std::unordered_map<std::string, json> additional_properties;
    };

    void to_json(json &, const property_bag_struct &);
    void from_json(const json &, property_bag_struct &);

    //
    // Static Analysis Results Format (SARIF) Version 2.1.0 JSON Schema: a standard format for the output of static analysis tools.
    //
    struct root_struct {
        //
        // The SARIF format version of this log file.
        //
        version_enum version;

        //
        // The set of runs contained in this log file.
        //
        std::forward_list<run_struct> runs;

        //
        // References to external property files that share data between runs.
        //
        std::optional<std::forward_list<external_properties_struct>> inlineExternalProperties = std::nullopt;

        //
        // Key/value pairs that provide additional information about the log file.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const root_struct &);
    void from_json(const json &, root_struct &);

    //
    // A physical or virtual address, or a range of addresses, in an 'addressable region' (memory or a binary file).
    //
    struct address_struct {
        //
        // The address expressed as a byte offset from the start of the addressable region.
        //
        std::optional<int64_t> absoluteAddress = std::nullopt;

        //
        // The address expressed as a byte offset from the absolute address of the top-most parent object.
        //
        std::optional<int64_t> relativeAddress = std::nullopt;

        //
        // The number of bytes in this range of addresses.
        //
        std::optional<int64_t> length = std::nullopt;

        //
        // An open-ended string that identifies the address kind. 'data', 'function', 'header','instruction', 'module', 'page', 'section', 'segment', 'stack', 'stackFrame', 'table' are well-known values.
        //
        std::optional<std::string> kind = std::nullopt;

        //
        // A name that is associated with the address, e.g., '.text'.
        //
        std::optional<std::string> name = std::nullopt;

        //
        // A human-readable fully qualified name that is associated with the address.
        //
        std::optional<std::string> fullyQualifiedName = std::nullopt;

        //
        // The byte offset of this address from the absolute or relative address of the parent object.
        //
        std::optional<int64_t> offsetFromParent = std::nullopt;

        //
        // The index within run.addresses of the cached object for this address.
        //
        std::optional<int64_t> index = std::nullopt;

        //
        // The index within run.addresses of the parent object.
        //
        std::optional<int64_t> parentIndex = std::nullopt;

        //
        // Key/value pairs that provide additional information about the address.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const address_struct &);
    void from_json(const json &, address_struct &);

    //
    // Encapsulates a message intended to be read by the end user.
    //
    struct message_struct {
        //
        // A plain text message string.
        //
        std::optional<std::string> text = std::nullopt;

        //
        // A Markdown message string.
        //
        std::optional<std::string> markdown = std::nullopt;

        //
        // The identifier for this message.
        //
        std::optional<std::string> id = std::nullopt;

        //
        // An array of strings to substitute into the message string.
        //
        std::optional<std::forward_list<std::string>> arguments = std::nullopt;

        //
        // Key/value pairs that provide additional information about the message.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const message_struct &);
    void from_json(const json &, message_struct &);

    //
    // Specifies the location of an artifact.
    //
    struct artifact_location_struct {
        //
        // A string containing a valid relative or absolute URI.
        //
        std::optional<std::string> uri = std::nullopt;

        //
        // A string which indirectly specifies the absolute URI with respect to which a relative URI in the "uri" property is interpreted.
        //
        std::optional<std::string> uriBaseId = std::nullopt;

        //
        // The index within the run artifacts array of the artifact object associated with the artifact location.
        //
        std::optional<int64_t> index = std::nullopt;

        //
        // A short description of the artifact location.
        //
        std::optional<message_struct> description = std::nullopt;

        //
        // Key/value pairs that provide additional information about the artifact location.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const artifact_location_struct &);
    void from_json(const json &, artifact_location_struct &);

    enum class roles_enum {
        kAnalysisTarget,
        kAttachment,
        kResponseFile,
        kResultFile,
        kStandardStream,
        kTracedFile,
        kUnmodified,
        kModified,
        kAdded,
        kDeleted,
        kRenamed,
        kUncontrolled,
        kDriver,
        kExtension,
        kTranslation,
        kTaxonomy,
        kPolicy,
        kReferencedOnCommandLine,
        kMemoryContents,
        kDirectory,
        kUserSpecifiedConfiguration,
        kToolSpecifiedConfiguration,
        kDebugOutputFile,
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(roles_enum, {
        { roles_enum::kAnalysisTarget, "analysisTarget" },
        { roles_enum::kAttachment, "attachment" },
        { roles_enum::kResponseFile, "responseFile" },
        { roles_enum::kResultFile, "resultFile" },
        { roles_enum::kStandardStream, "standardStream" },
        { roles_enum::kTracedFile, "tracedFile" },
        { roles_enum::kUnmodified, "unmodified" },
        { roles_enum::kModified, "modified" },
        { roles_enum::kAdded, "added" },
        { roles_enum::kDeleted, "deleted" },
        { roles_enum::kRenamed, "renamed" },
        { roles_enum::kUncontrolled, "uncontrolled" },
        { roles_enum::kDriver, "driver" },
        { roles_enum::kExtension, "extension" },
        { roles_enum::kTranslation, "translation" },
        { roles_enum::kTaxonomy, "taxonomy" },
        { roles_enum::kPolicy, "policy" },
        { roles_enum::kReferencedOnCommandLine, "referencedOnCommandLine" },
        { roles_enum::kMemoryContents, "memoryContents" },
        { roles_enum::kDirectory, "directory" },
        { roles_enum::kUserSpecifiedConfiguration, "userSpecifiedConfiguration" },
        { roles_enum::kToolSpecifiedConfiguration, "toolSpecifiedConfiguration" },
        { roles_enum::kDebugOutputFile, "debugOutputFile" },
    })

    //
    // A message string or message format string rendered in multiple formats.
    //
    struct multiformat_message_string_struct {
        //
        // A plain text message string or format string.
        //
        std::string text;

        //
        // A Markdown message string or format string.
        //
        std::optional<std::string> markdown = std::nullopt;

        //
        // Key/value pairs that provide additional information about the message.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const multiformat_message_string_struct &);
    void from_json(const json &, multiformat_message_string_struct &);

    //
    // Represents the contents of an artifact.
    //
    struct artifact_content_struct {
        //
        // UTF-8-encoded content from a text artifact.
        //
        std::optional<std::string> text = std::nullopt;

        //
        // MIME Base64-encoded content from a binary artifact, or from a text artifact in its original encoding.
        //
        std::optional<std::string> binary = std::nullopt;

        //
        // An alternate rendered representation of the artifact (e.g., a decompiled representation of a binary region).
        //
        std::optional<multiformat_message_string_struct> rendered = std::nullopt;

        //
        // Key/value pairs that provide additional information about the artifact content.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const artifact_content_struct &);
    void from_json(const json &, artifact_content_struct &);

    //
    // A dictionary, each of whose keys is the name of a hash function and each of whose values is the hashed value of the artifact produced by the specified hash function.
    //
    struct artifact_hashes_struct {
        std::unordered_map<std::string, std::string> additional_properties;
    };

    void to_json(json &, const artifact_hashes_struct &);
    void from_json(const json &, artifact_hashes_struct &);

    //
    // A single artifact. In some cases, this artifact might be nested within another artifact.
    //
    struct artifact_struct {
        //
        // A short description of the artifact.
        //
        std::optional<message_struct> description = std::nullopt;

        //
        // The location of the artifact.
        //
        std::optional<artifact_location_struct> location = std::nullopt;

        //
        // Identifies the index of the immediate parent of the artifact, if this artifact is nested.
        //
        std::optional<int64_t> parentIndex = std::nullopt;

        //
        // The offset in bytes of the artifact within its containing artifact.
        //
        std::optional<int64_t> offset = std::nullopt;

        //
        // The length of the artifact in bytes.
        //
        std::optional<int64_t> length = std::nullopt;

        //
        // The role or roles played by the artifact in the analysis.
        //
        std::optional<std::forward_list<roles_enum>> roles = std::nullopt;

        //
        // The MIME type (RFC 2045) of the artifact.
        //
        std::optional<std::string> mimeType = std::nullopt;

        //
        // The contents of the artifact.
        //
        std::optional<artifact_content_struct> contents = std::nullopt;

        //
        // Specifies the encoding for an artifact object that refers to a text file.
        //
        std::optional<std::string> encoding = std::nullopt;

        //
        // Specifies the source language for any artifact object that refers to a text file that contains source code.
        //
        std::optional<std::string> sourceLanguage = std::nullopt;

        //
        // A dictionary, each of whose keys is the name of a hash function and each of whose values is the hashed value of the artifact produced by the specified hash function.
        //
        std::optional<artifact_hashes_struct> hashes = std::nullopt;

        //
        // The Coordinated Universal Time (UTC) date and time at which the artifact was most recently modified. See "Date/time properties" in the SARIF spec for the required format.
        //
        std::optional<std::string> lastModifiedTimeUtc = std::nullopt;

        //
        // Key/value pairs that provide additional information about the artifact.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const artifact_struct &);
    void from_json(const json &, artifact_struct &);
    struct replacement_struct;

    //
    // A change to a single artifact.
    //
    struct artifact_change_struct {
        //
        // The location of the artifact to change.
        //
        artifact_location_struct artifactLocation;

        //
        // An array of replacement objects, each of which represents the replacement of a single region in a single artifact specified by 'artifactLocation'.
        //
        std::forward_list<replacement_struct> replacements;

        //
        // Key/value pairs that provide additional information about the change.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const artifact_change_struct &);
    void from_json(const json &, artifact_change_struct &);
    struct region_struct;
    struct rectangle_struct;

    //
    // An artifact relevant to a result.
    //
    struct attachment_struct {
        //
        // A message describing the role played by the attachment.
        //
        std::optional<message_struct> description = std::nullopt;

        //
        // The location of the attachment.
        //
        artifact_location_struct artifactLocation;

        //
        // An array of regions of interest within the attachment.
        //
        std::optional<std::forward_list<region_struct>> regions = std::nullopt;

        //
        // An array of rectangles specifying areas of interest within the image.
        //
        std::optional<std::forward_list<rectangle_struct>> rectangles = std::nullopt;

        //
        // Key/value pairs that provide additional information about the attachment.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const attachment_struct &);
    void from_json(const json &, attachment_struct &);
    struct thread_flow_struct;

    //
    // A set of threadFlows which together describe a pattern of code execution relevant to detecting a result.
    //
    struct code_flow_struct {
        //
        // A message relevant to the code flow.
        //
        std::optional<message_struct> message = std::nullopt;

        //
        // An array of one or more unique threadFlow objects, each of which describes the progress of a program through a thread of execution.
        //
        std::forward_list<thread_flow_struct> threadFlows;

        //
        // Key/value pairs that provide additional information about the code flow.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const code_flow_struct &);
    void from_json(const json &, code_flow_struct &);

    enum class level_enum {
        kNone,
        kNote,
        kWarning,
        kError,
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(level_enum, {
        { level_enum::kNone, "none" },
        { level_enum::kNote, "note" },
        { level_enum::kWarning, "warning" },
        { level_enum::kError, "error" },
    })

    //
    // Information about a rule or notification that can be configured at runtime.
    //
    struct reporting_configuration_struct {
        //
        // Specifies whether the report may be produced during the scan.
        //
        std::optional<bool> enabled = std::nullopt;

        //
        // Specifies the failure level for the report.
        //
        std::optional<level_enum> level = std::nullopt;

        //
        // Specifies the relative priority of the report. Used for analysis output only.
        //
        std::optional<double> rank = std::nullopt;

        //
        // Contains configuration information specific to a report.
        //
        std::optional<property_bag_struct> parameters = std::nullopt;

        //
        // Key/value pairs that provide additional information about the reporting configuration.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const reporting_configuration_struct &);
    void from_json(const json &, reporting_configuration_struct &);

    //
    // Identifies a particular toolComponent object, either the driver or an extension.
    //
    struct tool_component_reference_struct {
        //
        // The 'name' property of the referenced toolComponent.
        //
        std::optional<std::string> name = std::nullopt;

        //
        // An index into the referenced toolComponent in tool.extensions.
        //
        std::optional<int64_t> index = std::nullopt;

        //
        // The 'guid' property of the referenced toolComponent.
        //
        std::optional<std::string> guid = std::nullopt;

        //
        // Key/value pairs that provide additional information about the toolComponentReference.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const tool_component_reference_struct &);
    void from_json(const json &, tool_component_reference_struct &);

    //
    // Information about how to locate a relevant reporting descriptor.
    //
    struct reporting_descriptor_reference_struct {
        //
        // The id of the descriptor.
        //
        std::optional<std::string> id = std::nullopt;

        //
        // The index into an array of descriptors in toolComponent.ruleDescriptors, toolComponent.notificationDescriptors, or toolComponent.taxonomyDescriptors, depending on context.
        //
        std::optional<int64_t> index = std::nullopt;

        //
        // A guid that uniquely identifies the descriptor.
        //
        std::optional<std::string> guid = std::nullopt;

        //
        // A reference used to locate the toolComponent associated with the descriptor.
        //
        std::optional<tool_component_reference_struct> toolComponent = std::nullopt;

        //
        // Key/value pairs that provide additional information about the reporting descriptor reference.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const reporting_descriptor_reference_struct &);
    void from_json(const json &, reporting_descriptor_reference_struct &);

    //
    // Information about how a specific rule or notification was reconfigured at runtime.
    //
    struct configuration_override_struct {
        //
        // Specifies how the rule or notification was configured during the scan.
        //
        reporting_configuration_struct configuration;

        //
        // A reference used to locate the descriptor whose configuration was overridden.
        //
        reporting_descriptor_reference_struct descriptor;

        //
        // Key/value pairs that provide additional information about the configuration override.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const configuration_override_struct &);
    void from_json(const json &, configuration_override_struct &);

    //
    // A dictionary, each of whose keys is a resource identifier and each of whose values is a multiformatMessageString object, which holds message strings in plain text and (optionally) Markdown format. The strings can include placeholders, which can be used to construct a message in combination with an arbitrary number of additional string arguments.
    //
    struct tool_component_global_message_strings_struct {
        std::unordered_map<std::string, multiformat_message_string_struct> additional_properties;
    };

    void to_json(json &, const tool_component_global_message_strings_struct &);
    void from_json(const json &, tool_component_global_message_strings_struct &);
    struct reporting_descriptor_struct;

    enum class contents_enum {
        kLocalizedData,
        kNonLocalizedData,
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(contents_enum, {
        { contents_enum::kLocalizedData, "localizedData" },
        { contents_enum::kNonLocalizedData, "nonLocalizedData" },
    })

    //
    // Provides additional metadata related to translation.
    //
    struct translation_metadata_struct {
        //
        // The name associated with the translation metadata.
        //
        std::string name;

        //
        // The full name associated with the translation metadata.
        //
        std::optional<std::string> fullName = std::nullopt;

        //
        // A brief description of the translation metadata.
        //
        std::optional<multiformat_message_string_struct> shortDescription = std::nullopt;

        //
        // A comprehensive description of the translation metadata.
        //
        std::optional<multiformat_message_string_struct> fullDescription = std::nullopt;

        //
        // The absolute URI from which the translation metadata can be downloaded.
        //
        std::optional<std::string> downloadUri = std::nullopt;

        //
        // The absolute URI from which information related to the translation metadata can be downloaded.
        //
        std::optional<std::string> informationUri = std::nullopt;

        //
        // Key/value pairs that provide additional information about the translation metadata.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const translation_metadata_struct &);
    void from_json(const json &, translation_metadata_struct &);

    //
    // A component, such as a plug-in or the driver, of the analysis tool that was run.
    //
    struct tool_component_struct {
        //
        // A unique identifer for the tool component in the form of a GUID.
        //
        std::optional<std::string> guid = std::nullopt;

        //
        // The name of the tool component.
        //
        std::string name;

        //
        // The organization or company that produced the tool component.
        //
        std::optional<std::string> organization = std::nullopt;

        //
        // A product suite to which the tool component belongs.
        //
        std::optional<std::string> product = std::nullopt;

        //
        // A localizable string containing the name of the suite of products to which the tool component belongs.
        //
        std::optional<std::string> productSuite = std::nullopt;

        //
        // A brief description of the tool component.
        //
        std::optional<multiformat_message_string_struct> shortDescription = std::nullopt;

        //
        // A comprehensive description of the tool component.
        //
        std::optional<multiformat_message_string_struct> fullDescription = std::nullopt;

        //
        // The name of the tool component along with its version and any other useful identifying information, such as its locale.
        //
        std::optional<std::string> fullName = std::nullopt;

        //
        // The tool component version, in whatever format the component natively provides.
        //
        std::optional<std::string> version = std::nullopt;

        //
        // The tool component version in the format specified by Semantic Versioning 2.0.
        //
        std::optional<std::string> semanticVersion = std::nullopt;

        //
        // The binary version of the tool component's primary executable file expressed as four non-negative integers separated by a period (for operating systems that express file versions in this way).
        //
        std::optional<std::string> dottedQuadFileVersion = std::nullopt;

        //
        // A string specifying the UTC date (and optionally, the time) of the component's release.
        //
        std::optional<std::string> releaseDateUtc = std::nullopt;

        //
        // The absolute URI from which the tool component can be downloaded.
        //
        std::optional<std::string> downloadUri = std::nullopt;

        //
        // The absolute URI at which information about this version of the tool component can be found.
        //
        std::optional<std::string> informationUri = std::nullopt;

        //
        // A dictionary, each of whose keys is a resource identifier and each of whose values is a multiformatMessageString object, which holds message strings in plain text and (optionally) Markdown format. The strings can include placeholders, which can be used to construct a message in combination with an arbitrary number of additional string arguments.
        //
        std::optional<tool_component_global_message_strings_struct> globalMessageStrings = std::nullopt;

        //
        // An array of reportingDescriptor objects relevant to the notifications related to the configuration and runtime execution of the tool component.
        //
        std::optional<std::forward_list<reporting_descriptor_struct>> notifications = std::nullopt;

        //
        // An array of reportingDescriptor objects relevant to the analysis performed by the tool component.
        //
        std::optional<std::forward_list<reporting_descriptor_struct>> rules = std::nullopt;

        //
        // An array of reportingDescriptor objects relevant to the definitions of both standalone and tool-defined taxonomies.
        //
        std::optional<std::forward_list<reporting_descriptor_struct>> taxa = std::nullopt;

        //
        // An array of the artifactLocation objects associated with the tool component.
        //
        std::optional<std::forward_list<artifact_location_struct>> locations = std::nullopt;

        //
        // The language of the messages emitted into the log file during this run (expressed as an ISO 639-1 two-letter lowercase language code) and an optional region (expressed as an ISO 3166-1 two-letter uppercase subculture code associated with a country or region). The casing is recommended but not required (in order for this data to conform to RFC5646).
        //
        std::optional<std::string> language = std::nullopt;

        //
        // The kinds of data contained in this object.
        //
        std::optional<std::forward_list<contents_enum>> contents = std::nullopt;

        //
        // Specifies whether this object contains a complete definition of the localizable and/or non-localizable data for this component, as opposed to including only data that is relevant to the results persisted to this log file.
        //
        std::optional<bool> isComprehensive = std::nullopt;

        //
        // The semantic version of the localized strings defined in this component; maintained by components that provide translations.
        //
        std::optional<std::string> localizedDataSemanticVersion = std::nullopt;

        //
        // The minimum value of localizedDataSemanticVersion required in translations consumed by this component; used by components that consume translations.
        //
        std::optional<std::string> minimumRequiredLocalizedDataSemanticVersion = std::nullopt;

        //
        // The component which is strongly associated with this component. For a translation, this refers to the component which has been translated. For an extension, this is the driver that provides the extension's plugin model.
        //
        std::optional<tool_component_reference_struct> associatedComponent = std::nullopt;

        //
        // Translation metadata, required for a translation, not populated by other component types.
        //
        std::optional<translation_metadata_struct> translationMetadata = std::nullopt;

        //
        // An array of toolComponentReference objects to declare the taxonomies supported by the tool component.
        //
        std::optional<std::forward_list<tool_component_reference_struct>> supportedTaxonomies = std::nullopt;

        //
        // Key/value pairs that provide additional information about the tool component.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const tool_component_struct &);
    void from_json(const json &, tool_component_struct &);

    //
    // The analysis tool that was run.
    //
    struct tool_struct {
        //
        // The analysis tool that was run.
        //
        tool_component_struct driver;

        //
        // Tool extensions that contributed to or reconfigured the analysis tool that was run.
        //
        std::optional<std::forward_list<tool_component_struct>> extensions = std::nullopt;

        //
        // Key/value pairs that provide additional information about the tool.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const tool_struct &);
    void from_json(const json &, tool_struct &);
    struct notification_struct;

    //
    // The environment variables associated with the analysis tool process, expressed as key/value pairs.
    //
    struct invocation_environment_variables_struct {
        std::unordered_map<std::string, std::string> additional_properties;
    };

    void to_json(json &, const invocation_environment_variables_struct &);
    void from_json(const json &, invocation_environment_variables_struct &);

    //
    // The runtime environment of the analysis tool run.
    //
    struct invocation_struct {
        //
        // The command line used to invoke the tool.
        //
        std::optional<std::string> commandLine = std::nullopt;

        //
        // An array of strings, containing in order the command line arguments passed to the tool from the operating system.
        //
        std::optional<std::forward_list<std::string>> arguments = std::nullopt;

        //
        // The locations of any response files specified on the tool's command line.
        //
        std::optional<std::forward_list<artifact_location_struct>> responseFiles = std::nullopt;

        //
        // The Coordinated Universal Time (UTC) date and time at which the run started. See "Date/time properties" in the SARIF spec for the required format.
        //
        std::optional<std::string> startTimeUtc = std::nullopt;

        //
        // The Coordinated Universal Time (UTC) date and time at which the run ended. See "Date/time properties" in the SARIF spec for the required format.
        //
        std::optional<std::string> endTimeUtc = std::nullopt;

        //
        // The process exit code.
        //
        std::optional<int64_t> exitCode = std::nullopt;

        //
        // An array of configurationOverride objects that describe rules related runtime overrides.
        //
        std::optional<std::forward_list<configuration_override_struct>> ruleConfigurationOverrides = std::nullopt;

        //
        // An array of configurationOverride objects that describe notifications related runtime overrides.
        //
        std::optional<std::forward_list<configuration_override_struct>> notificationConfigurationOverrides = std::nullopt;

        //
        // A list of runtime conditions detected by the tool during the analysis.
        //
        std::optional<std::forward_list<notification_struct>> toolExecutionNotifications = std::nullopt;

        //
        // A list of conditions detected by the tool that are relevant to the tool's configuration.
        //
        std::optional<std::forward_list<notification_struct>> toolConfigurationNotifications = std::nullopt;

        //
        // The reason for the process exit.
        //
        std::optional<std::string> exitCodeDescription = std::nullopt;

        //
        // The name of the signal that caused the process to exit.
        //
        std::optional<std::string> exitSignalName = std::nullopt;

        //
        // The numeric value of the signal that caused the process to exit.
        //
        std::optional<int64_t> exitSignalNumber = std::nullopt;

        //
        // The reason given by the operating system that the process failed to start.
        //
        std::optional<std::string> processStartFailureMessage = std::nullopt;

        //
        // Specifies whether the tool's execution completed successfully.
        //
        bool executionSuccessful;

        //
        // The machine that hosted the analysis tool run.
        //
        std::optional<std::string> machine = std::nullopt;

        //
        // The account that ran the analysis tool.
        //
        std::optional<std::string> account = std::nullopt;

        //
        // The process id for the analysis tool run.
        //
        std::optional<int64_t> processId = std::nullopt;

        //
        // An absolute URI specifying the location of the analysis tool's executable.
        //
        std::optional<artifact_location_struct> executableLocation = std::nullopt;

        //
        // The working directory for the analysis tool run.
        //
        std::optional<artifact_location_struct> workingDirectory = std::nullopt;

        //
        // The environment variables associated with the analysis tool process, expressed as key/value pairs.
        //
        std::optional<invocation_environment_variables_struct> environmentVariables = std::nullopt;

        //
        // A file containing the standard input stream to the process that was invoked.
        //
        std::optional<artifact_location_struct> stdin = std::nullopt;

        //
        // A file containing the standard output stream from the process that was invoked.
        //
        std::optional<artifact_location_struct> stdout = std::nullopt;

        //
        // A file containing the standard error stream from the process that was invoked.
        //
        std::optional<artifact_location_struct> stderr = std::nullopt;

        //
        // A file containing the interleaved standard output and standard error stream from the process that was invoked.
        //
        std::optional<artifact_location_struct> stdoutStderr = std::nullopt;

        //
        // Key/value pairs that provide additional information about the invocation.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const invocation_struct &);
    void from_json(const json &, invocation_struct &);

    //
    // Describes how a converter transformed the output of a static analysis tool from the analysis tool's native output format into the SARIF format.
    //
    struct conversion_struct {
        //
        // A tool object that describes the converter.
        //
        tool_struct tool;

        //
        // An invocation object that describes the invocation of the converter.
        //
        std::optional<invocation_struct> invocation = std::nullopt;

        //
        // The locations of the analysis tool's per-run log files.
        //
        std::optional<std::forward_list<artifact_location_struct>> analysisToolLogFiles = std::nullopt;

        //
        // Key/value pairs that provide additional information about the conversion.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const conversion_struct &);
    void from_json(const json &, conversion_struct &);

    //
    // Represents a directed edge in a graph.
    //
    struct edge_struct {
        //
        // A string that uniquely identifies the edge within its graph.
        //
        std::string id;

        //
        // A short description of the edge.
        //
        std::optional<message_struct> label = std::nullopt;

        //
        // Identifies the source node (the node at which the edge starts).
        //
        std::string sourceNodeId;

        //
        // Identifies the target node (the node at which the edge ends).
        //
        std::string targetNodeId;

        //
        // Key/value pairs that provide additional information about the edge.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const edge_struct &);
    void from_json(const json &, edge_struct &);

    //
    // The values of relevant expressions after the edge has been traversed.
    //
    struct edge_traversal_final_state_struct {
        std::unordered_map<std::string, multiformat_message_string_struct> additional_properties;
    };

    void to_json(json &, const edge_traversal_final_state_struct &);
    void from_json(const json &, edge_traversal_final_state_struct &);

    //
    // Represents the traversal of a single edge during a graph traversal.
    //
    struct edge_traversal_struct {
        //
        // Identifies the edge being traversed.
        //
        std::string edgeId;

        //
        // A message to display to the user as the edge is traversed.
        //
        std::optional<message_struct> message = std::nullopt;

        //
        // The values of relevant expressions after the edge has been traversed.
        //
        std::optional<edge_traversal_final_state_struct> finalState = std::nullopt;

        //
        // The number of edge traversals necessary to return from a nested graph.
        //
        std::optional<int64_t> stepOverEdgeCount = std::nullopt;

        //
        // Key/value pairs that provide additional information about the edge traversal.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const edge_traversal_struct &);
    void from_json(const json &, edge_traversal_struct &);
    struct stack_frame_struct;

    //
    // A call stack that is relevant to a result.
    //
    struct stack_struct {
        //
        // A message relevant to this call stack.
        //
        std::optional<message_struct> message = std::nullopt;

        //
        // An array of stack frames that represents a sequence of calls, rendered in reverse chronological order, that comprise the call stack.
        //
        std::forward_list<stack_frame_struct> frames;

        //
        // Key/value pairs that provide additional information about the stack.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const stack_struct &);
    void from_json(const json &, stack_struct &);
    struct exception_struct;

    //
    // Describes a runtime exception encountered during the execution of an analysis tool.
    //
    struct exception_struct {
        //
        // A string that identifies the kind of exception, for example, the fully qualified type name of an object that was thrown, or the symbolic name of a signal.
        //
        std::optional<std::string> kind = std::nullopt;

        //
        // A message that describes the exception.
        //
        std::optional<std::string> message = std::nullopt;

        //
        // The sequence of function calls leading to the exception.
        //
        std::optional<stack_struct> stack = std::nullopt;

        //
        // An array of exception objects each of which is considered a cause of this exception.
        //
        std::optional<std::forward_list<exception_struct>> innerExceptions = std::nullopt;

        //
        // Key/value pairs that provide additional information about the exception.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const exception_struct &);
    void from_json(const json &, exception_struct &);
    struct graph_struct;
    struct logical_location_struct;
    struct thread_flow_location_struct;
    struct result_struct;
    struct web_request_struct;
    struct web_response_struct;

    //
    // The top-level element of an external property file.
    //
    struct external_properties_struct {
        //
        // The URI of the JSON schema corresponding to the version of the external property file format.
        //
        std::optional<std::string> schema = std::nullopt;

        //
        // The SARIF format version of this external properties object.
        //
        std::optional<version_enum> version = std::nullopt;

        //
        // A stable, unique identifer for this external properties object, in the form of a GUID.
        //
        std::optional<std::string> guid = std::nullopt;

        //
        // A stable, unique identifer for the run associated with this external properties object, in the form of a GUID.
        //
        std::optional<std::string> runGuid = std::nullopt;

        //
        // A conversion object that will be merged with a separate run.
        //
        std::optional<conversion_struct> conversion = std::nullopt;

        //
        // An array of graph objects that will be merged with a separate run.
        //
        std::optional<std::forward_list<graph_struct>> graphs = std::nullopt;

        //
        // Key/value pairs that provide additional information that will be merged with a separate run.
        //
        std::optional<property_bag_struct> externalizedProperties = std::nullopt;

        //
        // An array of artifact objects that will be merged with a separate run.
        //
        std::optional<std::forward_list<artifact_struct>> artifacts = std::nullopt;

        //
        // Describes the invocation of the analysis tool that will be merged with a separate run.
        //
        std::optional<std::forward_list<invocation_struct>> invocations = std::nullopt;

        //
        // An array of logical locations such as namespaces, types or functions that will be merged with a separate run.
        //
        std::optional<std::forward_list<logical_location_struct>> logicalLocations = std::nullopt;

        //
        // An array of threadFlowLocation objects that will be merged with a separate run.
        //
        std::optional<std::forward_list<thread_flow_location_struct>> threadFlowLocations = std::nullopt;

        //
        // An array of result objects that will be merged with a separate run.
        //
        std::optional<std::forward_list<result_struct>> results = std::nullopt;

        //
        // Tool taxonomies that will be merged with a separate run.
        //
        std::optional<std::forward_list<tool_component_struct>> taxonomies = std::nullopt;

        //
        // The analysis tool object that will be merged with a separate run.
        //
        std::optional<tool_component_struct> driver = std::nullopt;

        //
        // Tool extensions that will be merged with a separate run.
        //
        std::optional<std::forward_list<tool_component_struct>> extensions = std::nullopt;

        //
        // Tool policies that will be merged with a separate run.
        //
        std::optional<std::forward_list<tool_component_struct>> policies = std::nullopt;

        //
        // Tool translations that will be merged with a separate run.
        //
        std::optional<std::forward_list<tool_component_struct>> translations = std::nullopt;

        //
        // Addresses that will be merged with a separate run.
        //
        std::optional<std::forward_list<address_struct>> addresses = std::nullopt;

        //
        // Requests that will be merged with a separate run.
        //
        std::optional<std::forward_list<web_request_struct>> webRequests = std::nullopt;

        //
        // Responses that will be merged with a separate run.
        //
        std::optional<std::forward_list<web_response_struct>> webResponses = std::nullopt;

        //
        // Key/value pairs that provide additional information about the external properties.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const external_properties_struct &);
    void from_json(const json &, external_properties_struct &);

    //
    // Contains information that enables a SARIF consumer to locate the external property file that contains the value of an externalized property associated with the run.
    //
    struct external_property_file_reference_struct {
        //
        // The location of the external property file.
        //
        std::optional<artifact_location_struct> location = std::nullopt;

        //
        // A stable, unique identifer for the external property file in the form of a GUID.
        //
        std::optional<std::string> guid = std::nullopt;

        //
        // A non-negative integer specifying the number of items contained in the external property file.
        //
        std::optional<int64_t> itemCount = std::nullopt;

        //
        // Key/value pairs that provide additional information about the external property file.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const external_property_file_reference_struct &);
    void from_json(const json &, external_property_file_reference_struct &);

    //
    // References to external property files that should be inlined with the content of a root log file.
    //
    struct external_property_file_references_struct {
        //
        // An external property file containing a run.conversion object to be merged with the root log file.
        //
        std::optional<external_property_file_reference_struct> conversion = std::nullopt;

        //
        // An array of external property files containing a run.graphs object to be merged with the root log file.
        //
        std::optional<std::forward_list<external_property_file_reference_struct>> graphs = std::nullopt;

        //
        // An external property file containing a run.properties object to be merged with the root log file.
        //
        std::optional<external_property_file_reference_struct> externalizedProperties = std::nullopt;

        //
        // An array of external property files containing run.artifacts arrays to be merged with the root log file.
        //
        std::optional<std::forward_list<external_property_file_reference_struct>> artifacts = std::nullopt;

        //
        // An array of external property files containing run.invocations arrays to be merged with the root log file.
        //
        std::optional<std::forward_list<external_property_file_reference_struct>> invocations = std::nullopt;

        //
        // An array of external property files containing run.logicalLocations arrays to be merged with the root log file.
        //
        std::optional<std::forward_list<external_property_file_reference_struct>> logicalLocations = std::nullopt;

        //
        // An array of external property files containing run.threadFlowLocations arrays to be merged with the root log file.
        //
        std::optional<std::forward_list<external_property_file_reference_struct>> threadFlowLocations = std::nullopt;

        //
        // An array of external property files containing run.results arrays to be merged with the root log file.
        //
        std::optional<std::forward_list<external_property_file_reference_struct>> results = std::nullopt;

        //
        // An array of external property files containing run.taxonomies arrays to be merged with the root log file.
        //
        std::optional<std::forward_list<external_property_file_reference_struct>> taxonomies = std::nullopt;

        //
        // An array of external property files containing run.addresses arrays to be merged with the root log file.
        //
        std::optional<std::forward_list<external_property_file_reference_struct>> addresses = std::nullopt;

        //
        // An external property file containing a run.driver object to be merged with the root log file.
        //
        std::optional<external_property_file_reference_struct> driver = std::nullopt;

        //
        // An array of external property files containing run.extensions arrays to be merged with the root log file.
        //
        std::optional<std::forward_list<external_property_file_reference_struct>> extensions = std::nullopt;

        //
        // An array of external property files containing run.policies arrays to be merged with the root log file.
        //
        std::optional<std::forward_list<external_property_file_reference_struct>> policies = std::nullopt;

        //
        // An array of external property files containing run.translations arrays to be merged with the root log file.
        //
        std::optional<std::forward_list<external_property_file_reference_struct>> translations = std::nullopt;

        //
        // An array of external property files containing run.requests arrays to be merged with the root log file.
        //
        std::optional<std::forward_list<external_property_file_reference_struct>> webRequests = std::nullopt;

        //
        // An array of external property files containing run.responses arrays to be merged with the root log file.
        //
        std::optional<std::forward_list<external_property_file_reference_struct>> webResponses = std::nullopt;

        //
        // Key/value pairs that provide additional information about the external property files.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const external_property_file_references_struct &);
    void from_json(const json &, external_property_file_references_struct &);

    //
    // A proposed fix for the problem represented by a result object. A fix specifies a set of artifacts to modify. For each artifact, it specifies a set of bytes to remove, and provides a set of new bytes to replace them.
    //
    struct fix_struct {
        //
        // A message that describes the proposed fix, enabling viewers to present the proposed change to an end user.
        //
        std::optional<message_struct> description = std::nullopt;

        //
        // One or more artifact changes that comprise a fix for a result.
        //
        std::forward_list<artifact_change_struct> artifactChanges;

        //
        // Key/value pairs that provide additional information about the fix.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const fix_struct &);
    void from_json(const json &, fix_struct &);
    struct node_struct;

    //
    // A network of nodes and directed edges that describes some aspect of the structure of the code (for example, a call graph).
    //
    struct graph_struct {
        //
        // A description of the graph.
        //
        std::optional<message_struct> description = std::nullopt;

        //
        // An array of node objects representing the nodes of the graph.
        //
        std::optional<std::forward_list<node_struct>> nodes = std::nullopt;

        //
        // An array of edge objects representing the edges of the graph.
        //
        std::optional<std::forward_list<edge_struct>> edges = std::nullopt;

        //
        // Key/value pairs that provide additional information about the graph.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const graph_struct &);
    void from_json(const json &, graph_struct &);

    //
    // Values of relevant expressions at the start of the graph traversal that may change during graph traversal.
    //
    struct graph_traversal_initial_state_struct {
        std::unordered_map<std::string, multiformat_message_string_struct> additional_properties;
    };

    void to_json(json &, const graph_traversal_initial_state_struct &);
    void from_json(const json &, graph_traversal_initial_state_struct &);

    //
    // Values of relevant expressions at the start of the graph traversal that remain constant for the graph traversal.
    //
    struct graph_traversal_immutable_state_struct {
        std::unordered_map<std::string, multiformat_message_string_struct> additional_properties;
    };

    void to_json(json &, const graph_traversal_immutable_state_struct &);
    void from_json(const json &, graph_traversal_immutable_state_struct &);

    //
    // Represents a path through a graph.
    //
    struct graph_traversal_struct {
        //
        // The index within the run.graphs to be associated with the result.
        //
        std::optional<int64_t> runGraphIndex = std::nullopt;

        //
        // The index within the result.graphs to be associated with the result.
        //
        std::optional<int64_t> resultGraphIndex = std::nullopt;

        //
        // A description of this graph traversal.
        //
        std::optional<message_struct> description = std::nullopt;

        //
        // Values of relevant expressions at the start of the graph traversal that may change during graph traversal.
        //
        std::optional<graph_traversal_initial_state_struct> initialState = std::nullopt;

        //
        // Values of relevant expressions at the start of the graph traversal that remain constant for the graph traversal.
        //
        std::optional<graph_traversal_immutable_state_struct> immutableState = std::nullopt;

        //
        // The sequences of edges traversed by this graph traversal.
        //
        std::optional<std::forward_list<edge_traversal_struct>> edgeTraversals = std::nullopt;

        //
        // Key/value pairs that provide additional information about the graph traversal.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const graph_traversal_struct &);
    void from_json(const json &, graph_traversal_struct &);

    //
    // A region within an artifact where a result was detected.
    //
    struct region_struct {
        //
        // The line number of the first character in the region.
        //
        std::optional<int64_t> startLine = std::nullopt;

        //
        // The column number of the first character in the region.
        //
        std::optional<int64_t> startColumn = std::nullopt;

        //
        // The line number of the last character in the region.
        //
        std::optional<int64_t> endLine = std::nullopt;

        //
        // The column number of the character following the end of the region.
        //
        std::optional<int64_t> endColumn = std::nullopt;

        //
        // The zero-based offset from the beginning of the artifact of the first character in the region.
        //
        std::optional<int64_t> charOffset = std::nullopt;

        //
        // The length of the region in characters.
        //
        std::optional<int64_t> charLength = std::nullopt;

        //
        // The zero-based offset from the beginning of the artifact of the first byte in the region.
        //
        std::optional<int64_t> byteOffset = std::nullopt;

        //
        // The length of the region in bytes.
        //
        std::optional<int64_t> byteLength = std::nullopt;

        //
        // The portion of the artifact contents within the specified region.
        //
        std::optional<artifact_content_struct> snippet = std::nullopt;

        //
        // A message relevant to the region.
        //
        std::optional<message_struct> message = std::nullopt;

        //
        // Specifies the source language, if any, of the portion of the artifact specified by the region object.
        //
        std::optional<std::string> sourceLanguage = std::nullopt;

        //
        // Key/value pairs that provide additional information about the region.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const region_struct &);
    void from_json(const json &, region_struct &);

    //
    // A physical location relevant to a result. Specifies a reference to a programming artifact together with a range of bytes or characters within that artifact.
    //
    struct physical_location_struct {
        //
        // The address of the location.
        //
        std::optional<address_struct> address = std::nullopt;

        //
        // The location of the artifact.
        //
        std::optional<artifact_location_struct> artifactLocation = std::nullopt;

        //
        // Specifies a portion of the artifact.
        //
        std::optional<region_struct> region = std::nullopt;

        //
        // Specifies a portion of the artifact that encloses the region. Allows a viewer to display additional context around the region.
        //
        std::optional<region_struct> contextRegion = std::nullopt;

        //
        // Key/value pairs that provide additional information about the physical location.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const physical_location_struct &);
    void from_json(const json &, physical_location_struct &);
    struct location_relationship_struct;

    //
    // A location within a programming artifact.
    //
    struct location_struct {
        //
        // Value that distinguishes this location from all other locations within a single result object.
        //
        std::optional<int64_t> id = std::nullopt;

        //
        // Identifies the artifact and region.
        //
        std::optional<physical_location_struct> physicalLocation = std::nullopt;

        //
        // The logical locations associated with the result.
        //
        std::optional<std::forward_list<logical_location_struct>> logicalLocations = std::nullopt;

        //
        // A message relevant to the location.
        //
        std::optional<message_struct> message = std::nullopt;

        //
        // A set of regions relevant to the location.
        //
        std::optional<std::forward_list<region_struct>> annotations = std::nullopt;

        //
        // An array of objects that describe relationships between this location and others.
        //
        std::optional<std::forward_list<location_relationship_struct>> relationships = std::nullopt;

        //
        // Key/value pairs that provide additional information about the location.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const location_struct &);
    void from_json(const json &, location_struct &);

    //
    // Information about the relation of one location to another.
    //
    struct location_relationship_struct {
        //
        // A reference to the related location.
        //
        int64_t target;

        //
        // A set of distinct strings that categorize the relationship. Well-known kinds include 'includes', 'isIncludedBy' and 'relevant'.
        //
        std::optional<std::forward_list<std::string>> kinds = std::nullopt;

        //
        // A description of the location relationship.
        //
        std::optional<message_struct> description = std::nullopt;

        //
        // Key/value pairs that provide additional information about the location relationship.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const location_relationship_struct &);
    void from_json(const json &, location_relationship_struct &);

    //
    // A logical location of a construct that produced a result.
    //
    struct logical_location_struct {
        //
        // Identifies the construct in which the result occurred. For example, this property might contain the name of a class or a method.
        //
        std::optional<std::string> name = std::nullopt;

        //
        // The index within the logical locations array.
        //
        std::optional<int64_t> index = std::nullopt;

        //
        // The human-readable fully qualified name of the logical location.
        //
        std::optional<std::string> fullyQualifiedName = std::nullopt;

        //
        // The machine-readable name for the logical location, such as a mangled function name provided by a C++ compiler that encodes calling convention, return type and other details along with the function name.
        //
        std::optional<std::string> decoratedName = std::nullopt;

        //
        // Identifies the index of the immediate parent of the construct in which the result was detected. For example, this property might point to a logical location that represents the namespace that holds a type.
        //
        std::optional<int64_t> parentIndex = std::nullopt;

        //
        // The type of construct this logical location component refers to. Should be one of 'function', 'member', 'module', 'namespace', 'parameter', 'resource', 'returnType', 'type', 'variable', 'object', 'array', 'property', 'value', 'element', 'text', 'attribute', 'comment', 'declaration', 'dtd' or 'processingInstruction', if any of those accurately describe the construct.
        //
        std::optional<std::string> kind = std::nullopt;

        //
        // Key/value pairs that provide additional information about the logical location.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const logical_location_struct &);
    void from_json(const json &, logical_location_struct &);

    //
    // Represents a node in a graph.
    //
    struct node_struct {
        //
        // A string that uniquely identifies the node within its graph.
        //
        std::string id;

        //
        // A short description of the node.
        //
        std::optional<message_struct> label = std::nullopt;

        //
        // A code location associated with the node.
        //
        std::optional<location_struct> location = std::nullopt;

        //
        // Array of child nodes.
        //
        std::optional<std::forward_list<node_struct>> children = std::nullopt;

        //
        // Key/value pairs that provide additional information about the node.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const node_struct &);
    void from_json(const json &, node_struct &);

    //
    // Describes a condition relevant to the tool itself, as opposed to being relevant to a target being analyzed by the tool.
    //
    struct notification_struct {
        //
        // The locations relevant to this notification.
        //
        std::optional<std::forward_list<location_struct>> locations = std::nullopt;

        //
        // A message that describes the condition that was encountered.
        //
        message_struct message;

        //
        // A value specifying the severity level of the notification.
        //
        std::optional<level_enum> level = std::nullopt;

        //
        // The thread identifier of the code that generated the notification.
        //
        std::optional<int64_t> threadId = std::nullopt;

        //
        // The Coordinated Universal Time (UTC) date and time at which the analysis tool generated the notification.
        //
        std::optional<std::string> timeUtc = std::nullopt;

        //
        // The runtime exception, if any, relevant to this notification.
        //
        std::optional<exception_struct> exception = std::nullopt;

        //
        // A reference used to locate the descriptor relevant to this notification.
        //
        std::optional<reporting_descriptor_reference_struct> descriptor = std::nullopt;

        //
        // A reference used to locate the rule descriptor associated with this notification.
        //
        std::optional<reporting_descriptor_reference_struct> associatedRule = std::nullopt;

        //
        // Key/value pairs that provide additional information about the notification.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const notification_struct &);
    void from_json(const json &, notification_struct &);

    //
    // An area within an image.
    //
    struct rectangle_struct {
        //
        // The Y coordinate of the top edge of the rectangle, measured in the image's natural units.
        //
        std::optional<double> top = std::nullopt;

        //
        // The X coordinate of the left edge of the rectangle, measured in the image's natural units.
        //
        std::optional<double> left = std::nullopt;

        //
        // The Y coordinate of the bottom edge of the rectangle, measured in the image's natural units.
        //
        std::optional<double> bottom = std::nullopt;

        //
        // The X coordinate of the right edge of the rectangle, measured in the image's natural units.
        //
        std::optional<double> right = std::nullopt;

        //
        // A message relevant to the rectangle.
        //
        std::optional<message_struct> message = std::nullopt;

        //
        // Key/value pairs that provide additional information about the rectangle.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const rectangle_struct &);
    void from_json(const json &, rectangle_struct &);

    //
    // The replacement of a single region of an artifact.
    //
    struct replacement_struct {
        //
        // The region of the artifact to delete.
        //
        region_struct deletedRegion;

        //
        // The content to insert at the location specified by the 'deletedRegion' property.
        //
        std::optional<artifact_content_struct> insertedContent = std::nullopt;

        //
        // Key/value pairs that provide additional information about the replacement.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const replacement_struct &);
    void from_json(const json &, replacement_struct &);

    //
    // A set of name/value pairs with arbitrary names. Each value is a multiformatMessageString object, which holds message strings in plain text and (optionally) Markdown format. The strings can include placeholders, which can be used to construct a message in combination with an arbitrary number of additional string arguments.
    //
    struct reporting_descriptor_message_strings_struct {
        std::unordered_map<std::string, multiformat_message_string_struct> additional_properties;
    };

    void to_json(json &, const reporting_descriptor_message_strings_struct &);
    void from_json(const json &, reporting_descriptor_message_strings_struct &);
    struct reporting_descriptor_relationship_struct;

    //
    // Metadata that describes a specific report produced by the tool, as part of the analysis it provides or its runtime reporting.
    //
    struct reporting_descriptor_struct {
        //
        // A stable, opaque identifier for the report.
        //
        std::string id;

        //
        // An array of stable, opaque identifiers by which this report was known in some previous version of the analysis tool.
        //
        std::optional<std::forward_list<std::string>> deprecatedIds = std::nullopt;

        //
        // A unique identifer for the reporting descriptor in the form of a GUID.
        //
        std::optional<std::string> guid = std::nullopt;

        //
        // An array of unique identifies in the form of a GUID by which this report was known in some previous version of the analysis tool.
        //
        std::optional<std::forward_list<std::string>> deprecatedGuids = std::nullopt;

        //
        // A report identifier that is understandable to an end user.
        //
        std::optional<std::string> name = std::nullopt;

        //
        // An array of readable identifiers by which this report was known in some previous version of the analysis tool.
        //
        std::optional<std::forward_list<std::string>> deprecatedNames = std::nullopt;

        //
        // A concise description of the report. Should be a single sentence that is understandable when visible space is limited to a single line of text.
        //
        std::optional<multiformat_message_string_struct> shortDescription = std::nullopt;

        //
        // A description of the report. Should, as far as possible, provide details sufficient to enable resolution of any problem indicated by the result.
        //
        std::optional<multiformat_message_string_struct> fullDescription = std::nullopt;

        //
        // A set of name/value pairs with arbitrary names. Each value is a multiformatMessageString object, which holds message strings in plain text and (optionally) Markdown format. The strings can include placeholders, which can be used to construct a message in combination with an arbitrary number of additional string arguments.
        //
        std::optional<reporting_descriptor_message_strings_struct> messageStrings = std::nullopt;

        //
        // Default reporting configuration information.
        //
        std::optional<reporting_configuration_struct> defaultConfiguration = std::nullopt;

        //
        // A URI where the primary documentation for the report can be found.
        //
        std::optional<std::string> helpUri = std::nullopt;

        //
        // Provides the primary documentation for the report, useful when there is no online documentation.
        //
        std::optional<multiformat_message_string_struct> help = std::nullopt;

        //
        // An array of objects that describe relationships between this reporting descriptor and others.
        //
        std::optional<std::forward_list<reporting_descriptor_relationship_struct>> relationships = std::nullopt;

        //
        // Key/value pairs that provide additional information about the report.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const reporting_descriptor_struct &);
    void from_json(const json &, reporting_descriptor_struct &);

    //
    // Information about the relation of one reporting descriptor to another.
    //
    struct reporting_descriptor_relationship_struct {
        //
        // A reference to the related reporting descriptor.
        //
        reporting_descriptor_reference_struct target;

        //
        // A set of distinct strings that categorize the relationship. Well-known kinds include 'canPrecede', 'canFollow', 'willPrecede', 'willFollow', 'superset', 'subset', 'equal', 'disjoint', 'relevant', and 'incomparable'.
        //
        std::optional<std::forward_list<std::string>> kinds = std::nullopt;

        //
        // A description of the reporting descriptor relationship.
        //
        std::optional<message_struct> description = std::nullopt;

        //
        // Key/value pairs that provide additional information about the reporting descriptor reference.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const reporting_descriptor_relationship_struct &);
    void from_json(const json &, reporting_descriptor_relationship_struct &);

    enum class kind_enum {
        kNotApplicable,
        kPass,
        kFail,
        kReview,
        kOpen,
        kInformational,
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(kind_enum, {
        { kind_enum::kNotApplicable, "notApplicable" },
        { kind_enum::kPass, "pass" },
        { kind_enum::kFail, "fail" },
        { kind_enum::kReview, "review" },
        { kind_enum::kOpen, "open" },
        { kind_enum::kInformational, "informational" },
    })

    //
    // A set of strings that contribute to the stable, unique identity of the result.
    //
    struct result_partial_fingerprints_struct {
        std::unordered_map<std::string, std::string> additional_properties;
    };

    void to_json(json &, const result_partial_fingerprints_struct &);
    void from_json(const json &, result_partial_fingerprints_struct &);

    //
    // A set of strings each of which individually defines a stable, unique identity for the result.
    //
    struct result_fingerprints_struct {
        std::unordered_map<std::string, std::string> additional_properties;
    };

    void to_json(json &, const result_fingerprints_struct &);
    void from_json(const json &, result_fingerprints_struct &);
    struct suppression_struct;

    enum class baseline_state_enum {
        kNew,
        kUnchanged,
        kUpdated,
        kAbsent,
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(baseline_state_enum, {
        { baseline_state_enum::kNew, "new" },
        { baseline_state_enum::kUnchanged, "unchanged" },
        { baseline_state_enum::kUpdated, "updated" },
        { baseline_state_enum::kAbsent, "absent" },
    })

    //
    // Contains information about how and when a result was detected.
    //
    struct result_provenance_struct {
        //
        // The Coordinated Universal Time (UTC) date and time at which the result was first detected. See "Date/time properties" in the SARIF spec for the required format.
        //
        std::optional<std::string> firstDetectionTimeUtc = std::nullopt;

        //
        // The Coordinated Universal Time (UTC) date and time at which the result was most recently detected. See "Date/time properties" in the SARIF spec for the required format.
        //
        std::optional<std::string> lastDetectionTimeUtc = std::nullopt;

        //
        // A GUID-valued string equal to the automationDetails.guid property of the run in which the result was first detected.
        //
        std::optional<std::string> firstDetectionRunGuid = std::nullopt;

        //
        // A GUID-valued string equal to the automationDetails.guid property of the run in which the result was most recently detected.
        //
        std::optional<std::string> lastDetectionRunGuid = std::nullopt;

        //
        // The index within the run.invocations array of the invocation object which describes the tool invocation that detected the result.
        //
        std::optional<int64_t> invocationIndex = std::nullopt;

        //
        // An array of physicalLocation objects which specify the portions of an analysis tool's output that a converter transformed into the result.
        //
        std::optional<std::forward_list<physical_location_struct>> conversionSources = std::nullopt;

        //
        // Key/value pairs that provide additional information about the result.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const result_provenance_struct &);
    void from_json(const json &, result_provenance_struct &);

    //
    // The request headers.
    //
    struct web_request_headers_struct {
        std::unordered_map<std::string, std::string> additional_properties;
    };

    void to_json(json &, const web_request_headers_struct &);
    void from_json(const json &, web_request_headers_struct &);

    //
    // The request parameters.
    //
    struct web_request_parameters_struct {
        std::unordered_map<std::string, std::string> additional_properties;
    };

    void to_json(json &, const web_request_parameters_struct &);
    void from_json(const json &, web_request_parameters_struct &);

    //
    // Describes an HTTP request.
    //
    struct web_request_struct {
        //
        // The index within the run.webRequests array of the request object associated with this result.
        //
        std::optional<int64_t> index = std::nullopt;

        //
        // The request protocol. Example: 'http'.
        //
        std::optional<std::string> protocol = std::nullopt;

        //
        // The request version. Example: '1.1'.
        //
        std::optional<std::string> version = std::nullopt;

        //
        // The target of the request.
        //
        std::optional<std::string> target = std::nullopt;

        //
        // The HTTP method. Well-known values are 'GET', 'PUT', 'POST', 'DELETE', 'PATCH', 'HEAD', 'OPTIONS', 'TRACE', 'CONNECT'.
        //
        std::optional<std::string> method = std::nullopt;

        //
        // The request headers.
        //
        std::optional<web_request_headers_struct> headers = std::nullopt;

        //
        // The request parameters.
        //
        std::optional<web_request_parameters_struct> parameters = std::nullopt;

        //
        // The body of the request.
        //
        std::optional<artifact_content_struct> body = std::nullopt;

        //
        // Key/value pairs that provide additional information about the request.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const web_request_struct &);
    void from_json(const json &, web_request_struct &);

    //
    // The response headers.
    //
    struct web_response_headers_struct {
        std::unordered_map<std::string, std::string> additional_properties;
    };

    void to_json(json &, const web_response_headers_struct &);
    void from_json(const json &, web_response_headers_struct &);

    //
    // Describes the response to an HTTP request.
    //
    struct web_response_struct {
        //
        // The index within the run.webResponses array of the response object associated with this result.
        //
        std::optional<int64_t> index = std::nullopt;

        //
        // The response protocol. Example: 'http'.
        //
        std::optional<std::string> protocol = std::nullopt;

        //
        // The response version. Example: '1.1'.
        //
        std::optional<std::string> version = std::nullopt;

        //
        // The response status code. Example: 451.
        //
        std::optional<int64_t> statusCode = std::nullopt;

        //
        // The response reason. Example: 'Not found'.
        //
        std::optional<std::string> reasonPhrase = std::nullopt;

        //
        // The response headers.
        //
        std::optional<web_response_headers_struct> headers = std::nullopt;

        //
        // The body of the response.
        //
        std::optional<artifact_content_struct> body = std::nullopt;

        //
        // Specifies whether a response was received from the server.
        //
        std::optional<bool> noResponseReceived = std::nullopt;

        //
        // Key/value pairs that provide additional information about the response.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const web_response_struct &);
    void from_json(const json &, web_response_struct &);

    //
    // A result produced by an analysis tool.
    //
    struct result_struct {
        //
        // The stable, unique identifier of the rule, if any, to which this notification is relevant. This member can be used to retrieve rule metadata from the rules dictionary, if it exists.
        //
        std::optional<std::string> ruleId = std::nullopt;

        //
        // The index within the tool component rules array of the rule object associated with this result.
        //
        std::optional<int64_t> ruleIndex = std::nullopt;

        //
        // A reference used to locate the rule descriptor relevant to this result.
        //
        std::optional<reporting_descriptor_reference_struct> rule = std::nullopt;

        //
        // A value that categorizes results by evaluation state.
        //
        std::optional<kind_enum> kind = std::nullopt;

        //
        // A value specifying the severity level of the result.
        //
        std::optional<level_enum> level = std::nullopt;

        //
        // A message that describes the result. The first sentence of the message only will be displayed when visible space is limited.
        //
        message_struct message;

        //
        // Identifies the artifact that the analysis tool was instructed to scan. This need not be the same as the artifact where the result actually occurred.
        //
        std::optional<artifact_location_struct> analysisTarget = std::nullopt;

        //
        // The set of locations where the result was detected. Specify only one location unless the problem indicated by the result can only be corrected by making a change at every specified location.
        //
        std::optional<std::forward_list<location_struct>> locations = std::nullopt;

        //
        // A stable, unique identifer for the result in the form of a GUID.
        //
        std::optional<std::string> guid = std::nullopt;

        //
        // A stable, unique identifier for the equivalence class of logically identical results to which this result belongs, in the form of a GUID.
        //
        std::optional<std::string> correlationGuid = std::nullopt;

        //
        // A positive integer specifying the number of times this logically unique result was observed in this run.
        //
        std::optional<int64_t> occurrenceCount = std::nullopt;

        //
        // A set of strings that contribute to the stable, unique identity of the result.
        //
        std::optional<result_partial_fingerprints_struct> partialFingerprints = std::nullopt;

        //
        // A set of strings each of which individually defines a stable, unique identity for the result.
        //
        std::optional<result_fingerprints_struct> fingerprints = std::nullopt;

        //
        // An array of 'stack' objects relevant to the result.
        //
        std::optional<std::forward_list<stack_struct>> stacks = std::nullopt;

        //
        // An array of 'codeFlow' objects relevant to the result.
        //
        std::optional<std::forward_list<code_flow_struct>> codeFlows = std::nullopt;

        //
        // An array of zero or more unique graph objects associated with the result.
        //
        std::optional<std::forward_list<graph_struct>> graphs = std::nullopt;

        //
        // An array of one or more unique 'graphTraversal' objects.
        //
        std::optional<std::forward_list<graph_traversal_struct>> graphTraversals = std::nullopt;

        //
        // A set of locations relevant to this result.
        //
        std::optional<std::forward_list<location_struct>> relatedLocations = std::nullopt;

        //
        // A set of suppressions relevant to this result.
        //
        std::optional<std::forward_list<suppression_struct>> suppressions = std::nullopt;

        //
        // The state of a result relative to a baseline of a previous run.
        //
        std::optional<baseline_state_enum> baselineState = std::nullopt;

        //
        // A number representing the priority or importance of the result.
        //
        std::optional<double> rank = std::nullopt;

        //
        // A set of artifacts relevant to the result.
        //
        std::optional<std::forward_list<attachment_struct>> attachments = std::nullopt;

        //
        // An absolute URI at which the result can be viewed.
        //
        std::optional<std::string> hostedViewerUri = std::nullopt;

        //
        // The URIs of the work items associated with this result.
        //
        std::optional<std::forward_list<std::string>> workItemUris = std::nullopt;

        //
        // Information about how and when the result was detected.
        //
        std::optional<result_provenance_struct> provenance = std::nullopt;

        //
        // An array of 'fix' objects, each of which represents a proposed fix to the problem indicated by the result.
        //
        std::optional<std::forward_list<fix_struct>> fixes = std::nullopt;

        //
        // An array of references to taxonomy reporting descriptors that are applicable to the result.
        //
        std::optional<std::forward_list<reporting_descriptor_reference_struct>> taxa = std::nullopt;

        //
        // A web request associated with this result.
        //
        std::optional<web_request_struct> webRequest = std::nullopt;

        //
        // A web response associated with this result.
        //
        std::optional<web_response_struct> webResponse = std::nullopt;

        //
        // Key/value pairs that provide additional information about the result.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const result_struct &);
    void from_json(const json &, result_struct &);
    struct version_control_details_struct;

    //
    // The artifact location specified by each uriBaseId symbol on the machine where the tool originally ran.
    //
    struct run_original_uri_base_ids_struct {
        std::unordered_map<std::string, artifact_location_struct> additional_properties;
    };

    void to_json(json &, const run_original_uri_base_ids_struct &);
    void from_json(const json &, run_original_uri_base_ids_struct &);

    //
    // Information that describes a run's identity and role within an engineering system process.
    //
    struct run_automation_details_struct {
        //
        // A description of the identity and role played within the engineering system by this object's containing run object.
        //
        std::optional<message_struct> description = std::nullopt;

        //
        // A hierarchical string that uniquely identifies this object's containing run object.
        //
        std::optional<std::string> id = std::nullopt;

        //
        // A stable, unique identifer for this object's containing run object in the form of a GUID.
        //
        std::optional<std::string> guid = std::nullopt;

        //
        // A stable, unique identifier for the equivalence class of runs to which this object's containing run object belongs in the form of a GUID.
        //
        std::optional<std::string> correlationGuid = std::nullopt;

        //
        // Key/value pairs that provide additional information about the run automation details.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const run_automation_details_struct &);
    void from_json(const json &, run_automation_details_struct &);

    enum class column_kind_enum {
        kUtf16CodeUnits,
        kUnicodeCodePoints,
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(column_kind_enum, {
        { column_kind_enum::kUtf16CodeUnits, "utf16CodeUnits" },
        { column_kind_enum::kUnicodeCodePoints, "unicodeCodePoints" },
    })

    //
    // Defines locations of special significance to SARIF consumers.
    //
    struct special_locations_struct {
        //
        // Provides a suggestion to SARIF consumers to display file paths relative to the specified location.
        //
        std::optional<artifact_location_struct> displayBase = std::nullopt;

        //
        // Key/value pairs that provide additional information about the special locations.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const special_locations_struct &);
    void from_json(const json &, special_locations_struct &);

    //
    // Describes a single run of an analysis tool, and contains the reported output of that run.
    //
    struct run_struct {
        //
        // Information about the tool or tool pipeline that generated the results in this run. A run can only contain results produced by a single tool or tool pipeline. A run can aggregate results from multiple log files, as long as context around the tool run (tool command-line arguments and the like) is identical for all aggregated files.
        //
        tool_struct tool;

        //
        // Describes the invocation of the analysis tool.
        //
        std::optional<std::forward_list<invocation_struct>> invocations = std::nullopt;

        //
        // A conversion object that describes how a converter transformed an analysis tool's native reporting format into the SARIF format.
        //
        std::optional<conversion_struct> conversion = std::nullopt;

        //
        // The language of the messages emitted into the log file during this run (expressed as an ISO 639-1 two-letter lowercase culture code) and an optional region (expressed as an ISO 3166-1 two-letter uppercase subculture code associated with a country or region). The casing is recommended but not required (in order for this data to conform to RFC5646).
        //
        std::optional<std::string> language = std::nullopt;

        //
        // Specifies the revision in version control of the artifacts that were scanned.
        //
        std::optional<std::forward_list<version_control_details_struct>> versionControlProvenance = std::nullopt;

        //
        // The artifact location specified by each uriBaseId symbol on the machine where the tool originally ran.
        //
        std::optional<run_original_uri_base_ids_struct> originalUriBaseIds = std::nullopt;

        //
        // An array of artifact objects relevant to the run.
        //
        std::optional<std::forward_list<artifact_struct>> artifacts = std::nullopt;

        //
        // An array of logical locations such as namespaces, types or functions.
        //
        std::optional<std::forward_list<logical_location_struct>> logicalLocations = std::nullopt;

        //
        // An array of zero or more unique graph objects associated with the run.
        //
        std::optional<std::forward_list<graph_struct>> graphs = std::nullopt;

        //
        // The set of results contained in an SARIF log. The results array can be omitted when a run is solely exporting rules metadata. It must be present (but may be empty) if a log file represents an actual scan.
        //
        std::optional<std::forward_list<result_struct>> results = std::nullopt;

        //
        // Automation details that describe this run.
        //
        std::optional<run_automation_details_struct> automationDetails = std::nullopt;

        //
        // Automation details that describe the aggregate of runs to which this run belongs.
        //
        std::optional<std::forward_list<run_automation_details_struct>> runAggregates = std::nullopt;

        //
        // The 'guid' property of a previous SARIF 'run' that comprises the baseline that was used to compute result 'baselineState' properties for the run.
        //
        std::optional<std::string> baselineGuid = std::nullopt;

        //
        // An array of strings used to replace sensitive information in a redaction-aware property.
        //
        std::optional<std::forward_list<std::string>> redactionTokens = std::nullopt;

        //
        // Specifies the default encoding for any artifact object that refers to a text file.
        //
        std::optional<std::string> defaultEncoding = std::nullopt;

        //
        // Specifies the default source language for any artifact object that refers to a text file that contains source code.
        //
        std::optional<std::string> defaultSourceLanguage = std::nullopt;

        //
        // An ordered list of character sequences that were treated as line breaks when computing region information for the run.
        //
        std::optional<std::forward_list<std::string>> newlineSequences = std::nullopt;

        //
        // Specifies the unit in which the tool measures columns.
        //
        std::optional<column_kind_enum> columnKind = std::nullopt;

        //
        // References to external property files that should be inlined with the content of a root log file.
        //
        std::optional<external_property_file_references_struct> externalPropertyFileReferences = std::nullopt;

        //
        // An array of threadFlowLocation objects cached at run level.
        //
        std::optional<std::forward_list<thread_flow_location_struct>> threadFlowLocations = std::nullopt;

        //
        // An array of toolComponent objects relevant to a taxonomy in which results are categorized.
        //
        std::optional<std::forward_list<tool_component_struct>> taxonomies = std::nullopt;

        //
        // Addresses associated with this run instance, if any.
        //
        std::optional<std::forward_list<address_struct>> addresses = std::nullopt;

        //
        // The set of available translations of the localized data provided by the tool.
        //
        std::optional<std::forward_list<tool_component_struct>> translations = std::nullopt;

        //
        // Contains configurations that may potentially override both reportingDescriptor.defaultConfiguration (the tool's default severities) and invocation.configurationOverrides (severities established at run-time from the command line).
        //
        std::optional<std::forward_list<tool_component_struct>> policies = std::nullopt;

        //
        // An array of request objects cached at run level.
        //
        std::optional<std::forward_list<web_request_struct>> webRequests = std::nullopt;

        //
        // An array of response objects cached at run level.
        //
        std::optional<std::forward_list<web_response_struct>> webResponses = std::nullopt;

        //
        // A specialLocations object that defines locations of special significance to SARIF consumers.
        //
        std::optional<special_locations_struct> specialLocations = std::nullopt;

        //
        // Key/value pairs that provide additional information about the run.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const run_struct &);
    void from_json(const json &, run_struct &);

    //
    // A function call within a stack trace.
    //
    struct stack_frame_struct {
        //
        // The location to which this stack frame refers.
        //
        std::optional<location_struct> location = std::nullopt;

        //
        // The name of the module that contains the code of this stack frame.
        //
        std::optional<std::string> module = std::nullopt;

        //
        // The thread identifier of the stack frame.
        //
        std::optional<int64_t> threadId = std::nullopt;

        //
        // The parameters of the call that is executing.
        //
        std::optional<std::forward_list<std::string>> parameters = std::nullopt;

        //
        // Key/value pairs that provide additional information about the stack frame.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const stack_frame_struct &);
    void from_json(const json &, stack_frame_struct &);

    enum class state_enum {
        kAccepted,
        kUnderReview,
        kRejected,
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(state_enum, {
        { state_enum::kAccepted, "accepted" },
        { state_enum::kUnderReview, "underReview" },
        { state_enum::kRejected, "rejected" },
    })

    //
    // A suppression that is relevant to a result.
    //
    struct suppression_struct {
        //
        // A stable, unique identifer for the suprression in the form of a GUID.
        //
        std::optional<std::string> guid = std::nullopt;

        //
        // A string that indicates where the suppression is persisted.
        //
        kind_enum kind;

        //
        // A string that indicates the state of the suppression.
        //
        std::optional<state_enum> state = std::nullopt;

        //
        // A string representing the justification for the suppression.
        //
        std::optional<std::string> justification = std::nullopt;

        //
        // Identifies the location associated with the suppression.
        //
        std::optional<location_struct> location = std::nullopt;

        //
        // Key/value pairs that provide additional information about the suppression.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const suppression_struct &);
    void from_json(const json &, suppression_struct &);

    //
    // Values of relevant expressions at the start of the thread flow that may change during thread flow execution.
    //
    struct thread_flow_initial_state_struct {
        std::unordered_map<std::string, multiformat_message_string_struct> additional_properties;
    };

    void to_json(json &, const thread_flow_initial_state_struct &);
    void from_json(const json &, thread_flow_initial_state_struct &);

    //
    // Values of relevant expressions at the start of the thread flow that remain constant.
    //
    struct thread_flow_immutable_state_struct {
        std::unordered_map<std::string, multiformat_message_string_struct> additional_properties;
    };

    void to_json(json &, const thread_flow_immutable_state_struct &);
    void from_json(const json &, thread_flow_immutable_state_struct &);

    //
    // Describes a sequence of code locations that specify a path through a single thread of execution such as an operating system or fiber.
    //
    struct thread_flow_struct {
        //
        // An string that uniquely identifies the threadFlow within the codeFlow in which it occurs.
        //
        std::optional<std::string> id = std::nullopt;

        //
        // A message relevant to the thread flow.
        //
        std::optional<message_struct> message = std::nullopt;

        //
        // Values of relevant expressions at the start of the thread flow that may change during thread flow execution.
        //
        std::optional<thread_flow_initial_state_struct> initialState = std::nullopt;

        //
        // Values of relevant expressions at the start of the thread flow that remain constant.
        //
        std::optional<thread_flow_immutable_state_struct> immutableState = std::nullopt;

        //
        // A temporally ordered array of 'threadFlowLocation' objects, each of which describes a location visited by the tool while producing the result.
        //
        std::forward_list<thread_flow_location_struct> locations;

        //
        // Key/value pairs that provide additional information about the thread flow.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const thread_flow_struct &);
    void from_json(const json &, thread_flow_struct &);

    //
    // A dictionary, each of whose keys specifies a variable or expression, the associated value of which represents the variable or expression value. For an annotation of kind 'continuation', for example, this dictionary might hold the current assumed values of a set of global variables.
    //
    struct thread_flow_location_state_struct {
        std::unordered_map<std::string, multiformat_message_string_struct> additional_properties;
    };

    void to_json(json &, const thread_flow_location_state_struct &);
    void from_json(const json &, thread_flow_location_state_struct &);

    enum class importance_enum {
        kImportant,
        kEssential,
        kUnimportant,
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(importance_enum, {
        { importance_enum::kImportant, "important" },
        { importance_enum::kEssential, "essential" },
        { importance_enum::kUnimportant, "unimportant" },
    })

    //
    // A location visited by an analysis tool while simulating or monitoring the execution of a program.
    //
    struct thread_flow_location_struct {
        //
        // The index within the run threadFlowLocations array.
        //
        std::optional<int64_t> index = std::nullopt;

        //
        // The code location.
        //
        std::optional<location_struct> location = std::nullopt;

        //
        // The call stack leading to this location.
        //
        std::optional<stack_struct> stack = std::nullopt;

        //
        // A set of distinct strings that categorize the thread flow location. Well-known kinds include 'acquire', 'release', 'enter', 'exit', 'call', 'return', 'branch', 'implicit', 'false', 'true', 'caution', 'danger', 'unknown', 'unreachable', 'taint', 'function', 'handler', 'lock', 'memory', 'resource', 'scope' and 'value'.
        //
        std::optional<std::forward_list<std::string>> kinds = std::nullopt;

        //
        // An array of references to rule or taxonomy reporting descriptors that are applicable to the thread flow location.
        //
        std::optional<std::forward_list<reporting_descriptor_reference_struct>> taxa = std::nullopt;

        //
        // The name of the module that contains the code that is executing.
        //
        std::optional<std::string> module = std::nullopt;

        //
        // A dictionary, each of whose keys specifies a variable or expression, the associated value of which represents the variable or expression value. For an annotation of kind 'continuation', for example, this dictionary might hold the current assumed values of a set of global variables.
        //
        std::optional<thread_flow_location_state_struct> state = std::nullopt;

        //
        // An integer representing a containment hierarchy within the thread flow.
        //
        std::optional<int64_t> nestingLevel = std::nullopt;

        //
        // An integer representing the temporal order in which execution reached this location.
        //
        std::optional<int64_t> executionOrder = std::nullopt;

        //
        // The Coordinated Universal Time (UTC) date and time at which this location was executed.
        //
        std::optional<std::string> executionTimeUtc = std::nullopt;

        //
        // Specifies the importance of this location in understanding the code flow in which it occurs. The order from most to least important is "essential", "important", "unimportant". Default: "important".
        //
        std::optional<importance_enum> importance = std::nullopt;

        //
        // A web request associated with this thread flow location.
        //
        std::optional<web_request_struct> webRequest = std::nullopt;

        //
        // A web response associated with this thread flow location.
        //
        std::optional<web_response_struct> webResponse = std::nullopt;

        //
        // Key/value pairs that provide additional information about the threadflow location.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const thread_flow_location_struct &);
    void from_json(const json &, thread_flow_location_struct &);

    //
    // Specifies the information necessary to retrieve a desired revision from a version control system.
    //
    struct version_control_details_struct {
        //
        // The absolute URI of the repository.
        //
        std::string repositoryUri;

        //
        // A string that uniquely and permanently identifies the revision within the repository.
        //
        std::optional<std::string> revisionId = std::nullopt;

        //
        // The name of a branch containing the revision.
        //
        std::optional<std::string> branch = std::nullopt;

        //
        // A tag that has been applied to the revision.
        //
        std::optional<std::string> revisionTag = std::nullopt;

        //
        // A Coordinated Universal Time (UTC) date and time that can be used to synchronize an enlistment to the state of the repository at that time.
        //
        std::optional<std::string> asOfTimeUtc = std::nullopt;

        //
        // The location in the local file system to which the root of the repository was mapped at the time of the analysis.
        //
        std::optional<artifact_location_struct> mappedTo = std::nullopt;

        //
        // Key/value pairs that provide additional information about the version control details.
        //
        std::optional<property_bag_struct> properties = std::nullopt;
    };

    void to_json(json &, const version_control_details_struct &);
    void from_json(const json &, version_control_details_struct &);
} // namespace gap::sarif::definitions