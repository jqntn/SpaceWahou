cmake_minimum_required(VERSION 3.20)

include(FetchContent)

set(FETCHCONTENT_QUIET OFF)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

project(SpaceWahou LANGUAGES CXX)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
  add_compile_options("-pthread")
  add_compile_definitions(MA_ENABLE_AUDIO_WORKLETS)
endif()

FetchContent_Declare(zsfml URL "https://github.com/Zombieschannel/SFML/archive/refs/heads/SFML-3.x.x-EMCC.tar.gz")
FetchContent_MakeAvailable(zsfml)

add_executable(SpaceWahou)

set_property(TARGET SpaceWahou PROPERTY CXX_STANDARD 20)
set_property(TARGET SpaceWahou PROPERTY WIN32_EXECUTABLE $<NOT:$<CONFIG:Debug>>)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
  set_property(TARGET SpaceWahou PROPERTY SUFFIX ".html")
  target_compile_definitions(SpaceWahou PRIVATE EMSCRIPTEN)
  target_link_options(SpaceWahou PRIVATE
    -sAUDIO_WORKLET=1
    -sWASM_WORKERS=1
    -sASYNCIFY=1
    -sFULL_ES2=1
    --preload-file=${CMAKE_SOURCE_DIR}/../Assets@Assets
    --shell-file=${CMAKE_SOURCE_DIR}/emscripten/shell.html
  )
endif()

file(GLOB_RECURSE SpaceWahou_Sources "../Sources/*.cpp")
target_sources(SpaceWahou PRIVATE "${SpaceWahou_Sources}")

target_include_directories(SpaceWahou PRIVATE "../Sources")

target_link_libraries(SpaceWahou PRIVATE
  SFML::System
  SFML::Window
  SFML::Graphics
  SFML::Audio
  $<$<NOT:$<STREQUAL:${CMAKE_SYSTEM_NAME},Emscripten>>:SFML::Main>
)