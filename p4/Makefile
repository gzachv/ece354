# Makefile for assignment 4, CS 354
# Author: Gustavo Zach Vargas, Section 1

# Compiler Variable
CC = gcc

# Compiler Flags
CFLAGS = -Wall -m32

# Pin Variable
PIN = /p/course/cs354-common/public/cache/pin -t /p/course/cs354-common/public/cache/source/tools/Memory/obj-ia32/allcache.so

# Pin Config Flags
# INSTRUCTION CACHE: -ia 1 = set assoc to be 1, direct mapp; -is N = capacity for cache; -ib N = N bytes per block
# DATA CACHE: -da 1 = set assoc to be 1, direct mapp; -ds N = capacity for cache; -db N = N bytes per block
# BSIZE = block size in bytes
BSIZE = 64
PFLAGS = -is 16384 -ia 1 -ib $(BSIZE) -ds 16384 -da 1 -db $(BSIZE) --

# pin
pin1D: cache1D
	$(PIN) $(PFLAGS) cache1D

pin2Drows: cache2Drows
	$(PIN) $(PFLAGS) cache2Drows

pin2Dcols: cache2Dcols
	$(PIN) $(PFLAGS) cache2Dcols

# 1D array
cache1D: cache1D.o
	$(CC) $(CFLAGS) cache1D.o -o cache1D

cache1D.o: cache1D.c
	$(CC) $(CFLAGS) -c cache1D.c

test1D: cache1D_COPY.o
	$(CC) $(CFLAGS) cache1D_COPY.o -o test1D

cache1D_COPY.o: cache1D_COPY.c
	$(CC) $(CFLAGS) -c cache1D_COPY.c

# 2D arrays
cache2Drows: cache2Drows.o
	$(CC) $(CFLAGS) cache2Drows.o -o cache2Drows

cache2Drows.o: cache2Drows.c
	$(CC) $(CFLAGS) -c cache2Drows.c

test2Drows: cache2Drows_COPY.o
	$(CC) $(CFLAGS) cache2Drows_COPY.o -o test2Drows

cache2Drows_COPY.o: cache2Drows_COPY.c
	$(CC) $(CFLAGS) -c cache2Drows_COPY.c

cache2Dcols: cache2Dcols.o
	$(CC) $(CFLAGS) cache2Dcols.o -o cache2Dcols

cache2Dcols.o: cache2Dcols.c
	$(CC) $(CFLAGS) -c cache2Dcols.c

test2Dcols: cache2Dcols_COPY.o
	$(CC) $(CFLAGS) cache2Dcols_COPY.o -o test2Dcols

cache2Dcols_COPY.o: cache2Dcols_COPY.c
	$(CC) $(CFLAGS) -c cache2Dcols_COPY.c

# clean
clean:
	rm -f *.o
