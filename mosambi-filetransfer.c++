#include<bits/stdc++.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
int main()
{
    signal(SIGINT, exit);
    std::string dash = "====Welcome to Mosambi File Transfer====\n"
                       "1.Send File\n"
                       "2.Receive File";
    std::cout << dash << std::endl;
    int input;
    std::cin >> input;
    if (input == 1)
    {
        std::string ip, name;
        std::cout << "Enter the Server IP address:";
        std::cin >> ip;
        int port;
        std::cout << "Enter the Server Port:";
        std::cin >> port;
        std::cout << "Enter the File name:";
        std::cin >> name;
        int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (s < 0)
        {
            perror("Socket Error");
            exit(0);
        }
        else
            perror("Socket");
        sockaddr_in addr;
        addr.sin_addr.s_addr = inet_addr(ip.c_str());
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        int ret = bind(s, (sockaddr *)&addr, sizeof(addr));
        if (ret < 0)
        {
            perror("Bind Error");
            exit(0);
        }
        else
            perror("Bind");
        ret = listen(s, 5);
        if (ret < 0)
        {
            perror("Listen Error");
            exit(0);
        }
        else
            perror("Listen");
        sockaddr_in client;
        socklen_t i = sizeof(client);
        int c = accept(s, (sockaddr *)&client, &i);
        if (c < 0)
        {
            perror("Accept Error");
            exit(0);
        }
        else
            perror("Accept");
        std::cout << "Connected:" << inet_ntoa(client.sin_addr) << ":" << htons(client.sin_port) << std::endl;
        char buf[1] = {'\0'};
        int f = 0;
        FILE *fp = fopen(name.c_str(), "r");
        while (fread(buf, sizeof(buf), 1, fp))
        {
            send(c, buf, 1, 0);
            f++;
        }
        std::cout << "Sended Buffer Size:" << f << std::endl;
        std::cout << "File is Sended" << std::endl;
        fclose(fp);
    }
    else if (input == 2)
    {
        std::string ip, name;
        std::cout << "Enter the Server IP address:";
        std::cin >> ip;
        int port;
        std::cout << "Enter the Server Port:";
        std::cin >> port;
        std::cout << "Enter the Save name for incoming file:";
        std::cin >> name;
        int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (s < 0)
        {
            perror("Socket Error");
            exit(0);
        }
        else
            perror("Socket");
        sockaddr_in addr;
        addr.sin_addr.s_addr = inet_addr(ip.c_str());
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        int ret = connect(s, (sockaddr *)&addr, sizeof(addr));
        if (ret < 0)
        {
            perror("Connect Error");
            exit(0);
        }
        else
            perror("Connection");
        char buf[1] = {'\0'};
        int i = 0;
        FILE *fp = fopen(name.c_str(), "w");
        while (true)
        {
            ret = recv(s, buf, 1, 0);
            if (ret <= 0)
            {
                perror("Client Disconnected");
                break;
            }
            i++;
            fwrite(buf, sizeof(buf), 1, fp);
        }
        std::cout << "Buffer Size:" << i << std::endl;
        std::cout << "Received File" << std::endl;
        fclose(fp);
    }
    else
    {
        std::cout << "invalid num" << std::endl;
        exit(0);
    }
    return 0;
}