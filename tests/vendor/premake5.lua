project "gtest"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"googletest/googletest/include/**.h",
        "googletest/googletest/src/**.cc",
	}

	defines "GTEST_HAS_PTHREAD=0"

	includedirs {
        "googletest/googletest/include",
        "googletest/googletest"
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
