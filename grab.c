//#include <limits.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define FRAMES 10
#define FPS 2
#define MPLAYER_DEFAULT_FILENAME "00000001.png"


int main (int argc, char *argv[]) {
	char *argv_mplayer[7];
	argv_mplayer[0] = "mplayer";
	argv_mplayer[1] = "-vo";
	argv_mplayer[2] = "png";
	argv_mplayer[3] = "-frames";
	argv_mplayer[4] = "1";
	argv_mplayer[5] = "tv://\n";
	argv_mplayer[6] = NULL;

	for (int i = 0; i < FRAMES; i++) {
		pid_t mplayer = fork();
		if (mplayer == 0) {
			execvp("mplayer", argv_mplayer);	
			return -1;
		}

		int status;
		waitpid(mplayer, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
			char filename[FILENAME_MAX];
			sprintf(filename, "%d.png", i);
			int stat = rename(MPLAYER_DEFAULT_FILENAME, filename);
		}
		else if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			printf("!! status: %d\n", status);
		sleep(2);
	}

	return 0;

}