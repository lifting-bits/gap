// Copyright 2024-present, Trail of Bits, Inc.

#pragma once

//
// These definitions were generated from a JSON Schema description of SARIF
// found at https://github.com/microsoft/sarif-python-om/blob/7a84e8c2b2b9d8b9a8d25b1d376f039a0bf92a7c/sarif-schema-2.1.0.json
//
// The naming convention used is to convert all of the definition names from camelCase to snake_case,
// suffixed with either _struct or _enum depending on the kind.
// "Nested" definitions are prefixed by the name of the parent definition, for example the `headers`
// property of the `webRequest` definition is called web_request_headers_struct, in order to
// distinguish it from the `headers` property of the `webResponse` definition.
// Property names are kept as-is.
//
// Enum value names are converted from camelCase to PascalCase and prefixed with `k`.
//

#include <cstdint>
#include <forward_list>
#include <optional>
#include <string>
#include <unordered_map>

#include <nlohmann/json.hpp>

namespace gap::sarif
{
    using json = nlohmann::json;

    enum class version {
        k2_1_0,
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(version, {
        { version::k2_1_0, "2.1.0" },
    })
    struct run;
    struct external_properties;

    //
    // Key/value pairs that provide additional information about the object.
    //
    struct property_bag {
        //
        // A set of distinct strings that provide additional information.
        //
        std::optional< std::forward_list< std::string > > tags = std::nullopt;

        json additional_properties;
    };

    void to_json(json &, const property_bag &);
    void from_json(const json &, property_bag &);

    //
    // Static Analysis Results Format (SARIF) Version 2.1.0 JSON Schema: a standard format for the output of static analysis tools.
    //
    struct root {
        //
        // The SARIF format version of this log file.
        //
        version version;

        //
        // The set of runs contained in this log file.
        //
        std::forward_list< run > runs;

        //
        // References to external property files that share data between runs.
        //
        std::optional< std::forward_list< external_properties > > inlineExternalProperties = std::nullopt;

        //
        // Key/value pairs that provide additional information about the log file.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const root &);
    void from_json(const json &, root &);

    //
    // A physical or virtual address, or a range of addresses, in an 'addressable region' (memory or a binary file).
    //
    struct address {
        //
        // The address expressed as a byte offset from the start of the addressable region.
        //
        std::optional< int64_t > absoluteAddress = std::nullopt;

        //
        // The address expressed as a byte offset from the absolute address of the top-most parent object.
        //
        std::optional< int64_t > relativeAddress = std::nullopt;

        //
        // The number of bytes in this range of addresses.
        //
        std::optional< int64_t > length = std::nullopt;

        //
        // An open-ended string that identifies the address kind. 'data', 'function', 'header','instruction', 'module', 'page', 'section', 'segment', 'stack', 'stackFrame', 'table' are well-known values.
        //
        std::optional< std::string > kind = std::nullopt;

        //
        // A name that is associated with the address, e.g., '.text'.
        //
        std::optional< std::string > name = std::nullopt;

        //
        // A human-readable fully qualified name that is associated with the address.
        //
        std::optional< std::string > fullyQualifiedName = std::nullopt;

        //
        // The byte offset of this address from the absolute or relative address of the parent object.
        //
        std::optional< int64_t > offsetFromParent = std::nullopt;

        //
        // The index within run.addresses of the cached object for this address.
        //
        std::optional< int64_t > index = std::nullopt;

        //
        // The index within run.addresses of the parent object.
        //
        std::optional< int64_t > parentIndex = std::nullopt;

        //
        // Key/value pairs that provide additional information about the address.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const address &);
    void from_json(const json &, address &);

    //
    // Encapsulates a message intended to be read by the end user.
    //
    struct message {
        //
        // A plain text message string.
        //
        std::optional< std::string > text = std::nullopt;

        //
        // A Markdown message string.
        //
        std::optional< std::string > markdown = std::nullopt;

        //
        // The identifier for this message.
        //
        std::optional< std::string > id = std::nullopt;

        //
        // An array of strings to substitute into the message string.
        //
        std::optional< std::forward_list< std::string > > arguments = std::nullopt;

        //
        // Key/value pairs that provide additional information about the message.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const message &);
    void from_json(const json &, message &);

    //
    // Specifies the location of an artifact.
    //
    struct artifact_location {
        //
        // A string containing a valid relative or absolute URI.
        //
        std::optional< std::string > uri = std::nullopt;

        //
        // A string which indirectly specifies the absolute URI with respect to which a relative URI in the "uri" property is interpreted.
        //
        std::optional< std::string > uriBaseId = std::nullopt;

        //
        // The index within the run artifacts array of the artifact object associated with the artifact location.
        //
        std::optional< int64_t > index = std::nullopt;

        //
        // A short description of the artifact location.
        //
        std::optional< message > description = std::nullopt;

        //
        // Key/value pairs that provide additional information about the artifact location.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const artifact_location &);
    void from_json(const json &, artifact_location &);

    enum class roles {
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

    NLOHMANN_JSON_SERIALIZE_ENUM(roles, {
        { roles::kAnalysisTarget, "analysisTarget" },
        { roles::kAttachment, "attachment" },
        { roles::kResponseFile, "responseFile" },
        { roles::kResultFile, "resultFile" },
        { roles::kStandardStream, "standardStream" },
        { roles::kTracedFile, "tracedFile" },
        { roles::kUnmodified, "unmodified" },
        { roles::kModified, "modified" },
        { roles::kAdded, "added" },
        { roles::kDeleted, "deleted" },
        { roles::kRenamed, "renamed" },
        { roles::kUncontrolled, "uncontrolled" },
        { roles::kDriver, "driver" },
        { roles::kExtension, "extension" },
        { roles::kTranslation, "translation" },
        { roles::kTaxonomy, "taxonomy" },
        { roles::kPolicy, "policy" },
        { roles::kReferencedOnCommandLine, "referencedOnCommandLine" },
        { roles::kMemoryContents, "memoryContents" },
        { roles::kDirectory, "directory" },
        { roles::kUserSpecifiedConfiguration, "userSpecifiedConfiguration" },
        { roles::kToolSpecifiedConfiguration, "toolSpecifiedConfiguration" },
        { roles::kDebugOutputFile, "debugOutputFile" },
    })

    //
    // A message string or message format string rendered in multiple formats.
    //
    struct multiformat_message_string {
        //
        // A plain text message string or format string.
        //
        std::string text;

        //
        // A Markdown message string or format string.
        //
        std::optional< std::string > markdown = std::nullopt;

        //
        // Key/value pairs that provide additional information about the message.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const multiformat_message_string &);
    void from_json(const json &, multiformat_message_string &);

    //
    // Represents the contents of an artifact.
    //
    struct artifact_content {
        //
        // UTF-8-encoded content from a text artifact.
        //
        std::optional< std::string > text = std::nullopt;

        //
        // MIME Base64-encoded content from a binary artifact, or from a text artifact in its original encoding.
        //
        std::optional< std::string > binary = std::nullopt;

        //
        // An alternate rendered representation of the artifact (e.g., a decompiled representation of a binary region).
        //
        std::optional< multiformat_message_string > rendered = std::nullopt;

        //
        // Key/value pairs that provide additional information about the artifact content.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const artifact_content &);
    void from_json(const json &, artifact_content &);

    //
    // A single artifact. In some cases, this artifact might be nested within another artifact.
    //
    struct artifact {
        //
        // A short description of the artifact.
        //
        std::optional< message > description = std::nullopt;

        //
        // The location of the artifact.
        //
        std::optional< artifact_location > location = std::nullopt;

        //
        // Identifies the index of the immediate parent of the artifact, if this artifact is nested.
        //
        std::optional< int64_t > parentIndex = std::nullopt;

        //
        // The offset in bytes of the artifact within its containing artifact.
        //
        std::optional< int64_t > offset = std::nullopt;

        //
        // The length of the artifact in bytes.
        //
        std::optional< int64_t > length = std::nullopt;

        //
        // The role or roles played by the artifact in the analysis.
        //
        std::optional< std::forward_list< roles > > roles = std::nullopt;

        //
        // The MIME type (RFC 2045) of the artifact.
        //
        std::optional< std::string > mimeType = std::nullopt;

        //
        // The contents of the artifact.
        //
        std::optional< artifact_content > contents = std::nullopt;

        //
        // Specifies the encoding for an artifact object that refers to a text file.
        //
        std::optional< std::string > encoding = std::nullopt;

        //
        // Specifies the source language for any artifact object that refers to a text file that contains source code.
        //
        std::optional< std::string > sourceLanguage = std::nullopt;

        //
        // A dictionary, each of whose keys is the name of a hash function and each of whose values is the hashed value of the artifact produced by the specified hash function.
        //
        std::optional< std::unordered_map< std::string, std::string > > hashes = std::nullopt;

        //
        // The Coordinated Universal Time (UTC) date and time at which the artifact was most recently modified. See "Date/time properties" in the SARIF spec for the required format.
        //
        std::optional< std::string > lastModifiedTimeUtc = std::nullopt;

        //
        // Key/value pairs that provide additional information about the artifact.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const artifact &);
    void from_json(const json &, artifact &);
    struct replacement;

    //
    // A change to a single artifact.
    //
    struct artifact_change {
        //
        // The location of the artifact to change.
        //
        artifact_location artifactLocation;

        //
        // An array of replacement objects, each of which represents the replacement of a single region in a single artifact specified by 'artifactLocation'.
        //
        std::forward_list< replacement > replacements;

        //
        // Key/value pairs that provide additional information about the change.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const artifact_change &);
    void from_json(const json &, artifact_change &);
    struct region;
    struct rectangle;

    //
    // An artifact relevant to a result.
    //
    struct attachment {
        //
        // A message describing the role played by the attachment.
        //
        std::optional< message > description = std::nullopt;

        //
        // The location of the attachment.
        //
        artifact_location artifactLocation;

        //
        // An array of regions of interest within the attachment.
        //
        std::optional< std::forward_list< region > > regions = std::nullopt;

        //
        // An array of rectangles specifying areas of interest within the image.
        //
        std::optional< std::forward_list< rectangle > > rectangles = std::nullopt;

        //
        // Key/value pairs that provide additional information about the attachment.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const attachment &);
    void from_json(const json &, attachment &);
    struct thread_flow;

    //
    // A set of threadFlows which together describe a pattern of code execution relevant to detecting a result.
    //
    struct code_flow {
        //
        // A message relevant to the code flow.
        //
        std::optional< message > message = std::nullopt;

        //
        // An array of one or more unique threadFlow objects, each of which describes the progress of a program through a thread of execution.
        //
        std::forward_list< thread_flow > threadFlows;

        //
        // Key/value pairs that provide additional information about the code flow.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const code_flow &);
    void from_json(const json &, code_flow &);

    enum class level {
        kNone,
        kNote,
        kWarning,
        kError,
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(level, {
        { level::kNone, "none" },
        { level::kNote, "note" },
        { level::kWarning, "warning" },
        { level::kError, "error" },
    })

    //
    // Information about a rule or notification that can be configured at runtime.
    //
    struct reporting_configuration {
        //
        // Specifies whether the report may be produced during the scan.
        //
        std::optional< bool > enabled = std::nullopt;

        //
        // Specifies the failure level for the report.
        //
        std::optional< level > level = std::nullopt;

        //
        // Specifies the relative priority of the report. Used for analysis output only.
        //
        std::optional< double > rank = std::nullopt;

        //
        // Contains configuration information specific to a report.
        //
        std::optional< property_bag > parameters = std::nullopt;

        //
        // Key/value pairs that provide additional information about the reporting configuration.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const reporting_configuration &);
    void from_json(const json &, reporting_configuration &);

    //
    // Identifies a particular toolComponent object, either the driver or an extension.
    //
    struct tool_component_reference {
        //
        // The 'name' property of the referenced toolComponent.
        //
        std::optional< std::string > name = std::nullopt;

        //
        // An index into the referenced toolComponent in tool.extensions.
        //
        std::optional< int64_t > index = std::nullopt;

        //
        // The 'guid' property of the referenced toolComponent.
        //
        std::optional< std::string > guid = std::nullopt;

        //
        // Key/value pairs that provide additional information about the toolComponentReference.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const tool_component_reference &);
    void from_json(const json &, tool_component_reference &);

    //
    // Information about how to locate a relevant reporting descriptor.
    //
    struct reporting_descriptor_reference {
        //
        // The id of the descriptor.
        //
        std::optional< std::string > id = std::nullopt;

        //
        // The index into an array of descriptors in toolComponent.ruleDescriptors, toolComponent.notificationDescriptors, or toolComponent.taxonomyDescriptors, depending on context.
        //
        std::optional< int64_t > index = std::nullopt;

        //
        // A guid that uniquely identifies the descriptor.
        //
        std::optional< std::string > guid = std::nullopt;

        //
        // A reference used to locate the toolComponent associated with the descriptor.
        //
        std::optional< tool_component_reference > toolComponent = std::nullopt;

        //
        // Key/value pairs that provide additional information about the reporting descriptor reference.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const reporting_descriptor_reference &);
    void from_json(const json &, reporting_descriptor_reference &);

    //
    // Information about how a specific rule or notification was reconfigured at runtime.
    //
    struct configuration_override {
        //
        // Specifies how the rule or notification was configured during the scan.
        //
        reporting_configuration configuration;

        //
        // A reference used to locate the descriptor whose configuration was overridden.
        //
        reporting_descriptor_reference descriptor;

        //
        // Key/value pairs that provide additional information about the configuration override.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const configuration_override &);
    void from_json(const json &, configuration_override &);
    struct reporting_descriptor;

    enum class contents {
        kLocalizedData,
        kNonLocalizedData,
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(contents, {
        { contents::kLocalizedData, "localizedData" },
        { contents::kNonLocalizedData, "nonLocalizedData" },
    })

    //
    // Provides additional metadata related to translation.
    //
    struct translation_metadata {
        //
        // The name associated with the translation metadata.
        //
        std::string name;

        //
        // The full name associated with the translation metadata.
        //
        std::optional< std::string > fullName = std::nullopt;

        //
        // A brief description of the translation metadata.
        //
        std::optional< multiformat_message_string > shortDescription = std::nullopt;

        //
        // A comprehensive description of the translation metadata.
        //
        std::optional< multiformat_message_string > fullDescription = std::nullopt;

        //
        // The absolute URI from which the translation metadata can be downloaded.
        //
        std::optional< std::string > downloadUri = std::nullopt;

        //
        // The absolute URI from which information related to the translation metadata can be downloaded.
        //
        std::optional< std::string > informationUri = std::nullopt;

        //
        // Key/value pairs that provide additional information about the translation metadata.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const translation_metadata &);
    void from_json(const json &, translation_metadata &);

    //
    // A component, such as a plug-in or the driver, of the analysis tool that was run.
    //
    struct tool_component {
        //
        // A unique identifer for the tool component in the form of a GUID.
        //
        std::optional< std::string > guid = std::nullopt;

        //
        // The name of the tool component.
        //
        std::string name;

        //
        // The organization or company that produced the tool component.
        //
        std::optional< std::string > organization = std::nullopt;

        //
        // A product suite to which the tool component belongs.
        //
        std::optional< std::string > product = std::nullopt;

        //
        // A localizable string containing the name of the suite of products to which the tool component belongs.
        //
        std::optional< std::string > productSuite = std::nullopt;

        //
        // A brief description of the tool component.
        //
        std::optional< multiformat_message_string > shortDescription = std::nullopt;

        //
        // A comprehensive description of the tool component.
        //
        std::optional< multiformat_message_string > fullDescription = std::nullopt;

        //
        // The name of the tool component along with its version and any other useful identifying information, such as its locale.
        //
        std::optional< std::string > fullName = std::nullopt;

        //
        // The tool component version, in whatever format the component natively provides.
        //
        std::optional< std::string > version = std::nullopt;

        //
        // The tool component version in the format specified by Semantic Versioning 2.0.
        //
        std::optional< std::string > semanticVersion = std::nullopt;

        //
        // The binary version of the tool component's primary executable file expressed as four non-negative integers separated by a period (for operating systems that express file versions in this way).
        //
        std::optional< std::string > dottedQuadFileVersion = std::nullopt;

        //
        // A string specifying the UTC date (and optionally, the time) of the component's release.
        //
        std::optional< std::string > releaseDateUtc = std::nullopt;

        //
        // The absolute URI from which the tool component can be downloaded.
        //
        std::optional< std::string > downloadUri = std::nullopt;

        //
        // The absolute URI at which information about this version of the tool component can be found.
        //
        std::optional< std::string > informationUri = std::nullopt;

        //
        // A dictionary, each of whose keys is a resource identifier and each of whose values is a multiformatMessageString object, which holds message strings in plain text and (optionally) Markdown format. The strings can include placeholders, which can be used to construct a message in combination with an arbitrary number of additional string arguments.
        //
        std::optional< std::unordered_map< std::string, multiformat_message_string > > globalMessageStrings = std::nullopt;

        //
        // An array of reportingDescriptor objects relevant to the notifications related to the configuration and runtime execution of the tool component.
        //
        std::optional< std::forward_list< reporting_descriptor > > notifications = std::nullopt;

        //
        // An array of reportingDescriptor objects relevant to the analysis performed by the tool component.
        //
        std::optional< std::forward_list< reporting_descriptor > > rules = std::nullopt;

        //
        // An array of reportingDescriptor objects relevant to the definitions of both standalone and tool-defined taxonomies.
        //
        std::optional< std::forward_list< reporting_descriptor > > taxa = std::nullopt;

        //
        // An array of the artifactLocation objects associated with the tool component.
        //
        std::optional< std::forward_list< artifact_location > > locations = std::nullopt;

        //
        // The language of the messages emitted into the log file during this run (expressed as an ISO 639-1 two-letter lowercase language code) and an optional region (expressed as an ISO 3166-1 two-letter uppercase subculture code associated with a country or region). The casing is recommended but not required (in order for this data to conform to RFC5646).
        //
        std::optional< std::string > language = std::nullopt;

        //
        // The kinds of data contained in this object.
        //
        std::optional< std::forward_list< contents > > contents = std::nullopt;

        //
        // Specifies whether this object contains a complete definition of the localizable and/or non-localizable data for this component, as opposed to including only data that is relevant to the results persisted to this log file.
        //
        std::optional< bool > isComprehensive = std::nullopt;

        //
        // The semantic version of the localized strings defined in this component; maintained by components that provide translations.
        //
        std::optional< std::string > localizedDataSemanticVersion = std::nullopt;

        //
        // The minimum value of localizedDataSemanticVersion required in translations consumed by this component; used by components that consume translations.
        //
        std::optional< std::string > minimumRequiredLocalizedDataSemanticVersion = std::nullopt;

        //
        // The component which is strongly associated with this component. For a translation, this refers to the component which has been translated. For an extension, this is the driver that provides the extension's plugin model.
        //
        std::optional< tool_component_reference > associatedComponent = std::nullopt;

        //
        // Translation metadata, required for a translation, not populated by other component types.
        //
        std::optional< translation_metadata > translationMetadata = std::nullopt;

        //
        // An array of toolComponentReference objects to declare the taxonomies supported by the tool component.
        //
        std::optional< std::forward_list< tool_component_reference > > supportedTaxonomies = std::nullopt;

        //
        // Key/value pairs that provide additional information about the tool component.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const tool_component &);
    void from_json(const json &, tool_component &);

    //
    // The analysis tool that was run.
    //
    struct tool {
        //
        // The analysis tool that was run.
        //
        tool_component driver;

        //
        // Tool extensions that contributed to or reconfigured the analysis tool that was run.
        //
        std::optional< std::forward_list< tool_component > > extensions = std::nullopt;

        //
        // Key/value pairs that provide additional information about the tool.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const tool &);
    void from_json(const json &, tool &);
    struct notification;

    //
    // The runtime environment of the analysis tool run.
    //
    struct invocation {
        //
        // The command line used to invoke the tool.
        //
        std::optional< std::string > commandLine = std::nullopt;

        //
        // An array of strings, containing in order the command line arguments passed to the tool from the operating system.
        //
        std::optional< std::forward_list< std::string > > arguments = std::nullopt;

        //
        // The locations of any response files specified on the tool's command line.
        //
        std::optional< std::forward_list< artifact_location > > responseFiles = std::nullopt;

        //
        // The Coordinated Universal Time (UTC) date and time at which the run started. See "Date/time properties" in the SARIF spec for the required format.
        //
        std::optional< std::string > startTimeUtc = std::nullopt;

        //
        // The Coordinated Universal Time (UTC) date and time at which the run ended. See "Date/time properties" in the SARIF spec for the required format.
        //
        std::optional< std::string > endTimeUtc = std::nullopt;

        //
        // The process exit code.
        //
        std::optional< int64_t > exitCode = std::nullopt;

        //
        // An array of configurationOverride objects that describe rules related runtime overrides.
        //
        std::optional< std::forward_list< configuration_override > > ruleConfigurationOverrides = std::nullopt;

        //
        // An array of configurationOverride objects that describe notifications related runtime overrides.
        //
        std::optional< std::forward_list< configuration_override > > notificationConfigurationOverrides = std::nullopt;

        //
        // A list of runtime conditions detected by the tool during the analysis.
        //
        std::optional< std::forward_list< notification > > toolExecutionNotifications = std::nullopt;

        //
        // A list of conditions detected by the tool that are relevant to the tool's configuration.
        //
        std::optional< std::forward_list< notification > > toolConfigurationNotifications = std::nullopt;

        //
        // The reason for the process exit.
        //
        std::optional< std::string > exitCodeDescription = std::nullopt;

        //
        // The name of the signal that caused the process to exit.
        //
        std::optional< std::string > exitSignalName = std::nullopt;

        //
        // The numeric value of the signal that caused the process to exit.
        //
        std::optional< int64_t > exitSignalNumber = std::nullopt;

        //
        // The reason given by the operating system that the process failed to start.
        //
        std::optional< std::string > processStartFailureMessage = std::nullopt;

        //
        // Specifies whether the tool's execution completed successfully.
        //
        bool executionSuccessful;

        //
        // The machine that hosted the analysis tool run.
        //
        std::optional< std::string > machine = std::nullopt;

        //
        // The account that ran the analysis tool.
        //
        std::optional< std::string > account = std::nullopt;

        //
        // The process id for the analysis tool run.
        //
        std::optional< int64_t > processId = std::nullopt;

        //
        // An absolute URI specifying the location of the analysis tool's executable.
        //
        std::optional< artifact_location > executableLocation = std::nullopt;

        //
        // The working directory for the analysis tool run.
        //
        std::optional< artifact_location > workingDirectory = std::nullopt;

        //
        // The environment variables associated with the analysis tool process, expressed as key/value pairs.
        //
        std::optional< std::unordered_map< std::string, std::string > > environmentVariables = std::nullopt;

        //
        // A file containing the standard input stream to the process that was invoked.
        //
        std::optional< artifact_location > stdin = std::nullopt;

        //
        // A file containing the standard output stream from the process that was invoked.
        //
        std::optional< artifact_location > stdout = std::nullopt;

        //
        // A file containing the standard error stream from the process that was invoked.
        //
        std::optional< artifact_location > stderr = std::nullopt;

        //
        // A file containing the interleaved standard output and standard error stream from the process that was invoked.
        //
        std::optional< artifact_location > stdoutStderr = std::nullopt;

        //
        // Key/value pairs that provide additional information about the invocation.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const invocation &);
    void from_json(const json &, invocation &);

    //
    // Describes how a converter transformed the output of a static analysis tool from the analysis tool's native output format into the SARIF format.
    //
    struct conversion {
        //
        // A tool object that describes the converter.
        //
        tool tool;

        //
        // An invocation object that describes the invocation of the converter.
        //
        std::optional< invocation > invocation = std::nullopt;

        //
        // The locations of the analysis tool's per-run log files.
        //
        std::optional< std::forward_list< artifact_location > > analysisToolLogFiles = std::nullopt;

        //
        // Key/value pairs that provide additional information about the conversion.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const conversion &);
    void from_json(const json &, conversion &);

    //
    // Represents a directed edge in a graph.
    //
    struct edge {
        //
        // A string that uniquely identifies the edge within its graph.
        //
        std::string id;

        //
        // A short description of the edge.
        //
        std::optional< message > label = std::nullopt;

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
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const edge &);
    void from_json(const json &, edge &);

    //
    // Represents the traversal of a single edge during a graph traversal.
    //
    struct edge_traversal {
        //
        // Identifies the edge being traversed.
        //
        std::string edgeId;

        //
        // A message to display to the user as the edge is traversed.
        //
        std::optional< message > message = std::nullopt;

        //
        // The values of relevant expressions after the edge has been traversed.
        //
        std::optional< std::unordered_map< std::string, multiformat_message_string > > finalState = std::nullopt;

        //
        // The number of edge traversals necessary to return from a nested graph.
        //
        std::optional< int64_t > stepOverEdgeCount = std::nullopt;

        //
        // Key/value pairs that provide additional information about the edge traversal.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const edge_traversal &);
    void from_json(const json &, edge_traversal &);
    struct stack_frame;

    //
    // A call stack that is relevant to a result.
    //
    struct stack {
        //
        // A message relevant to this call stack.
        //
        std::optional< message > message = std::nullopt;

        //
        // An array of stack frames that represents a sequence of calls, rendered in reverse chronological order, that comprise the call stack.
        //
        std::forward_list< stack_frame > frames;

        //
        // Key/value pairs that provide additional information about the stack.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const stack &);
    void from_json(const json &, stack &);
    struct exception;

    //
    // Describes a runtime exception encountered during the execution of an analysis tool.
    //
    struct exception {
        //
        // A string that identifies the kind of exception, for example, the fully qualified type name of an object that was thrown, or the symbolic name of a signal.
        //
        std::optional< std::string > kind = std::nullopt;

        //
        // A message that describes the exception.
        //
        std::optional< std::string > message = std::nullopt;

        //
        // The sequence of function calls leading to the exception.
        //
        std::optional< stack > stack = std::nullopt;

        //
        // An array of exception objects each of which is considered a cause of this exception.
        //
        std::optional< std::forward_list< exception > > innerExceptions = std::nullopt;

        //
        // Key/value pairs that provide additional information about the exception.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const exception &);
    void from_json(const json &, exception &);
    struct graph;
    struct logical_location;
    struct thread_flow_location;
    struct result;
    struct web_request;
    struct web_response;

    //
    // The top-level element of an external property file.
    //
    struct external_properties {
        //
        // The URI of the JSON schema corresponding to the version of the external property file format.
        //
        std::optional< std::string > schema = std::nullopt;

        //
        // The SARIF format version of this external properties object.
        //
        std::optional< version > version = std::nullopt;

        //
        // A stable, unique identifer for this external properties object, in the form of a GUID.
        //
        std::optional< std::string > guid = std::nullopt;

        //
        // A stable, unique identifer for the run associated with this external properties object, in the form of a GUID.
        //
        std::optional< std::string > runGuid = std::nullopt;

        //
        // A conversion object that will be merged with a separate run.
        //
        std::optional< conversion > conversion = std::nullopt;

        //
        // An array of graph objects that will be merged with a separate run.
        //
        std::optional< std::forward_list< graph > > graphs = std::nullopt;

        //
        // Key/value pairs that provide additional information that will be merged with a separate run.
        //
        std::optional< property_bag > externalizedProperties = std::nullopt;

        //
        // An array of artifact objects that will be merged with a separate run.
        //
        std::optional< std::forward_list< artifact > > artifacts = std::nullopt;

        //
        // Describes the invocation of the analysis tool that will be merged with a separate run.
        //
        std::optional< std::forward_list< invocation > > invocations = std::nullopt;

        //
        // An array of logical locations such as namespaces, types or functions that will be merged with a separate run.
        //
        std::optional< std::forward_list< logical_location > > logicalLocations = std::nullopt;

        //
        // An array of threadFlowLocation objects that will be merged with a separate run.
        //
        std::optional< std::forward_list< thread_flow_location > > threadFlowLocations = std::nullopt;

        //
        // An array of result objects that will be merged with a separate run.
        //
        std::optional< std::forward_list< result > > results = std::nullopt;

        //
        // Tool taxonomies that will be merged with a separate run.
        //
        std::optional< std::forward_list< tool_component > > taxonomies = std::nullopt;

        //
        // The analysis tool object that will be merged with a separate run.
        //
        std::optional< tool_component > driver = std::nullopt;

        //
        // Tool extensions that will be merged with a separate run.
        //
        std::optional< std::forward_list< tool_component > > extensions = std::nullopt;

        //
        // Tool policies that will be merged with a separate run.
        //
        std::optional< std::forward_list< tool_component > > policies = std::nullopt;

        //
        // Tool translations that will be merged with a separate run.
        //
        std::optional< std::forward_list< tool_component > > translations = std::nullopt;

        //
        // Addresses that will be merged with a separate run.
        //
        std::optional< std::forward_list< address > > addresses = std::nullopt;

        //
        // Requests that will be merged with a separate run.
        //
        std::optional< std::forward_list< web_request > > webRequests = std::nullopt;

        //
        // Responses that will be merged with a separate run.
        //
        std::optional< std::forward_list< web_response > > webResponses = std::nullopt;

        //
        // Key/value pairs that provide additional information about the external properties.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const external_properties &);
    void from_json(const json &, external_properties &);

    //
    // Contains information that enables a SARIF consumer to locate the external property file that contains the value of an externalized property associated with the run.
    //
    struct external_property_file_reference {
        //
        // The location of the external property file.
        //
        std::optional< artifact_location > location = std::nullopt;

        //
        // A stable, unique identifer for the external property file in the form of a GUID.
        //
        std::optional< std::string > guid = std::nullopt;

        //
        // A non-negative integer specifying the number of items contained in the external property file.
        //
        std::optional< int64_t > itemCount = std::nullopt;

        //
        // Key/value pairs that provide additional information about the external property file.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const external_property_file_reference &);
    void from_json(const json &, external_property_file_reference &);

    //
    // References to external property files that should be inlined with the content of a root log file.
    //
    struct external_property_file_references {
        //
        // An external property file containing a run.conversion object to be merged with the root log file.
        //
        std::optional< external_property_file_reference > conversion = std::nullopt;

        //
        // An array of external property files containing a run.graphs object to be merged with the root log file.
        //
        std::optional< std::forward_list< external_property_file_reference > > graphs = std::nullopt;

        //
        // An external property file containing a run.properties object to be merged with the root log file.
        //
        std::optional< external_property_file_reference > externalizedProperties = std::nullopt;

        //
        // An array of external property files containing run.artifacts arrays to be merged with the root log file.
        //
        std::optional< std::forward_list< external_property_file_reference > > artifacts = std::nullopt;

        //
        // An array of external property files containing run.invocations arrays to be merged with the root log file.
        //
        std::optional< std::forward_list< external_property_file_reference > > invocations = std::nullopt;

        //
        // An array of external property files containing run.logicalLocations arrays to be merged with the root log file.
        //
        std::optional< std::forward_list< external_property_file_reference > > logicalLocations = std::nullopt;

        //
        // An array of external property files containing run.threadFlowLocations arrays to be merged with the root log file.
        //
        std::optional< std::forward_list< external_property_file_reference > > threadFlowLocations = std::nullopt;

        //
        // An array of external property files containing run.results arrays to be merged with the root log file.
        //
        std::optional< std::forward_list< external_property_file_reference > > results = std::nullopt;

        //
        // An array of external property files containing run.taxonomies arrays to be merged with the root log file.
        //
        std::optional< std::forward_list< external_property_file_reference > > taxonomies = std::nullopt;

        //
        // An array of external property files containing run.addresses arrays to be merged with the root log file.
        //
        std::optional< std::forward_list< external_property_file_reference > > addresses = std::nullopt;

        //
        // An external property file containing a run.driver object to be merged with the root log file.
        //
        std::optional< external_property_file_reference > driver = std::nullopt;

        //
        // An array of external property files containing run.extensions arrays to be merged with the root log file.
        //
        std::optional< std::forward_list< external_property_file_reference > > extensions = std::nullopt;

        //
        // An array of external property files containing run.policies arrays to be merged with the root log file.
        //
        std::optional< std::forward_list< external_property_file_reference > > policies = std::nullopt;

        //
        // An array of external property files containing run.translations arrays to be merged with the root log file.
        //
        std::optional< std::forward_list< external_property_file_reference > > translations = std::nullopt;

        //
        // An array of external property files containing run.requests arrays to be merged with the root log file.
        //
        std::optional< std::forward_list< external_property_file_reference > > webRequests = std::nullopt;

        //
        // An array of external property files containing run.responses arrays to be merged with the root log file.
        //
        std::optional< std::forward_list< external_property_file_reference > > webResponses = std::nullopt;

        //
        // Key/value pairs that provide additional information about the external property files.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const external_property_file_references &);
    void from_json(const json &, external_property_file_references &);

    //
    // A proposed fix for the problem represented by a result object. A fix specifies a set of artifacts to modify. For each artifact, it specifies a set of bytes to remove, and provides a set of new bytes to replace them.
    //
    struct fix {
        //
        // A message that describes the proposed fix, enabling viewers to present the proposed change to an end user.
        //
        std::optional< message > description = std::nullopt;

        //
        // One or more artifact changes that comprise a fix for a result.
        //
        std::forward_list< artifact_change > artifactChanges;

        //
        // Key/value pairs that provide additional information about the fix.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const fix &);
    void from_json(const json &, fix &);
    struct node;

    //
    // A network of nodes and directed edges that describes some aspect of the structure of the code (for example, a call graph).
    //
    struct graph {
        //
        // A description of the graph.
        //
        std::optional< message > description = std::nullopt;

        //
        // An array of node objects representing the nodes of the graph.
        //
        std::optional< std::forward_list< node > > nodes = std::nullopt;

        //
        // An array of edge objects representing the edges of the graph.
        //
        std::optional< std::forward_list< edge > > edges = std::nullopt;

        //
        // Key/value pairs that provide additional information about the graph.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const graph &);
    void from_json(const json &, graph &);

    //
    // Represents a path through a graph.
    //
    struct graph_traversal {
        //
        // The index within the run.graphs to be associated with the result.
        //
        std::optional< int64_t > runGraphIndex = std::nullopt;

        //
        // The index within the result.graphs to be associated with the result.
        //
        std::optional< int64_t > resultGraphIndex = std::nullopt;

        //
        // A description of this graph traversal.
        //
        std::optional< message > description = std::nullopt;

        //
        // Values of relevant expressions at the start of the graph traversal that may change during graph traversal.
        //
        std::optional< std::unordered_map< std::string, multiformat_message_string > > initialState = std::nullopt;

        //
        // Values of relevant expressions at the start of the graph traversal that remain constant for the graph traversal.
        //
        std::optional< std::unordered_map< std::string, multiformat_message_string > > immutableState = std::nullopt;

        //
        // The sequences of edges traversed by this graph traversal.
        //
        std::optional< std::forward_list< edge_traversal > > edgeTraversals = std::nullopt;

        //
        // Key/value pairs that provide additional information about the graph traversal.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const graph_traversal &);
    void from_json(const json &, graph_traversal &);

    //
    // A region within an artifact where a result was detected.
    //
    struct region {
        //
        // The line number of the first character in the region.
        //
        std::optional< int64_t > startLine = std::nullopt;

        //
        // The column number of the first character in the region.
        //
        std::optional< int64_t > startColumn = std::nullopt;

        //
        // The line number of the last character in the region.
        //
        std::optional< int64_t > endLine = std::nullopt;

        //
        // The column number of the character following the end of the region.
        //
        std::optional< int64_t > endColumn = std::nullopt;

        //
        // The zero-based offset from the beginning of the artifact of the first character in the region.
        //
        std::optional< int64_t > charOffset = std::nullopt;

        //
        // The length of the region in characters.
        //
        std::optional< int64_t > charLength = std::nullopt;

        //
        // The zero-based offset from the beginning of the artifact of the first byte in the region.
        //
        std::optional< int64_t > byteOffset = std::nullopt;

        //
        // The length of the region in bytes.
        //
        std::optional< int64_t > byteLength = std::nullopt;

        //
        // The portion of the artifact contents within the specified region.
        //
        std::optional< artifact_content > snippet = std::nullopt;

        //
        // A message relevant to the region.
        //
        std::optional< message > message = std::nullopt;

        //
        // Specifies the source language, if any, of the portion of the artifact specified by the region object.
        //
        std::optional< std::string > sourceLanguage = std::nullopt;

        //
        // Key/value pairs that provide additional information about the region.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const region &);
    void from_json(const json &, region &);

    //
    // A physical location relevant to a result. Specifies a reference to a programming artifact together with a range of bytes or characters within that artifact.
    //
    struct physical_location {
        //
        // The address of the location.
        //
        std::optional< address > address = std::nullopt;

        //
        // The location of the artifact.
        //
        std::optional< artifact_location > artifactLocation = std::nullopt;

        //
        // Specifies a portion of the artifact.
        //
        std::optional< region > region = std::nullopt;

        //
        // Specifies a portion of the artifact that encloses the region. Allows a viewer to display additional context around the region.
        //
        std::optional< ::gap::sarif::region > contextRegion = std::nullopt;

        //
        // Key/value pairs that provide additional information about the physical location.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const physical_location &);
    void from_json(const json &, physical_location &);
    struct location_relationship;

    //
    // A location within a programming artifact.
    //
    struct location {
        //
        // Value that distinguishes this location from all other locations within a single result object.
        //
        std::optional< int64_t > id = std::nullopt;

        //
        // Identifies the artifact and region.
        //
        std::optional< physical_location > physicalLocation = std::nullopt;

        //
        // The logical locations associated with the result.
        //
        std::optional< std::forward_list< logical_location > > logicalLocations = std::nullopt;

        //
        // A message relevant to the location.
        //
        std::optional< message > message = std::nullopt;

        //
        // A set of regions relevant to the location.
        //
        std::optional< std::forward_list< region > > annotations = std::nullopt;

        //
        // An array of objects that describe relationships between this location and others.
        //
        std::optional< std::forward_list< location_relationship > > relationships = std::nullopt;

        //
        // Key/value pairs that provide additional information about the location.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const location &);
    void from_json(const json &, location &);

    //
    // Information about the relation of one location to another.
    //
    struct location_relationship {
        //
        // A reference to the related location.
        //
        int64_t target;

        //
        // A set of distinct strings that categorize the relationship. Well-known kinds include 'includes', 'isIncludedBy' and 'relevant'.
        //
        std::optional< std::forward_list< std::string > > kinds = std::nullopt;

        //
        // A description of the location relationship.
        //
        std::optional< message > description = std::nullopt;

        //
        // Key/value pairs that provide additional information about the location relationship.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const location_relationship &);
    void from_json(const json &, location_relationship &);

    //
    // A logical location of a construct that produced a result.
    //
    struct logical_location {
        //
        // Identifies the construct in which the result occurred. For example, this property might contain the name of a class or a method.
        //
        std::optional< std::string > name = std::nullopt;

        //
        // The index within the logical locations array.
        //
        std::optional< int64_t > index = std::nullopt;

        //
        // The human-readable fully qualified name of the logical location.
        //
        std::optional< std::string > fullyQualifiedName = std::nullopt;

        //
        // The machine-readable name for the logical location, such as a mangled function name provided by a C++ compiler that encodes calling convention, return type and other details along with the function name.
        //
        std::optional< std::string > decoratedName = std::nullopt;

        //
        // Identifies the index of the immediate parent of the construct in which the result was detected. For example, this property might point to a logical location that represents the namespace that holds a type.
        //
        std::optional< int64_t > parentIndex = std::nullopt;

        //
        // The type of construct this logical location component refers to. Should be one of 'function', 'member', 'module', 'namespace', 'parameter', 'resource', 'returnType', 'type', 'variable', 'object', 'array', 'property', 'value', 'element', 'text', 'attribute', 'comment', 'declaration', 'dtd' or 'processingInstruction', if any of those accurately describe the construct.
        //
        std::optional< std::string > kind = std::nullopt;

        //
        // Key/value pairs that provide additional information about the logical location.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const logical_location &);
    void from_json(const json &, logical_location &);

    //
    // Represents a node in a graph.
    //
    struct node {
        //
        // A string that uniquely identifies the node within its graph.
        //
        std::string id;

        //
        // A short description of the node.
        //
        std::optional< message > label = std::nullopt;

        //
        // A code location associated with the node.
        //
        std::optional< location > location = std::nullopt;

        //
        // Array of child nodes.
        //
        std::optional< std::forward_list< node > > children = std::nullopt;

        //
        // Key/value pairs that provide additional information about the node.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const node &);
    void from_json(const json &, node &);

    //
    // Describes a condition relevant to the tool itself, as opposed to being relevant to a target being analyzed by the tool.
    //
    struct notification {
        //
        // The locations relevant to this notification.
        //
        std::optional< std::forward_list< location > > locations = std::nullopt;

        //
        // A message that describes the condition that was encountered.
        //
        message message;

        //
        // A value specifying the severity level of the notification.
        //
        std::optional< level > level = std::nullopt;

        //
        // The thread identifier of the code that generated the notification.
        //
        std::optional< int64_t > threadId = std::nullopt;

        //
        // The Coordinated Universal Time (UTC) date and time at which the analysis tool generated the notification.
        //
        std::optional< std::string > timeUtc = std::nullopt;

        //
        // The runtime exception, if any, relevant to this notification.
        //
        std::optional< exception > exception = std::nullopt;

        //
        // A reference used to locate the descriptor relevant to this notification.
        //
        std::optional< reporting_descriptor_reference > descriptor = std::nullopt;

        //
        // A reference used to locate the rule descriptor associated with this notification.
        //
        std::optional< reporting_descriptor_reference > associatedRule = std::nullopt;

        //
        // Key/value pairs that provide additional information about the notification.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const notification &);
    void from_json(const json &, notification &);

    //
    // An area within an image.
    //
    struct rectangle {
        //
        // The Y coordinate of the top edge of the rectangle, measured in the image's natural units.
        //
        std::optional< double > top = std::nullopt;

        //
        // The X coordinate of the left edge of the rectangle, measured in the image's natural units.
        //
        std::optional< double > left = std::nullopt;

        //
        // The Y coordinate of the bottom edge of the rectangle, measured in the image's natural units.
        //
        std::optional< double > bottom = std::nullopt;

        //
        // The X coordinate of the right edge of the rectangle, measured in the image's natural units.
        //
        std::optional< double > right = std::nullopt;

        //
        // A message relevant to the rectangle.
        //
        std::optional< message > message = std::nullopt;

        //
        // Key/value pairs that provide additional information about the rectangle.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const rectangle &);
    void from_json(const json &, rectangle &);

    //
    // The replacement of a single region of an artifact.
    //
    struct replacement {
        //
        // The region of the artifact to delete.
        //
        region deletedRegion;

        //
        // The content to insert at the location specified by the 'deletedRegion' property.
        //
        std::optional< artifact_content > insertedContent = std::nullopt;

        //
        // Key/value pairs that provide additional information about the replacement.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const replacement &);
    void from_json(const json &, replacement &);
    struct reporting_descriptor_relationship;

    //
    // Metadata that describes a specific report produced by the tool, as part of the analysis it provides or its runtime reporting.
    //
    struct reporting_descriptor {
        //
        // A stable, opaque identifier for the report.
        //
        std::string id;

        //
        // An array of stable, opaque identifiers by which this report was known in some previous version of the analysis tool.
        //
        std::optional< std::forward_list< std::string > > deprecatedIds = std::nullopt;

        //
        // A unique identifer for the reporting descriptor in the form of a GUID.
        //
        std::optional< std::string > guid = std::nullopt;

        //
        // An array of unique identifies in the form of a GUID by which this report was known in some previous version of the analysis tool.
        //
        std::optional< std::forward_list< std::string > > deprecatedGuids = std::nullopt;

        //
        // A report identifier that is understandable to an end user.
        //
        std::optional< std::string > name = std::nullopt;

        //
        // An array of readable identifiers by which this report was known in some previous version of the analysis tool.
        //
        std::optional< std::forward_list< std::string > > deprecatedNames = std::nullopt;

        //
        // A concise description of the report. Should be a single sentence that is understandable when visible space is limited to a single line of text.
        //
        std::optional< multiformat_message_string > shortDescription = std::nullopt;

        //
        // A description of the report. Should, as far as possible, provide details sufficient to enable resolution of any problem indicated by the result.
        //
        std::optional< multiformat_message_string > fullDescription = std::nullopt;

        //
        // A set of name/value pairs with arbitrary names. Each value is a multiformatMessageString object, which holds message strings in plain text and (optionally) Markdown format. The strings can include placeholders, which can be used to construct a message in combination with an arbitrary number of additional string arguments.
        //
        std::optional< std::unordered_map< std::string, multiformat_message_string > > messageStrings = std::nullopt;

        //
        // Default reporting configuration information.
        //
        std::optional< reporting_configuration > defaultConfiguration = std::nullopt;

        //
        // A URI where the primary documentation for the report can be found.
        //
        std::optional< std::string > helpUri = std::nullopt;

        //
        // Provides the primary documentation for the report, useful when there is no online documentation.
        //
        std::optional< multiformat_message_string > help = std::nullopt;

        //
        // An array of objects that describe relationships between this reporting descriptor and others.
        //
        std::optional< std::forward_list< reporting_descriptor_relationship > > relationships = std::nullopt;

        //
        // Key/value pairs that provide additional information about the report.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const reporting_descriptor &);
    void from_json(const json &, reporting_descriptor &);

    //
    // Information about the relation of one reporting descriptor to another.
    //
    struct reporting_descriptor_relationship {
        //
        // A reference to the related reporting descriptor.
        //
        reporting_descriptor_reference target;

        //
        // A set of distinct strings that categorize the relationship. Well-known kinds include 'canPrecede', 'canFollow', 'willPrecede', 'willFollow', 'superset', 'subset', 'equal', 'disjoint', 'relevant', and 'incomparable'.
        //
        std::optional< std::forward_list< std::string > > kinds = std::nullopt;

        //
        // A description of the reporting descriptor relationship.
        //
        std::optional< message > description = std::nullopt;

        //
        // Key/value pairs that provide additional information about the reporting descriptor reference.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const reporting_descriptor_relationship &);
    void from_json(const json &, reporting_descriptor_relationship &);

    enum class kind {
        kNotApplicable,
        kPass,
        kFail,
        kReview,
        kOpen,
        kInformational,
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(kind, {
        { kind::kNotApplicable, "notApplicable" },
        { kind::kPass, "pass" },
        { kind::kFail, "fail" },
        { kind::kReview, "review" },
        { kind::kOpen, "open" },
        { kind::kInformational, "informational" },
    })
    struct suppression;

    enum class baseline_state {
        kNew,
        kUnchanged,
        kUpdated,
        kAbsent,
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(baseline_state, {
        { baseline_state::kNew, "new" },
        { baseline_state::kUnchanged, "unchanged" },
        { baseline_state::kUpdated, "updated" },
        { baseline_state::kAbsent, "absent" },
    })

    //
    // Contains information about how and when a result was detected.
    //
    struct result_provenance {
        //
        // The Coordinated Universal Time (UTC) date and time at which the result was first detected. See "Date/time properties" in the SARIF spec for the required format.
        //
        std::optional< std::string > firstDetectionTimeUtc = std::nullopt;

        //
        // The Coordinated Universal Time (UTC) date and time at which the result was most recently detected. See "Date/time properties" in the SARIF spec for the required format.
        //
        std::optional< std::string > lastDetectionTimeUtc = std::nullopt;

        //
        // A GUID-valued string equal to the automationDetails.guid property of the run in which the result was first detected.
        //
        std::optional< std::string > firstDetectionRunGuid = std::nullopt;

        //
        // A GUID-valued string equal to the automationDetails.guid property of the run in which the result was most recently detected.
        //
        std::optional< std::string > lastDetectionRunGuid = std::nullopt;

        //
        // The index within the run.invocations array of the invocation object which describes the tool invocation that detected the result.
        //
        std::optional< int64_t > invocationIndex = std::nullopt;

        //
        // An array of physicalLocation objects which specify the portions of an analysis tool's output that a converter transformed into the result.
        //
        std::optional< std::forward_list< physical_location > > conversionSources = std::nullopt;

        //
        // Key/value pairs that provide additional information about the result.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const result_provenance &);
    void from_json(const json &, result_provenance &);

    //
    // Describes an HTTP request.
    //
    struct web_request {
        //
        // The index within the run.webRequests array of the request object associated with this result.
        //
        std::optional< int64_t > index = std::nullopt;

        //
        // The request protocol. Example: 'http'.
        //
        std::optional< std::string > protocol = std::nullopt;

        //
        // The request version. Example: '1.1'.
        //
        std::optional< std::string > version = std::nullopt;

        //
        // The target of the request.
        //
        std::optional< std::string > target = std::nullopt;

        //
        // The HTTP method. Well-known values are 'GET', 'PUT', 'POST', 'DELETE', 'PATCH', 'HEAD', 'OPTIONS', 'TRACE', 'CONNECT'.
        //
        std::optional< std::string > method = std::nullopt;

        //
        // The request headers.
        //
        std::optional< std::unordered_map< std::string, std::string > > headers = std::nullopt;

        //
        // The request parameters.
        //
        std::optional< std::unordered_map< std::string, std::string > > parameters = std::nullopt;

        //
        // The body of the request.
        //
        std::optional< artifact_content > body = std::nullopt;

        //
        // Key/value pairs that provide additional information about the request.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const web_request &);
    void from_json(const json &, web_request &);

    //
    // Describes the response to an HTTP request.
    //
    struct web_response {
        //
        // The index within the run.webResponses array of the response object associated with this result.
        //
        std::optional< int64_t > index = std::nullopt;

        //
        // The response protocol. Example: 'http'.
        //
        std::optional< std::string > protocol = std::nullopt;

        //
        // The response version. Example: '1.1'.
        //
        std::optional< std::string > version = std::nullopt;

        //
        // The response status code. Example: 451.
        //
        std::optional< int64_t > statusCode = std::nullopt;

        //
        // The response reason. Example: 'Not found'.
        //
        std::optional< std::string > reasonPhrase = std::nullopt;

        //
        // The response headers.
        //
        std::optional< std::unordered_map< std::string, std::string > > headers = std::nullopt;

        //
        // The body of the response.
        //
        std::optional< artifact_content > body = std::nullopt;

        //
        // Specifies whether a response was received from the server.
        //
        std::optional< bool > noResponseReceived = std::nullopt;

        //
        // Key/value pairs that provide additional information about the response.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const web_response &);
    void from_json(const json &, web_response &);

    //
    // A result produced by an analysis tool.
    //
    struct result {
        //
        // The stable, unique identifier of the rule, if any, to which this notification is relevant. This member can be used to retrieve rule metadata from the rules dictionary, if it exists.
        //
        std::optional< std::string > ruleId = std::nullopt;

        //
        // The index within the tool component rules array of the rule object associated with this result.
        //
        std::optional< int64_t > ruleIndex = std::nullopt;

        //
        // A reference used to locate the rule descriptor relevant to this result.
        //
        std::optional< reporting_descriptor_reference > rule = std::nullopt;

        //
        // A value that categorizes results by evaluation state.
        //
        std::optional< kind > kind = std::nullopt;

        //
        // A value specifying the severity level of the result.
        //
        std::optional< level > level = std::nullopt;

        //
        // A message that describes the result. The first sentence of the message only will be displayed when visible space is limited.
        //
        message message;

        //
        // Identifies the artifact that the analysis tool was instructed to scan. This need not be the same as the artifact where the result actually occurred.
        //
        std::optional< artifact_location > analysisTarget = std::nullopt;

        //
        // The set of locations where the result was detected. Specify only one location unless the problem indicated by the result can only be corrected by making a change at every specified location.
        //
        std::optional< std::forward_list< location > > locations = std::nullopt;

        //
        // A stable, unique identifer for the result in the form of a GUID.
        //
        std::optional< std::string > guid = std::nullopt;

        //
        // A stable, unique identifier for the equivalence class of logically identical results to which this result belongs, in the form of a GUID.
        //
        std::optional< std::string > correlationGuid = std::nullopt;

        //
        // A positive integer specifying the number of times this logically unique result was observed in this run.
        //
        std::optional< int64_t > occurrenceCount = std::nullopt;

        //
        // A set of strings that contribute to the stable, unique identity of the result.
        //
        std::optional< std::unordered_map< std::string, std::string > > partialFingerprints = std::nullopt;

        //
        // A set of strings each of which individually defines a stable, unique identity for the result.
        //
        std::optional< std::unordered_map< std::string, std::string > > fingerprints = std::nullopt;

        //
        // An array of 'stack' objects relevant to the result.
        //
        std::optional< std::forward_list< stack > > stacks = std::nullopt;

        //
        // An array of 'codeFlow' objects relevant to the result.
        //
        std::optional< std::forward_list< code_flow > > codeFlows = std::nullopt;

        //
        // An array of zero or more unique graph objects associated with the result.
        //
        std::optional< std::forward_list< graph > > graphs = std::nullopt;

        //
        // An array of one or more unique 'graphTraversal' objects.
        //
        std::optional< std::forward_list< graph_traversal > > graphTraversals = std::nullopt;

        //
        // A set of locations relevant to this result.
        //
        std::optional< std::forward_list< location > > relatedLocations = std::nullopt;

        //
        // A set of suppressions relevant to this result.
        //
        std::optional< std::forward_list< suppression > > suppressions = std::nullopt;

        //
        // The state of a result relative to a baseline of a previous run.
        //
        std::optional< baseline_state > baselineState = std::nullopt;

        //
        // A number representing the priority or importance of the result.
        //
        std::optional< double > rank = std::nullopt;

        //
        // A set of artifacts relevant to the result.
        //
        std::optional< std::forward_list< attachment > > attachments = std::nullopt;

        //
        // An absolute URI at which the result can be viewed.
        //
        std::optional< std::string > hostedViewerUri = std::nullopt;

        //
        // The URIs of the work items associated with this result.
        //
        std::optional< std::forward_list< std::string > > workItemUris = std::nullopt;

        //
        // Information about how and when the result was detected.
        //
        std::optional< result_provenance > provenance = std::nullopt;

        //
        // An array of 'fix' objects, each of which represents a proposed fix to the problem indicated by the result.
        //
        std::optional< std::forward_list< fix > > fixes = std::nullopt;

        //
        // An array of references to taxonomy reporting descriptors that are applicable to the result.
        //
        std::optional< std::forward_list< reporting_descriptor_reference > > taxa = std::nullopt;

        //
        // A web request associated with this result.
        //
        std::optional< web_request > webRequest = std::nullopt;

        //
        // A web response associated with this result.
        //
        std::optional< web_response > webResponse = std::nullopt;

        //
        // Key/value pairs that provide additional information about the result.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const result &);
    void from_json(const json &, result &);
    struct version_control_details;

    //
    // Information that describes a run's identity and role within an engineering system process.
    //
    struct run_automation_details {
        //
        // A description of the identity and role played within the engineering system by this object's containing run object.
        //
        std::optional< message > description = std::nullopt;

        //
        // A hierarchical string that uniquely identifies this object's containing run object.
        //
        std::optional< std::string > id = std::nullopt;

        //
        // A stable, unique identifer for this object's containing run object in the form of a GUID.
        //
        std::optional< std::string > guid = std::nullopt;

        //
        // A stable, unique identifier for the equivalence class of runs to which this object's containing run object belongs in the form of a GUID.
        //
        std::optional< std::string > correlationGuid = std::nullopt;

        //
        // Key/value pairs that provide additional information about the run automation details.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const run_automation_details &);
    void from_json(const json &, run_automation_details &);

    enum class column_kind {
        kUtf16CodeUnits,
        kUnicodeCodePoints,
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(column_kind, {
        { column_kind::kUtf16CodeUnits, "utf16CodeUnits" },
        { column_kind::kUnicodeCodePoints, "unicodeCodePoints" },
    })

    //
    // Defines locations of special significance to SARIF consumers.
    //
    struct special_locations {
        //
        // Provides a suggestion to SARIF consumers to display file paths relative to the specified location.
        //
        std::optional< artifact_location > displayBase = std::nullopt;

        //
        // Key/value pairs that provide additional information about the special locations.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const special_locations &);
    void from_json(const json &, special_locations &);

    //
    // Describes a single run of an analysis tool, and contains the reported output of that run.
    //
    struct run {
        //
        // Information about the tool or tool pipeline that generated the results in this run. A run can only contain results produced by a single tool or tool pipeline. A run can aggregate results from multiple log files, as long as context around the tool run (tool command-line arguments and the like) is identical for all aggregated files.
        //
        tool tool;

        //
        // Describes the invocation of the analysis tool.
        //
        std::optional< std::forward_list< invocation > > invocations = std::nullopt;

        //
        // A conversion object that describes how a converter transformed an analysis tool's native reporting format into the SARIF format.
        //
        std::optional< conversion > conversion = std::nullopt;

        //
        // The language of the messages emitted into the log file during this run (expressed as an ISO 639-1 two-letter lowercase culture code) and an optional region (expressed as an ISO 3166-1 two-letter uppercase subculture code associated with a country or region). The casing is recommended but not required (in order for this data to conform to RFC5646).
        //
        std::optional< std::string > language = std::nullopt;

        //
        // Specifies the revision in version control of the artifacts that were scanned.
        //
        std::optional< std::forward_list< version_control_details > > versionControlProvenance = std::nullopt;

        //
        // The artifact location specified by each uriBaseId symbol on the machine where the tool originally ran.
        //
        std::optional< std::unordered_map< std::string, artifact_location > > originalUriBaseIds = std::nullopt;

        //
        // An array of artifact objects relevant to the run.
        //
        std::optional< std::forward_list< artifact > > artifacts = std::nullopt;

        //
        // An array of logical locations such as namespaces, types or functions.
        //
        std::optional< std::forward_list< logical_location > > logicalLocations = std::nullopt;

        //
        // An array of zero or more unique graph objects associated with the run.
        //
        std::optional< std::forward_list< graph > > graphs = std::nullopt;

        //
        // The set of results contained in an SARIF log. The results array can be omitted when a run is solely exporting rules metadata. It must be present (but may be empty) if a log file represents an actual scan.
        //
        std::optional< std::forward_list< result > > results = std::nullopt;

        //
        // Automation details that describe this run.
        //
        std::optional< run_automation_details > automationDetails = std::nullopt;

        //
        // Automation details that describe the aggregate of runs to which this run belongs.
        //
        std::optional< std::forward_list< run_automation_details > > runAggregates = std::nullopt;

        //
        // The 'guid' property of a previous SARIF 'run' that comprises the baseline that was used to compute result 'baselineState' properties for the run.
        //
        std::optional< std::string > baselineGuid = std::nullopt;

        //
        // An array of strings used to replace sensitive information in a redaction-aware property.
        //
        std::optional< std::forward_list< std::string > > redactionTokens = std::nullopt;

        //
        // Specifies the default encoding for any artifact object that refers to a text file.
        //
        std::optional< std::string > defaultEncoding = std::nullopt;

        //
        // Specifies the default source language for any artifact object that refers to a text file that contains source code.
        //
        std::optional< std::string > defaultSourceLanguage = std::nullopt;

        //
        // An ordered list of character sequences that were treated as line breaks when computing region information for the run.
        //
        std::optional< std::forward_list< std::string > > newlineSequences = std::nullopt;

        //
        // Specifies the unit in which the tool measures columns.
        //
        std::optional< column_kind > columnKind = std::nullopt;

        //
        // References to external property files that should be inlined with the content of a root log file.
        //
        std::optional< external_property_file_references > externalPropertyFileReferences = std::nullopt;

        //
        // An array of threadFlowLocation objects cached at run level.
        //
        std::optional< std::forward_list< thread_flow_location > > threadFlowLocations = std::nullopt;

        //
        // An array of toolComponent objects relevant to a taxonomy in which results are categorized.
        //
        std::optional< std::forward_list< tool_component > > taxonomies = std::nullopt;

        //
        // Addresses associated with this run instance, if any.
        //
        std::optional< std::forward_list< address > > addresses = std::nullopt;

        //
        // The set of available translations of the localized data provided by the tool.
        //
        std::optional< std::forward_list< tool_component > > translations = std::nullopt;

        //
        // Contains configurations that may potentially override both reportingDescriptor.defaultConfiguration (the tool's default severities) and invocation.configurationOverrides (severities established at run-time from the command line).
        //
        std::optional< std::forward_list< tool_component > > policies = std::nullopt;

        //
        // An array of request objects cached at run level.
        //
        std::optional< std::forward_list< web_request > > webRequests = std::nullopt;

        //
        // An array of response objects cached at run level.
        //
        std::optional< std::forward_list< web_response > > webResponses = std::nullopt;

        //
        // A specialLocations object that defines locations of special significance to SARIF consumers.
        //
        std::optional< special_locations > specialLocations = std::nullopt;

        //
        // Key/value pairs that provide additional information about the run.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const run &);
    void from_json(const json &, run &);

    //
    // A function call within a stack trace.
    //
    struct stack_frame {
        //
        // The location to which this stack frame refers.
        //
        std::optional< location > location = std::nullopt;

        //
        // The name of the module that contains the code of this stack frame.
        //
        std::optional< std::string > module = std::nullopt;

        //
        // The thread identifier of the stack frame.
        //
        std::optional< int64_t > threadId = std::nullopt;

        //
        // The parameters of the call that is executing.
        //
        std::optional< std::forward_list< std::string > > parameters = std::nullopt;

        //
        // Key/value pairs that provide additional information about the stack frame.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const stack_frame &);
    void from_json(const json &, stack_frame &);

    enum class state {
        kAccepted,
        kUnderReview,
        kRejected,
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(state, {
        { state::kAccepted, "accepted" },
        { state::kUnderReview, "underReview" },
        { state::kRejected, "rejected" },
    })

    //
    // A suppression that is relevant to a result.
    //
    struct suppression {
        //
        // A stable, unique identifer for the suprression in the form of a GUID.
        //
        std::optional< std::string > guid = std::nullopt;

        //
        // A string that indicates where the suppression is persisted.
        //
        kind kind;

        //
        // A string that indicates the state of the suppression.
        //
        std::optional< state > state = std::nullopt;

        //
        // A string representing the justification for the suppression.
        //
        std::optional< std::string > justification = std::nullopt;

        //
        // Identifies the location associated with the suppression.
        //
        std::optional< location > location = std::nullopt;

        //
        // Key/value pairs that provide additional information about the suppression.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const suppression &);
    void from_json(const json &, suppression &);

    //
    // Describes a sequence of code locations that specify a path through a single thread of execution such as an operating system or fiber.
    //
    struct thread_flow {
        //
        // An string that uniquely identifies the threadFlow within the codeFlow in which it occurs.
        //
        std::optional< std::string > id = std::nullopt;

        //
        // A message relevant to the thread flow.
        //
        std::optional< message > message = std::nullopt;

        //
        // Values of relevant expressions at the start of the thread flow that may change during thread flow execution.
        //
        std::optional< std::unordered_map< std::string, multiformat_message_string > > initialState = std::nullopt;

        //
        // Values of relevant expressions at the start of the thread flow that remain constant.
        //
        std::optional< std::unordered_map< std::string, multiformat_message_string > > immutableState = std::nullopt;

        //
        // A temporally ordered array of 'threadFlowLocation' objects, each of which describes a location visited by the tool while producing the result.
        //
        std::forward_list< thread_flow_location > locations;

        //
        // Key/value pairs that provide additional information about the thread flow.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const thread_flow &);
    void from_json(const json &, thread_flow &);

    enum class importance {
        kImportant,
        kEssential,
        kUnimportant,
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(importance, {
        { importance::kImportant, "important" },
        { importance::kEssential, "essential" },
        { importance::kUnimportant, "unimportant" },
    })

    //
    // A location visited by an analysis tool while simulating or monitoring the execution of a program.
    //
    struct thread_flow_location {
        //
        // The index within the run threadFlowLocations array.
        //
        std::optional< int64_t > index = std::nullopt;

        //
        // The code location.
        //
        std::optional< location > location = std::nullopt;

        //
        // The call stack leading to this location.
        //
        std::optional< stack > stack = std::nullopt;

        //
        // A set of distinct strings that categorize the thread flow location. Well-known kinds include 'acquire', 'release', 'enter', 'exit', 'call', 'return', 'branch', 'implicit', 'false', 'true', 'caution', 'danger', 'unknown', 'unreachable', 'taint', 'function', 'handler', 'lock', 'memory', 'resource', 'scope' and 'value'.
        //
        std::optional< std::forward_list< std::string > > kinds = std::nullopt;

        //
        // An array of references to rule or taxonomy reporting descriptors that are applicable to the thread flow location.
        //
        std::optional< std::forward_list< reporting_descriptor_reference > > taxa = std::nullopt;

        //
        // The name of the module that contains the code that is executing.
        //
        std::optional< std::string > module = std::nullopt;

        //
        // A dictionary, each of whose keys specifies a variable or expression, the associated value of which represents the variable or expression value. For an annotation of kind 'continuation', for example, this dictionary might hold the current assumed values of a set of global variables.
        //
        std::optional< std::unordered_map< std::string, multiformat_message_string > > state = std::nullopt;

        //
        // An integer representing a containment hierarchy within the thread flow.
        //
        std::optional< int64_t > nestingLevel = std::nullopt;

        //
        // An integer representing the temporal order in which execution reached this location.
        //
        std::optional< int64_t > executionOrder = std::nullopt;

        //
        // The Coordinated Universal Time (UTC) date and time at which this location was executed.
        //
        std::optional< std::string > executionTimeUtc = std::nullopt;

        //
        // Specifies the importance of this location in understanding the code flow in which it occurs. The order from most to least important is "essential", "important", "unimportant". Default: "important".
        //
        std::optional< importance > importance = std::nullopt;

        //
        // A web request associated with this thread flow location.
        //
        std::optional< web_request > webRequest = std::nullopt;

        //
        // A web response associated with this thread flow location.
        //
        std::optional< web_response > webResponse = std::nullopt;

        //
        // Key/value pairs that provide additional information about the threadflow location.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const thread_flow_location &);
    void from_json(const json &, thread_flow_location &);

    //
    // Specifies the information necessary to retrieve a desired revision from a version control system.
    //
    struct version_control_details {
        //
        // The absolute URI of the repository.
        //
        std::string repositoryUri;

        //
        // A string that uniquely and permanently identifies the revision within the repository.
        //
        std::optional< std::string > revisionId = std::nullopt;

        //
        // The name of a branch containing the revision.
        //
        std::optional< std::string > branch = std::nullopt;

        //
        // A tag that has been applied to the revision.
        //
        std::optional< std::string > revisionTag = std::nullopt;

        //
        // A Coordinated Universal Time (UTC) date and time that can be used to synchronize an enlistment to the state of the repository at that time.
        //
        std::optional< std::string > asOfTimeUtc = std::nullopt;

        //
        // The location in the local file system to which the root of the repository was mapped at the time of the analysis.
        //
        std::optional< artifact_location > mappedTo = std::nullopt;

        //
        // Key/value pairs that provide additional information about the version control details.
        //
        std::optional< property_bag > properties = std::nullopt;
    };

    void to_json(json &, const version_control_details &);
    void from_json(const json &, version_control_details &);
} // namespace gap::sarif::definitions