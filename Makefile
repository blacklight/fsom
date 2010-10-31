all:
	gcc -w -O3 -pipe -fomit-frame-pointer -ffast-math *.c -o fsom_example
clean:
	rm -f *.o fsom_example