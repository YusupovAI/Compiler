FROM ubuntu:18.04

RUN apt-get update 
RUN apt-get install -y wget tar cmake make g++ vim flex
RUN wget https://ftp.gnu.org/gnu/bison/bison-3.5.1.tar.gz && tar -zxvf bison-3.5.1.tar.gz 
RUN cd bison-3.5.1 && ./configure && make && make install 
ARG UID=1000
ARG username=default_user
RUN useradd -u $UID -m $username && mkdir /home/$usernane/compilers

USER $username

WORKDIR /home/$username
ENTRYPOINT ["bash"]
