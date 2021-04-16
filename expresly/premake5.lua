project "expresly"
	kind "StaticLib"
	language "c++"
	cppdialect "C++latest"
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
		"vendor/fmt/include"
	}

	links {
		"fmt"
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
