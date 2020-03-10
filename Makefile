.PHONY: build
build: lab2

lab2: main.c
	gcc --std=c11 -Wall -O3 -masm=intel -o $@ $^
