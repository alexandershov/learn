#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#include <iostream>

int main() {
  struct stat file_stat;
  stat("../src/main.cpp", &file_stat);
  std::cerr << "ino = " << file_stat.st_ino
    // change time, changed when either inode or contents changes
	    << ", ctime = " << file_stat.st_ctime
    // access time, can be changed by `touch`. Usually doesn't change when you read a file (as an optimization).
    // You can bypass this optimization by changing noatime to atime in /etc/fstab and remounting
	    << ", atime = " << file_stat.st_atime
    // modification time, changed when content changes
	    << ", mtime = " << file_stat.st_mtime
	    << "\n";
  if (close(1) != 0) {
    std::cerr << "couldn't close stdout\n";
  }
  // fd is equal to minimum free number, in this case 1 (because we closed 1)
  int fd = open("../src/main.cpp", O_RDONLY);
  std::cerr << "open result " << fd << "\n";
}
