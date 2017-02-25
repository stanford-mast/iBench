FROM gcc:6.3.0

ADD . /ibench

RUN cd /ibench && make

ENV PATH="/ibench/src:${PATH}"

WORKDIR /ibench/src