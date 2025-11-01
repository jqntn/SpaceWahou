cmake_minimum_required(VERSION 3.20)

include(FetchContent)

set(FETCHCONTENT_QUIET OFF)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

project(SpaceWahou LANGUAGES CXX)

FetchContent_Declare(sfml URL "https://github.com/SFML/SFML/archive/refs/tags/3.0.2.tar.gz")
FetchContent_MakeAvailable(sfml)

add_executable(SpaceWahou WIN32)

set_property(TARGET SpaceWahou PROPERTY CXX_STANDARD 20)

file(GLOB_RECURSE SpaceWahou_Sources "../Sources/*.cpp")
target_sources(SpaceWahou PRIVATE "${SpaceWahou_Sources}")

target_include_directories(SpaceWahou PRIVATE
  "../Sources"
  "${sfml_SOURCE_DIR}/include"
)

target_link_libraries(SpaceWahou PRIVATE
  SFML::System
  SFML::Window
  SFML::Graphics
  SFML::Audio
  SFML::Main
)