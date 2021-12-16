#include "file.h"
File::File(){
      fd_ = open("prueba.txt", O_RDONLY);
}
    File::~file(close(fd_));