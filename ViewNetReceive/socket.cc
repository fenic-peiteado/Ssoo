#include "socket.h"

Socket::Socket(const sockaddr_in& address) {
  fd_ = socket(AF_INET, SOCK_DGRAM, 0);
  if (fd_ < 0) {
    throw "no se pudo crear el socket: ";
    // std::strerror(errno)
  }
  int result =
      bind(fd_, reinterpret_cast<const sockaddr*>(&address), sizeof(address));
  if (result < 0) {
    throw "Error en el bind ";
  }
}

Socket::~Socket() { close(fd_); }
//
void Socket::send_to(const Message& message, const sockaddr_in& address) {
  int result =
      sendto(fd_, message.text.data(), message.text.size(), 0,
             reinterpret_cast<const sockaddr*>(&address), sizeof(address));
  //
  if (result < 0) {
    throw "falló sendto: ";
  }
}
void Socket::receive_from(Message& message, sockaddr_in& address) {
  int result =
      recvfrom(fd_, message.text.data(), message.text.size(), MSG_WAITALL, 0,
               reinterpret_cast<socklen_t*>(sizeof(address)));
  if (result < 0) {
    throw "falló recvfrom: ";
  }
  char* remote_ip = inet_ntoa(address.sin_addr);
  int remote_port = ntohs(address.sin_port);
  message.text[1023] = '\0';
  std::cout << "El sistema " << remote_ip << ":" << remote_port
            << " envió el mensaje '" << message.text.data() << "'\n";
}