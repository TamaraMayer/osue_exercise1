cmake_minimum_required (VERSION 3.1)
project (VocaliDTTS C CXX)

set(EXTRA_C_FLAGS "${EXTRA_C_FLAGS} -std=c++1y -msse2 -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_C_FLAGS}")

# specify output subdirs
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/release/${TARGET_ABI}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/release/${TARGET_ABI}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/release/${TARGET_ABI}/bin)

include_directories (
	"${CMAKE_SOURCE_DIR}/src"
	"${CMAKE_SOURCE_DIR}/engine/manager/include"
	"${CMAKE_SOURCE_DIR}/engine/synthesis/dnn/include"
	"${CMAKE_SOURCE_DIR}/external/mimic/include"
	"${CMAKE_SOURCE_DIR}/external/eigen"
	"${CMAKE_SOURCE_DIR}/external/protobuf"
	)

add_executable (ryksim
    "src/drm.cpp"
    "src/main.cpp"
    )