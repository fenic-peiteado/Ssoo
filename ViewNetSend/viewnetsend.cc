#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>  //https://www.gta.ufrj.br/ensino/eel878/sockets/sockaddr_inman.html
#include <stdint.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <cerrno>
#include <iostream>

#include "socket.h"
// https://man7.org/linux/man-pages/man2/socket.2.html
//  int socket(int domain, int type, int protocol);

// reciba una dirección IP como cadena y un puerto como entero
// y devuelva una estructura sockaddr_in
sockaddr_in make_ip_address(int port,
                            const std::string& ip_address = std::string());
int main() {
  try {
    sockaddr_in addr_send = make_ip_address(2001);
    sockaddr_in addr_send_port = make_ip_address(3009);
    Socket socket_send(addr_send);
    int fd = open("prueba.txt", O_RDONLY);
    if(fd<0){
      throw "Error en la apertura del fichero de lectura";
    }
    Message mensaje;
    while (read(fd, mensaje.text.data(), sizeof(mensaje.text))) {
      socket_send.send_to(mensaje, addr_send_port);
    }

  } catch (const char* dato) {
    std::cerr << dato << '\n';
  }
  return 0;
}

sockaddr_in make_ip_address(int port, const std::string& ip_address) {
  sockaddr_in description;
  if (ip_address == "") {
    description.sin_family = AF_INET;
    description.sin_port = htons(port);
    description.sin_addr.s_addr = htonl(INADDR_ANY);
  } else {
    const char* aux = &ip_address[0];
    description.sin_family = AF_INET;
    description.sin_port = htons(port);
    // comprobar que la direccion es validad
    if (!inet_aton(aux, &description.sin_addr)) {
      throw "error en convertir la ip en make ip address";
    }
    description.sin_addr.s_addr = htonl(description.sin_addr.s_addr);
  }
  return description;
}
