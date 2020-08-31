cmake_minimum_required(VERSION 3.0.0)
project(Pokemon_TG VERSION 0.1.0)

set(Boost_USE_MULTITHREADED ON)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)
include_directories(/usr/local/include ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

add_subdirectory(tgbot-cpp)

include(CTest)
enable_testing()

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(Pokemon_TG ${SOURCES})
include_directories(include /usr/local/include ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
target_link_libraries(Pokemon_TG TgBot)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
