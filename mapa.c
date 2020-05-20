#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "mapa.h"
#include "graph.h"

#define clear() printf("\033[H\033[J")
#define AV 3 // 1/AV chances de nao ativar fuga  
struct map{
	int casa[6][6];
	int x_pacman;
	int y_pacman;
	int x_ghost;
	int y_ghost;
};

void printa_mapa(MAP* mapa){
	clear();
	printf("\n\n");
	for(int i = 0;i<6; i++){
		for(int j = 0; j<6; j++){
			printf("  %c   ", mapa->casa[i][j]);
		}
		printf("\n\n");
	}
	printf("\n\n");
	sleep(2);
}

MAP* criar_mapa(){
	MAP* mapa = (MAP*)malloc(sizeof(MAP));

	for(int i=0; i<6; i++){
		for(int j=0; j<6; j++){
			mapa->casa[i][j] = ' ';
		}
	}

	//spawnando pacman e fantasma
	mapa->x_pacman = 0;
	mapa->y_pacman = 2;
	mapa->x_ghost = 0;
	mapa->y_ghost = 2;
	srand(time(NULL));
	while((mapa->x_pacman == 0 && mapa->y_pacman == 2) || (mapa->x_pacman == 0 && mapa->y_pacman == 3) || (mapa->x_pacman == 5 && mapa->y_pacman == 4)){
		mapa->x_pacman = rand()%6;
		mapa->y_pacman = rand()%6;
	}

	mapa->casa[mapa->y_pacman][mapa->x_pacman] = 'O';

	while((mapa->x_ghost == 0 && mapa->y_ghost == 2) || (mapa->x_ghost == 0 && mapa->y_ghost == 3) || (mapa->x_ghost == 5 && mapa->y_ghost == 4)){
		mapa->x_ghost = rand()%6;
		mapa->y_ghost = rand()%6;
	}

	mapa->casa[mapa->y_ghost][mapa->x_ghost] = 'A';

	printa_mapa(mapa);

	return mapa;
}

void move_pacman(MAP* mapa, GRAFO* grafo, int avoid){
		int flag_mov = 0;
		int mov_pac [4] = {1,2,3,4};
		int move[4] = {0,0,0,0};
		int cont_mov = 0;

		//apagando o pacman da antiga posição
		mapa->casa[mapa->y_pacman][mapa->x_pacman] = ' ';


		//define as  possiveis novas casas do pacman
		if(get_matriz(grafo,mapa->y_pacman*6+mapa->x_pacman,(mapa->y_pacman-1)*6+mapa->x_pacman) && mapa->y_pacman >= 0) move[0] = 1;
		if(get_matriz(grafo,mapa->y_pacman*6+mapa->x_pacman,(mapa->y_pacman+1)*6+mapa->x_pacman) && mapa->y_pacman <= 5) move[1] = 1;
		if(get_matriz(grafo,mapa->y_pacman*6+mapa->x_pacman,(mapa->y_pacman)*6+mapa->x_pacman-1) && mapa->x_pacman >= 0) move[2] = 1;
		if(get_matriz(grafo,mapa->y_pacman*6+mapa->x_pacman,(mapa->y_pacman)*6+mapa->x_pacman+1) && mapa->x_pacman <= 5) move[3] = 1;

		//verifica se é possivel fugir do fantasma
		for(int i =0; i<4;i++){
			cont_mov += move[i];
		}

		//caso seja possivel a fuga define para onde não deve ir
		if(cont_mov > 1 && (rand()%AV > 0) ){
			if(((mapa->y_pacman-1)*6+mapa->x_pacman) == avoid) move[0] = 0;
			if(((mapa->y_pacman+1)*6+mapa->x_pacman) == avoid) move[1] = 0;
			if(((mapa->y_pacman)*6+mapa->x_pacman-1) == avoid) move[2] = 0;
			if(((mapa->y_pacman)*6+mapa->x_pacman+1) == avoid) move[3] = 0;
		}

		while(flag_mov != 1){
			switch(mov_pac[rand()%4]){
				case 1:
					if(move[0]){
						mapa->y_pacman = mapa->y_pacman -1;
						flag_mov = 1;
					}
				break;

				case 2:
					if(move[1]){
						mapa->y_pacman = mapa->y_pacman +1;
						flag_mov = 1;
					}
				break;

				case 3:
					if(move[2]){
						mapa->x_pacman = mapa->x_pacman -1;
						flag_mov = 1;
					}
				break;

				case 4:
					if(move[3]){
						mapa->x_pacman = mapa->x_pacman +1;
						flag_mov = 1;
					}
				break;
			}
		}

		mapa->casa[mapa->y_pacman][mapa->x_pacman] = 'O';
		printa_mapa(mapa);
}

void clear_mapa(MAP* mapa){

	for(int i = 0;i<6; i++){
		for(int j = 0; j<6; j++){
			mapa->casa[i][j] = ' ';
		}
	}
}

int ghost_equals_pacman(MAP* mapa){
	if(mapa->x_pacman == mapa->x_ghost && mapa->y_pacman == mapa->y_ghost)
		return 1;
	else
		return 0;
}

int move_ghost(MAP* mapa, GRAFO* grafo){

	int origem = mapa->y_ghost*6+mapa->x_ghost;
	int destino = mapa->y_pacman*6+mapa->x_pacman;
	int* menor_caminho = (int*)malloc(36*sizeof(int));
	int aux_x, aux_y;
	int last;

	menor_caminho = calculate_path(grafo, origem, destino);
	last = menor_caminho[0];

	if (menor_caminho[1]==-1) return -1;

	for (int i = 1; menor_caminho[i]!=-1; i++){
		aux_x = menor_caminho[i]%6;
		aux_y = menor_caminho[i]/6;

		if(mapa->casa[aux_y][aux_x]!='O'){
			mapa->casa[aux_y][aux_x] = '-';
			last = menor_caminho[i];
		}
	}

	printa_mapa(mapa);

	//reset casa ghost
	mapa->casa[mapa->y_ghost][mapa->x_ghost] = ' ';

	mapa->x_ghost = menor_caminho[1]%6;
	mapa->y_ghost = menor_caminho[1]/6;

	mapa->casa[mapa->y_ghost][mapa->x_ghost] = 'A';

	printa_mapa(mapa);

	//limpa o caminho
	for(int i = 0;i<6; i++){
		for(int j = 0; j<6; j++){
			if(mapa->casa[i][j] == '-')
				mapa->casa[i][j] = ' ';
		}
	}
	return last;
}
