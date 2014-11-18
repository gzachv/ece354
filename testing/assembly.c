/**
 * Testing for x86 assembly understanding.
 *
 */


#include <stdio.h>

void c() {
}

int b() {
	int i = 1;
	int x = 2;
	int z = x + x;
	c();
	return i + z;
}

int a(int i) {
	i = b();
	return i;
}


int main (int argc, char* argv[]) {
	int i = 0;
	i = a(i);
	return 0;
}
