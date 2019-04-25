cmake_minimum_required (VERSION 3.1)
project (Ryskim C CXX)

set(EXTRA_C_FLAGS "${EXTRA_C_FLAGS} -std=c++1y -msse2 -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_C_FLAGS}")

# specify output subdirs
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/release/${TARGET_ABI}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/release/${TARGET_ABI}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/release/${TARGET_ABI}/bin)

include_directories (
	"${CMAKE_SOURCE_DIR}/src"
	"${CMAKE_SOURCE_DIR}/lib/raylib-macos/include"
	)


link_directories(${CMAKE_SOURCE_DIR}/lib/raylib-macos/lib)

add_executable (ryskim
    "src/drm.cpp"
	"src/game.cpp"
    "src/main.cpp"
	"src/gfx.cpp"
	"src/audio.cpp"
    )

target_link_libraries(ryskim raylib)