cmake_minimum_required(VERSION 3.0.0)
project(Pokemon_TG VERSION 0.1.0)

find_package(fmt REQUIRED)
find_package(libpqxx REQUIRED)
find_package(PostgreSQL REQUIRED)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)

find_program(iwyu_path NAMES include-what-you-use iwyu)
if(NOT iwyu_path)
  message(FATAL_ERROR "Could not find the program include-what-you-use")
endif()

set(PQXX /usr/local/include/pqxx)

find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SKIP_BUILD_TEST on)

if(WIN32)
    macro(get_WIN32_WINNT version)
        if(CMAKE_SYSTEM_VERSION)
            set(ver ${CMAKE_SYSTEM_VERSION})
            string(REGEX MATCH "^([0-9]+).([0-9])" ver ${ver})
            string(REGEX MATCH "^([0-9]+)" verMajor ${ver})
            # Check for Windows 10, b/c we'll need to convert to hex 'A'.
            if("${verMajor}" MATCHES "10")
                set(verMajor "A")
                string(REGEX REPLACE "^([0-9]+)" ${verMajor} ver ${ver})
            endif()
            # Remove all remaining '.' characters.
            string(REPLACE "." "" ver ${ver})
            # Prepend each digit with a zero.
            string(REGEX REPLACE "([0-9A-Z])" "0\\1" ver ${ver})
            set(${version} "0x${ver}")
        endif()
    endmacro()

    get_WIN32_WINNT(ver)
    add_definitions(-D_WIN32_WINNT=${ver})
endif()

set(Boost_USE_MULTITHREADED ON)

include(CTest)
enable_testing()

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

set(SOURCES
    src/box.cpp
    src/global.cpp
    src/main.cpp
    src/moves.cpp
    src/pokemon.cpp
    src/battle/battle.cpp
    src/battle/BaseBattle/baseBattle.cpp
    src/battle/BaseBattle/handlers.cpp
    src/battle/BaseBattle/generators.cpp
    src/battle/DualBattle/dualBattle.cpp
    src/battle/DualBattle/handlers.cpp
    src/battle/WildBattle/wildBattle.cpp
    src/battle/WildBattle/handlers.cpp
    src/bot/bot.cpp
    src/bot/events/battle.cpp
    src/bot/events/dualbattle.cpp
    src/bot/events/events.cpp
    src/bot/events/starters.cpp
    src/bot/events/wildbattle.cpp
    src/database/conn.cpp
    src/database/moves.cpp
    src/database/player.cpp
    src/database/pokemon.cpp
    src/database/starters.cpp
    src/database/utils.cpp
    src/user/player.cpp
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(PostgresSQL_INCLUDE_DIR ${PostgresSQL_INCLUDE_DIRS})
set(PostgresSQL_TYPE_INCLUDE_DIR ${PostgresSQL_INCLUDE_DIRS})

include_directories(include ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})

add_subdirectory(vendor/tgbot)

add_executable(Pokemon_TG ${SOURCES})
# set_property(TARGET Pokemon_TG PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})

if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

target_link_libraries(Pokemon_TG TgBot ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES} ${PQXX_LIB} ${PQ_LIB} fmt::fmt)
set_target_properties(Pokemon_TG PROPERTIES
            CXX_STANDARD 17
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
