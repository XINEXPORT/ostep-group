#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define LS_PATH "/bin/ls"

void q3and5() {
	pid_t cpid = fork();
	if (cpid == 0) {
		puts("hello");
	} else {
		// sleep(2);
		cpid = wait(&cpid);
		if (cpid == -1) {
			perror("wait");
			puts("wait failed");
		}
		puts("goodbye");
		printf("%d\n", cpid);
	}
}

void q6() {
	pid_t cpid = fork();
	if (cpid == 0) {
		puts("hello");
	} else {
		// sleep(2);
		int wstatus;
		// waitpid gives more information on what happened, when the
		// process was terminated
		// WUNTRACED - return if child has been stopped but not traced by ptrace
		// WCONTINUED - return if stopped child was continued
		int w = waitpid(cpid, &wstatus, WUNTRACED | WCONTINUED);
		if (w == -1) {
			perror("wait");
			puts("wait failed");
		}
		puts("goodbye");
		if (WIFEXITED(wstatus)) {
			printf("exited, status=%d\n", WEXITSTATUS(wstatus));
		} else if (WIFSIGNALED(wstatus)) {
			printf("killed by signal %d\n", WTERMSIG(wstatus));
		} else if (WIFSTOPPED(wstatus)) {
			printf("stopped by signal %d\n", WSTOPSIG(wstatus));
		} else if (WIFCONTINUED(wstatus)) {
			printf("continued\n");
		}
	}
}

typedef enum { EXECVE, EXECL, EXECLP } Execv;

int q4(Execv exec_v) {
	pid_t cpid = fork();
	if (cpid == -1) {
		perror("fork");
		return EXIT_FAILURE;
	}

	if (cpid == 0) {
		// NOTE: use man 3 exec to read exec fns from unistd.h
		// also, man 2 execve gives information on the syscall wrapper

		static char *newargv[] = {LS_PATH, ".", "-la", NULL};
		static char *newenv[] = {NULL};

		switch (exec_v) {
		case EXECVE:
			execve(LS_PATH, newargv, newenv);
		case EXECL:
			execl(LS_PATH, LS_PATH, ".", "-la", NULL);
			break;
		case EXECLP:
			// works here because the env is copied from parent
			execlp("ls", "ls", ".", "-la", NULL);
		default:
			fprintf(stderr, "unsupported exec type: %d\n", exec_v);
		}

	} else {
		puts("parent doesn't do anything");
	}

	return EXIT_SUCCESS;
}

int q7() {
	int cpid = fork();
	if (cpid == -1) {
		perror("fork");
		return EXIT_FAILURE;
	}

	if (cpid != 0) {
		puts("parent return early");
		wait(&cpid);
		return EXIT_SUCCESS;
	}

	printf("before closing, printing to %d\n", STDOUT_FILENO);
	int rc = close(STDOUT_FILENO);
	if (rc == -1) {
		perror("close");
		return EXIT_FAILURE;
	}
	rc = printf("closed %d in child process\n", STDOUT_FILENO);
	fflush(stdout);
	if (rc < 0) {
		perror("printf");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int q8() {
	int pfd[2];
	if (pipe(pfd) == -1) {
		perror("pipe");
		return EXIT_FAILURE;
	}
	int rfd = pfd[0];
	int wfd = pfd[1];

	pid_t cpid1 = fork();
	if (cpid1 == -1) {
		perror("fork");
		return EXIT_FAILURE;
	}
	if (cpid1 == 0) {
		fflush(stdout);
		dup2(wfd, STDOUT_FILENO);
		close(rfd);
		close(wfd);
		puts("from child 1");
		puts("hey buddy");
		puts("hey pal");
		exit(EXIT_SUCCESS);
	}

	pid_t cpid2 = fork();
	if (cpid2 == -1) {
		perror("fork");
		return EXIT_FAILURE;
	}
	if (cpid2 == 0) {
		// child 2: stdin <- pipe
		dup2(rfd, STDIN_FILENO);
		close(rfd);
		close(wfd);

		char buf[128];
		ssize_t n;
		while ((n = read(STDIN_FILENO, buf, sizeof buf)) > 0) {
			fprintf(stderr, "child 2 got: %.*s", (int)n, buf);
		}
		exit(EXIT_SUCCESS);
	}

	// parent: needs neither end, must close both or child 2 never sees EOF
	close(rfd);
	close(wfd);

	wait(NULL);
	wait(NULL);
	return EXIT_SUCCESS;
}

int main(void) {
	q8();
	// q6();
	// return q4(EXECLP);
}
