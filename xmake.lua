add_rules("mode.debug", "mode.release")

add_requires("imgui", { configs = { sdl2 = true }})
add_requires("libsdl", "libsdl_image", "fmt", "entt", "lz4", "nlohmann_json", "chipmunk2d", "openal-soft", "dr_wav")

set_allowedarchs("windows|x64")
set_warnings("allextra")

add_includedirs("include")
set_rundir("bin")

set_languages("c++20")

if is_plat("windows") then
    set_runtimes("MD")
    add_cxflags("/wd4251")
    add_cxflags("/wd4275")
end

target("Engine")
    set_kind("static")
    add_headerfiles("include/Engine/*.hh")
    add_files("src/Engine/**.cc")
    add_packages("imgui", "libsdl", "libsdl_image", "fmt", "entt", "lz4", "nlohmann_json", "chipmunk2d", "openal-soft", "dr_wav", { public = true })
    set_targetdir("lib")

target("Game")
    add_deps("Engine")
    add_headerfiles("include/Game/**.hh")
    add_files("src/Game/**.cc")
    set_targetdir("bin")

target("Test")
    add_deps("Engine")
    add_headerfiles("include/Test/**.hh")
    add_files("src/Test/**.cc")
    set_targetdir("bin")

target("Minesweeper")
    add_deps("Engine")
    add_headerfiles("include/Minesweeper/**.hh")
    add_files("src/Minesweeper/**.cc")
    set_targetdir("bin")