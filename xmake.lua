-- Led Cube
-- Run on RaspberryPi (3B, 3B+, 4B)
-- Need 40Pin version

target("led_cube")
    set_kind("binary")

    -- std=C+=11
    set_languages("c99", "cxx11")

    add_includedirs("src/json")

    -- source file
    add_files("src/*/*/*.cpp")
    add_files("src/*/*.cpp")
    add_files("src/*.cpp")

    -- build dir
    set_objectdir("build/objs")
    set_targetdir(".")

    -- link flags
    add_links("pthread", "wiringPi")

    add_mflags("-O3")
    

