# CADG Apache
Utilizes version 2.4 of the Apache httpd server Docker image. There are two components the Apache serves, the REST API and the React user interface. This Apache container is designed to run as the first point of contact for the docker-compose, encapsulating the other components.

There are two components that must be in their respective sub-directories when building the Apache image.<br>
The built React web app in `./html_files` and<br>
the SSL certificate in `./ssl_cert`.

If you are building the entire application with docker-compose, you only need to provide the SSL certificate. The React app is built by the docker-compose.

## Docker
The Apache Docker is meant to be used in the docker-compose, but it can be run separately for testing, say for ensuring the React web app serves correctly from within the Apache without docker-composing up the whole application.

To build locally
```bash
docker build -t cadg-apache .
```
To run the container
```bash
docker run -d -p 8080:80 cadg-apache
```
