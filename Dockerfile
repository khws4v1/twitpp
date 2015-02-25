FROM ubuntu
MAINTAINER khws4v1 <khws4v1@gmail.com>

RUN sudo apt-get -y update
RUN sudo apt-get -y install g++-4.8 libboost1.55-all-dev cmake libssl-dev

ADD . /tmp/build
WORKDIR /tmp/build
RUN if [ -e CMakeCache.txt ]; then rm -f CMakeCache.txt; fi
RUN if [ -e CMakeFiles ]; then rm -rf CMakeFiles; fi
RUN cmake . 
RUN make VERBOSE=1
RUN make install