cmake_minimum_required(VERSION 3.1)

project(cadg-rest-server)

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
                                ./src/services/data_access_object.cpp
                                ./src/services/logger.cpp
                                ./src/util/network_utils.cpp)

# header locations
set(CONTROLLER_INCLUDE_DIR "./src/controller")
set(MODEL_INCLUDE_DIR "./src/model")
set(SERVICES_INCLUDE_DIR "./src/services")
set(UTILITIES_INCLUDE_DIR "./src/util")
set(HEADER_PATHS ${CONTROLLER_INCLUDE_DIR} ${MODEL_INCLUDE_DIR} ${SERVICES_INCLUDE_DIR} ${UTILITIES_INCLUDE_DIR} ${OPENSSL_INCLUDE_DIR})

# library paths
set(BOOST_LIBRARY "-lboost_system")
set(CPPRESTSDK_LIBRARY "-lcpprest")
set(OPENSSL_LIBS "${OPENSSL_LIBRARIES}")
set(SPDLOG_LIBRARY spdlog::spdlog)
set(THREADS Threads::Threads)
set(LIBRARIES_SEARCH_PATHS ${CPPRESTSDK_LIBRARY} ${OPENSSL_LIBS} ${SPDLOG_LIBRARY} ${THREADS} ${BOOST_LIBRARY})

include_directories(${HEADER_PATHS})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES_SEARCH_PATHS})

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/logs")
