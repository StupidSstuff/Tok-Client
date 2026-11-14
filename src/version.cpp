#include "tok/version.hpp"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <appmodel.h>
#include <vector>
namespace tok {
VersionInfo DetectInstalledVersion() noexcept {
    VersionInfo result{};
    UINT32 bytes = 0;
    const LONG size_status = GetCurrentPackageId(&bytes, nullptr);
    if (size_status == APPMODEL_ERROR_NO_PACKAGE) {
        result.compatibility = Compatibility::NotPackaged;
        return result;
    }
    if (size_status != ERROR_INSUFFICIENT_BUFFER || bytes == 0) return result;
    std::vector<std::uint8_t> storage(bytes);
    auto* package_id = reinterpret_cast<PACKAGE_ID*>(storage.data());
    if (GetCurrentPackageId(&bytes, package_id) != ERROR_SUCCESS) return result;
    result.package_identity_available = true;
    result.package = { package_id->version.Major, package_id->version.Minor,
                       package_id->version.Build, package_id->version.Revision };
    const auto& v = result.package;
    // 26.63 package family: 1.26.63xx. Unknown builds remain unsupported.
    if (v.major == 1 && v.minor == 26 && v.build >= 6300 && v.build <= 6399)
        result.compatibility = Compatibility::Bedrock_26_63;
    return result;
}
const char* CompatibilityName(Compatibility value) noexcept {
    switch (value) {
    case Compatibility::NotPackaged: return "not-running-in-app-container";
    case Compatibility::Unsupported: return "unsupported-build";
    case Compatibility::Bedrock_26_63: return "bedrock-26.63";
    default: return "unknown";
    }
}
}
