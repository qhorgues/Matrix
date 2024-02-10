cmake_minimum_required (VERSION 3.20)

project (Matrix LANGUAGES CXX VERSION 1.0)

include (${CMAKE_SOURCE_DIR}/cmake/option.cmake)

set_choice (CMAKE_BUILD_TYPE "Debug;Release;MinSizeRel;RelWithDebInfo" "Debug" "Choose type of build")

set (SRCS
    include/Matrix.tpp
)

set (HEADERS
    include/Matrix.hpp
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

set_option (BUILD_TESTING_MATRIX OFF BOOL "Compile matrix test")

if (BUILD_TESTING_MATRIX)
    add_subdirectory(${CMAKE_SOURCE_DIR}/test)
endif()

add_library (${PROJECT_NAME} INTERFACE ${SRCS} ${HEADERS})


include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME} ARCHIVE)
install(TARGETS ${PROJECT_NAME} PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

SET(CPACK_BINARY_DEB TRUE)
SET(CPACK_PACKAGE_NAME ${CMAKE_PROJECT_NAME})
SET(CPACK_SET_DESTDIR TRUE)
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "quentin.horgues@outllok.fr")

SET(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6")
SET(CPACK_PACKAGE_VENDOR "Horgues")
# make postinst run after install                                                #

include(CPack)