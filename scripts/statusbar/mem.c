#if 0
gcc -s -O2 -o mem -Wno-unused-result mem.c -lm
exit
#endif

#include <stdio.h>
#include <stdlib.h>

int
main()
{
	FILE *meminfo = fopen("/proc/meminfo", "r");
	char line[256];

	long total_mem = 0;
	long free_mem = 0;
	long shared_mem = 0;
	long used_mem = 0;
	long cached_mem = 0;
	long buffers_mem = 0;
	long reclaimable_mem = 0;
	int symb_idx = 0;

	const char *symb_s2d_color = "^C8^";
	const char *hl_s2d_color = "";
	const char *norm_s2d_color = "";
	const char *end_s2d_color = "^d^";

	/* These are symbols from the Nerd Font collection and they represent a moon going from empty
	 * (e.g. an eclipse) to a full moon, i.e. gradually showing the amount of memory used.
	 * The characters used are in the range U+E3D5 to U+E3E3.
	 * Going from full to empty can be achieved by U+E3E3 followed by U+E3C8 through U+E3D5.
	 * The last character is repeated twice because we want to show that the memory is full before
	 * it reaches 100%.
	 */
	//const char *symb[] = { "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" }; // full to empty
	const char *symb[] = { "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" }; // empty to full
	const int symb_length = sizeof symb / sizeof symb[0];

	while (fgets(line, sizeof(line), meminfo)) {
		sscanf(line, "MemTotal: %ld kB", &total_mem);
		sscanf(line, "MemFree: %ld kB", &free_mem);
		sscanf(line, "Shmem: %ld kB", &shared_mem);
		sscanf(line, "Cached: %ld kB", &cached_mem);
		sscanf(line, "Buffers: %ld kB", &buffers_mem);
		sscanf(line, "SReclaimable: %ld kB", &reclaimable_mem);
	}

	used_mem = (total_mem - free_mem - cached_mem - buffers_mem - reclaimable_mem) + shared_mem;
	symb_idx = symb_length * used_mem / total_mem;

	printf("%s%s%s %s%d%s/%d %sMB%s\n",
		symb_s2d_color,
		symb[symb_idx],
		end_s2d_color,
		hl_s2d_color,
		used_mem/1024,
		norm_s2d_color,
		total_mem/1024,
		hl_s2d_color,
		end_s2d_color
	);

	fclose(meminfo);

	return 0;
}
