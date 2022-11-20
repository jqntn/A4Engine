add_rules("mode.debug", "mode.release")

add_requires("libsdl", "libsdl_image", "fmt", "entt", "nlohmann_json", "chipmunk2d", "openal-soft", "dr_wav")
add_requires("imgui", {configs = {sdl2 = true}})

set_allowedarchs("windows|x64")
set_warnings("allextra")

set_languages("c++20")

add_includedirs("include")
set_rundir("bin")

if is_plat("windows") then
    add_cxflags("/wd4251")
    add_cxflags("/wd4275")
end

target("A4Engine")
    set_kind("static")
    add_headerfiles("include/*.h")
    add_files("src/*.cc")
    set_targetdir("lib")
    add_packages("libsdl_image")
    add_packages("libsdl", "fmt", "imgui", "entt", "nlohmann_json", "chipmunk2d", "openal-soft", "dr_wav", {public = true})

target("A4Demo")
    add_deps("A4Engine")
    add_headerfiles("demo_include/*.h")
    add_files("demo_src/*.cc")
    set_targetdir("bin")

target("A4Test")
    add_deps("A4Engine")
    add_headerfiles("test_include/*.h")
    add_files("test_src/*.cc")
    set_targetdir("bin")