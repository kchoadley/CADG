# Central Aggregator and Dissemination Gateway REST Server

This is an open source solution designed to be utilized as a substitute for FEMA's IPAWS system.

## Using Docker to Build and Test Locally
To run locally, first build the image.
```
docker build --rm -t cadg-rest-server .
```
Then run with the following command. The first port number is where your computer will be able to access endpoint.
```
docker run -d -it -p 8080:8080 cadg-rest-server
```
In Postman or your browser, navigate to
```
http://localhost:8080/v1/cadg/api/users
```
The response for a GET request will be for the whole collection of users
```
{
    "users": {
        "12": {
            "name": "Shawn Hulce",
            "password": "ecluhwordpass!4"
        },
        "17": {
            "name": "Kris Hoadley",
            "password": "TheBestLikeNoOneEverWas"
        }
    }
}
```
To get a user by id
```
http://localhost:8080/v1/aoi/api/users/12
```
The response
```
{
    "users": {
        "12": {
            "name": "Shawn Hulce",
            "password": "ecluhwordpass!4"
        }
    }
}
```
To get a user by partial name match, use a query like
```
http://localhost:8080/v1/aoi/api/users?name=kris
```
The response
```
{
    "users": {
        "17": {
            "name": "Kris Hoadley",
            "password": "TheBestLikeNoOneEverWas"
        }
    }
}
```
A POST with a well formed body with the same schema will add new users.
Example POST body
```
{
    "users": {
        "23": {
            "name": "Michael McCully",
            "password": "Starbucks32"
        },
        "97": {
            "name": "Vaniya Agawal",
            "password": "p8932rqfn;fjp8weER$Q#E9"
        },
        "76": {
            "name": "Ross Arcemont",
            "password": "dankmemes"
        }
    }
}
```
Run a GET again to see the updated collection of users!