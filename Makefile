CC=gcc
CFLAGS =  -Wall -Wextra -g -fsanitize=address -static-libasan
OF = main.o man.o data.o hand.o

main: 
	$(CC) -c main.c $(CFLAGS)
	$(CC) -c man.c $(CFLAGS)
	$(CC) -c data.c $(CFLAGS)
	$(CC) -c hand.c $(CFLAGS)

	$(CC)  $(OF) $(CFLAGS) -o csve
	rm *.o