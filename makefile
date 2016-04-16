CC = gcc
FLAGS =


all:
	$(CC) $(FLAGS) src/test/test.c -o bin/test/test
	$(CC) $(FLAGS) src/test/speedtest.c -o bin/test/speedtest

test: all
	bin/test/test

speedtest: all
	bin/test/speedtest

clean:
	find bin -type f -delete
