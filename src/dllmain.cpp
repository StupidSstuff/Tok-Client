#include "tok/version.hpp"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
extern "C" __declspec(dllexport) int TokClient_Initialize() noexcept {
    const auto info = tok::DetectInstalledVersion();
    if (!info.package_identity_available ||
        info.compatibility != tok::Compatibility::Bedrock_26_63) return 0;
    // Initialize client services here, outside DllMain.
    return 1;
}
extern "C" __declspec(dllexport) void TokClient_Shutdown() noexcept {
    // Stop client services here.
}
extern "C" __declspec(dllexport) const char* TokClient_GetCompatibility() noexcept {
    return tok::CompatibilityName(tok::DetectInstalledVersion().compatibility);
}
BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID) { return TRUE; }
