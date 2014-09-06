#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define FRAMES 100
#define FPS 2

int main (int argc, char *argv[]) {
	for (int i = 0; i < FRAMES; i++) {
		char *argv_mplayer[7];
		argv_mplayer[0] = "mplayer";
		argv_mplayer[1] = "-vo";
		argv_mplayer[2] = "png";
		argv_mplayer[3] = "-frames";
		argv_mplayer[4] = "1";
		argv_mplayer[5] = "tv://";
		argv_mplayer[6] = NULL;

		pid_t mplayer = fork();
		if (mplayer > 0)
			execvp("mplayer", argv_mplayer);	
		
		int status;
		waitpid(mplayer, &status, 0);
	}



}