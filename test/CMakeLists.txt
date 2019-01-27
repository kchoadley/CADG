# Basic CMake project
cmake_minimum_required(VERSION 3.10.2) # version that is currently installed in test env

# Set project name
project(CADG)

# Locate packages
find_package(GTest REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread)
find_package(OpenSSL 1.0.1 REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Threads REQUIRED)

SET( ODBC_FOUND 0 )

FIND_PATH(ODBC_INCLUDE_DIRECTORIES sql.h
        /usr/include
        /usr/include/odbc
        /usr/local/include
        /usr/local/include/odbc
        /usr/local/odbc/include
        "C:/Program Files/ODBC/include"
        "C:/ODBC/include"
        DOC "Specify the directory containing sql.h.")

FIND_LIBRARY( ODBC_LIBRARY
        NAMES odbc iodbc unixodbc odbc32
        PATHS
        /usr/lib
        /usr/lib/odbc
        /usr/local/lib
        /usr/local/lib/odbc
        /usr/local/odbc/lib
        "C:/Program Files/ODBC/lib"
        "C:/ODBC/lib/debug"
        DOC "Specify the ODBC driver manager library here."
        )

IF (ODBC_LIBRARY)
    IF (ODBC_INCLUDE_DIRECTORIES)
        SET( ODBC_FOUND 1 )
    ENDIF ()
ENDIF ()

SET( ODBC_LIBRARIES ${ODBC_LIBRARY} )

# Set C++17 as the standard
set(CMAKE_CXX_STANDARD 17)

# Set source files
set(TEST_SOURCES
        test_suite.cpp
        rest-server/controller/controller_test.cpp
        soap/xml-parsing/xml_parser_test.cpp
        soap/xml-parsing/soap_message_test.xml
        rest-server/controller/user_controller_test.cpp
        rest-server/model/alert_test.cpp
        )

set(CADG_SOURCES
        ../rest-server/src/controller/controller.cpp
        ../rest-server/src/controller/user_controller.cpp
        ../rest-server/src/nanodbc/nanodbc.cpp
        ../rest-server/src/services/data_access_object.cpp
        ../rest-server/src/services/logger.cpp
        ../rest-server/src/util/network_utils.cpp)

set(SOAP_SOURCES
        ../soap/xml-parsing/xml_parser.cpp
        ../soap/xml-parsing/soap_message_test.xml)

# header locations
set(CONTROLLER_INCLUDE_DIR "../rest-server/src/controller")
set(MODEL_INCLUDE_DIR "../rest-server/src/model")
set(SERVICES_INCLUDE_DIR "../rest-server/src/services")
set(UTILITIES_INCLUDE_DIR "../rest-server/src/util")
set(NANODBC_INCLUDE_DIR "../rest-server/src/nanodbc")
set(SOAP_INCLUDE_DIR "../soap/xml-parsing")
set(TEST_INCLUDE_DIR "./rest-server/controller")
set(HEADER_PATHS
        ${CONTROLLER_INCLUDE_DIR}
        ${MODEL_INCLUDE_DIR}
        ${NANODBC_INCLUDE_DIR}
        ${SERVICES_INCLUDE_DIR}
        ${UTILITIES_INCLUDE_DIR}
        ${OPENSSL_INCLUDE_DIR}
        ${ODBC_INCLUDE_DIR}
        ${SOAP_INCLUDE_DIR}
        ${TEST_INCLUDE_DIR})

# library paths
set(BOOST_LIBRARY "-lboost_system")
set(CPPRESTSDK_LIBRARY "-lcpprest")
set(OPENSSL_LIBS "${OPENSSL_LIBRARIES}")
set(SPDLOG_LIBRARY spdlog::spdlog)
set(THREADS Threads::Threads)
set(LIBRARIES_SEARCH_PATHS ${CPPRESTSDK_LIBRARY} ${OPENSSL_LIBS} ${SPDLOG_LIBRARY} ${THREADS} ${BOOST_LIBRARY} ${ODBC_LIBRARIES})

include_directories(${HEADER_PATHS} ${GTEST_INCLUDE_DIRS})

add_executable(runTests ${TEST_SOURCES} ${CADG_SOURCES} ${SOAP_SOURCES})

target_link_libraries(runTests ${LIBRARIES_SEARCH_PATHS} ${GTEST_LIBRARIES} pthread fruit)
