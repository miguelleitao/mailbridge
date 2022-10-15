cmake_minimum_required(VERSION 3.5.1)
project(mailbridge VERSION "2.0.1")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_C_FLAGS_DEBUG "-g -DIS_DEBUG -fdiagnostics-show-option")
set(CMAKE_C_FLAGS_RELEASE "-O3 -s")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DIS_DEBUG -fdiagnostics-show-option")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -s")

add_definitions(-DMAILBRIDGE_VERSION="${PROJECT_VERSION}")

find_package(Base64 REQUIRED)
find_package(CURL REQUIRED)
find_package(Json REQUIRED)

file(GLOB configurations_SRC
    "src/configurations/*.h"
    "src/configurations/*.cpp")

file(GLOB handlers_SRC
    "src/handlers/*.h"
    "src/handlers/*.cpp")

file(GLOB messages_SRC
    "src/messages/*.h"
    "src/messages/*.cpp")

file(GLOB servers_SRC
    "src/servers/*.h"
    "src/servers/*.cpp"
    "src/servers/**/*.h"
    "src/servers/**/*.cpp")

file(GLOB util_SRC
    "src/util/*.h"
    "src/util/*.cpp")

add_compile_options(-Wall -Wextra -Wpedantic -Wno-missing-field-initializers -Wno-unused-parameter)

add_executable(mailbridge src/main.cpp ${configurations_SRC} ${handlers_SRC} ${messages_SRC} ${servers_SRC} ${util_SRC})
target_link_libraries(mailbridge curl mosquitto pthread)

include_directories(${BASE64_INCLUDE_DIRS})
include_directories(${JSON_INCLUDE_DIRS})
