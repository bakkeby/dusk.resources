#if 0
gcc -s -O2 -o cpu -Wno-unused-result cpu.c -lm
exit
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_CPUS 64 // Maximum number of CPUs
#define AVG_CPU (MAX_CPUS - 1)
#define arg(A) (!strcmp(argv[i], A))

enum {
	USER,
	NICE,
	SYSTEM,
	IDLE,
	IOWAIT,
	IRQ,
	SOFTIRQ,
	STEAL,
	GUEST,
	GUEST_NICE,
	COLS
};

static int
readStatFromFile(char *filename, unsigned long long int (*data)[COLS])
{
	int c;
	char line[256] = {0};
	int ret = access(filename, F_OK);

	if (ret == -1)
		return ret;

	c = AVG_CPU;
	FILE *file = fopen(filename, "rt");
	while (fgets(line, sizeof(line), file)) {
		if (strncmp(line, "cpu", 3) != 0)
			break;

		sscanf(line, "%*s %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu",
		       &data[c][0], &data[c][1], &data[c][2], &data[c][3], &data[c][4],
		       &data[c][5], &data[c][6], &data[c][7], &data[c][8], &data[c][9]);

		if (c == AVG_CPU)
			c = -1;
		c++;
	}

	fclose(file);

	return c;
}

static void
writeStatToFile(char *filename, unsigned long long int (*data)[COLS])
{
	FILE *file = fopen(filename, "wt");
	int c;

	for (c = 0; c < AVG_CPU && data[c][0] != 0; c++) {
		fprintf(file, "cpu%d %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu\n", c,
		        data[c][0], data[c][1], data[c][2], data[c][3], data[c][4],
		        data[c][5], data[c][6], data[c][7], data[c][8], data[c][9]);
	}

	fclose(file);
}

static void
cp(char *source, char *dest)
{
    char buffer[1024];
    size_t bytesRead;
	FILE *sourceFile, *destFile;

	sourceFile = fopen(source, "rt");
	if (!sourceFile) {
		fprintf(stderr, "Error: cp - failed to read source file %s\n", source);
		exit(1);
	}

	destFile = fopen(dest, "wt");
	if (!destFile) {
		fprintf(stderr, "Error: cp - failed to open destination file %s\n", dest);
		exit(1);
	}

	while ((bytesRead = fread(buffer, 1, sizeof(buffer), sourceFile)) > 0) {
		fwrite(buffer, 1, bytesRead, destFile);
	}

	fclose(sourceFile);
	fclose(destFile);
}

static void
printStat(unsigned long long int (*data)[COLS])
{
	int c;
	for (c = 0; c < MAX_CPUS && data[c][0]; c++) {
		printf("cpu%d %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu\n", c,
		       data[c][0], data[c][1], data[c][2], data[c][3], data[c][4],
		       data[c][5], data[c][6], data[c][7], data[c][8], data[c][9]);
	}
}

static void
printStatus2DOutput(
	unsigned long long int (*cData)[COLS],
	unsigned long long int (*pData)[COLS],
	int maxHeight,
	int lrpad,
	char *textcol,
	char *oddcol,
	char *evencol
) {
	unsigned int c, j, x, y, w, h;
	long long cIdle, pIdle, cTotal, pTotal;
	int pct;
	x = lrpad;
	w = 2;

	for (c = 0; c < MAX_CPUS; c++) {
		if (!cData[c][0])
			continue;

		pIdle = pData[c][IDLE];
		cIdle = cData[c][IDLE];
		pTotal = 0;
		cTotal = 0;

		for (j = 0; j < COLS; j++) {
			pTotal += pData[c][j];
			cTotal += cData[c][j];
		}

		if (cTotal == pTotal)
			continue;

		if (c == 0) {
			pct = 100 - ((cIdle - pIdle) / (double)(cTotal - pTotal)) * 100;
			continue;
		}

		h = (maxHeight - 2) * (1.0 - (double)(cIdle - pIdle) / (double)(cTotal - pTotal));
		y = maxHeight - h;

		printf("%s^r%d,%d,%d,%d^", c % 2 ? evencol : oddcol, x, y, w, h);
		x += 3;
	}

	x += lrpad;
	printf("^d^^f%d^%s%d%% CPU^d^\n", x, textcol, pct);
}

void
usage()
{
	char ofmt[] = "   %-20s%s\n";
	puts("usage: cpu [options]");
	puts("");
	puts("CPU monitoring widget for status2d enabled status bars.");
	puts("Generates a status2d string on the form:");
	puts("   ^C1^^r6,16,2,0^^C2^^r9,16,2,0^...^r51,16,2,0^^d^^f60^ 0% CPU^d^");
	puts("");
	puts("The string consists of one rectangular bar for each core with the height");
	puts("of the bar determined by the CPU usage of that core, followed by average");
	puts("CPU usage percentage and the word CPU.");
	puts("");
	puts("Options:");
	printf(ofmt, "--help", "this help section");
	printf(ofmt, "--oddcolor", "status2d colour for odd bars, defaults to ^C1^");
	printf(ofmt, "--evencolor", "status2d colour for even bars, defaults to ^C2^");
	printf(ofmt, "--textcolor", "status2d text colour, not used by default");
	printf(ofmt, "--lrpad", "left/right padding, defaults to 6 pixels");
	printf(ofmt, "-h, --height", "specifies the height of the bar");
	puts("");
}

int
main(int argc, char *argv[])
{
	int i, p, c, cpu_num;
	int height = 16;
	int lrpad = 6;
	char *oddcol = "^C1^";
	char *evencol = "^C2^";
	char *textcol = "";

	const char *tmpFileFmt = "/tmp/.%s.statusbar.cpu.%s.dat~";
	char tmpFileName[255];
	snprintf(tmpFileName, sizeof(tmpFileName) - 1, tmpFileFmt, getenv("USER"), getenv("DISPLAY"));

	for (i = 1; i < argc; i++) {
		if (arg("--help") || i + 1 == argc) {
			usage();
			exit(0);
		} else if arg("--oddcolor") {
			oddcol = argv[++i];
		} else if arg("--evencolor") {
			evencol = argv[++i];
		} else if arg("--textcolor") {
			textcol = argv[++i];
		} else if arg("--lrpad") {
			lrpad = strtol(argv[++i], NULL, 10);
		} else if (arg("-h") || arg("--height")) {
			height = strtol(argv[++i], NULL, 10);
		}
	}

	/* Previous and current data arrays */
	unsigned long long pData[MAX_CPUS][COLS] = {0};
	unsigned long long cData[MAX_CPUS][COLS] = {0};

	/* The general idea here is:
	 *    - read previous data from temporary file
	 *    - copy /proc/stat to temporary file
	 *    - read current data (now in temporary file)
	 *    - if we had previous data, then generate output based
	 *      on the diff between the previous and current data
	 */
	p = readStatFromFile(tmpFileName, pData);
	cp("/proc/stat", tmpFileName);
	c = readStatFromFile(tmpFileName, cData);

	if (p == -1)
		exit(0);

	printStatus2DOutput(cData, pData, height, lrpad, textcol, oddcol, evencol);
	return 0;
}
