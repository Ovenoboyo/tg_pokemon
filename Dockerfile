# GCC support can be specified at major, minor, or micro version
# (e.g. 8, 8.2 or 8.2.0).
# See https://hub.docker.com/r/library/gcc/ for all supported GCC
# tags from Docker Hub.
# See https://docs.docker.com/samples/library/gcc/ for more on how to use this image
FROM ubuntu:latest

# Update apps on the base image
RUN apt-get -y update && apt-get install -y

# Install the Clang compiler, Conan and cmake
RUN apt-get -y install clang
RUN apt-get -y install software-properties-common
RUN add-apt-repository ppa:deadsnakes/ppa
RUN apt update
RUN apt-get -y install python3.8
RUN apt-get -y install python3-pip
RUN pip3 install conan --upgrade
RUN apt-get -y install cmake
RUN apt-get -y install ninja-build

# These commands copy your files into the specified directory in the image
# and set that as the working location
COPY . /usr/src/tg_pokemon
WORKDIR /usr/src/tg_pokemon

# This command compiles your app using GCC, adjust for your source code
RUN chmod +x scripts/build.sh
RUN ./scripts/build.sh
RUN chmod +x /usr/src/tg_pokemon/build/bin/Pokemon_TG

# This command runs your application, comment out this line to compile only
CMD ["./usr/src/tg_pokemon/build/bin/Pokemon_TG >> /usr/src/log.txt"]

LABEL Name=tg_pokemon Version=0.0.1
