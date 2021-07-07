#include<stdio.h>

typedef unsigned char* byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
	size_t i;
	for (i = 0; i < len; i++)
		printf(" %.2x", start[i]);
	printf("\n");
}

void show_short(short x) {
	show_bytes((byte_pointer)&x, sizeof(short));
}

void show_long(long x) {
	show_bytes((byte_pointer)&x, sizeof(long));
}

void show_double(double x) {
	show_bytes((byte_pointer)&x, sizeof(double));
}

int is_little_endian() {
	short s = 1;
	byte_pointer p = (byte_pointer)&s;
	return *p;
}

int Problem_2_59_(int x, int y) {
	return (x & 0xff) | (y & (~0xff));
}

unsigned replace_byte(unsigned x, int i, unsigned char b)
{
	unsigned mask = 0xff << (i * 8);
	x = x & (~mask);
	return x | (b << (i * 8));
}

int main()
{
	printf("%x", replace_byte(0x12345678, 0, 0xab));
	return 0;
}