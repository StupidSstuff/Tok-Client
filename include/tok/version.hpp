#pragma once
#include <cstdint>
namespace tok {
struct PackageVersion { std::uint16_t major{}, minor{}, build{}, revision{}; };
enum class Compatibility { NotPackaged, Unsupported, Bedrock_26_63 };
struct VersionInfo {
    PackageVersion package{};
    Compatibility compatibility{Compatibility::Unsupported};
    bool package_identity_available{false};
};
[[nodiscard]] VersionInfo DetectInstalledVersion() noexcept;
[[nodiscard]] const char* CompatibilityName(Compatibility value) noexcept;
}
