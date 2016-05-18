#include<string>
using namespace std;

class Seed {

public:
  int port;
  int socket_fd;

  Seed(int port) {
    struct addrinfo *result, *rp;
    struct addrinfo hints;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;    /* Allow IPv4 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    int s = getaddrinfo(NULL, port, &hints, &result);

    for (rp = result; rp != NULL; rp = rp->ai_next) {

      socket_fd = socket(rp->ai_family, rp->ai_socktype,
		   rp->ai_protocol);

      if (socket_fd == -1)
	continue;

      if (bind(socket_fd, rp->ai_addr, rp->ai_addrlen) == 0)
	break;                  /* Success */

      close(socket_fd);
    }

    if (rp == NULL) {               /* No address succeeded */
      fprintf(stderr, "Could not bind\n");
      exit(EXIT_FAILURE);
    }

    freeaddrinfo(result);           /* No longer needed */
  };


  bool tracker_register(string hostname, string secret) {
    tracker_transport.send(hostname + "+++++++++++++++" + secret);
  }

  bool tracker_unregister(string hostname, string secret) {
    tracker_transport.send(hostname + "---------------" + secret);
  }
};
