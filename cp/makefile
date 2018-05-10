.PHONY:clean mycp


mycp:mycp.o
	gcc $^ -o $@

mycp.o:mycp.c
	gcc -c $^ -o $@


clean:
	rm -rf *.o mycp
