cmake_minimum_required(VERSION 3.10)
project(soap_server)

set(CMAKE_CXX_STANDARD 17)

find_package(spdlog CONFIG REQUIRED)

add_executable(soap_server
        src/soap_server.cpp
        src/gSOAPFiles/soapC.cpp
        src/gSOAPFiles/CAPSoapHttp.nsmap
        src/gSOAPFiles/soapCAPSoapHttpService.cpp
        src/gSOAPFiles/stdsoap2.cpp
        src/services/logger.cpp)

set(SERVICE_HEADERS "src/services")
set(SOAP_HEADERS "src/gSOAPFiles")

set(HEADER_PATHS ${SERVICE_HEADERS} ${SOAP_HEADERS})

set(SPDLOG_LIBRARY spdlog::spdlog)
set(LIBRARY_SEARCH_PATHS ${SPDLOG_LIBRARY})

include_directories(${HEADER_PATHS})
target_link_libraries(${PROJECT_NAME} ${LIBRARY_SEARCH_PATHS})

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/logs")