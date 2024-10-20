project "ImGui"
    kind "StaticLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    -- Add the root directory of ImGui and the backends as include directories
    includedirs {
        "vendor/imgui",
        "vendor/imgui/backends",
        "vendor/GLFW/include",
        "vendor/Glad/include"
    }
    

    -- Specify the ImGui source files and backend implementations
    files {
        "*.cpp",  
        "*.h",
        "./backends/imgui_impl_glfw.cpp",  
        "./backends/imgui_impl_opengl3.cpp"
    }
    

    filter "system:windows"
        systemversion "latest"
        cppdialect "C++17"
        staticruntime "Off"

    filter "system:linux"
        pic "On"
        systemversion "latest"
        cppdialect "C++17"
        staticruntime "Off"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"
