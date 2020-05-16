CC = gcc *.c -o
CFLAGS = -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0
VALGRIND = valgrind --leak-check=full --track-origins=yes --show-reachable=yes
EXECUTABLE = pruebas
OBJET = lista.c lista.h lista_pruebas.c 
ZIP = zip
NAMETP = TDA_LISTA.zip

comprimir:
	$(ZIP) $(NAMETP) $(OBJET)

all:valgrind

	echo2222
	notify-send "Compilado!" -t 1500

valgrind:compilar

	$(VALGRIND) ./$(EXECUTABLE)

compilar:

	clear
	$(CC) $(EXECUTABLE) $(CFLAGS)

borrar:

	rm $(EXECUTABLE)