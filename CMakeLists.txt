cmake_minimum_required(VERSION 3.31)
project(aime_io_pn532)

set(CMAKE_CXX_STANDARD 23)
find_library(LIBNFC NAMES nfc PATHS ${CMAKE_SOURCE_DIR}/libs)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(aimeio_pn532_test
        src/test.cpp
        src/Felica.cpp
        src/Felica.h
)

add_library(
        aimeio_pn532
        SHARED
        src/util/dprintf.cpp
        src/util/dprintf.h
        src/util/logging.h
        src/Felica.h
        src/Felica.cpp
        src/aimeio.cpp
        src/aimeio.h
        src/aimeio.def
)

if (LIBNFC)
    message(STATUS "Found libnfc at ${LIBNFC}")
    target_link_libraries(aimeio_pn532 PRIVATE ${LIBNFC})
    target_link_libraries(aimeio_pn532_test PRIVATE ${LIBNFC})
else ()
    message(FATAL_ERROR "Could not find libnfc")
endif ()

