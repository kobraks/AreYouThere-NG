project "AreYouThereSE NG"
    kind "SharedLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	targetname "AreYouThere"

	pchheader "pch.h"
	pchsource "src/pch.cpp"

	-- flags { "FatalCompileWarnings" }

    files 
    {
        "src/**.h",
        "src/**.cpp",
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS",
        "SPDLOG_FMT_EXTERNAL",
		"SPDLOG_COMPILED_LIB",
		"SKYRIM_SUPPORT_AE",
    }

    includedirs
    {
		"src",
        "%{IncludeDir.Spdlog}",
        "%{IncludeDir.Fmt}",
        "%{IncludeDir.CommonLibSSE}",
        "%{IncludeDir.Boost}",
        "%{IncludeDir.Binary_io}",
    }

    links
    {
        "Fmt",
		"spdlog",
        "CommonLibSSE",
    }

    filter "action:vs*"
		externalanglebrackets "On"
		externalwarnings "Off"

	filter "system:windows"
		systemversion "latest"

		defines
		{
		}

		links
		{
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

		defines { "DEBUG", "SPDLOG_ACTIVE_LEVEL=0" }

		links
		{
		}

	filter "configurations:Release"
		runtime "Release"
		optimize "On"
		symbols "Off"

		defines { "NDEBUG", "SPDLOG_ACTIVE_LEVEL=2" }

		links
		{
		}

	filter "configurations:Dist"
		runtime "Release"
		optimize "on"
		symbols "Off"

		defines { "NDEBUG", "SPDLOG_ACTIVE_LEVEL=2" }

		links
		{
		}