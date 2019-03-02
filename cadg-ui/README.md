# CADG-UI
A React app frontend for interacting with the CADG system. It supports, or will support, several functions:
* View current alerts
* View/edit Alert Originators
* View/edit Alert Disseminators
* View/edit CADG Users

## NPM Scripts
In the project directory, you can run:

### `npm install`
You should run this first to install dependencies.

### `npm start`
Runs the app in the development mode.<br>
Open [http://localhost:3000](http://localhost:3000) to view it in the browser.<br>
The page will reload if you make edits.<br>
You will also see any lint errors in the console.

### `npm run build`
Builds the app for production to the `build` folder.<br>
It correctly bundles React in production mode and optimizes the build for the best performance.

A postbuild script in the [package.json](package.json) copies the build files to the `../docker-cadg-apache/html_files/` directory for deployment from the Apache server in a docker container.<br>
It only works on Linux (only tested on Ubuntu), else it fails the first check and won't continue (but won't fail the build either).<br>
The post build script will clean the `../docker-cadg-apache/html_files/` before copying over files.

## Docker
A docker container is used as a build container during the CADG docker-compose to ensure the most recent version of the CADG-UI is deployed. <br>
It is not designed for running the React app locally, but with some modification would work for such a use case. The better recommended way to test locally is to use the Apache docker container to run it locally.

To run inside the Apache docker container:
1. Run `npm run build`
2. If you are **not** running Ubuntu, or in WSL (Windows Subsytem for Linux), you will need to copy the build files from `/build` to `../docker-cadg-apache/html_files/`
3. See instructions to build and run the apache docker.

## Dependencies
Below is a list of major libraries and tools we used in the CADG-UI React app.
* babel
* react-bootstrap
* react-redux
* react-router-dom
* redux-thunk