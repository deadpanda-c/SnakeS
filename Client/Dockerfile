# Build the graphical cpp app using CMake and X11
FROM gcc:latest

# Install CMake
RUN apt-get update; apt-get install -y cmake

# Install X11 and SFML dependencies
RUN apt-get update; \
    apt-get install -y \
    build-essential \
    git \
    dbus-x11 \
    libx11-dev \
    libsfml-dev \
    libfreetype-dev \
    libfreetype6 \
    libfreetype6-dev \
    libxrandr-dev \
    libxcursor-dev \
    libudev-dev \
    libopenal-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev \
    libdrm-dev \
    libgbm-dev

# These commands copy your files into the specified directory in the image
# and set that as the working location
COPY . /usr/src/snakes
WORKDIR /usr/src/snakes

# Generating a universally unique ID for the Container
RUN  dbus-uuidgen > /etc/machine-id

# This command compiles your app based on the CMakeLists.txt file
RUN cmake . && make

# This command runs your application, comment out this line to compile only
CMD ["./c_snakes"]

LABEL Name=c_snakes Version=0.0.1
