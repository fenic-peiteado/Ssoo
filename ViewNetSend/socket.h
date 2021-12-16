#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>  //https://www.gta.ufrj.br/ensino/eel878/sockets/sockaddr_inman.html
#include <stdint.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <array>
#include <cerrno>
#include <iostream>
struct Message {
  std::array<char, 1024> text;
};

class Socket {
 public:
  Socket(const sockaddr_in& address);
  ~Socket();
  void send_to(const Message& message, const sockaddr_in& address);
  void receive_from(Message& message, sockaddr_in& address);

 private:
  int fd_;
};