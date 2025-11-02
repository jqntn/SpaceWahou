cmake_minimum_required(VERSION 3.20)

include(FetchContent)

set(FETCHCONTENT_QUIET OFF)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

project(SpaceWahou LANGUAGES CXX)

FetchContent_Declare(zsfml URL "https://github.com/Zombieschannel/SFML/archive/refs/heads/SFML-3.x.x-EMCC.tar.gz")
FetchContent_MakeAvailable(zsfml)

add_executable(SpaceWahou)

set_property(TARGET SpaceWahou PROPERTY CXX_STANDARD 20)
set_property(TARGET SpaceWahou PROPERTY WIN32_EXECUTABLE $<NOT:$<CONFIG:Debug>>)
set_property(TARGET SpaceWahou PROPERTY SUFFIX ".html")

set(SFML_EMSCRIPTEN_TARGET_COMPILE_OPTIONS_DEBUG -g3 -gsource-map -O0)
set(SFML_EMSCRIPTEN_TARGET_COMPILE_OPTIONS_RELEASE -O3)
set(SFML_EMSCRIPTEN_TARGET_COMPILE_OPTIONS
  $<$<CONFIG:Debug>:${SFML_EMSCRIPTEN_TARGET_COMPILE_OPTIONS_DEBUG}>
  $<$<CONFIG:Release>:${SFML_EMSCRIPTEN_TARGET_COMPILE_OPTIONS_RELEASE}>
  --use-port=freetype
)

set(SFML_EMSCRIPTEN_TARGET_LINK_OPTIONS_DEBUG -g3 -gsource-map -sASSERTIONS=2 -sCHECK_NULL_WRITES=1 -sSAFE_HEAP=1 -sSTACK_OVERFLOW_CHECK=1)
set(SFML_EMSCRIPTEN_TARGET_LINK_OPTIONS_RELEASE -O3)
set(SFML_EMSCRIPTEN_TARGET_LINK_OPTIONS_ASYNCIFY -sASYNCIFY=1)
set(SFML_EMSCRIPTEN_TARGET_LINK_OPTIONS
  $<$<CONFIG:Debug>:${SFML_EMSCRIPTEN_TARGET_LINK_OPTIONS_DEBUG}>
  $<$<CONFIG:Release>:${SFML_EMSCRIPTEN_TARGET_LINK_OPTIONS_RELEASE}>

  ${SFML_EMSCRIPTEN_TARGET_LINK_OPTIONS_ASYNCIFY}

  -Wno-limited-postlink-optimizations # warning: running limited binaryen optimizations because DWARF info requested (or indirectly required)
  -Wno-pthreads-mem-growth            # warning: -pthread + ALLOW_MEMORY_GROWTH may run non-wasm code slowly, see https://github.com/WebAssembly/design/issues/1271

  -sALLOW_MEMORY_GROWTH=1             # Grow the memory arrays at runtime
  -sEXIT_RUNTIME=1                    # Execute cleanup (e.g. `atexit`) after `main` completes
  -sFETCH=1                           # Enables `emscripten_fetch` API
  -sFORCE_FILESYSTEM=1                # Makes full filesystem support be included
  -sFULL_ES2=1                        # Forces support for all GLES2 features, not just the WebGL-friendly subset
  -sMAX_WEBGL_VERSION=1               # Specifies the highest WebGL version to target
  -sMIN_WEBGL_VERSION=1               # Specifies the lowest WebGL version to target
  -sSTACK_SIZE=4mb                    # Set the total stack size
  -sWASM=1                            # Compile code to WebAssembly

  -sGL_EXPLICIT_UNIFORM_LOCATION=1    # TODO P0:
  -sGL_EXPLICIT_UNIFORM_BINDING=1     # TODO P0:

  --emrun                             # Add native support for `emrun` (I/O capture)
  --embed-file ${CMAKE_SOURCE_DIR}/Assets@/
  -sTOTAL_MEMORY=16mb

  --shell-file=${CMAKE_SOURCE_DIR}/shell.html
)

target_compile_options(SpaceWahou PRIVATE ${SFML_EMSCRIPTEN_TARGET_COMPILE_OPTIONS})
target_link_options(SpaceWahou PRIVATE ${SFML_EMSCRIPTEN_TARGET_LINK_OPTIONS})
target_compile_definitions(SpaceWahou PRIVATE SFML_OPENGL_ES)

file(GLOB_RECURSE SpaceWahou_Sources "../Sources/*.cpp")
target_sources(SpaceWahou PRIVATE "${SpaceWahou_Sources}")

target_include_directories(SpaceWahou PRIVATE "../Sources")

target_link_libraries(SpaceWahou PRIVATE
  SFML::System
  SFML::Window
  SFML::Graphics
  SFML::Audio
)