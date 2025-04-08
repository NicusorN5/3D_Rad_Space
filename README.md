# 3DRadSpace

3DRadSpace is a free, simple to use, rapid application development game engine. Still in very early development. 

[![Github all releases](https://img.shields.io/github/downloads/3DRadSpace/3D_Rad_Space/total.svg)](https://GitHub.com/3DRadSpace/3D_Rad_Space/releases/)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/fb1763ca6663456f934c96ad109aefd8)](https://www.codacy.com/gh/NicusorN5/3D_Rad_Space/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=NicusorN5/3D_Rad_Space&amp;utm_campaign=Badge_Grade)
[![Discord](https://img.shields.io/discord/319515587263070209.svg?label=&logo=discord&logoColor=ffffff&color=7389D8&labelColor=6A7EC2)](https://discord.gg/9BcQQyu)
[![Website shields.io](https://img.shields.io/website-up-down-green-red/http/3dradspace.com.svg)](http://3dradspace.org/)
[![GitHub issues](https://img.shields.io/github/issues/3DRadSpace/3D_Rad_Space.svg)](https://GitHub.com/3DRadSpace/3D_Rad_Space/issues/)
[![CC-0 license](https://img.shields.io/badge/License-CC--0-blue.svg)](https://creativecommons.org/licenses/by-nd/4.0)

# Downloading releases

Old releases can be found [here](https://github.com/3DRadSpace/3D_Rad_Space/releases) (Lastest release: 0.0.6a, currently working on 0.1.0a)

# Building 3DRadSpace

Status:

![Windows-x64](https://github.com/NicusorN5/3D_Rad_Space/actions/workflows/cmake-multi-platform.yml/badge.svg)

1.) Download the source using Git
`git clone https://github.com/3DRadSpace/3D_Rad_Space`

2.) Install the dependencies (⚠️ NuGet versions can cause conflicts)

- Windows API 
> Included in Windows SDK, use VS Installer
>
> ⚠️ Source won't compile if using versions < 10.0.20348.0
- DirectX11 Toolkit (directxtk_desktop_2019)
> `.\vcpkg install directxtk:x64-Windows`
- Assimp
> `.\vcpkg install assimp:x64-Windows`
- nlohmann JSON
> `.\vcpkg install nlohmann-json:x64-windows`
- Freetype
> `.\vcpkg install freetype:x64-windows`
- OpenAL-Soft
> `.\vcpkg install openal-soft:x64-windows`
- NVidia PhysX 5.30
> `.\vcpkg install physx:x64-windows`
- AngelScript (optional, for the AngelScript plugin)
> `.\vcpkg install angelscript:x64-windows`

- Google test (Optional, for test units.)
> `vcpkg install gtest:x64-windows`

2.) Open the folder as a CMake project (preferably using Visual Studio 2022 / other IDEs were not tested yet).

3.) Set the starting project to `3DRadSpace-editor.exe`.

4.) Compile the solution (Ctrl+Shift+B or F5) with any desired configuration (`x64-Debug`/`x64-Release`).

5.) If there are "failed to compile shaders" errors when debugging, copy "Data" from `<root>/3DRadSpace/` to `<root>/3DRadSpace/out/build/x64-Debug` (or x64-Release).

Notices: 

- Only x64-Windows is supported. No support for x86 is planned. 
- Linux support is planned, but will be implemented much later.

# License 
 This project uses a creative commons licence (*CC0-1.0 license*).
