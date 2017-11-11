#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <iostream>

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "usage: files /path/to/file/to/stat\n";
    return 1;
  }
  std::cerr << "euid = " << geteuid() << "\n";
  struct stat file_stat;
  stat(argv[1], &file_stat);
  std::cerr << "ino = " << file_stat.st_ino
    // change time, changed when either inode or contents changes
	    << ", ctime = " << file_stat.st_ctime
    // access time, can be changed by `touch`. Usually doesn't change when you read a file (as an optimization).
    // You can bypass this optimization by changing noatime to atime in /etc/fstab and remounting
	    << ", atime = " << file_stat.st_atime
    // modification time, changed when content changes
	    << ", mtime = " << file_stat.st_mtime
	    << "\n";
  // is suid (set user id) is set, then when you're executing a file you'll
  // effectively run it as file's owner
  std::cerr << "suid = " << (file_stat.st_mode & S_ISUID) << "\n";
  std::cerr << "sgid = " << (file_stat.st_mode & S_ISGID) << "\n";
  // is sticky bit is set, then only owner of file can delete/rename it
  // this is used for /tmp directory, everyone can create files in it
  // but you can't change other's files
  std::cerr << "sticky = " << (file_stat.st_mode & S_ISVTX) << "\n";
  if (close(1) != 0) {
    std::cerr << "couldn't close stdout\n";
  }
  // fd is equal to minimum free number, in this case 1 (because we closed 1)
  int fd = open("../src/main.cpp", O_RDONLY);
  std::cerr << "open result " << fd << "\n";
}
