my_shell: my_shell.c ls.c mkdir.c rm.c date.c cat.c
	gcc my_shell.c -o my_shell
	gcc ls.c -o ls
	gcc mkdir.c -o mkdir
	gcc rm.c -o rm
	gcc date.c -o date
	gcc cat.c -o cat

