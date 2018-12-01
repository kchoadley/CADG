cmake_minimum_required(VERSION 3.1)

project(cadg-rest-server)

SET( ODBC_FOUND 0 )

FIND_PATH(ODBC_INCLUDE_DIRECTORIES sql.h
  /usr/include
  /usr/include/odbc
  /usr/local/include
  /usr/local/include/odbc
  /usr/local/odbc/include
  "C:/Program Files/ODBC/include"
  "C:/ODBC/include"
  DOC "Specify the directory containing sql.h."
)

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

MARK_AS_ADVANCED( ODBC_FOUND ODBC_LIBRARY ODBC_EXTRA_LIBRARIES ODBC_INCLUDE_DIRECTORIES )

find_package(Boost REQUIRED COMPONENTS system thread)
find_package(OpenSSL 1.0.1 REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Threads REQUIRED)

set(OPENSSL_VERSION "1.0.1")

message("-- configuring gcc options")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17 -DBOOST_LOG_DYN_LINK")

# source files
add_executable(${PROJECT_NAME}  
                                ./src/rest_server.cpp
                                ./src/controller/controller.cpp
                                ./src/controller/user_controller.cpp
                                ./src/nanodbc/nanodbc.cpp
                                ./src/services/data_access_object.cpp
                                ./src/services/logger.cpp
                                ./src/util/network_utils.cpp)

# header locations
set(CONTROLLER_INCLUDE_DIR "./src/controller")
set(MODEL_INCLUDE_DIR "./src/model")
set(SERVICES_INCLUDE_DIR "./src/services")
set(UTILITIES_INCLUDE_DIR "./src/util")
set(NANODBC_INCLUDE_DIR "./src/nanodbc")
set(HEADER_PATHS ${CONTROLLER_INCLUDE_DIR} ${MODEL_INCLUDE_DIR} ${NANODBC_INCLUDE_DIR} ${SERVICES_INCLUDE_DIR} ${UTILITIES_INCLUDE_DIR} ${OPENSSL_INCLUDE_DIR} ${ODBC_INCLUDE_DIR})

# library paths
set(BOOST_LIBRARY "-lboost_system")
set(CPPRESTSDK_LIBRARY "-lcpprest")
set(OPENSSL_LIBS "${OPENSSL_LIBRARIES}")
set(SPDLOG_LIBRARY spdlog::spdlog)
set(THREADS Threads::Threads)
set(LIBRARIES_SEARCH_PATHS ${CPPRESTSDK_LIBRARY} ${OPENSSL_LIBS} ${SPDLOG_LIBRARY} ${THREADS} ${BOOST_LIBRARY} ${ODBC_LIBRARIES})

include_directories(${HEADER_PATHS})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES_SEARCH_PATHS})

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/logs")
