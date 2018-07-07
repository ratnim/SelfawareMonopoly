FROM ubuntu:xenial

MAINTAINER martin.fischer@student.hpi.de

# Install Cpp Dependecies
RUN apt-get -y update && apt-get install -y --no-install-recommends \
  software-properties-common\
  build-essential \
  gcc-5 \
  g++-5 \
  libx11-dev \
  mesa-common-dev \
  libglu1-mesa-dev \
  && apt-get autoremove

# Install QT 5.10 Xenial
RUN apt-add-repository ppa:beineri/opt-qt-5.10.0-xenial
RUN apt-get update --fix-missing \
  && apt-get install -y --fix-missing --no-install-recommends \
  qt510-meta-minimal \
  qt510websockets \
  && apt-get autoremove
RUN /bin/bash -c "source /opt/qt510/bin/qt510-env.sh"

# Install sudo and create user
RUN apt-get update \
  && apt-get install -y --no-install-recommends \
  sudo
RUN adduser --disabled-password --gecos '' docker
RUN adduser docker sudo
RUN echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers
USER docker

# Install cmake
ADD https://cmake.org/files/v3.11/cmake-3.11.4-Linux-x86_64.sh /cmake-3.11.4-Linux-x86_64.sh
RUN sudo mkdir /opt/cmake
RUN sudo sh /cmake-3.11.4-Linux-x86_64.sh --prefix=/opt/cmake --skip-license
RUN sudo ln -s /opt/cmake/bin/cmake /usr/local/bin/cmake
RUN cmake --version

# Prepare files
WORKDIR /usr/src/app/server
COPY ./source ./source
COPY ./cmake ./cmake
COPY ./tests ./tests
COPY ./CMakeLists.txt ./CMakeLists.txt

# CI test file
COPY ./test.sh ./test.sh

# Build Server
WORKDIR /usr/src/app/server/build
RUN sudo cmake -DCMAKE_PREFIX_PATH=/opt/qt510 .. \
  && sudo make

# Prepare Run
WORKDIR /usr/src/app
EXPOSE 31415
ENTRYPOINT [ "./server/build/server" ]
