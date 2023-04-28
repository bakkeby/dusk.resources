#if 0
gcc -s -O2 -o status2d_volume -Wno-unused-result status2d_volume.c -lm
exit
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX(A, B) ((A) > (B) ? (A) : (B))
#define MIN(A, B) ((A) < (B) ? (A) : (B))
#define arg(A) (!strcmp(argv[i], A))

void
printStatus2DOutput(
	float percentage,
	int height,
	int width,
	int gap,
	int tbpad,
	char *oddcol,
	char *evencol,
	char *textcol
) {
	int i;
	int x = 0, y = 0, w = 0, h = 0;

	int incr = 1;
	int numberOfBars = 0;
	int maxHeight = height - tbpad;

	w = width ? width : 1 + (maxHeight / 10);

	if (maxHeight > 15) {
		incr += (maxHeight / 15);
	}

	if (!numberOfBars && percentage) {
		/* Anything over 1% has at least one bar. Volume at or above 85% to show as full. */
		// numberOfBars = 1 + ((maxHeight - tbpad) / incr) * (percentage >= 85 ? 1 : percentage / 85);
		numberOfBars = 1 + ((maxHeight - tbpad) / incr) * (MIN(percentage, 85) / 85);
	}

	for (i = 0; i < numberOfBars; i++) {
		h += incr;
		y = maxHeight - h;

		printf("%s^r%d,%d,%d,%d^", i % 2 ? oddcol : evencol, x, y, w, h);
		x += w + gap;
	}

	x += 8;
	printf("^f%d^", x);
	printf("%s%0.f%%\n", textcol, percentage);
}

void
usage()
{
	char ofmt[] = "   %-20s%s\n";
	puts("usage: status2d_volume [options]");
	puts("");
	puts("Prints a status2d volume widget based on a given percentage and height.");
	puts("Generates a status2d string on the form:");
	puts("   ^C14^^r0,22,3,2^^C8^^r4,20,3,4^^C14^^r8,18,3,6^...^r40,2,3,22^^f52^^d^100%");
	puts("");
	puts("The string consists of one rectangular bar for each volume level, the number of which");
	puts("is determined by the height of the bar.");
	puts("");
	puts("Options:");
	printf(ofmt, "--help", "this help section");
	printf(ofmt, "--oddcolor", "status2d colour for odd bars, defaults to ^C1^");
	printf(ofmt, "--evencolor", "status2d colour for even bars, defaults to ^C2^");
	printf(ofmt, "--textcolor", "status2d text colour, not used by default");
	printf(ofmt, "--tbpad", "top/bottom padding, defaults to 2 pixels");
	printf(ofmt, "-p, --percentage", "the current volume level in percentage");
	printf(ofmt, "-h, --height", "specifies the height of the bar");
	printf(ofmt, "-w, --width", "specifies the width of each volume column");
	printf(ofmt, "-g, --gap", "space between volume columsn (defaults to 1 pixel)");
	puts("");
}

int
main(int argc, char *argv[])
{
	int i, p, c, cpu_num;
	int height = 18;
	int width = 0; /* will be dynamically calculated if left as 0 */
	int gap = 1; /* space between volume columns */
	int lrpad = 6;
	int tbpad = 4; /* top and bottom padding for the generated status2d text */
	char *oddcol = "^C14^";
	char *evencol = "^C8^";
	char *textcol = "^d^";
	float percentage = 100.0;

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
		} else if arg("--tbpad") {
			tbpad = strtol(argv[++i], NULL, 10);
		} else if (arg("-p") || arg("--percentage")) {
			percentage = atof(argv[++i]);
		} else if (arg("-h") || arg("--height")) {
			height = strtol(argv[++i], NULL, 10);
		} else if (arg("-w") || arg("--width")) {
			width = strtol(argv[++i], NULL, 10);
		} else if (arg("-g") || arg("--gap")) {
			gap = strtol(argv[++i], NULL, 10);
		}
	}

	printStatus2DOutput(percentage, height, width, gap, tbpad, oddcol, evencol, textcol);
	return 0;
}
