docker build -t os .
docker run -it -v .:/os os
target remote host.docker.internal:1234

lldb build/os
gdb-remote localhost:1234
b kernel_main
next
lldb -o "gdb-remote localhost:1234" build/os