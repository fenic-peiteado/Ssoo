#include <arpa/inet.h>
#include <netinet/in.h>  //https://www.gta.ufrj.br/ensino/eel878/sockets/sockaddr_inman.html
#include <stdint.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <cerrno>
#include <iostream>

#include "socket.h"

sockaddr_in make_ip_address(int port,
                            const std::string& ip_address = std::string());
int main() {
    try {
 sockaddr_in addr_receive = make_ip_address(3009);
 Socket socket_receive(addr_receive);

  Message dato;

  while(true){
    socket_receive.receive_from(dato,addr_receive);
  }
    } catch (const char* dato) {
    std::cerr << dato << '\n';
  }
  return 0;
}

sockaddr_in make_ip_address(int port, const std::string& ip_address) {
  sockaddr_in description{};
  if (ip_address.empty()) {
    description.sin_family = AF_INET;
    description.sin_port = htons(port);
    description.sin_addr.s_addr = htonl(INADDR_ANY);
  } else {
    const char* aux = &ip_address[0];
    description.sin_family = AF_INET;
    description.sin_port = htons(port);
    
    // comprobar que la direccion es validad
    if(!inet_aton(aux, &description.sin_addr)){
      std::cout << "Error en la conversion inet aton";
    }

    description.sin_addr.s_addr=htonl(description.sin_addr.s_addr);
  }
  return description;
}
