#include <sys/stat.h>

#include <iostream>

int main() {
  struct stat file_stat;
  stat("../src/main.cpp", &file_stat);
  std::cerr << "ino = " << file_stat.st_ino
	    << ", ctime = " << file_stat.st_ctime
	    << ", atime = " << file_stat.st_atime
	    << ", mtime = " << file_stat.st_mtime
	    << "\n";
}
