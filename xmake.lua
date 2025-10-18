add_rules("mode.debug", "mode.release")
set_targetdir("build/${plat}/${arch}/${mode}")

target("TomatoEngine")  
    set_kind("binary")
    set_languages("c++20")
    add_files("demo/*.cpp") -- if you want to try the demo, you can open it.It will be compiled.
    add_includedirs("include")

    -- by your path (need config)
    add_includedirs("C:/TDM-GCC-64/x86_64-w64-mingw32/include/glfw-3.4.bin.WIN64/include/GLFW")
    add_links("C:/TDM-GCC-64/libexec/gcc/x86_64-w64-mingw32/10.3.0/lib-mingw-w64/libglfw3.a")
    add_links("glfw3")

    -- MODE

    if is_mode("debug") then
        add_defines("DEBUG")
    end

    -- System Links (Windows)
    add_syslinks("opengl32", "gdi32", "user32")

    -- Compiler
    set_toolchains("gcc")
    set_toolset("cc", "gcc")
    set_toolset("cxx", "g++")