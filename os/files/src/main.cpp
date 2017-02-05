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
}
