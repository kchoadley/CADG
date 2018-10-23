# Travis Test - CADG Build and Test Environment Base Image Docker File

If the base image needs to be adjusted, this is the Dockerfile that generates it. Leave off `my-tag` to update the latest version for production.

Build simply with 
```
docker build -t cadg-test-env:my-tag .
```

To push image to DockerHub
```
$ docker tag cadg-test-env:my-tag oswasabi/cadg-test-env:my-tag

$ docker push oswasabi/cadg-test-env:my-tag
```