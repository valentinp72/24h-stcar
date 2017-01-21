/*
 * C toolbox : Headers
 *
 * Initially created by:
 * MOTTIER Emeric
 * PELLOIN Valentin
 * TEYSSIER Titouan
 *
 * Creation:    11/28/2016
 * Last update: 01/13/2017
*/
#ifndef TOOLS
#define TOOLS

	// -- CONSTANTS -- //

	#define TRUE  1
	#define FALSE 0

	typedef enum {
		COLOR_RED = 1,
		COLOR_GREEN,
		COLOR_YELLOW,
		COLOR_BLUE,
		COLOR_MAGENTA,
		COLOR_CYAN,
		COLOR_WHITE,
		COLOR_RESET
	} t_colors;

	typedef struct {int x, y;} pt2D;
	typedef struct {int x, y, z;} pt3D;

	// -- FUNCTIONS -- //

	void initRandom();
	int randab(int a, int b);
	int didItHappen(int chance);

	int min(int a, int b);
	int max(int a, int b);

	void switchAB(int * a, int * b);
	int distBetweenAB(int a, int b);
	int isBetween(int val, int a, int b);
	float pt2D_Dist(pt2D a, pt2D b);
	float pt3D_Dist(pt3D a, pt3D b);
	int pt2D_equals(pt2D a, pt2D b);
	int pt3D_equals(pt3D a, pt3D b);
	int intervalOverlaping(int a, int b, int c, int d);
	int mapping(int value, int min, int max, int destMin, int destMax);
	float average(int n, ...);

	int  car2val(char car);
	char up2low(char car);
	char low2up(char car);

	void err(char msg[], int dir);
	void errInit();
	void errClose();

	int fileExist(char * fileName);
	int nLinesFile(char * file);
	int nColsFile(char * file);

	void termClear();
	void termGoXY(int x, int y);
	void termForegroundColor(t_colors color);
	void termBackgroundColor(t_colors color);
	void termResetColors();

#endif
