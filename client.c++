#include <bits/stdc++.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <dirent.h>
#include <netinet/in.h>
#include <arpa/inet.h>
void end(std::string e)
{
    perror(e.c_str());
    exit(0);
}
int main(int argc, char const *argv[])
{
    if (argc == 1)
    {
        exit(1);
    }
    int ret;
    int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s < 0)
    {
        end("Socket Error");
    }
    sockaddr_in addr;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(std::stoi(argv[2]));
    ret = connect(s, (sockaddr *)&addr, sizeof(addr));
    if (ret < 0)
    {
        end("Connect Error");
    }
        int input;
        std::cin >> input;
        write(s, &input, sizeof(int));
        if (input == 1)
        {
            char buf[256];
            read(s, &input, sizeof(int));
            for (int i = 0; i < input; i++)
            {
                recv(s, buf, sizeof(buf), 0);
                std::cout << buf;
                bzero(buf, sizeof(buf));
            }
            
        }
        else if (input == 2)
        {
            std::string file;
            char buf[1];
            std::cout << "Enter the file name:";
            std::cin >> file;
            write(s, file.c_str(), file.size());
            std::cout << "Set the Filename for Save:";
            std::cin >> file;
            FILE *fp = fopen(file.c_str(), "w");
            read(s, &input, sizeof(input));
            for (int i = 0; i < input; i++)
            {
                read(s, buf, sizeof(buf));
                fwrite(buf, sizeof(buf), 1, fp);
            }
            fclose(fp);
        }
        else if (input == 3)
        {
            std::cout << "Exited" << std::endl;
            exit(0);
        }
    exit(0);
}