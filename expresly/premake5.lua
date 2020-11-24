project "expresly"
	kind "StaticLib"
	language "c++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		-- "include/**.h",
		"src/**.cpp",
		"include/**.h"
		-- "vendor/modular-boost/boost/**.h"
	}

	includedirs {
        "src",
        "include"
		-- "%{wks.location}/n3/vendor/modular-boost"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
		}
	
	filter "configurations:Debug"
		defines "EXP_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "EXP_RELEASE"
		runtime "Release"
		optimize "on"
