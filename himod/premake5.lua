project "himod"
	kind "WindowedApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
        "src/**.cpp",
        "include/**.h"
	}

	includedirs {
		"include",
		"%{wks.location}/expresly/include",
		"vendor/wxWidgets/include"
	}

	links {
		"expresly",
	}

	

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	filter "system:windows"
		systemversion "latest"
		includedirs {
			"vendor/wxWidgets/include/msvc",
		}
		libdirs {
			"vendor/wxWidgets/lib/vc_x64_lib"
		}

	filter "system:linux"
		includedirs {
			"vendor/wxWidgets/build_gtk/lib/wx/include/gtk3-unicode-3.1",
		}
		libdirs {
			"vendor/wxWidgets/build_gtk/lib"
		}
		defines {
			"__WXGTK__"
		}

		linkoptions { "`wx-config --cxxflags --libs`"}

	
    filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
