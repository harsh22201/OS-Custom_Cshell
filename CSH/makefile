CC = gcc
CFLAGS = WNO-IMPLICIT FUCNTION DECLARATION

shell: cshell dir date execute

cshell: cshell.c
	$(CC) cshell.c -o cshell 

dir: dir.c
	$(CC) dir.c -o dir 

date: date.c
	$(CC)  date.c -o date 

execute: cshell
	./cshell


clean:
	rm -f Q1a Q1b Q1b_bonus cshell dir date
