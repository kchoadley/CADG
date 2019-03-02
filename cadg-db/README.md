# CADG-DB
Database for the CADG. Contains the [sql file](create_cadg_db.sql) to create the database as well as a [Dockerfile](Dockerfile) to run it in.

## Schemas
Below are all the schemas and the tables contained.
### CADG
Main schema of the database, holds most tables.
#### Alert
An alert is a alert CAP message that has been sent to the CADG and has been verified to be properly formatted and valid.
#### Disseminator
Disseminators are the entities that will receive an emergency alert to be further disseminated to their end users. Currently we only plan to support CMSP (Commercial Mobile Service Providers).
#### Originator
Originators are entities that send alerts to the CADG system to be further processed and disseminated.
### ADMIN
Holds information about administrators of the CADG system.

## Docker
To use Docker to run the CADG database:
1. Set `MYSQL_ROOT_PASSWORD` in the Dockerfile.
2. Build the image with `docker build -t cadg-db .` in the cadg-db directory.
3. Run the container with `docker run -p 3360:3360 cadg-db` to expose the port 3360 locally.
