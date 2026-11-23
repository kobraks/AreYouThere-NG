include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

workspace "AreYouThere"
    architecture "x86_64"
    startproject "AreYouThereSE NG"

    configurations {
        "Debug",
        "Release",
    }

    solution_items {
        ".editorconfig"
    }

	defines {
        "ENABLE_SKYRIM_AE",
	}

    multiprocessorcompile "on"
    staticruntime "off"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

filter ("action:vs*")
    buildoptions {"/utf-8"}

filter ("system:windows", "action:vs*")
	characterset "Unicode"

filter ("configurations:Debug")
	runtime "Debug"
	symbols "On"
	optimize "Off"

	defines { "DEBUG" }

filter ("configurations:Release")
	runtime "Release"
	symbols "Off"
	optimize "On"

	defines { "NDEBUG" }

    filter {}

group "Dependencies"
    include "vendor/premake"
    include "vendor/fmt"
    include "vendor/CommonLibSSE-NG"
    include "vendor/binary_io"
    include "vendor/spdlog"
group ""

group "Core"
    include "AreYouThereSE NG"
group ""