cmake_minimum_required (VERSION 3.20)

project (Test_Matrix LANGUAGES CXX VERSION 1.0)

include (${CMAKE_SOURCE_DIR}/cmake/CompilerWarnings.cmake)
include (${CMAKE_SOURCE_DIR}/cmake/option.cmake)

set_choice (CMAKE_BUILD_TYPE "Debug;Release;MinSizeRel;RelWithDebInfo" "Debug" "Choose type of build")

set (SRCS
	main.cpp
)

set (HEADERS
)

include_directories(${CMAKE_SOURCE_DIR}/include)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)


if (MINGW)
    set (CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")

    if (${CMAKE_BUILD_TYPE} MATCHES "Debug" OR ${CMAKE_BUILD_TYPE} MATCHES "RelWithDebInfo")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
    endif()
endif (MINGW)

add_executable (${PROJECT_NAME} ${SRCS} ${HEADERS})
target_link_libraries(${PROJECT_NAME} Matrix)
set_target_warnings(${PROJECT_NAME})