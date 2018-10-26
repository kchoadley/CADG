### This script automates setting up a
### Build and Test Environment on Ubuntu 18.04 for CADG

# Add ubuntu toolchain repository
apt-get -q -d update
apt-get install -q -y software-properties-common
add-apt-repository -y ppa:ubuntu-toolchain-r/test
apt-get -q -d update

# Install tools
apt-get -q -y install \
    cmake \
    cppcheck \
    g++-6 \
    libcpprest-dev \
    libspdlog-dev \
    software-properties-common \
    wget

# Make g++ 6 the default g++ executable
update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-6 90

# Google Fruit dependency injection, build install remove old files
cd /usr/src &&\
    mkdir gfruit &&\
    cd gfruit &&\
    wget https://github.com/google/fruit/archive/v3.4.0.tar.gz &&\
    tar -xvzf v3.4.0.tar.gz &&\
    cd fruit-3.4.0 &&\
    cmake -DCMAKE_BUILD_TYPE=Release -DFRUIT_USES_BOOST=False . && make -j &&\
    make install &&\
    ldconfig

# Get gtest libraries, compile, move to lib folder, cleanup
cd /usr/src &&\
    apt-get install libgtest-dev -y -q &&\
    cd /usr/src/gtest &&\
    cmake CMakeLists.txt &&\
    make &&\
    cp *.a /usr/lib &&\
    cd .. &&\
    rm -R gtest

# Download cpplint.py and set the file permissions so that it is executable
cd /usr/src &&\
    mkdir cadg &&\
    cd cadg &&\
    wget https://raw.githubusercontent.com/google/styleguide/gh-pages/cpplint/cpplint.py &&\
    chmod +x cpplint.py
