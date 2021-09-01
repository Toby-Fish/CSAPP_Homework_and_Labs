#include "cachelab.h"

#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <getopt.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <fcntl.h>

#include <unistd.h>

#include <limits.h>



#define MAXBUF 128					/* 缓冲区大小 */

#define IDX(m, n, E) m * E + n		/* 计算m行n列元素位置 */



void help(char *argv[]);

void load_store(int count, unsigned tag, unsigned index, unsigned offset, unsigned size, int E);

int hextodec(char c);				/* 十六进制转十进制 */

void print(char buf[]);



int hit_count = 0, miss_count = 0, eviction_count = 0;

int v = 0;							/* v代表是否开启详细显示模式 */

char buffer[MAXBUF];				/* 读取缓冲区 */

FILE *fp;							

typedef struct {

	int valid;						/* 有效位 */

	int tag;

	int count;						/* count值越大，说明最近被使用 */

}unit;								/* 一个unit单元即为cache中一行 */

unit* cache;



int main(int argc, char *argv[])

{

	char opt;

	unsigned int s = 0, E = 0, b = 0, s_pow = 0;

	while ((opt = getopt(argc, argv, "hvs:E:b:t:")) != -1) {

		switch(opt) {

			case 'h':

				help(argv);

				return 0;

			case 'v':

				v = 1;

				break;

			case 's':

				s = atoi(optarg);

				s_pow = 1 << s;

				break;

			case 'E':

				E = atoi(optarg);

				break;

			case 'b':

				b = atoi(optarg);

				break;

			case 't':

				if ((fp = fopen(optarg, "r")) == NULL) {

					printf("ERROR!%s open failed!\n", optarg);

					exit(1);

				}

				break;

			case '?':

				help(argv);

				return 0;

		}

	}

	if (s == 0 || E == 0 || b == 0) {

		printf("%s: Missing required command line argument\n", argv[0]);

		help(argv);

		return 0;

	}

	cache = (unit*)malloc(16 * s_pow * E);		/* 16是因为考虑了对齐 */

	for (int i = 0; i < s_pow * E; i++) {

		cache[i].valid = cache[i].tag = cache[i].count = 0;

	}

	

	int count = 0;

	while (fgets(buffer, MAXBUF, fp)) {			/* 逐行分析 */

		char c;

		int op = 0, comma = 0;

		unsigned int offset = 0, tag = 0, index = 0;

		unsigned int size = 0, address = 0;

		count++;



		for (int i = 0; (c = buffer[i]) && (c != '\n'); i++) {

			if (c == ' ') continue;

			else if (c == 'I') op = 0;

			else if (c == 'L' || c == 'S') op = 1;

			else if (c == 'M') op = 2;

			else if (c == ',') comma = 1;

			else {

				if (comma)	size = hextodec(c);	/* 当读取到逗号时，之后的数据是size大小 */

				else		address = 16 * address + hextodec(c);

			}

		}



		for (int i = 0; i < b; i++) {			/* 实际上offset在本实验中没用，可以抛弃 */

			offset = offset * 2 + address % 2;

			address >>= 1;

		}



		for (int i = 0; i < s; i++) {

			index = index * 2 + address % 2;

			address >>= 1;

		}



		tag = address;



		if (v && op)

			print(buffer);

		if (op == 1) {

			load_store(count, tag, index, offset, size, E);

			if (v) printf("\n");

		}

			

		if (op == 2) {

			load_store(count, tag, index, offset, size, E);

			hit_count++;

			if (v)	printf(" hit\n");

		}

	}	



	free(cache);

	fclose(fp);

	printSummary(hit_count, miss_count, eviction_count);

	return 0;

}



void help(char *argv[]) {

	printf("Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file>\n", argv[0]);

	printf("Options:\n");

	printf("  -h\t\tPrint this help message.\n");

	printf("  -v\t\tOptional verbose flag.\n");

	printf("  -s <num>\tNumber of set index bits.\n");

	printf("  -E <num>\tNumber of lines per set.\n");

	printf("  -b <num>\tNumber of block offset bits.\n");

	printf("  -t <file>\tTrace file.\n\n");

	printf("Examples:\n");

	printf("  linux>  %s -s 4 -E 1 -b 4 -t traces/yi.trace\n", argv[0]);

	printf("  linux>  %s -v -s 8 -E 2 -b 4 -t traces/yi.trace\n", argv[0]);

}



void load_store(int count, unsigned tag, unsigned index, unsigned offset, unsigned size, int E) {

	//is it already in the cache?

	for (int i = 0; i < E; i++) {

		if (cache[IDX(index, i, E)].tag == tag && cache[IDX(index, i, E)].valid) {

			cache[IDX(index, i, E)].count = count;

			hit_count++;

			if (v) printf(" hit");

			return;

		}

	}

	

	miss_count++;

	if (v) printf(" miss");

	//is set already full?

	for (int i = 0; i < E; i++) {

		if (!cache[IDX(index, i, E)].valid) {

			cache[IDX(index, i, E)].valid = 1;

			cache[IDX(index, i, E)].tag = tag;

			cache[IDX(index, i, E)].count = count;

			return;

		}

	}

	

	//full

	int min_index = 0, min_count = INT_MAX;

	for (int i = 0; i < E; i++) {

		if (cache[IDX(index, i, E)].count < min_count) {

			min_count = cache[IDX(index, i, E)].count;

			min_index = i;

		}

	}

	cache[IDX(index, min_index, E)].tag = tag;

	cache[IDX(index, min_index, E)].count = count;

 	eviction_count++;

	if (v) printf(" eviction");

}	



int hextodec(char c) {

	if (c >= '0' && c <= '9') {

    	return c - '0';

  	}

  	if (c >= 'A' && c <= 'F') {

    	return c - 'A' + 10;

  	}

  	if (c >= 'a' && c <= 'f') {

    	return c - 'a' + 10;

  	}

  	return 0;

}



void print(char buf[]) {

	for (int i = 0; buf[i] != '\n'; i++)

		printf("%c", buf[i]);

}
