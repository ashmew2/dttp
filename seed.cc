#include<string>
using namespace std;
// Return: True or false denoting success

class Seed {

public:
  bool tracker_register(string hostname, string secret) {
    tracker_transport.send(hostname + "+++++++++++++++" + secret);
  }

  bool tracker_unregister(string hostname, string secret) {
    tracker_transport.send(hostname + "---------------" + secret);
  }
};

