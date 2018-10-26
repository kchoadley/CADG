# Get the base test environment image from Docker Hub
FROM oswasabi/cadg-test-env:latest

# Set the working directory
WORKDIR "/usr/src/cadg"

# Copy the current folder which contains C++ source code to the Docker image under /usr/src
COPY . .

# You have to set an explicit error code, otherwise it goes undetected and you have to check the logs to see if there is an issue
RUN cppcheck --error-exitcode=1 .

# Lint the files
RUN ./cpplint.py --headers=h --extensions=cpp *.cpp

# Create build directory
RUN mkdir build
WORKDIR "/usr/src/cadg/build"

# Build and run tests
RUN cmake -G "Unix Makefiles" ..
RUN make
RUN ./runTests
