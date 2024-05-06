include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

workspace "AreYouThere"
    architecture "x86_64"
    startproject "AreYouThereSE NG"

    configurations {
        "Debug",
        "Release",
        "Dist",
    }

    solution_items {
        ".editorconfig"
    }

    flags {
         "MultiProcessorCompile"
    }
	
	defines {
        "ENABLE_SKYRIM_AE",
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

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