include "./vendor/premake/premake_customization/solution_items.lua"

workspace "expresly"
	architecture "x86_64"
	startproject "tests"

	configurations {
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "vendor/premake"
	include "tests/vendor"

group ""

include "expresly"
include "tests"
include "tests/vendor"
