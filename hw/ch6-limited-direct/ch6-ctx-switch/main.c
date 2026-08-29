#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// TODO:
// - [ ] setaffinity - read man sched_setaffinity. figure out to ensure two ps
// are on same processor

static int p1(int rfd, int wfd) {
	puts("in p1");

	char buf[24];
	strcpy(buf, "This is a test form p1\n");
	puts("copied");
	size_t nbytes = strlen(buf);
	ssize_t bytes_written = write(wfd, buf, nbytes);

	puts("wrote");
	if (bytes_written != strlen(buf)) {
		perror("write");
		return EXIT_FAILURE;
	}

	printf("p1 wrote %ld bytes\n", bytes_written);
	close(rfd);
	close(wfd);
	puts("closed");

	return EXIT_SUCCESS;
}

static int p2(int rfd, int wfd) {
	puts("in p2");

	close(wfd);
	char buf[28];
	// n = read(rfd, buf, sizeof buf);
	// buf[n] = '\0';
	// puts(buf);
	while (read(rfd, buf, sizeof buf) > 0) {
		printf("p2 got: %s", buf);
	}
	// while ((n = read(rfd, buf, sizeof buf)) > 0) {
	// 	buf[n] = '\0';
	// 	puts(buf);
	// 	// fprintf(stderr, "p2 got: %.*s", (int)n, buf);
	// }
	puts("after reader");

	// strcpy(buf, "This is a test form p2\n");
	// size_t nbytes = strlen(buf);
	// ssize_t bytes_written = write(wfd, buf, nbytes);
	// if (bytes_written < 0) {0
	// 	perror("write");
	// 	exit(1);
	// }
	// printf("p2 wrote %ld bytes\n", bytes_written);
	//
	// close(rfd);

	close(rfd);
	return EXIT_SUCCESS;
}

int main(void) {
	puts("before");

	// setup pipe
	int fds1[2];
	if (pipe(fds1) != 0) {
		perror("pipe");
		return EXIT_FAILURE;
	}

	int fds2[2];
	if (pipe(fds2) != 0) {
		perror("pipe");
		return EXIT_FAILURE;
	}
	int r1 = fds1[0], w1 = fds1[1], r2 = fds2[0], w2 = fds2[1];

	int pr1 = fork();
	if (pr1 == -1) {
		perror("fork");
		return EXIT_FAILURE;
	}
	if (pr1 == 0) {
		puts("p1 call");
		int rc = p1(r2, w1);
		return rc;
	}

	close(r2);
	close(w1);

	int pr2 = fork();
	if (pr2 == -1) {
		perror("fork");
		return EXIT_FAILURE;
	}

	if (pr2 == 0) {
		puts("p2 call");
		int rc = p2(r1, w2);
		return rc;
	}

	close(r1);
	close(w2);

	// wait for both processes to finish
	wait(NULL);
	wait(NULL);
	printf("main p exiting\n");

	return EXIT_SUCCESS;
}
