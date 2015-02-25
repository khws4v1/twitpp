FROM ubuntu
MAINTAINER khws4v1 <khws4v1@gmail.com>

RUN sudo apt-get -y update
RUN sudo apt-get -y install g++-4.8 libboost1.55-all-dev cmake libssl-dev

ADD . /tmp/build
WORKDIR /tmp/build
RUN test -e CMakeCache.txt && rm -f CMakeCache.txt
RUN test -e CMakeFiles     && rm -rf CMakeFiles
RUN cmake . 
RUN make
RUN make install