FROM --platform=linux/x86_64 alpine:3.14

COPY . /os

WORKDIR /os


RUN apk update && \ 
    apk add binutils && \ 
    apk add gcc && \ 
    apk add make && \ 
    apk add gdb && \  
    echo "done"

RUN sh -c "$(wget -O- https://github.com/deluan/zsh-in-docker/releases/download/v1.1.5/zsh-in-docker.sh)" -- \
-a 'CASE_SENSITIVE="true"'

CMD ["zsh"]