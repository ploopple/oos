FROM --platform=linux/x86_64 alpine:3.14

COPY . /os

WORKDIR /os


RUN apk update && \ 
    apk add binutils && \ 
    apk add gcc && \ 
    apk add make && \ 
    apk add gdb && \  
    echo "done" \ 
