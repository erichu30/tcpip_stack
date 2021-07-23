# UDP_socket_server

```
cd UDP_socket_server
gcc -o server.out server.c
gcc -o client.out client.c
./server.out 8888   # port number depends on you
```

open another terminal window
```
cd UDP_socket_server
./client.out localhost 8888
```