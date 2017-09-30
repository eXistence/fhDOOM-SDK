cmake_minimum_required (VERSION 3.2.0)
project (fhDOOM-SDK)

include(setup.cmake)

add_definitions(-D_D3SDK -DGAME_DLL)

add_subdirectory (idlib)
add_subdirectory (game)
add_subdirectory (d3xp)