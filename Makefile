shell:shell.c
	gcc ls.c -o ls
	gcc rm.c -o rm
	gcc mkdir.c -o mkdir
	gcc cat.c -o cat
	gcc date.c -o date
	gcc shell.c -o shell
	clear
	./shell
clean:
	rm shell
