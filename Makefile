all:
	gcc client.c -o c.out
	gcc server.c -o s.out
clean:
	rm -f *.out
	rm -f *~
	rm -f *.log
