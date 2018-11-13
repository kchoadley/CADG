<<<<<<< 66012de80710ec1cfde28b119c18d7961a1fdef4
### Create the CADG Apache web frontend image
=======
### Create the AOI Apache web frontend image
>>>>>>> Prototype apache docker image built. Configuration changes will be required later.

# Get base apache image from Docker Hub
FROM httpd:2.4

# Install VIM editor for configuration changes inside the machine 
# This is not the recommended way to do it, its best to configure the file first.
# However, it may be necessary to modify depending on the server.
RUN apt-get update
<<<<<<< e3d19c0619dff417359b2a58de99f8f71d06e848
<<<<<<< fd91337dfaecc0701fecb2a15d05a0353768652a
<<<<<<< 66012de80710ec1cfde28b119c18d7961a1fdef4
RUN apt-get install vim nano -y
=======
RUN apt-get install vim -y
>>>>>>> Prototype apache docker image built. Configuration changes will be required later.
=======
RUN apt-get install vim nano -y
>>>>>>> PR Review modifications. Minor adjustments
=======
RUN apt-get install vim -y
>>>>>>> Revert "PR Review modifications. Minor adjustments"

# Copy apache configuration file into the Docker
COPY "./apache_config/*" "/usr/local/apache2/conf"

# Copy any HTML files to be served locally into the Docker
COPY "./html_files/*" "/usr/local/apache2/htdocs"


