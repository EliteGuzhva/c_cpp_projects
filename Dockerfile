FROM ubuntu:20.04

RUN apt-get update && \
    DEBIAN_FRONTEND=non-interactive \
    apt-get install -y --no-install-recommends \
    build-essential git ninja-build cmake python3-dev python3-pip

RUN pip3 install -U conan

CMD [ "bash" ]
