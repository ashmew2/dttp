#include<cstdlib>
#include<iostream>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string>
using namespace std;

class Seed {

public:
  int port;
  int socket_fd;
  sockaddr_in tracker;
  
  Seed() {
    socket_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(socket_fd < 0)
      exit(-1);
    
    tracker.sin_addr.s_addr = inet_addr("127.0.0.1");
    tracker.sin_port = htons(40000);
    tracker.sin_family = AF_INET;

    if(connect(socket_fd, (struct sockaddr *)&tracker, sizeof(tracker)) < 0)
      exit(-1);
  }

  bool tracker_register(string secret) {
    if(send(socket_fd, "seed_register_1337", 18, 0) != 18) {
      cout<<"Registration failed with tracker!";
      exit(-1);
    }
  }

  bool tracker_unregister(string hostname, string secret) {
    if(send(socket_fd, "seed_unregister_1337", 20, 0) != 20) {
      cout<<"Unregistration failed with tracker!";
      exit(-1);
    }
  }
};

int main(int argc, char *argv[]) {
  Seed mySeed = Seed();
  mySeed.tracker_register("oogabooga");
}
