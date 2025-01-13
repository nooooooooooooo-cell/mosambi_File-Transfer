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
void path(std::string path, std::vector<std::string> &data)
{
    DIR *ep = opendir(path.c_str());
    if (ep != NULL)
    {
        while (auto it = readdir64(ep))
        {
            data.push_back(it->d_name);
        }
    }
}
int main(int argc, char const *argv[])
{
    std::vector<std::string> dir;
    path(".", dir);

    if (argc == 1)
        exit(0);
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
    ret = bind(s, (sockaddr *)&addr, sizeof(addr));
    if (ret < 0)
    {
        end("Bind Error");
    }
    ret = listen(s, 5);
    if (ret < 0)
    {
        end("Listen Error");
    }
    int c = accept(s, NULL, NULL);
    if (c < 0)
    {
        end("Accept Error");
    }
    std::cout << "Connected" << std::endl;
    int ch;
    char buf[256] = {'\0'};
    read(c, &ch, sizeof(int));
    if (ch == 1)
    {
        ch = dir.size();
        write(c,&ch,sizeof(int));
        for(auto it:dir){
            it+='\n';
            write(c,it.c_str(),it.size());
        }
    }
    else if(ch == 2){
        read(c,buf,sizeof(buf));
        FILE *fp = fopen(buf,"r");
        if(fp==NULL)exit(0);
        int n;
        fseek(fp,0,SEEK_END);
        n = ftell(fp);
        rewind(fp);
        write(c,&n,sizeof(int));
        char ch[1] = {'\n'};
        while(fread(ch,sizeof(char),1,fp)){
            write(c,ch,sizeof(ch));
        }
        std::cout << "Done" << std::endl;
    }
    std::cout << "Client Disconnected" << std::endl;
    close(c);
    exit(0);
    return 0;
}