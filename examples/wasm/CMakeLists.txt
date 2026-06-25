cmake_minimum_required(VERSION 3.26)
project(zvec_wasm C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT EMSCRIPTEN)
  message(FATAL_ERROR "This example requires Emscripten. Use emcmake cmake ...")
endif()

set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..)

include(${PROJECT_ROOT_DIR}/cmake/bazel.cmake)

set(BUILD_ZVEC_SHARED OFF)
set(BUILD_ZVEC_AILEGO_SHARED OFF)
set(BUILD_ZVEC_CORE_SHARED OFF)
set(BUILD_PYTHON_BINDINGS OFF)
set(BUILD_C_BINDINGS OFF)
set(BUILD_TOOLS OFF)
set(AUTO_DETECT_ARCH OFF)

include_directories(${PROJECT_ROOT_DIR}/src/include)
include_directories(${PROJECT_ROOT_DIR}/src)

cc_directory(${PROJECT_ROOT_DIR}/thirdparty thirdparty)
cc_directory(${PROJECT_ROOT_DIR}/src/ailego ailego)

add_executable(zvec_wasm zvec_wasm.cc)

target_link_libraries(zvec_wasm
  PRIVATE
    zvec_ailego_static
)

set_target_properties(zvec_wasm PROPERTIES
  SUFFIX ".js"
  LINK_FLAGS "\
    -s EXPORTED_FUNCTIONS='[\"_malloc\",\"_free\"]' \
    -s EXPORTED_RUNTIME_METHODS='[\"ccall\",\"cwrap\",\"getValue\",\"setValue\",\"HEAPF32\"]' \
    -s ALLOW_MEMORY_GROWTH=1 \
    -s MODULARIZE=1 \
    -s EXPORT_NAME='ZvecWasm' \
    -s ENVIRONMENT='web,node' \
    -O3 \
    --no-entry \
  "
)
