# Get the base test environment image from Docker Hub
FROM oswasabi/cadg-test-env:latest

# Set the working directory
WORKDIR "/usr/src/cadg-rest-server"

# Copy the current folder which contains C++ source code to the Docker image under /usr/src
COPY . .

ENV DB_TEST_NAME=${DB_TEST_NAME}
ENV DB_TEST_TABLE=${DB_TEST_TABLE}
ENV DB_PASSWORD=${DB_PASSWORD}
ENV DB_PORT=${DB_PORT}
ENV DB_SERVER=${DB_SERVER}
ENV DB_UID=${DB_UID}

RUN mkdir build
WORKDIR "/usr/src/cadg-rest-server/build"

RUN cmake -G "Unix Makefiles" ..
RUN make

CMD ["./cadg-rest-server"]
