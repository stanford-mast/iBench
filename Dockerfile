FROM gcc:6.3.0

ADD . /ibench

RUN cd /ibench && make

WORKDIR /ibench/src