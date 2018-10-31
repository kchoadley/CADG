# CADG Apache Docker Image

This utilizes version 2.4 of the Apache httpd server. The configuration file is extremely basic at present and will need to be built. As such, this has been tagged as prototype for the time being.

To build locally

docker build -t image-name:tag .

Note: Replace image-name:tag with your desired nomenclature. Also note that you can pull the current prototype image from the docker hub with:

docker pull os-wasabi/cadg-apache:prototype


Run Directions:
To run this container you will need to provide it port information as well as a name. As below:

docker run -d --name container-name -p 8080:80 cadg-apache:prototype

Note: If you built the image locally and named it something different substitute that in the previous command.
