cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 23)

project(ip_filter
        LANGUAGES CXX
)

if (CMAKE_COMPILER_IS_GNUCXX AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 13.1)
    message(FATAL_ERROR "Require at least gcc-13.1")
endif()

enable_testing()
find_package(GTest REQUIRED)
add_subdirectory(src/tests)


set(DEFAULT_PROJECT_VERSION_MAJOR 1)
set(DEFAULT_PROJECT_VERSION_MINOR 119)

if(WITH_DEFAULT_NON_ZERO_BUILD_NUMBER)
    set(DEFAULT_PROJECT_VERSION_BUILD 117)
else()
    set(DEFAULT_PROJECT_VERSION_BUILD 0)
endif()

if (DEFINED HW2_PROJECT_VERSION_MAJOR)
    set(PROJECT_VERSION_MAJOR ${HW2_PROJECT_VERSION_MAJOR})
else ()
    set(PROJECT_VERSION_MAJOR ${DEFAULT_PROJECT_VERSION_MAJOR})
endif ()

if (DEFINED HW2_PROJECT_VERSION_MINOR)
    set(PROJECT_VERSION_MINOR ${HW2_PROJECT_VERSION_MINOR})
else ()
    set(PROJECT_VERSION_MINOR ${DEFAULT_PROJECT_VERSION_MINOR})
endif ()

if (DEFINED HW2_PROJECT_VERSION_BUILD)
    set(PROJECT_VERSION_BUILD ${HW2_PROJECT_VERSION_BUILD})
else ()
    set(PROJECT_VERSION_BUILD ${DEFAULT_PROJECT_VERSION_BUILD})
endif ()

configure_file(${PROJECT_SOURCE_DIR}/src/versioning/ProjectVersion.h.in ${PROJECT_SOURCE_DIR}/src/versioning/ProjectVersion.h)

set(DEFAULT_TARGET_NAME ip_filter)
set(DEFAULT_BOOST_TESTS_NAME ip_filter_boost_tests)

if (DEFINED MAIN_TARGET_EXECUTABLE_NAME)
    set(TARGET_EXEC_NAME ${MAIN_TARGET_EXECUTABLE_NAME})
else()
    set(TARGET_EXEC_NAME ${DEFAULT_TARGET_NAME})
endif()

if (DEFINED BOOST_TESTS_EXEC_NAME)
    set(BOOST_TESTS_EXEC_NAME ${BOOST_TESTS_EXEC_NAME} CACHE INTERNAL "")
else()
    set(BOOST_TESTS_EXEC_NAME ${DEFAULT_BOOST_TESTS_NAME} CACHE INTERNAL "")
endif()

message("-- Target name: ${TARGET_EXEC_NAME}")
message("-- Boost tests name: ${BOOST_TESTS_EXEC_NAME}")

list(APPEND homework_SRC
        src/ipaddr/IpV4.cpp
        src/util/Utilities.cpp
)

add_executable(${TARGET_EXEC_NAME} src/main.cpp ${homework_SRC})
target_include_directories(${TARGET_EXEC_NAME} PRIVATE src include)

add_library(checker_lib STATIC ${homework_SRC})
target_include_directories(checker_lib PUBLIC src ${CMAKE_SOURCE_DIR}/include)

set(TARGET_LIST ${TARGET_EXEC_NAME})

if (DEFINED HW2_INSTALL_PREFIX)
    set(CMAKE_INSTALL_PREFIX ${HW2_INSTALL_PREFIX})
    install(TARGETS ${TARGET_LIST} DESTINATION ${CMAKE_INSTALL_PREFIX})
else()
    set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install)
    install(TARGETS ${TARGET_LIST} DESTINATION ${PROJECT_SOURCE_DIR}/install)
endif (DEFINED HW2_INSTALL_PREFIX)
message("-- Install prefix is: ${CMAKE_INSTALL_PREFIX}")
