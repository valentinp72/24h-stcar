#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SCREEN_NAME "56293.ttys000.MBP-Valentin-2"

void execCommand(char * cmd){
	char exec[1000];
	sprintf(exec, "screen -S %s -L -p 0 -X stuff \"%s`echo -ne '\015'`\"", SCREEN_NAME, cmd);
	system(exec);
}

void changeSpeed(int speed){
	if(speed >= -1 && speed <= 3){
		char cmd[100];
		sprintf(cmd, "rouler %i", speed);
		execCommand(cmd);
	}
}

void turn(int dir){
	if(dir >= 0 && dir <= 2){
		char cmd[100];
		sprintf(cmd, "turn %i", dir);
		execCommand(cmd);
	}
}

int readData(){
	FILE * file;
	char tmp;
	int size = 0;
	int data = -2;
	int fin = FALSE;
	char cmd[1000];
	execCommand("infoVitesse ");

	do{

		sprintf(cmd, "screen -S %s -p0 -X hardcopy $(echo cmd.out)", SCREEN_NAME);
		system(cmd);

		file = fopen("cmd.out", "r");
		if(file == NULL){
			exit(5);
		}

		fscanf(file, "%c", &tmp);
		while(!feof(file)){
			fscanf(file, "%c", &tmp);

			if(tmp == '@'){
				fscanf(file, "%i", &data);
				fin = TRUE;
			}
		}
		fclose(file);

	}while(!fin);

	return data;

}
