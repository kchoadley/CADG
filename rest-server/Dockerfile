# Get the base test environment image from Docker Hub
FROM oswasabi/cadg-test-env:latest

# Set the working directory
WORKDIR "/usr/src/cadg-rest-server"

# Copy the current folder which contains C++ source code to the Docker image under /usr/src
COPY . .

RUN mkdir build
WORKDIR "/usr/src/cadg-rest-server/build"

RUN cmake -G "Unix Makefiles" ..
RUN make

CMD ["./cadg-rest-server"]
