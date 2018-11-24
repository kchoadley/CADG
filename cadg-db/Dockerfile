# Get MySQL image from Docker Hub

FROM mysql

COPY *.sql .

RUN --default-authentication-plugin=mysql_native_password && mysql -p=$MYSQL_ROOT_PASSWORD < create_cadg_db.sql