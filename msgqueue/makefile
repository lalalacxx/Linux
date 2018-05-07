.PHONY:all

all:process1 process2

process1:process1.c com.c
	gcc $^ -o $@

process2:process2.c com.c
	gcc $^ -o $@

.PHONY:clean

clean:
	rm -f process1 process2
