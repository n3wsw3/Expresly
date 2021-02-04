project "expresly"
	kind "StaticLib"
	language "c++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"src/**.cpp",
		"include/**.h"
	}

	includedirs {
        "src",
		"include",
		"vendor/jpcre2/src"
	}

	links {
		"pcre2",
		"jpcre2"
	}

	filter "system:windows"
		systemversion "latest"
	
	filter "configurations:Debug"
		defines "EXP_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "EXP_RELEASE"
		runtime "Release"
		optimize "on"
