#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

#define MAXFILE_READS 1000
#define MEASUREMENT_TRIALS 100

static long get_time() {
	static struct timeval tv;
	int rc = gettimeofday(&tv, NULL);
	if (rc != 0) {
		perror("gettimeofday");
		return 0;
	}
	return tv.tv_usec;
}

typedef struct sc_result {
	long duration;
	float avg_sc_time;
} sc_result;

/** measure_syscall - reads an empty tmp file repeatedly  */
static int measure_syscall(FILE *f, sc_result *sc) {
	long start_time = get_time();
	for (int i = 0; i < MAXFILE_READS; i++) {
		char buffer[8];
		long r = read(f->_fileno, buffer, 0);
		if (r != 0) {
			perror("read");
			return 1;
		}
	}

	long end_time = get_time();
	sc->duration = end_time - start_time;
	sc->avg_sc_time = (float)sc->duration / MAXFILE_READS;

	return 0;
}

int main(void) {
	long total_duration = 0;

	printf("====================================RESULTS========================"
		   "===\n");
	printf("====================================SYSCALL=TEST==================="
		   "===\n");
	sc_result sc;
	FILE *tmpf = tmpfile();
	for (int i = 0; i < MEASUREMENT_TRIALS; i++) {
		measure_syscall(tmpf, &sc);
		printf("iteration: %d, duration: %ld, avg syscall time: %f\n", i,
			   sc.duration, sc.avg_sc_time);
		total_duration += sc.duration;
	}
	printf("==================================================================="
		   "===\n");
	printf("total duration across calls: %ld / total calls: %d = %f\n",
		   total_duration, MEASUREMENT_TRIALS,
		   (float)total_duration / MEASUREMENT_TRIALS);

	printf("====================================END=SYSCALL=TEST==============="
		   "===\n");
	return 0;
}
