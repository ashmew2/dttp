#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <iostream>
using namespace std;
#define BUF_SIZE 500

/****
Purpose of this file is to act as a client
For example, a web browser and simply contact the tracker and subsequently the seeds.
Once mature enough, most of this code should go into the Proxy Layer
****/

int
main(int argc, char *argv[]) {
  sockaddr_in client_socket, server;
  int client_fd;

  client_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(client_fd <0)
    exit(client_fd);

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  server.sin_port = htons(40000);

  cout<<"Connecting to server..";
  if(connect(client_fd, (struct sockaddr *)&server, sizeof(server)) < 0)
    exit(-1);

  cout<<"Client bye"<<endl;
}
