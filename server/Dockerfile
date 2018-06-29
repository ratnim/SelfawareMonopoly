FROM ubuntu:14.04

ENV DEBIAN_FRONTEND=noninteractive

RUN sudo apt-get update
RUN sudo apt-get -y upgrade
RUN sudo apt-get install -y software-properties-common curl
RUN sudo -E apt-add-repository -y "ppa:ubuntu-toolchain-r/test"
RUN curl -sSL "http://apt.llvm.org/llvm-snapshot.gpg.key" | sudo -E apt-key add -
RUN echo "deb http://apt.llvm.org/precise/ llvm-toolchain-precise-3.9 main" | sudo tee -a /etc/apt/sources.list > /dev/null
RUN sudo -E apt-add-repository -y "ppa:george-edison55/precise-backports"
RUN sudo -E apt-add-repository -y "ppa:beineri/opt-qt-5.10.1-trusty"


RUN sudo -E apt-get -yq update &>> ~/apt-get-update.log
RUN sudo -E apt-get -yq --no-install-suggests --no-install-recommends --force-yes install cmake cmake-data gcc-5 g++-5 qt510-meta-minimal qt510websockets
RUN source /opt/qt510/bin/qt510-env.sh

COPY . ~/server

RUN mkdir build
RUN cd build
RUN cmake .. && make

RUN ./server
