CC = gcc
CFLAGS = -Wall -Werror -ansi -pedantic -std=c89 -g
OBJ = file_io.o linked_list.o game_functions.o mainDefault.o
OBJ2 = file_io.o game_functions.o linked_list.o mainSecret.o
OBJ3 = file_io.o game_functions.o linked_list.o mainEditor.o

EXEC = TicTacToe
EXEC2 = TicTacToeSecret
EXEC3 = TicTacToeEditor

all : $(OBJ) $(OBJ2) $(OBJ3)
		$(CC) $(OBJ) -o $(EXEC)
		$(CC) $(OBJ2) -o $(EXEC2)
		$(CC) $(OBJ3) -o $(EXEC3)

$(EXEC) : $(OBJ)
		$(CC) $(OBJ) -o $(EXEC)

$(EXEC2) : $(OBJ2)
		$(CC) $(OBJ2) -o $(EXEC2)

$(EXEC3) : $(OBJ3)
		$(CC) $(OBJ3) -o $(EXEC3)

file_io.o : file_io.c
		$(CC) -c file_io.c $(CFLAGS)

game_functions.o : game_functions.c
		$(CC) -c game_functions.c $(CFLAGS)

linked_list.o : linked_list.c
		$(CC) -c linked_list.c $(CFLAGS)

main.o : linked_list.c game_functions.c
		$(CC) -c main.c $(CFLAGS)

mainDefault.o : linked_list.c game_functions.c
		$(CC) -c main.c $(CFLAGS)
		mv main.o mainDefault.o

mainSecret.o : linked_list.c game_functions.c
		$(CC) -c main.c $(CFLAGS) -DSECRET
		mv main.o mainSecret.o

mainEditor.o : linked_list.c game_functions.c
		$(CC) -c main.c $(CFLAGS) -DEDITOR
		mv main.o mainEditor.o

clean:
		rm -f $(EXEC) $(EXEC2) $(EXEC3) $(OBJ) $(OBJ2) $(OBJ3)
