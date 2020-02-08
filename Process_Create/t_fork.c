#include "../lib/tlpi_hdr.h"

static int idata = 111;

int main(int argc, char* argv[]) {
	int istack = 222;
	pid_t chiildPid;

	switch (chiildPid = fork()) {
		case -1:
			errExit("fork");
			break;
		case 0:
			idata *= 3;
			istack *= 3;
			break;
		default:
			sleep(3);
			break;
	}

	printf("PID=%ld %s idata=%d\n", (long)getpid(),
			(chiildPid == 0) ? "(child)" : "(parent)", idata, istack);
	exit(EXIT_SUCCESS);
}
