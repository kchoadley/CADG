# Get the base Ubuntu image from Docker Hub
FROM oswasabi/cadg-test-env:latest

# Set the folder name to be the same as the lesson name
ARG DIR=cadg

# Copy the current folder which contains C++ source code to the Docker image under /usr/src
COPY . "/usr/src/${DIR}"

# Specify the working DIRectory
WORKDIR "/usr/src/${DIR}"

# You have to set an explicit error code, otherwise it goes undetected and you have to check the logs to see if there is an issue
RUN cppcheck --error-exitcode=1 .

RUN mkdir build
WORKDIR "/usr/src/${DIR}/build"

RUN cmake -G "Unix Makefiles" ..
RUN make
RUN ./runTests
