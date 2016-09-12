#include<string>
using namespace std;

class Seed {

public:
  int port;
  int socket_fd;

  Seed(int port) {
    struct addrinfo *result, *rp;
    struct addrinfo hints;

  }

  bool tracker_register(string hostname, string secret) {
    tracker_transport.send(hostname + "+++++++++++++++" + secret);
  }

  bool tracker_unregister(string hostname, string secret) {
    tracker_transport.send(hostname + "---------------" + secret);
  }
};
