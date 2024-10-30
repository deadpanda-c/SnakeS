# Build and run the server of the SnakeS game
FROM gcc:latest

# Install CMake
RUN apt-get update; apt-get install -y cmake

# These commands copy your files into the specified directory in the image
# and set that as the working location
COPY . /usr/src/snakes
WORKDIR /usr/src/snakes

# This command compiles your app based on the CMakeLists.txt file
RUN cmake . && make

# This command runs your application, comment out this line to compile only
CMD ["./s_snakes"]

LABEL Name=s_snakes Version=0.0.1
