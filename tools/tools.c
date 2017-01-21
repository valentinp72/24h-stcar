/*
 * C toolbox : Source
 *
 * Initially created by:
 * MOTTIER Emeric
 * PELLOIN Valentin
 * TEYSSIER Titouan
 *
 * Creation:    11/28/2016
 * Last update: 01/13/2017
*/

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "tools.h"

#define ESC             "\x1b["
#define FILE_ERROR_NAME "error.log"
FILE * error;
int lvlError;


/*
 * Test if a file exists
 * 		fileName > Name of the file to check
 * = TRUE if the file exists
 * = FALSE otherwise
 */
int fileExist(char * fileName) {
	FILE * file = fopen(fileName, "r");
	if (file == NULL) return FALSE;
	else {
		fclose (file);
		return TRUE;
	}
}


/*
 * Initialize random function
 */
void initRandom() {
	srand(time(NULL));
}


/*
 * Choose a random number inside the interval
 * 		a > Min
 * 		b > Max
 * = A number between a and b (excluded) ]a;b[
 */
int randab(int a, int b) {
	int tmp;

	if (b < a) switchAB(&a, &b);
	return (rand()%(b-a)) + a;
}

/*
 * It has a chance (in %) of success
 * 		chance > probability (%) of success
 * = TRUE if it has succeed
 * = FALSE otherwise
 */
int didItHappen(int chance) {
	return rand()%100 < chance;
}


/*
 * Map a value from an interval to an other (proportionally)
 *		value   > the initial value
 *		min     > inferior bound of the reference interval
 *		max     > superior bound of the reference interval
 *		destMin > inferior bound of the target interval
 *		destMax > superior bound of the target interval
 * = the mapped value
 */
int mapping(int value, int min, int max, int destMin, int destMax) {

	if (destMin > destMax) return destMax + destMin - mapping(value, min, max, destMax, destMin);

	return ((destMax - destMin) * (value - min) / (max - min)) + destMin;
	/*	max - min -> value - min
		destMax - destMin -> ? - destMin
		=> ? - destMin = (destMax - destMin) * (value - min) / (max - min)
		=> ? = ((destMax - destMin) * (value - min) / (max - min)) + destMin
	*/
}


/*
 * Return the minimum between two integers
 * 		a > First value
 * 		b > Second value
 * = minimum between a and b
 */
int min(int a, int b) {
	if (a > b) return b;
	return a;
}

/*
 * Return the maximum between two integers
 * 		a > First value
 * 		b > Second value
 * = maximum between a and b
 */
int max(int a, int b) {
	if (a > b) return a;
	return b;
}


/*
 * Switch the value of a and b
 * 		a > First value
 * 		b > Second value
 */
void switchAB(int * a, int * b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

/*
 * Test if val is in [a;b]
 * 		val > Value to check
 *		a   > First bound of the interval
 * 		b   > Second bound of the interval
 * = TRUE if inside of [a;b]
 * = FALSE otherwise
 */
int isBetween(int val, int a, int b) {
	if (a <= val && b >= val) return TRUE;
	else return FALSE;
}

/*
 * Return the distance between a and b
 * 		a > The first value
 * 		b > The second
 * = the distance, always positive
 */
int distBetweenAB(int a, int b){
	return abs(a - b);
}

/*
 * Return the distance between 2 2D points
 * 		a > The fisrt point
 * 		b > The second point
 * = the distance, always positive
 */
float pt2D_Dist(pt2D a, pt2D b){
	int xDist = distBetweenAB(a.x, b.x);
	int yDist = distBetweenAB(a.y, b.y);
	return sqrt(xDist * xDist + yDist * yDist);
}

/*
 * Return the distance between 2 3D points
 * 		a > The fisrt point
 * 		b > The second point
 * = the distance, always positive
 */
float pt3D_Dist(pt3D a, pt3D b){
	int xDist = distBetweenAB(a.x, b.x);
	int yDist = distBetweenAB(a.y, b.y);
	int zDist = distBetweenAB(a.z, b.z);
	return sqrt(xDist * xDist + yDist * yDist + zDist * zDist);
}

/*
 * Test if the 2D points a and b are equals
 * 		a > The first point
 * 		b > The second point
 * = TRUE if they are equals
 * = FALSE otherwise
 */
int pt2D_equals(pt2D a, pt2D b){
	return (a.x == b.x && a.y == b.y);
}

/*
 * Test if the 3D points a and b are equals
 * 		a > The first point
 * 		b > The second point
 * = TRUE if they are equals
 * = FALSE otherwise
 */
int pt3D_equals(pt3D a, pt3D b){
	return (a.x == b.x && a.y == b.y && a.z == b.z);
}


/*
 * Test if the two intervals overlaps
 * 		a > inferior bound of the first interval
 * 		b > superior bound of the first interval
 * 		c > inferior bound of the second interval
 * 		d > superior bound of the second interval
 * = TRUE if the intersection of [a;b] and [c;d] is not empty
 * = FALSE otherwise
 */
int intervalOverlaping(int a, int b, int c, int d) {
	if (
		isBetween (a, c, d) ||
		isBetween (b, c, d) ||
		isBetween (c, a, b) ||
		isBetween (d, a, b)
	) return TRUE;
	else return FALSE;
}

/*
 * Average of a set of ints
 * 		  n > number of int to calc the average
 * 		... >  ints to calc the average
 * = the average
 */
float average(int n, ...){
	va_list args;
	int i, sum = 0;

	va_start(args, n);
	for(i = 0 ; i < n ; i++){
		sum += va_arg(args, int);
	}
	va_end(args);

	return sum / (n * 1.0);
}


/* Convert the letter to an alphabet position
 * 		car > Character we want the position
 * = Position of the character if it's a letter (A = 0, Z = 25)
 * = -1 otherwise
 */
int car2val(char car) {
	if (car >= 'a' && car <= 'z') return car - 'a';
	else if (car >= 'A' && car <= 'Z') return car - 'A';
	return -1;
}


/*
 * Transform the letter to a lower case
 * 		car > Character we want to convert
 * = the letter in lower case if it's a letter
 * = -1 otherwise
 */
char up2low(char car) {
	if (car >= 'A' && car <= 'Z') return car - 'A' + 'a';
	else if (car >= 'a' && car <= 'z') return car;
	else return -1;
}

/*
 * Transform the letter to a upper case
 * 		car > Character we want to convert
 * = the letter in upper case if it's a letter
 * = -1 otherwise
 */
char low2up(char car) {
	if (car >= 'A' && car <= 'Z') return car;
	else if (car >= 'a' && car <= 'z') return car - 'a' + 'A';
	else return -1;
}


/*
 * Initialize the error file
 */
void errInit(){
	remove(FILE_ERROR_NAME); //comme il est ouvert en mode ajout a chaque fois on le supprime en début d'execution
	error = fopen(FILE_ERROR_NAME, "a");
	lvlError = 0;
}

/*
 * Close the error file
 */
void errClose(){
	fclose(error);
}


/*
 * Add a message to the error file
 * 		msg > Message to add inside the file
 * 		dir >  1 : for the first call inside a function
 * 		      -1 : for the last call inside a function
 * 		       0 : otherwise
 */
void err(char msg[], int dir) {
	int i;

	if(dir == -1) lvlError--;
	for(i = 0; i < lvlError; i++) fprintf (error, "\t");
	fprintf(error, "%s\n", msg);
	if(dir == 1) lvlError++;
}


/*
 * Count the number of lines of a file
 * 		file > Name of the file
 * = number of lines of the file
 * = 0 if the opening of the file didn't worked
 */
int nLinesFile(char * file){

	char tmp;
	int line = 1;
	FILE * fic;

	fic = fopen(file, "r");

	if(fic != NULL){
		fscanf(fic, "%c", &tmp);
		while(!feof(fic)){
			if(tmp == '\n') line++;
			fscanf(fic, "%c", &tmp);
		}
		fclose(fic);
	}
	else return 0;

	return line;
}

/*
 * Count the number of columns of a file
 * 		file > Name of the file
 * = number (max) of columns of the file
 * = 0 if the opening of the file didn't worked
 */
int nColsFile(char * file){

	char tmp;
	int maxCol = 0;
	int tmpCol = 0;
	FILE * fic;

	fic = fopen(file, "r");

	if(fic != NULL){
		fscanf(fic, "%c", &tmp);
		while(!feof(fic)){
			if(tmp == '\n'){
				maxCol = max(maxCol, tmpCol);
				tmpCol = 0;
			}
			else tmpCol++;
			fscanf(fic, "%c", &tmp);
		}
		fclose(fic);
	}
	else return 0;

	return maxCol;
}

/*
 * Clear the screen (with ANSI escape codes)
 */
void termClear(){
	printf("\e[1;1H\e[2J");
}

/*
 * Go to x and y coords (with ANSI escape codes)
 */
void termGoXY(int x, int y){
	printf("%c[%d;%df", 0x1B, y, x);
}

/*
 * Change the text color (with ANSI escape codes)
 * 		color > The color (see the list in tools.h)
 */
void termForegroundColor(t_colors color){
	printf("%s3%im", ESC, color);
}

/*
 * Change the background color (with ANSI escape codes)
 * 		color > The color (see the list in tools.h)
 */
void termBackgroundColor(t_colors color){
	printf("%s4%im", ESC, color);
}

/*
 * Reset both background and foreground colors (with ANSI escape codes)
 */
void termResetColors(){
	termBackgroundColor(COLOR_RESET);
	termForegroundColor(COLOR_RESET);
	printf("\n");
}
