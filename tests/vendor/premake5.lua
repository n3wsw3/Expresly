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

	excludes {
		"googletest/googletest/src/gtest-all.cc"
	}

	includedirs {
        "googletest/googletest/include",
        "googletest/googletest"
	}

	filter "system:linux"
		buildoptions {"-pthread"}

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
