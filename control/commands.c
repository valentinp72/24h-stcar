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
