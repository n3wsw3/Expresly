project "pcre2"
    kind "StaticLib"
    language "c"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
    
    files {
        "pcre2/src/**.c",
        "pcre2/src/**.h",
        "pcre2/src/**.in"
    }

    includedirs {
        "pcre2/src"
    }

project "jpcre2"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
    
    files {
        "jpcre2/src/**.cpp",
        "jpcre2/src/**.hpp"
    }

    links {
        "pcre2"
    }

    includedirs {
        "jpcre2/src",
        "pcre2/src"
    }
