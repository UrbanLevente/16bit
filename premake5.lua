include "Dependencies.lua"

workspace "16bit"
    architecture "x64"
    startproject "16bit"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

	flags
	{
		"MultiProcessorCompile"
	}

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    group "Core"
    include "16bit"
    group ""
    
    group "Dependencies"
    include "16bit/vendor/GLFW"
	include "16bit/vendor/Glad"
	include "16bit/vendor/imgui"
    group ""