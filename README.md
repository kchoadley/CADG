# CADG Centralized Aggregator and Dissemination Gateway

This is an open source solution for a FEMA IPAWS-like alert aggregator. [![Build Status](https://api.travis-ci.org/OS-WASABI/CADG.svg?branch=dev)](https://travis-ci.org/OS-WASABI/CADG)

## Table of Contents
* [Docker Compose](#docker-compose)
* [Install](#install)
* [Running](#running)
* [Credits](#credits)

## Docker-Compose
The preferred and simplest 
Launch the application with Docker compose from the [docker-cadg-compose](docker-cadg-compose) directory with
```
docker-compose up
```

## Install
On Ubuntu 18.04 LTS, run the following [env-setup.sh](docker-test-env/env-setup.sh) to install all needed dependencies.
```
sudo ./env-setup.sh
```
## Running
How to run individual modules.
### REST-Server
From the [rest-server](rest-server) directory
```
mkdir build
cd build
cmake -G "Unix Makefiles" ..
make
./cadg-rest-server
```
### Testing
From the [test](test) directory
```
mkdir build
cd build
cmake -G "Unix Makefiles" ..
make
./runTests
```

## Credits
Dev | Name
-------|------
![Mike McCulley](https://avatars2.githubusercontent.com/u/37458102?s=64&v=4) | [Mike McCulley](https://github.com/ASUMike)
![Kristofer Hoadley](https://avatars2.githubusercontent.com/u/22945482?s=64&v=4) | [Kristofer Hoadley](https://github.com/kchoadley)
![Shawn Hulce](https://avatars3.githubusercontent.com/u/26700431?s=64&v=4) | [Shawn Hulce](https://github.com/SHulce)
![Ross Arcemont](https://avatars0.githubusercontent.com/u/23668393?s=64&v=4) | [Ross Arcemont](https://github.com/SilverStar07)
![Vaniya Agrawal](https://avatars0.githubusercontent.com/u/23622647?s=64&v=4) | [Vaniya Agrawal](https://github.com/vsagrawal0)