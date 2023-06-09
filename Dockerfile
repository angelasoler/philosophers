#Same version as the host so the binary works in boths sides
#Independent of where it was build
FROM gcc:12

ENV HOME /root

SHELL ["/bin/bash", "-c"]

RUN apt update &&\
    apt -y --no-install-recommends install \
    apt-utils \
    build-essential \
    make \
    valgrind \
    libpthread-stubs0-dev
