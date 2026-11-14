# Tok-Client

Native x64 C++ DLL scaffold for Minecraft Bedrock on Windows.

## Target
- Retail Bedrock UWP / packaged Windows app
- Runtime package-identity detection
- Compatibility profile: Bedrock 26.63 (expected 1.26.63xx package-version family)
- Unsupported versions fail closed

The game display version and Windows package version are not necessarily formatted
identically. Confirm the installed package manifest version on the target machine
before adding build-specific integration.

## Build
Use Visual Studio 2022 with the Desktop development with C++ workload and a
Windows 10/11 SDK.

```powershell
cmake -S . -B build -A x64
cmake --build build --config Release
```

Output: build/Release/TokClient.dll (generator-dependent).

## Integration boundary
This repository currently provides a DLL and explicit lifecycle exports only.
It does not include an injector, anti-cheat bypass, process tampering, or
game-memory manipulation. Load it only from an authorized development/test host.

Exports:
- TokClient_Initialize — returns 1 only when the current package matches the
  supported 26.63 family.
- TokClient_GetCompatibility — returns a static compatibility label.
- TokClient_Shutdown — reserved for orderly teardown.
