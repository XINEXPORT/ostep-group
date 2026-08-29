// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
//
// #define CONTENT "somecontent"
// #define CONTENT_L 11
//
// int read_f(FILE *f, const char *msg) {
// 	puts(msg);
//
// 	char buf[CONTENT_L + 1];
// 	size_t n = fread(buf, 1, CONTENT_L, f);
//
// 	// make sure to re wind for the next process
// 	rewind(f);
// 	if (n != CONTENT_L) {
// 		printf("did not read expected amount, read: %d\n", (int)n);
// 		return 1;
// 	}
//
// 	// add null terminator
// 	buf[CONTENT_L] = '\0';
// 	printf("read: %s\n", buf);
//
// 	return 0;
// }
//
// // int write_f(FILE *f, const char *msg) {
// //
// // }
//
// int main(void) {
// 	int sv = 100;
//
// 	FILE *f = tmpfile();
// 	if (f == NULL) {
// 		perror("tmpfile");
// 		return EXIT_FAILURE;
// 	}
//
// 	int rc = fputs(CONTENT, f);
// 	if (rc < 0) {
// 		perror("fputs");
// 		return EXIT_FAILURE;
// 	}
// 	// should flush file to disk
// 	rewind(f);
//
// 	int cpid = fork();
//
// 	switch (cpid) {
// 	case -1:
// 		perror("fork");
// 		return EXIT_FAILURE;
// 	case 0:
// 		printf("hello from fork(PID:%d), value: %d\n", getpid(), sv);
// 		rc = read_f(f, "from child");
// 		return rc;
// 	default:
// 		printf("hello from parent(PID:%d), value: %d\n", getpid(), sv);
// 		rc = read_f(f, "from parent");
// 		return rc;
// 	}
// }
