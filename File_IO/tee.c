#include <sys/stat.h>
#include <fcntl.h>
#include "../lib/tlpi_hdr.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main(int argc, char* argv[]) {

	int openFd, openFlags;
	mode_t filePerms;
	int is_append = 0;
	ssize_t numRead, numWritten;
	char buffer[BUF_SIZE];
	if (argc < 2 || strcmp(argv[1], "--help") == 0) {
		usageErr("%s file\n", argv[0]);
	} else if (argc < 2 && strcmp(argv[1], "-a") == 0) {
		usageErr("file name miss");
	} else if (argc == 3 && strcmp(argv[1], "-a") == 0) {
		is_append = O_APPEND;
	}

	openFlags = O_CREAT | O_RDWR | is_append;
	filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
				S_IROTH | S_IWOTH;
	if (is_append) {
		openFd = open(argv[2], openFlags, filePerms);
	} else {
		openFd = open(argv[1], openFlags, filePerms);
	}
	if (openFd == -1) { errExit("opening files %s", argv[2]); }
	while ((numRead = read(STDIN_FILENO, buffer, BUF_SIZE)) > 0) {
		if (write(openFd, buffer, numRead) != numRead) {
			fatal("couldn't write whole buffer");
		}
	}
	if (numRead == -1) { errExit("read"); }
	if (close(openFd) == -1) { errExit("close input"); }

}
