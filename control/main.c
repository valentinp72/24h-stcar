#include "../tools/tools.h"
#include "../tools/easySdl2.h"
#include "commands.h"
#include "display.h"

enum {VN1 = -20, V0 = 0, V1 = 20, V2 = 45, V3 = 60};

typedef struct {
	int speed;
	double lat;
	double lon;
	double distToNext;
} t_point;

typedef struct {
	double lat;
	double lon;
	int indexLastPoint;
	double distToNext;
} t_pos;

typedef struct {
	double lat;
	double lon;
} t_vect;

double dist2Coor (t_point a, t_point b) {
	double col = (b.lon - a.lon) * cos((a.lat + b.lat) / 2);
	double line = b.lat - a.lat;
	double dist = sqrt(col*col + line*line) * 6371.0; /*earth radius 6371 km*/
	return dist;
}

int askSpeedToCar (int speed) {
	return speed;
}

double getSpeed (int desireSpeed) {
	int actualSpeed = askSpeedToCar(desireSpeed);
	switch (actualSpeed) {
		case -1: return VN1;
		case  0: return V0;
		case  1: return V1;
		case  2: return V2;
		case  3: return V3;
		default: return V0;
	}
}

double distPosCoor (t_pos pos, t_point point) {
	double col = (point.lon - pos.lon) * cos((pos.lat + point.lat) / 2);
	double line = point.lat - pos.lat;
	double dist = sqrt(col*col + line*line) * 6371.0; /*earth radius 6371 km*/
	return dist;
}

t_point * getCircuit (int nbPoint);
int translateXML (int *nbLine);

void tellServer (double lat, double lon) {
	static int acc = 0;
	char msg[400];
	sprintf (msg, "wget --spider -q   --no-cookies --no-http-keep-alive  http://traccar.spc5studio.com:5055/\\?id\\=000001\\&lat\\=%.16lf\\&lon\\=%.16lf\\&altitude\\=72", lat, lon);
	printf("%d", acc++);
	fflush(stdout);
	system (msg);
	printf(" [V]\n");
}


t_point * getCircuit (int nbPoint) {
	t_point *circuit = malloc(nbPoint * sizeof(t_point));
	FILE * circuitFile = fopen ("circuit.txt", "r");

	int speed, i;
	double lat, lon;
	for (i = 0; i < nbPoint; i++) {
		fscanf (circuitFile, "%d %lf %lf", &speed, &lat, &lon);
		circuit[i] = (t_point) {speed, lat, lon};
	}

	fclose(circuitFile);
	return circuit;
}

int translateXML (int *nbLine) {
	FILE *xml = NULL, *dst = NULL;
	xml = fopen("CircuitBugatti.xml", "r");
	if (xml == NULL) return -1;
	dst = fopen("circuit.txt", "w");
	int acc = 0;
	int nbPoint = 0;
	char c;
	double number;
	int integer;
	int fileIsNotFinish;
	do {
		while (fscanf(xml, "%c", &c), c != '\"' && (fileIsNotFinish = !feof(xml)));

		if (fileIsNotFinish) {
			if (acc == 0) {
				fscanf (xml, "%d", &integer);
				fprintf(dst, "%d", integer);
			}
			else {
				fscanf (xml, "%lf", &number);
				fprintf(dst, "%.16lf", number);
			}
			fscanf(xml, "%*c");
			acc++;
			if (acc == 3) {
				fprintf(dst, "\n");
				nbPoint++;
				acc = 0;
			}
			else fprintf(dst, " ");
		}
	} while (fileIsNotFinish);
	*nbLine = nbPoint;
	fclose(xml);
	fclose(dst);
	return 0;
}

int main(){

	SDL_Event event;

    int quit = FALSE;
	int i, found = FALSE, data = 0;
	int isLampOn = FALSE, isTaillampOn = FALSE, isWindscreenOn = FALSE;



	int nbPoint;
	translateXML (&nbPoint);
	t_point *circuit = getCircuit(nbPoint);
	t_pos pos, lastPos;


	for (i = 0; i < nbPoint - 1; i++) {
		circuit[i].distToNext = dist2Coor(circuit[i], circuit[i+1]);
	}
	circuit[i].distToNext = dist2Coor (circuit[i], circuit[0]);

	pos.lat = circuit[0].lat;
	pos.lon = circuit[0].lon;
	pos.indexLastPoint = 0;
	pos.distToNext = circuit[0].distToNext;
	t_vect vect = {-1, -1}, lastvect;
	double angle;





	initSdl(HEIGHT, WIDTH, "Télécommande");

	SDL_Color counterColor = {0, 0, 0};
	TTF_Font * roboto = loadFont("media/Roboto-Light.ttf");
	//displayText("Compte-tour :", roboto, counterColor, 500, 20, 1);

	t_texture speedTextures[N_SPEED_TEXTURES];
	t_texture dirTextures[N_DIR_TEXTURES];

	t_texture selectionSpeed = {TOP_SHIFT + 3 * IMG_H, LEFT_SHIFT - 20, loadTexture("media/selection_left.png")};
	t_texture selectionClearSpeed = {TOP_SHIFT, LEFT_SHIFT - 20, loadTexture("media/selection_left_clear.png")};
	t_texture selectionDir = {HEIGHT - (3 * IMG_H) - 20, LEFT_SHIFT + 3*IMG_W, loadTexture("media/selection_dir.png")};
	t_texture selectionClearDir = {HEIGHT - (3 * IMG_H) - 20, LEFT_SHIFT + 3*IMG_W, loadTexture("media/selection_dir_clear.png")};


	t_texture lampOn = {TOP_SHIFT + IMG_H, LEFT_SHIFT + 2 * IMG_W, loadTexture("media/lamp_on.jpg")};
	t_texture lampOff = {TOP_SHIFT + IMG_H, LEFT_SHIFT + 2 * IMG_W, loadTexture("media/lamp_off.jpg")};

	t_texture taillampOn = {TOP_SHIFT + IMG_H, LEFT_SHIFT + 3 * IMG_W, loadTexture("media/taillamp_on.jpg")};
	t_texture taillampOff = {TOP_SHIFT + IMG_H, LEFT_SHIFT + 3 * IMG_W, loadTexture("media/taillamp_off.jpg")};

	t_texture windscreenOn = {TOP_SHIFT + IMG_H, LEFT_SHIFT + 4 * IMG_W, loadTexture("media/windscreen_on.jpg")};
	t_texture windscreenOff = {TOP_SHIFT + IMG_H, LEFT_SHIFT + 4 * IMG_W, loadTexture("media/windscreen_off.jpg")};


	loadSpeedTextures(speedTextures);
	loadDirTextures(dirTextures);

	draw(selectionSpeed, IMG_W + 40, IMG_H);
	draw(selectionDir, IMG_W, IMG_H + 40);

	draw(lampOff, IMG_W, IMG_H);
	draw(taillampOff, IMG_W, IMG_H);
	draw(windscreenOff, IMG_W, IMG_H);
	drawAllTextures(speedTextures, N_SPEED_TEXTURES);
	drawAllTextures(dirTextures, N_DIR_TEXTURES);


	render();

	int lastTime = 0, currentTime;

	while(quit == FALSE){
      	if(SDL_PollEvent(&event) != 0){
			switch(event.type){
		   		case SDL_KEYDOWN:
		   			switch(event.key.keysym.sym){
						case SDLK_q: quit = TRUE; break;
					}
		   			break;

				//En cas de click gauche
				case SDL_MOUSEBUTTONDOWN:
					//render();
					if(event.button.button == SDL_BUTTON_LEFT){

						int x = event.motion.x;
						int y = event.motion.y;

						// ** VITESSE ** //

						// Si on est sur la colonne de la vitesse
						if(x > LEFT_SHIFT && x < LEFT_SHIFT + IMG_W){

							// Si on est sur une ligne valide
							for(i = 0 ; i < N_SPEED_TEXTURES ; i++){
								if(y > TOP_SHIFT + (i) * (IMG_H) && y < TOP_SHIFT + (i + 1) * (IMG_H)){

									selectionClearSpeed.line = selectionSpeed.line;
									selectionSpeed.line = TOP_SHIFT + i * IMG_H;

									draw(selectionClearSpeed, IMG_W + 40, IMG_H);
									draw(selectionSpeed, IMG_W + 40, IMG_H);
									render();

									changeSpeed((N_SPEED_TEXTURES - 1) - (i+1));
								}
							}
						}

						// ** VOLANT ** //
						if(y > dirTextures[0].line && y < dirTextures[N_DIR_TEXTURES - 1].line + IMG_H){
							for(i = 0 ; i < N_DIR_TEXTURES ; i++){
								if(x > dirTextures[i].col && x < dirTextures[i].col + IMG_W){
									selectionClearDir.col = selectionDir.col;
									selectionDir.col = dirTextures[i].col;

									draw(selectionClearDir, IMG_W, IMG_H + 40);
									draw(selectionDir, IMG_W, IMG_H + 40);
									render();

									turn((i == 0) ? 1 : (i == 1) ? 0 : 2);
								}
							}
						}

						// ** Phare ** //
						if(clickedOnTexture(lampOn, x, y)){
							// On a appuyé sur le phare
							if(isLampOn){
								draw(lampOff, IMG_W, IMG_H);
								execCommand("feuAv 0");
							} else {
								draw(lampOn, IMG_W, IMG_H);
								execCommand("feuAv 1");
							}
							isLampOn = !isLampOn;
							render();
						}

						// ** Feu arrière ** //
						if(clickedOnTexture(taillampOn, x, y)){
							if(isTaillampOn){
								draw(taillampOff, IMG_W, IMG_H);
								execCommand("feuArr 0");
							} else {
								draw(taillampOn, IMG_W, IMG_H);
								execCommand("feuArr 1");
							}
							isTaillampOn = !isTaillampOn;
							render();
						}

						// ** Essui glace ** //
						if(clickedOnTexture(windscreenOn, x, y)){
							// On a appuyé sur l'essui glace
							if(isWindscreenOn){
								draw(windscreenOff, IMG_W, IMG_H);
								execCommand("suieGlace 0");
							} else {
								draw(windscreenOn, IMG_W, IMG_H);
								execCommand("suieGlace 1");
							}
							isWindscreenOn = !isWindscreenOn;
							render();
						}

					}
					break;
				case SDL_QUIT: quit = TRUE; break;
				default: break;
		   	 }
	 	}










		currentTime = SDL_GetTicks();
		if(currentTime > lastTime + 30) {
        	/*//printf("ffsdf\n");
			initRandom();
			if(didItHappen(50)){
				data = readData();
				char counter[100];
				sprintf(counter, "Compte-tour : %i  ", data * 1000);
				displayText(counter, roboto, counterColor, 500, 20, 1);
			}
			render();
			*/

			lastvect = vect;
			lastPos = pos;
			double speed = getSpeed(circuit[pos.indexLastPoint].speed);
			printf("%lf\n", speed);
			double distToTravel = speed * 10 / 3600.0;
			//printf("%.16lf %.16lf\n", distToTravel, pos.distToNext);
			while (distToTravel  >= pos.distToNext) {
				//printf("%.16lf %.16lf %.16lf\n", distToTravel, pos.distToNext, circuit[0].distToNext);
				distToTravel -= pos.distToNext;
				pos.indexLastPoint++;
				if (pos.indexLastPoint == nbPoint) pos.indexLastPoint = 0;
				int index = pos.indexLastPoint;
				pos.lat = circuit[index].lat;
				pos.lon = circuit[index].lon;
				pos.distToNext = circuit[index].distToNext;
			}

			double varLon = circuit[(pos.indexLastPoint + 1)%nbPoint].lon - circuit[pos.indexLastPoint].lon;
			double varLat = circuit[(pos.indexLastPoint + 1)%nbPoint].lat - circuit[pos.indexLastPoint].lat;

			double facteur = distToTravel / circuit[pos.indexLastPoint].distToNext;
			pos.lon += (varLon * facteur);
			pos.lat += (varLat * facteur);

			pos.distToNext -= distToTravel;
			vect = (t_vect) {pos.lat - lastPos.lat, pos.lon - lastPos.lon};
			if (lastvect.lat != -1 && lastvect.lon != -1) {
				double terma = (lastvect.lat * vect.lon + lastvect.lon * vect.lat);
				double termb = sqrt(lastvect.lat * lastvect.lat + lastvect.lon * lastvect.lon);
				double termc = sqrt(vect.lat * vect.lat + vect.lon * vect.lon);
				angle = acos (terma/(termb*termc));
				if (angle *180 /3 > 10){
					//execCommand("turn 1");
				}
				else if(angle * 180 /3 < -10){
					//execCommand("turn 2");
				}

			}

			tellServer (pos.lat, pos.lon);


        	lastTime = currentTime;

    	} else {
			SDL_Delay(30 - (currentTime - lastTime));
		}
	}


	unloadAllTextures(speedTextures, N_SPEED_TEXTURES);
	unloadAllTextures(dirTextures, N_DIR_TEXTURES);

	SDL_DestroyTexture(lampOn.texture);
	SDL_DestroyTexture(lampOff.texture);
	SDL_DestroyTexture(taillampOn.texture);
	SDL_DestroyTexture(taillampOff.texture);
	SDL_DestroyTexture(windscreenOn.texture);
	SDL_DestroyTexture(windscreenOff.texture);
	SDL_DestroyTexture(selectionSpeed.texture);
	SDL_DestroyTexture(selectionDir.texture);
	SDL_DestroyTexture(selectionClearSpeed.texture);
	SDL_DestroyTexture(selectionClearDir.texture);

	TTF_CloseFont(roboto);

	quitSdl();
}
