run:all
	./t <matrix_mapa.txt
all:
	gcc graph.c mapa.c fila.c main.c -g -Wall -o t

