#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define CONTENT "somecontent"
#define CONTENT_LENGTH 11

int read_file(int fd, const char *msg, int read_length) {
	char buf[read_length + 1];
	int n = read(fd, buf, read_length);
	if (n <= 0) {
		perror("read");
		return EXIT_FAILURE;
	}
	buf[read_length] = '\0';
	printf("%s: %s\n", msg, buf);
	lseek(fd, 0, SEEK_SET);
	return EXIT_SUCCESS;
}

int write_file(int fd, const char *msg) {
	lseek(fd, 0, SEEK_END);
	int n = write(fd, CONTENT, CONTENT_LENGTH);
	if (n == -1) {
		perror("write");
		return EXIT_FAILURE;
	}
	printf("%s, wrote %d bytes\n", msg, n);

	// seek to beginning for next reader
	lseek(fd, 0, SEEK_SET);
	return EXIT_SUCCESS;
}

int main(void) {
	int sv = 100;

	int fd = open("myfile", O_RDWR | O_CREAT | O_TRUNC,
				  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1) {
		perror("open");
		return EXIT_FAILURE;
	}

	int n = write(fd, CONTENT, CONTENT_LENGTH);
	lseek(fd, 0, SEEK_SET);
	if (n != CONTENT_LENGTH) {
		printf("did not write content length to file, wrote: %d\n", n);
		return EXIT_FAILURE;
	}

	int cpid = fork();

	int rc = 0;
	switch (cpid) {
	case -1:
		perror("fork");
		return EXIT_FAILURE;
	case 0:
		printf("hello from fork(PID:%d), value: %d\n", getpid(), sv);
		rc = read_file(fd, "from child", CONTENT_LENGTH);
		if (rc == EXIT_FAILURE) {
			return rc;
		}
		rc = write_file(fd, "from fork");
		if (rc == EXIT_FAILURE) {
			return rc;
		}

		return read_file(fd, "final from child", CONTENT_LENGTH * 2);
	default:
		// wait for child to complete
		wait(&cpid);
		printf("hello from parent(PID:%d), value: %d\n", getpid(), sv);
		rc = read_file(fd, "from parent", CONTENT_LENGTH * 2);
		if (rc == EXIT_FAILURE) {
			return rc;
		}
		rc = write_file(fd, "from parent");
		if (rc == EXIT_FAILURE) {
			return rc;
		}
		return read_file(fd, "final from parent", CONTENT_LENGTH * 3);
	}
}
