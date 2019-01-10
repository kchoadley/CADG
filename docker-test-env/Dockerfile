### This creates the base image for the Build and Test Environment for CADG

# Get the base Ubuntu image from Docker Hub
FROM ubuntu:18.04

# Add ubuntu toolchain repository
RUN apt-get -qq -d update
RUN apt-get install -qq -y software-properties-common
RUN add-apt-repository -y ppa:ubuntu-toolchain-r/test
RUN apt-get -qq -d update

# Install tools
RUN apt-get -qq -y install \
    cmake \
    cppcheck \
    g++-6 \
    libasio-dev \
    libcpprest-dev \
	libgsoap-dev \
    libspdlog-dev \
    software-properties-common \
    unixodbc-dev \
    wget

# Make g++ 6 the default g++ executable
RUN update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-6 90

# Google Fruit dependency injection, build install remove old files
RUN mkdir gfruit &&\
    cd gfruit &&\
    wget https://github.com/google/fruit/archive/v3.4.0.tar.gz &&\
    tar -xvzf v3.4.0.tar.gz &&\
    cd fruit-3.4.0 &&\
    cmake -DCMAKE_BUILD_TYPE=Release -DFRUIT_USES_BOOST=False . && make -j &&\
    make install &&\
    ldconfig

# Get gtest libraries, compile, move to lib folder, cleanup
RUN apt-get install libgtest-dev -y -qq &&\
    cd /usr/src/gtest &&\
    cmake CMakeLists.txt &&\
    make &&\
    cp *.a /usr/lib &&\
    cd .. &&\
    rm -R gtest
    
WORKDIR ~

RUN wget https://dev.mysql.com/get/Downloads/Connector-ODBC/8.0/mysql-connector-odbc-8.0.13-linux-ubuntu18.04-x86-64bit.tar.gz

RUN gunzip mysql-connector-odbc-8.0.13-linux-ubuntu18.04-x86-64bit.tar.gz && \
tar xvf mysql-connector-odbc-8.0.13-linux-ubuntu18.04-x86-64bit.tar

RUN cp mysql-connector-odbc-8.0.13-linux-ubuntu18.04-x86-64bit/bin/* /usr/local/bin

RUN cp mysql-connector-odbc-8.0.13-linux-ubuntu18.04-x86-64bit/lib/* /usr/local/lib

RUN myodbc-installer -a -d -n "MySQL8Driver" -t "Driver=/usr/local/lib/libmyodbc8w.so" && myodbc-installer -a -d -n "MySQL8" -t "Driver=/usr/local/lib/libmyodbc8a.so"

WORKDIR /usr/src/cadg

# Download cpplint.py and set the file permissions so that it is executable
RUN wget https://raw.githubusercontent.com/google/styleguide/gh-pages/cpplint/cpplint.py &&\
    chmod +x cpplint.py

### Concludes base image
