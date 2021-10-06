#include <math.h>		
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "Glut.h"
#include "BurgerTime.h"
#include "RgbImage.h"
#include <ctime>

// window size
const double Xmin = 0.0, Xmax = 3.0;
const double Ymin = 0.0, Ymax = 4.0;

// blue lines
double arrayOfXcoords1[] = { 0.425, 0.575, 0.925, 1.075, 1.425, 1.575, 1.925, 2.075, 2.425, 2.575 };
int arrayOfXcoords1Size = sizeof(arrayOfXcoords1) / sizeof(arrayOfXcoords1[0]);
double yCoord1 = 0.0;
bool arrayOfXcoords1ActiveLines[5][36];

// green lines
double arrayOfXcoords2[] = { 0.675, 0.825, 1.175, 1.325, 1.675, 1.825, 2.175, 2.325 };
int arrayOfXcoords2Size = sizeof(arrayOfXcoords2) / sizeof(arrayOfXcoords2[0]);
bool arrayOfXcoords2ActiveLines[4][36];

// chocolate lines
double arrayOfXcoords3[] = { 0.375, 1.125, 0.875, 1.625, 1.375, 2.125, 1.875, 2.625 };
int arrayOfXcoords3Size = sizeof(arrayOfXcoords3) / sizeof(arrayOfXcoords3[0]);
bool arrayOfXcoords3ActiveLines[4][10];

int k1 = 0, k2 = 0;	// counters

// header
char string[] = { 'S', 'c', 'o', 'r', 'e', ':', ' ', '\0' };
char string2[] = { 'N', 'u', 'm', 'O', 'f', 'L', 'i', 'v', 'e', 's', ':', ' ', '\0' };
char string3[] = { 'L', 'e', 'v', 'e', 'l', ':', ' ', '\0' };
char score[] = { '0', '0', '0', '0', '0', '\0' };
int score2 = 0, score3 = 0;	// pomocne promenljive za formiranje score-a
char numOfLives[] = { '5', '\0' };
char level[] = { '1', '\0' };
int level2 = 1;

// file names with the extension "bmp"
static GLuint textureName[8];
//	24-bit Bitmap
char str1[20] = "Peter_Pepper.bmp";
char str2[20] = "Hot_Dog.bmp";
char str3[20] = "Fried_Egg.bmp";
char str4[20] = "Pickle.bmp";
char str5[20] = "Burger_1.bmp";
char str6[20] = "Burger_2.bmp";
char str7[20] = "Burger_5.bmp";
char str8[20] = "Burger_6.bmp";
char str9[20] = "BurgerTimeLogo.bmp";
char* filenameArray[] = { str1, str2, str3, str4, str5, str6, str7, str8, str9 };

// coords
double peterPepperXcoord = 0.44;
double peterPepperYcoord = 1.035;

double hotDog1Xcoord = 2.155;
double hotDog1Ycoord = 1.035;

double hotDog2Xcoord = 1.665;
double hotDog2Ycoord = 1.595;

double friedEgg1Xcoord = 0.655;
double friedEgg1Ycoord = 3.555;

double friedEgg2Xcoord = 1.175;
double friedEgg2Ycoord = 1.595;

double pickle1Xcoord = 0.655;
double pickle1Ycoord = 3.555;

double pickle2Xcoord = 1.175;
double pickle2Ycoord = 3.555;

double burger1_xCoords[] = { 0.655, 0.655, 0.655, 0.655 };
double burger1_yCoords[] = { 2.995, 2.435, 1.595, 1.035 };
double burger1_2_yCoords[] = { 2.995, 2.435, 1.595, 1.035, 0.5 };

double burger2_xCoords[] = { 1.175, 1.175, 1.175, 1.175 };
double burger2_yCoords[] = { 3.555, 2.155, 1.595, 1.035 };

double burger3_xCoords[] = { 1.665, 1.665, 1.665, 1.665 };
double burger3_yCoords[] = { 3.555, 2.995, 2.155, 1.035 };

double burger4_xCoords[] = { 2.155, 2.155, 2.155, 2.155 };
double burger4_yCoords[] = { 3.555, 2.995, 2.435, 1.875 };

// for function "checkXCoord"
int arr[] = { 10350, 15950, 18750, 21550, 24350, 27150, 29950, 35550 };	
// morao sam u niz arr da sacuvam int brojeve, jer poredjenje double vrednosti je rizicno, zbog decimala
// npr. 10350 / 10000 = 1.035
// ako bi ostalo 1.035 i ako bi peterPepperYcoord = 1.035, ne znaci da je arr[0] == peterPepperYcoord, jer je mozda peterPepperYcoord = 1.0350000034
int arrSize = sizeof(arr) / sizeof(arr[0]);

// for function "drawScene3"
int arrt1[] = { 4, 3, 2, 1 };
int arrt2[] = { 5, 3, 2, 1 };
int arrt3[] = { 5, 4, 3, 1 };
int arrt4[] = { 5, 4, 3, 2 };

// for function "drawScene4"
int randomNumbersA[4] = { 1, 3, 1, 1 };
int randomNumbersB[4] = { 2, 2, 3, 1 };
int randomNumbersC[4] = { 1, 1, 3, 1 };
int randomNumbersD[4] = { 2, 1, 3, 1 };
int randomNumbersE[4] = { 3, 1, 1, 1 };
int randomNumbersF[4] = { 3, 2, 1, 2 };

// to start and stop the game
bool start = true;

// for draw a scene
int scene = 1;

double attackerSpeed = 0.0005;

// if(scene == 1) 
char string4[] = { 'L', 'e', 'v', 'e', 'l', ' ', '1', ' ', '\0' };
char string5[] = { 'L', 'e', 'v', 'e', 'l', ' ', '2', ' ', '\0' };
char string6[] = { 'n', 'i', 'k', 'o', 'l', 'a', '.', 'm', 'i', 't', 'r', 'e', 'v', 's', 'k', 'i', '1', '9', '9', '8', '@', 'g', 'm', 'a', 'i', 'l', '.', 'c', 'o', 'm', ' ', '\0' };

double arrowPosition = 0.15;

// if(scene == 3) 
char string7[] = { 'G', 'A', 'M', 'E', ' ', 'O', 'V', 'E', 'R', '!', ' ', '\0' };
char string8[] = { 'W', 'I', 'N', 'N', 'E', 'R', '!', ' ', '\0' };

void setActiveLines() {
	// postavljaju se vrednosti blokova na aktivan(true) ili neaktivan(false), gde svaki blok je predstavljen pomocu dve linije
	// 18 bloka predstavljaju 32 linije
	// blokovi se gledaju odozdo na gore
	arrayOfXcoords1ActiveLines[0][0] = true; 	arrayOfXcoords1ActiveLines[1][0] = true; 	arrayOfXcoords1ActiveLines[2][0] = true; 	arrayOfXcoords1ActiveLines[3][0] = true; 	arrayOfXcoords1ActiveLines[4][0] = true;
	arrayOfXcoords1ActiveLines[0][1] = true;	arrayOfXcoords1ActiveLines[1][1] = true; 	arrayOfXcoords1ActiveLines[2][1] = true; 	arrayOfXcoords1ActiveLines[3][1] = true; 	arrayOfXcoords1ActiveLines[4][1] = true;
	arrayOfXcoords1ActiveLines[0][2] = true;	arrayOfXcoords1ActiveLines[1][2] = true; 	arrayOfXcoords1ActiveLines[2][2] = true; 	arrayOfXcoords1ActiveLines[3][2] = true; 	arrayOfXcoords1ActiveLines[4][2] = true;
	arrayOfXcoords1ActiveLines[0][3] = true; 	arrayOfXcoords1ActiveLines[1][3] = true; 	arrayOfXcoords1ActiveLines[2][3] = true; 	arrayOfXcoords1ActiveLines[3][3] = true; 	arrayOfXcoords1ActiveLines[4][3] = true;
	arrayOfXcoords1ActiveLines[0][4] = true; 	arrayOfXcoords1ActiveLines[1][4] = true; 	arrayOfXcoords1ActiveLines[2][4] = true; 	arrayOfXcoords1ActiveLines[3][4] = true; 	arrayOfXcoords1ActiveLines[4][4] = true;
	arrayOfXcoords1ActiveLines[0][5] = true; 	arrayOfXcoords1ActiveLines[1][5] = true; 	arrayOfXcoords1ActiveLines[2][5] = true; 	arrayOfXcoords1ActiveLines[3][5] = true; 	arrayOfXcoords1ActiveLines[4][5] = true;
	arrayOfXcoords1ActiveLines[0][6] = true; 	arrayOfXcoords1ActiveLines[1][6] = true; 	arrayOfXcoords1ActiveLines[2][6] = true; 	arrayOfXcoords1ActiveLines[3][6] = true; 	arrayOfXcoords1ActiveLines[4][6] = false;
	arrayOfXcoords1ActiveLines[0][7] = true; 	arrayOfXcoords1ActiveLines[1][7] = true; 	arrayOfXcoords1ActiveLines[2][7] = true; 	arrayOfXcoords1ActiveLines[3][7] = true; 	arrayOfXcoords1ActiveLines[4][7] = false;
	arrayOfXcoords1ActiveLines[0][8] = true; 	arrayOfXcoords1ActiveLines[1][8] = true; 	arrayOfXcoords1ActiveLines[2][8] = true; 	arrayOfXcoords1ActiveLines[3][8] = true; 	arrayOfXcoords1ActiveLines[4][8] = false;
	arrayOfXcoords1ActiveLines[0][9] = true; 	arrayOfXcoords1ActiveLines[1][9] = true; 	arrayOfXcoords1ActiveLines[2][9] = true; 	arrayOfXcoords1ActiveLines[3][9] = true; 	arrayOfXcoords1ActiveLines[4][9] = false;
	arrayOfXcoords1ActiveLines[0][10] = false; 	arrayOfXcoords1ActiveLines[1][10] = true; 	arrayOfXcoords1ActiveLines[2][10] = true; 	arrayOfXcoords1ActiveLines[3][10] = true; 	arrayOfXcoords1ActiveLines[4][10] = true;
	arrayOfXcoords1ActiveLines[0][11] = false; 	arrayOfXcoords1ActiveLines[1][11] = true; 	arrayOfXcoords1ActiveLines[2][11] = true; 	arrayOfXcoords1ActiveLines[3][11] = true; 	arrayOfXcoords1ActiveLines[4][11] = true;
	arrayOfXcoords1ActiveLines[0][12] = false; 	arrayOfXcoords1ActiveLines[1][12] = true; 	arrayOfXcoords1ActiveLines[2][12] = true; 	arrayOfXcoords1ActiveLines[3][12] = true; 	arrayOfXcoords1ActiveLines[4][12] = true;
	arrayOfXcoords1ActiveLines[0][13] = false; 	arrayOfXcoords1ActiveLines[1][13] = true; 	arrayOfXcoords1ActiveLines[2][13] = true; 	arrayOfXcoords1ActiveLines[3][13] = true; 	arrayOfXcoords1ActiveLines[4][13] = true;
	arrayOfXcoords1ActiveLines[0][14] = true; 	arrayOfXcoords1ActiveLines[1][14] = true; 	arrayOfXcoords1ActiveLines[2][14] = true; 	arrayOfXcoords1ActiveLines[3][14] = true; 	arrayOfXcoords1ActiveLines[4][14] = true;
	arrayOfXcoords1ActiveLines[0][15] = true; 	arrayOfXcoords1ActiveLines[1][15] = true; 	arrayOfXcoords1ActiveLines[2][15] = true; 	arrayOfXcoords1ActiveLines[3][15] = true; 	arrayOfXcoords1ActiveLines[4][15] = true;
	arrayOfXcoords1ActiveLines[0][16] = true; 	arrayOfXcoords1ActiveLines[1][16] = true; 	arrayOfXcoords1ActiveLines[2][16] = true; 	arrayOfXcoords1ActiveLines[3][16] = true; 	arrayOfXcoords1ActiveLines[4][16] = true;
	arrayOfXcoords1ActiveLines[0][17] = true; 	arrayOfXcoords1ActiveLines[1][17] = true; 	arrayOfXcoords1ActiveLines[2][17] = true; 	arrayOfXcoords1ActiveLines[3][17] = true; 	arrayOfXcoords1ActiveLines[4][17] = true;

	arrayOfXcoords2ActiveLines[0][0] = false; 	arrayOfXcoords2ActiveLines[1][0] = false; 	arrayOfXcoords2ActiveLines[2][0] = false; 	arrayOfXcoords2ActiveLines[3][0] = true;
	arrayOfXcoords2ActiveLines[0][1] = false;	arrayOfXcoords2ActiveLines[1][1] = false; 	arrayOfXcoords2ActiveLines[2][1] = false; 	arrayOfXcoords2ActiveLines[3][1] = true;
	arrayOfXcoords2ActiveLines[0][2] = false;	arrayOfXcoords2ActiveLines[1][2] = false; 	arrayOfXcoords2ActiveLines[2][2] = false; 	arrayOfXcoords2ActiveLines[3][2] = true;
	arrayOfXcoords2ActiveLines[0][3] = false; 	arrayOfXcoords2ActiveLines[1][3] = false; 	arrayOfXcoords2ActiveLines[2][3] = false; 	arrayOfXcoords2ActiveLines[3][3] = true;
	arrayOfXcoords2ActiveLines[0][4] = true; 	arrayOfXcoords2ActiveLines[1][4] = false; 	arrayOfXcoords2ActiveLines[2][4] = false; 	arrayOfXcoords2ActiveLines[3][4] = true;
	arrayOfXcoords2ActiveLines[0][5] = true; 	arrayOfXcoords2ActiveLines[1][5] = false; 	arrayOfXcoords2ActiveLines[2][5] = false; 	arrayOfXcoords2ActiveLines[3][5] = true;
	arrayOfXcoords2ActiveLines[0][6] = true; 	arrayOfXcoords2ActiveLines[1][6] = false; 	arrayOfXcoords2ActiveLines[2][6] = false; 	arrayOfXcoords2ActiveLines[3][6] = true;
	arrayOfXcoords2ActiveLines[0][7] = true; 	arrayOfXcoords2ActiveLines[1][7] = false; 	arrayOfXcoords2ActiveLines[2][7] = false; 	arrayOfXcoords2ActiveLines[3][7] = true;
	arrayOfXcoords2ActiveLines[0][8] = true; 	arrayOfXcoords2ActiveLines[1][8] = false; 	arrayOfXcoords2ActiveLines[2][8] = true; 	arrayOfXcoords2ActiveLines[3][8] = true;
	arrayOfXcoords2ActiveLines[0][9] = true; 	arrayOfXcoords2ActiveLines[1][9] = false; 	arrayOfXcoords2ActiveLines[2][9] = true; 	arrayOfXcoords2ActiveLines[3][9] = true;
	arrayOfXcoords2ActiveLines[0][10] = true; 	arrayOfXcoords2ActiveLines[1][10] = false; 	arrayOfXcoords2ActiveLines[2][10] = true; 	arrayOfXcoords2ActiveLines[3][10] = false;
	arrayOfXcoords2ActiveLines[0][11] = true; 	arrayOfXcoords2ActiveLines[1][11] = false; 	arrayOfXcoords2ActiveLines[2][11] = true; 	arrayOfXcoords2ActiveLines[3][11] = false;
	arrayOfXcoords2ActiveLines[0][12] = true; 	arrayOfXcoords2ActiveLines[1][12] = true; 	arrayOfXcoords2ActiveLines[2][12] = true; 	arrayOfXcoords2ActiveLines[3][12] = false;
	arrayOfXcoords2ActiveLines[0][13] = true; 	arrayOfXcoords2ActiveLines[1][13] = true; 	arrayOfXcoords2ActiveLines[2][13] = true; 	arrayOfXcoords2ActiveLines[3][13] = false;
	arrayOfXcoords2ActiveLines[0][14] = false; 	arrayOfXcoords2ActiveLines[1][14] = true; 	arrayOfXcoords2ActiveLines[2][14] = false; 	arrayOfXcoords2ActiveLines[3][14] = false;
	arrayOfXcoords2ActiveLines[0][15] = false; 	arrayOfXcoords2ActiveLines[1][15] = true; 	arrayOfXcoords2ActiveLines[2][15] = false; 	arrayOfXcoords2ActiveLines[3][15] = false;
	arrayOfXcoords2ActiveLines[0][16] = false; 	arrayOfXcoords2ActiveLines[1][16] = true; 	arrayOfXcoords2ActiveLines[2][16] = false; 	arrayOfXcoords2ActiveLines[3][16] = false;
	arrayOfXcoords2ActiveLines[0][17] = false; 	arrayOfXcoords2ActiveLines[1][17] = true; 	arrayOfXcoords2ActiveLines[2][17] = false; 	arrayOfXcoords2ActiveLines[3][17] = false;

	arrayOfXcoords3ActiveLines[0][0] = true; 	arrayOfXcoords3ActiveLines[1][0] = true; 	arrayOfXcoords3ActiveLines[2][0] = true; 	arrayOfXcoords3ActiveLines[3][0] = true;
	arrayOfXcoords3ActiveLines[0][1] = false;	arrayOfXcoords3ActiveLines[1][1] = false; 	arrayOfXcoords3ActiveLines[2][1] = false; 	arrayOfXcoords3ActiveLines[3][1] = false;
	arrayOfXcoords3ActiveLines[0][2] = true;	arrayOfXcoords3ActiveLines[1][2] = true; 	arrayOfXcoords3ActiveLines[2][2] = true; 	arrayOfXcoords3ActiveLines[3][2] = false;
	arrayOfXcoords3ActiveLines[0][3] = false; 	arrayOfXcoords3ActiveLines[1][3] = false; 	arrayOfXcoords3ActiveLines[2][3] = false; 	arrayOfXcoords3ActiveLines[3][3] = true;
	arrayOfXcoords3ActiveLines[0][4] = false; 	arrayOfXcoords3ActiveLines[1][4] = true; 	arrayOfXcoords3ActiveLines[2][4] = true; 	arrayOfXcoords3ActiveLines[3][4] = false;
	arrayOfXcoords3ActiveLines[0][5] = true; 	arrayOfXcoords3ActiveLines[1][5] = false; 	arrayOfXcoords3ActiveLines[2][5] = false; 	arrayOfXcoords3ActiveLines[3][5] = true;
	arrayOfXcoords3ActiveLines[0][6] = false; 	arrayOfXcoords3ActiveLines[1][6] = true; 	arrayOfXcoords3ActiveLines[2][6] = false; 	arrayOfXcoords3ActiveLines[3][6] = false;
	arrayOfXcoords3ActiveLines[0][7] = true; 	arrayOfXcoords3ActiveLines[1][7] = false; 	arrayOfXcoords3ActiveLines[2][7] = true; 	arrayOfXcoords3ActiveLines[3][7] = true;
	arrayOfXcoords3ActiveLines[0][8] = false; 	arrayOfXcoords3ActiveLines[1][8] = false; 	arrayOfXcoords3ActiveLines[2][8] = false; 	arrayOfXcoords3ActiveLines[3][8] = false;
	arrayOfXcoords3ActiveLines[0][9] = true; 	arrayOfXcoords3ActiveLines[1][9] = true; 	arrayOfXcoords3ActiveLines[2][9] = true; 	arrayOfXcoords3ActiveLines[3][9] = true;
}

// funkcija koja ogranicava kretanje figure, da bi se figura kretala po plavim merdevinama
bool checkYCoordBL(double xCoord, double yCoord) {
	for (int i = 0; i < arrayOfXcoords1Size; i += 2) {
		if (((arrayOfXcoords1[i] - 0.15 / 2.0) <= xCoord) && ((arrayOfXcoords1[i + 1] - 0.15 / 2.0) >= xCoord)) {
			//printf("%f\n", yCoord);
			switch (i / 2 + 1) {
				case 1:	// predstavlja redni broj kolone sa plavim merdevinama
					// ogranicavam tako da ne postoji kretanje tamo gde nema merdevina(kretanje po y osi)
					if (yCoord <= 2.435 || yCoord >= 2.995) {
						if (yCoord >= 1.035 && yCoord <= 3.565) {
							return true;
						}
					}
					return false;
				case 2:
					if (yCoord >= 1.035 && yCoord <= 3.565) {
						return true;
					}
				case 3:
					if (yCoord >= 1.035 && yCoord <= 3.565) {
						return true;
					}
				case 4:
					if (yCoord >= 1.035 && yCoord <= 3.565) {
						return true;
					}
				case 5:
					if (yCoord <= 1.875 || yCoord >= 2.425) {
						if (yCoord >= 1.035 && yCoord <= 3.565) {
							return true;
						}
					}
					return false;
			}
		}
	}
	return false;
}

// funkcija koja ogranicava kretanje figure, da bi se figura kretala po zelenim merdevinama
bool checkYCoordGL(double xCoord, double yCoord) {
	for (int i = 0; i < arrayOfXcoords2Size; i += 2) {
		if (((arrayOfXcoords2[i] - 0.15 / 2.0) <= xCoord) && ((arrayOfXcoords2[i + 1] - 0.15 / 2.0) >= xCoord)) {
			//printf("%f\n", yCoord);
			switch (i / 2 + 1) {
				case 1:	// predstavlja redni broj kolone sa zelenim merdevinama
					// ogranicavam tako da ne postoji kretanje tamo gde nema merdevina(kretanje po y osi)
					if (yCoord >= 1.585 && yCoord <= 3.005) {
						if (yCoord >= 1.035 && yCoord <= 3.565) {
							return true;
						}
					}
					return false;
				case 2:
					if (yCoord >= 2.715) {
						if (yCoord >= 1.035 && yCoord <= 3.565) {
							return true;
						}
					}
					return false;
				case 3:
					if (yCoord >= 2.145 && yCoord <= 3.005) {
						if (yCoord >= 1.035 && yCoord <= 3.565) {
							return true;
						}
					}
					return false;
				case 4:
					if (yCoord <= 2.435) {
						if (yCoord >= 1.035 && yCoord <= 3.565) {
							return true;
						}
					}
					return false;
			}
		}
	}
	return false;
}

// funkcija koja ogranicava kretanje figure, da bi se figura kretala po linijama boje cokolade
bool checkXCoord(double xCoord, double yCoord) {
	int yCoord2 = yCoord * 10000;
	int index = arrSize + 5;	// za pocetnu vrednost, izabrao sam nasumicnu vrednost koja je razlicita od velicine niza, da bih aktivirao default case
	for (int i = 0; i < arrSize; i++) {
		//printf("i: %d y:%d arr[i]: %d\n", i, yCoord2, arr[i]);
		if (yCoord2 <= arr[i] + 5 && yCoord2 >= arr[i] - 5) {	// +-5 je zbog odstupanja
			index = i;
		}
	}
	//printf("index: %d\n", index);
	switch (index) {
		case 0:
			if (xCoord >= 0.37 && xCoord <= 2.47) {
				return true;
			}
			return false;
		case 1:
			if (xCoord >= 0.37 && xCoord <= 2.015) {
				return true;
			}
			return false;
		case 2:
			if (xCoord >= 1.875 && xCoord <= 2.47) {
				return true;
			}
			return false;
		case 3:
			if (xCoord >= 0.825 && xCoord <= 2.015) {
				return true;
			}
			return false;
		case 4:
			if ((xCoord >= 0.37 && xCoord <= 0.93) || (xCoord >= 1.875 && xCoord <= 2.47)) {
				return true;
			}
			return false;
		case 5:
			if (xCoord >= 0.825 && xCoord <= 1.455) {
				return true;
			}
			return false;
		case 6:
			if ((xCoord >= 0.37 && xCoord <= 0.93) || (xCoord >= 1.315 && xCoord <= 2.47)) {
				return true;
			}
			return false;
		case 7:
			if (xCoord >= 0.37 && xCoord <= 2.47) {
				return true;
			}
			return false;
		default:
			return false;
	}
}

/*
 * Draw a character string.
 *
 * @param x        The x position
 * @param y        The y position
 * @param z        The z position
 * @param string   The character string
 */
void drawString(float x, float y, float z, char* string) {
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos3f(x, y, z);

	for (char* c = string; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *c);  // Updates the position
	}
}

void drawString2(float x, float y, float z, char* string) {
	glColor3f(0.855, 0.647, 0.125);	// goldenrod
	glRasterPos3f(x, y, z);

	for (char* c = string; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);  // Updates the position
	}
}

void drawString3(float x, float y, float z, char* string) {
	glColor3f(1.0, 1.0, 1.0);	// goldenrod
	glRasterPos3f(x, y, z);

	for (char* c = string; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);  // Updates the position
	}
}

/* Read a texture map from a BMP bitmap file. */
void loadTextureFromFile(char* filename) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

	RgbImage theTexMap(filename);

	// Pixel alignment: each row is word aligned.  Word alignment is the default. 
	// glPixelStorei(GL_UNPACK_ALIGNMENT, 4);		

	// Set the interpolation settings to best quality.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, theTexMap.GetNumCols(), theTexMap.GetNumRows(), GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData());
}

/* Load the nine textures, by repeatedly called loadTextureFromFile(). */
void initNine(char* filenames[]) {
	glGenTextures(8, textureName);	// Load four texture names into array

	for (int i = 0; i < 9; i++) {
		glBindTexture(GL_TEXTURE_2D, textureName[i]);	// Texture #i is active now
		loadTextureFromFile(filenames[i]);			// Load texture #i
	}
}

/* Display the i-th texture. */
void drawTextureQuad(int i, int j) {
	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, textureName[i]);

	switch (j) {	// jer se crta ili hamburger ili figura
		case 1:
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.5);
			glTexCoord2f(0.0, 1.0); glVertex3f(0.0, 0.15, 0.5);
			glTexCoord2f(1.0, 1.0); glVertex3f(0.15, 0.15, 0.5);
			glTexCoord2f(1.0, 0.0); glVertex3f(0.15, 0.0, 0.5);
			glEnd();
			break;
		case 2:
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.5);
			glTexCoord2f(0.0, 1.0); glVertex3f(0.0, 0.1, 0.5);
			glTexCoord2f(1.0, 1.0); glVertex3f(0.2, 0.1, 0.5);
			glTexCoord2f(1.0, 0.0); glVertex3f(0.2, 0.0, 0.5);
			glEnd();
			break;
		case 3:
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.5);
			glTexCoord2f(0.0, 1.0); glVertex3f(0.0, 1.5, 0.5);
			glTexCoord2f(1.0, 1.0); glVertex3f(2.5, 1.5, 0.5);
			glTexCoord2f(1.0, 0.0); glVertex3f(2.5, 0.0, 0.5);
			glEnd();
			break;
	}
	
}

//	funkcija za iscrtavanje figure "Peter Pepper"
void peterPepperDraw() {
	//printf("x: %f y: %f\n", peterPepperXcoord, peterPepperYcoord);
	glPushMatrix();
	glTranslatef(peterPepperXcoord, peterPepperYcoord, 0.0f);
	drawTextureQuad(0, 1);
	glPopMatrix();
}

//	funkcija za promenu vrednosti koordinata figura hvataca i njihovo iscrtavanje
void moveCoordsGuard(double& xCoord, double& yCoord, int figureNumber, int randomNumbers[]) {
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	switch (randomNumbers[0]) {
		case 1:
			if (checkYCoordBL(xCoord, yCoord + attackerSpeed) || checkYCoordGL(xCoord, yCoord + attackerSpeed)) {
				yCoord += attackerSpeed;
			}
			else {
				randomNumbers[2] = (rand() % 99) + 11;
				randomNumbers[3] = (rand() % 10) + 2;
				randomNumbers[1] = (rand() % randomNumbers[2]) + randomNumbers[3];
				for (int i = 0; i < randomNumbers[1]; i++)
					randomNumbers[0] = (rand() % 4) + 1;
				//printf("%d\n", randomNumbers[0]);
			}
			break;
		case 2:
			if (checkXCoord(xCoord - attackerSpeed, yCoord)) {
				xCoord -= attackerSpeed;
			}
			else {
				randomNumbers[2] = (rand() % 99) + 11;
				randomNumbers[3] = (rand() % 10) + 2;
				randomNumbers[1] = (rand() % randomNumbers[2]) + randomNumbers[3];
				for (int i = 0; i < randomNumbers[1]; i++)
					randomNumbers[0] = (rand() % 4) + 1;
				//printf("%d\n", randomNumbers[0]);
			}
			break;
		case 3:
			if (checkYCoordBL(xCoord, yCoord - attackerSpeed) || checkYCoordGL(xCoord, yCoord - attackerSpeed)) {
				yCoord -= attackerSpeed;
			}
			else {
				randomNumbers[2] = (rand() % 99) + 11;
				randomNumbers[3] = (rand() % 10) + 2;
				randomNumbers[1] = (rand() % randomNumbers[2]) + randomNumbers[3];
				for (int i = 0; i < randomNumbers[1]; i++)
					randomNumbers[0] = (rand() % 4) + 1;
				//printf("%d\n", randomNumbers[0]);
			}
			break;
		case 4:
			if (checkXCoord(xCoord + attackerSpeed, yCoord)) {
				xCoord += attackerSpeed;
			}
			else {
				randomNumbers[2] = (rand() % 99) + 11;
				randomNumbers[3] = (rand() % 10) + 2;
				randomNumbers[1] = (rand() % randomNumbers[2]) + randomNumbers[3];
				for (int i = 0; i < randomNumbers[1]; i++)
					randomNumbers[0] = (rand() % 4) + 1;
				//printf("%d\n", randomNumbers[0]);
			}
			break;
	}

	glPushMatrix();
	glTranslatef(xCoord, yCoord, 0.0f);
	drawTextureQuad(figureNumber, 1);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

// funkcija koja proverava da li je figura "Peter Pepper" presla preko nekog dela Burger-a
bool compareCoordsPeterPepperAndBurger(double burgerXcoord, double burgerYcoord) {
	int BurgerXcoord = burgerXcoord * 10000;
	int BurgerYcoord = burgerYcoord * 10000;
	int PeterPepperXcoord = peterPepperXcoord * 10000;
	int PeterPepperYcoord = peterPepperYcoord * 10000;

	//printf("\nppX: %d bbX: %d\n", PeterPepperXcoord, BurgerXcoord);
	//printf("\nppY: %d bbY: %d\n", PeterPepperYcoord, BurgerYcoord);

	if (PeterPepperXcoord - 300 <= BurgerXcoord && PeterPepperXcoord + 300 >= BurgerXcoord) {	// +-300 je zbog greske
		if (PeterPepperYcoord - 5 <= BurgerYcoord && PeterPepperYcoord + 5 >= BurgerYcoord) {
			return true;
		}
		return false;
	}
	return false;
}

// funkcija koja proverava da li je kraj igre
bool checkEndGame() {
	for (int i = 0; i < 4; i++) {
		if (!(arrt1[i] == 0)) {
			return false;
		}
		if (!(arrt2[i] == 0)) {
			return false;
		}
		if (!(arrt3[i] == 0)) {
			return false;
		}
		if (!(arrt4[i] == 0)) {
			return false;
		}
	}
	return true;
}

// funkcija koja proverava da li je figura hvatac uhvatila figuru "Peter Pepper" 
void compareCoordsPeterPepperAndGuard(double x, double y) {
	int GuardXcoord = x * 10000;
	int GuardYcoord = y * 10000;
	int PeterPepperXcoord = peterPepperXcoord * 10000;
	int PeterPepperYcoord = peterPepperYcoord * 10000;

	if (PeterPepperXcoord - 1300 <= GuardXcoord && PeterPepperXcoord + 1300 >= GuardXcoord) {
		if (PeterPepperYcoord - 1300 <= GuardYcoord && PeterPepperYcoord + 1300 >= GuardYcoord) {
			// stopiraj igricu
			start = false;
			numOfLives[0] -= 1;
		}
	}
}

void myKeyboardFunc(unsigned char key, int x, int y) {
	switch (key) {
		case 13:	// ENTER
			if (scene == 1) {
				scene = 2;
			}
			break;
		case ' ':	// SPACE
			if (!start) {
				start = true;
				// vracam na pocetne koordinate
				peterPepperXcoord = 0.44;
				peterPepperYcoord = 1.035;
				hotDog1Xcoord = 2.155;
				hotDog1Ycoord = 1.035;
				hotDog2Xcoord = 1.665;
				hotDog2Ycoord = 1.595;
				friedEgg1Xcoord = 0.655;
				friedEgg1Ycoord = 3.555;
				friedEgg2Xcoord = 1.175;
				friedEgg2Ycoord = 1.595;
				pickle1Xcoord = 0.655;
				pickle1Ycoord = 3.555;

				if (numOfLives[0] == '0') {
					scene = 3;
				}
				glutPostRedisplay();
			}
			break;
		case 27:
			exit(1);
			break;
	}
}

// funkcija koja radi sa tasterima i koja menja koordinate figure "Peter Pepper" u zavisnosti od pritisnutog tastera
void mySpecialKeyFunc(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		if (scene == 1 && arrowPosition == 0.0) {
			arrowPosition += 0.15;
			level[0] -= 1;
			level2 = 1;
		}
		if (scene == 2) {
			if (checkYCoordBL(peterPepperXcoord, peterPepperYcoord + 0.035) || checkYCoordGL(peterPepperXcoord, peterPepperYcoord + 0.035)) {
				peterPepperYcoord += 0.035;
			}
		}
		break;
	case GLUT_KEY_DOWN:
		if (scene == 1 && arrowPosition == 0.15) {
			arrowPosition -= 0.15;
			level[0] += 1;
			level2 = 2;
		}
		if (scene == 2) {
			if (checkYCoordBL(peterPepperXcoord, peterPepperYcoord - 0.035) || checkYCoordGL(peterPepperXcoord, peterPepperYcoord - 0.035)) {
				peterPepperYcoord -= 0.035;
			}
		}
		break;
	case GLUT_KEY_LEFT:
		if (scene == 2) {
			if (checkXCoord(peterPepperXcoord - 0.035, peterPepperYcoord)) {
				peterPepperXcoord -= 0.035;
			}
		}
		break;
	case GLUT_KEY_RIGHT:
		if (scene == 2) {
			if (checkXCoord(peterPepperXcoord + 0.035, peterPepperYcoord)) {
				peterPepperXcoord += 0.035;
			}
		}
		break;
	}
}

void drawScene1() {
	// header
	drawString(0.375, 3.80, 0.0, string);
	drawString(0.375, 3.70, 0.0, score);

	drawString(1.175, 3.80, 0.0, string2);
	drawString(1.175, 3.70, 0.0, numOfLives);

	drawString(2.0, 3.80, 0.0, string3);
	drawString(2.0, 3.70, 0.0, level);
	
	// blue lines
	glLineWidth(2);
	glColor3f(0.118, 0.565, 1.000);
	for (int i = 0; i < arrayOfXcoords1Size; i += 2) {
		yCoord1 = 1.035;
		k1 = i / 2;
		k2 = 0;
		for (int j = 0; j < 36; j++) {
			glBegin(GL_LINES);
			if (arrayOfXcoords1ActiveLines[k1][k2]) {
				glVertex2f(arrayOfXcoords1[i + 0], yCoord1);
				glVertex2f(arrayOfXcoords1[i + 1], yCoord1);
			}
			if (j % 2 == 0) {
				yCoord1 += 0.036;
			}
			else {
				yCoord1 += (0.035 * 3);
				k2++;
			}
			glEnd();
		}
	}

	// green lines
	glColor3f(0.196, 0.804, 0.196);
	for (int i = 0; i < arrayOfXcoords2Size; i += 2) {
		yCoord1 = 1.035;
		k1 = i / 2;
		k2 = 0;
		for (int j = 0; j < 36; j++) {
			glBegin(GL_LINES);
			if (arrayOfXcoords2ActiveLines[k1][k2]) {
				glVertex2f(arrayOfXcoords2[i + 0], yCoord1);
				glVertex2f(arrayOfXcoords2[i + 1], yCoord1);
			}
			if (j % 2 == 0) {
				yCoord1 += 0.036;
			}
			else {
				yCoord1 += (0.035 * 3);
				k2++;
			}
			glEnd();
		}
	}

	k1 = 0;

	// chocolate lines
	glLineWidth(4);
	glColor3f(0.824, 0.412, 0.118);
	for (int i = 0; i < arrayOfXcoords3Size; i+=2) {
		yCoord1 = 1.020;
		for (int j = 0; j < 10; j++) {
			k2 = j;
			glBegin(GL_LINES);
			if (arrayOfXcoords3ActiveLines[k1][k2]) {
				glVertex2f(arrayOfXcoords3[i + 0], yCoord1);
				glVertex2f(arrayOfXcoords3[i + 1], yCoord1);
			}
			yCoord1 += 0.28;
			glEnd();
		}
		k1++;
	}

	// chocolate lines bottom
	glTranslatef(0.655, 0.5, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.2, 0.0);
	glEnd();
	glTranslatef(-0.655, -0.5, 0.0);

	glTranslatef(1.175, 0.5, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.2, 0.0);
	glEnd();
	glTranslatef(-1.175, -0.5, 0.0);

	glTranslatef(1.665, 0.5, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.2, 0.0);
	glEnd();
	glTranslatef(-1.665, -0.5, 0.0);

	glTranslatef(2.155, 0.5, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.2, 0.0);
	glEnd();
	glTranslatef(-2.155, -0.5, 0.0);

	glLineWidth(1);
}

void drawScene2() {
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	peterPepperDraw();

	//glFlush();
	glDisable(GL_TEXTURE_2D);
}

void drawScene3() {
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	for (int i = 0; i < 4; i++) {
		if (compareCoordsPeterPepperAndBurger(burger1_xCoords[i], burger1_yCoords[i])) {
			if (arrt1[i] == 4) {
				burger1_yCoords[i] = burger1_yCoords[i] - 0.560;
			}
			if (arrt1[i] == 3) {
				burger1_yCoords[i] = burger1_yCoords[i] - 1.5 * 0.560;
			}
			if (arrt1[i] == 2) {
				burger1_yCoords[i] = burger1_yCoords[i] - 0.560;
			}
			if (arrt1[i] == 1) {
				switch (i)
				{
					case 0:	//	Burger_1.bmp
						burger1_yCoords[i] = burger1_yCoords[i] - 0.410;
						break;
					case 1:	//	Burger_2.bmp
						burger1_yCoords[i] = burger1_yCoords[i] - 0.460;
						break;
					case 2:	//	Burger_5.bmp
						burger1_yCoords[i] = burger1_yCoords[i] - 0.510;
						break;
					case 3: //	Burger_6.bmp
						burger1_yCoords[i] = burger1_yCoords[i] - 0.560;
						break;
				}
				// Adding points
				score2 += 50;
				score3 = score2;
				for (int i = 4; i >= 0; i--) {
					score[i] = '0';
					score[i] += (score3 % 10);
					score3 /= 10;
				}
			}
			arrt1[i] = arrt1[i] - 1;
		}
		glPushMatrix();
		glTranslatef(burger1_xCoords[i], burger1_yCoords[i], 0.0f);
		drawTextureQuad(i + 4, 2);
		glPopMatrix();
	}

	for (int i = 0; i < 4; i++) {
		if (compareCoordsPeterPepperAndBurger(burger2_xCoords[i], burger2_yCoords[i])) {
			if (arrt2[i] == 5) {
				burger2_yCoords[i] = burger2_yCoords[i] - 1.5 * 0.560;
			}
			if (arrt2[i] == 4) {
				burger2_yCoords[i] = burger2_yCoords[i] - 0.560;
			}
			if (arrt2[i] == 3) {
				burger2_yCoords[i] = burger2_yCoords[i] - 0.560;
			}
			if (arrt2[i] == 2) {
				burger2_yCoords[i] = burger2_yCoords[i] - 0.560;
			}
			if (arrt2[i] == 1) {
				switch (i)
				{
					case 0:	//	Burger_1.bmp
						burger2_yCoords[i] = burger2_yCoords[i] - 0.410;
						break;
					case 1:	//	Burger_2.bmp
						burger2_yCoords[i] = burger2_yCoords[i] - 0.460;
						break;
					case 2:	//	Burger_5.bmp
						burger2_yCoords[i] = burger2_yCoords[i] - 0.510;
						break;
					case 3: //	Burger_6.bmp
						burger2_yCoords[i] = burger2_yCoords[i] - 0.560;
						break;
				}
				// Adding points
				score2 += 50;
				score3 = score2;
				for (int i = 4; i >= 0; i--) {
					score[i] = '0';
					score[i] += (score3 % 10);
					score3 /= 10;
				}
			}
			arrt2[i] = arrt2[i] - 1;
		}
		glPushMatrix();
		glTranslatef(burger2_xCoords[i], burger2_yCoords[i], 0.0f);
		drawTextureQuad(i + 4, 2);
		glPopMatrix();
	}

	for (int i = 0; i < 4; i++) {
		if (compareCoordsPeterPepperAndBurger(burger3_xCoords[i], burger3_yCoords[i])) {
			if (arrt3[i] == 5) {
				burger3_yCoords[i] = burger3_yCoords[i] - 0.560;
			}
			if (arrt3[i] == 4) {
				burger3_yCoords[i] = burger3_yCoords[i] - 1.5 * 0.560;
			}
			if (arrt3[i] == 3) {
				burger3_yCoords[i] = burger3_yCoords[i] - 0.560;
			}
			if (arrt3[i] == 2) {
				burger3_yCoords[i] = burger3_yCoords[i] - 0.560;
			}
			if (arrt3[i] == 1) {
				switch (i)
				{
				case 0:	//	Burger_1.bmp
					burger3_yCoords[i] = burger3_yCoords[i] - 0.410;
					break;
				case 1:	//	Burger_2.bmp
					burger3_yCoords[i] = burger3_yCoords[i] - 0.460;
					break;
				case 2:	//	Burger_5.bmp
					burger3_yCoords[i] = burger3_yCoords[i] - 0.510;
					break;
				case 3: //	Burger_6.bmp
					burger3_yCoords[i] = burger3_yCoords[i] - 0.560;
					break;
				}
				// Adding points
				score2 += 50;
				score3 = score2;
				for (int i = 4; i >= 0; i--) {
					score[i] = '0';
					score[i] += (score3 % 10);
					score3 /= 10;
				}
			}
			arrt3[i] = arrt3[i] - 1;
		}
		glPushMatrix();
		glTranslatef(burger3_xCoords[i], burger3_yCoords[i], 0.0f);
		drawTextureQuad(i + 4, 2);
		glPopMatrix();
	}

	for (int i = 0; i < 4; i++) {
		if (compareCoordsPeterPepperAndBurger(burger4_xCoords[i], burger4_yCoords[i])) {
			if (arrt4[i] == 5) {
				burger4_yCoords[i] = burger4_yCoords[i] - 0.560;
			}
			if (arrt4[i] == 4) {
				burger4_yCoords[i] = burger4_yCoords[i] - 0.560;
			}
			if (arrt4[i] == 3) {
				burger4_yCoords[i] = burger4_yCoords[i] - 0.560;
			}
			if (arrt4[i] == 2) {
				burger4_yCoords[i] = burger4_yCoords[i] - 1.5 * 0.560;
			}
			if (arrt4[i] == 1) {
				switch (i)
				{
				case 0:	//	Burger_1.bmp
					burger4_yCoords[i] = burger4_yCoords[i] - 0.410;
					break;
				case 1:	//	Burger_2.bmp
					burger4_yCoords[i] = burger4_yCoords[i] - 0.460;
					break;
				case 2:	//	Burger_5.bmp
					burger4_yCoords[i] = burger4_yCoords[i] - 0.510;
					break;
				case 3: //	Burger_6.bmp
					burger4_yCoords[i] = burger4_yCoords[i] - 0.560;
					break;
				}
				// Adding points
				score2 += 50;
				score3 = score2;
				for (int i = 4; i >= 0; i--) {
					score[i] = '0';
					score[i] += (score3 % 10);
					score3 /= 10;
				}
			}
			arrt4[i] = arrt4[i] - 1;
		}
		glPushMatrix();
		glTranslatef(burger4_xCoords[i], burger4_yCoords[i], 0.0f);
		drawTextureQuad(i + 4, 2);
		glPopMatrix();
	}

	// END OF GAME
	if (checkEndGame()) {
		scene = 4;
	}

	//glFlush();
	glDisable(GL_TEXTURE_2D);
}

void drawScene4() {
	// prvi hotdog
	moveCoordsGuard(hotDog1Xcoord, hotDog1Ycoord, 1, randomNumbersA);
	compareCoordsPeterPepperAndGuard(hotDog1Xcoord, hotDog1Ycoord);
	// drugi hotdog
	moveCoordsGuard(hotDog2Xcoord, hotDog2Ycoord, 1, randomNumbersB);
	compareCoordsPeterPepperAndGuard(hotDog2Xcoord, hotDog2Ycoord);
	// prvo peceno jaje
	moveCoordsGuard(friedEgg1Xcoord, friedEgg1Ycoord, 2, randomNumbersC);
	compareCoordsPeterPepperAndGuard(friedEgg1Xcoord, friedEgg1Ycoord);
	// drugo peceno jaje
	moveCoordsGuard(friedEgg2Xcoord, friedEgg2Ycoord, 2, randomNumbersD);
	compareCoordsPeterPepperAndGuard(friedEgg2Xcoord, friedEgg2Ycoord);
	// prvi krastavac
	moveCoordsGuard(pickle1Xcoord, pickle1Ycoord, 3, randomNumbersE);
	compareCoordsPeterPepperAndGuard(pickle1Xcoord, pickle1Ycoord);
	// drugi krastavac
	if (level2 == 2) {
		moveCoordsGuard(pickle2Xcoord, pickle2Ycoord, 3, randomNumbersF);
		compareCoordsPeterPepperAndGuard(pickle2Xcoord, pickle2Ycoord);
	}
}

void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	////////////////////////////////////////
	if (level2 == 1) {
		attackerSpeed = 0.0005;
	}
	if (level2 == 2) {
		attackerSpeed = 0.0008;
	}
	if (scene == 1) {
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glPushMatrix();
		glTranslatef(0.25, 2.0, 0.0f);
		drawTextureQuad(8, 3);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);

		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(0.0, arrowPosition, 0.0f);
		glBegin(GL_TRIANGLES);
		glVertex2f(1.1, 1.35);
		glVertex2f(1.1, 1.45);
		glVertex2f(1.2, 1.4);
		glEnd();
		glPopMatrix();

		drawString2(1.25, 1.5, 0.0, string4);
		drawString2(1.25, 1.35, 0.0, string5);
	}
	if (scene == 2) {
		drawScene1();
		drawScene2();
		drawScene3();
		drawScene4();
	}
	if (scene == 3) {
		drawString3(1.0, 3.0, 0.0, string7);
		drawString2(1.0, 2.0, 0.0, string);
		drawString2(1.55, 2.0, 0.0, score);
	}
	if (scene == 4) {
		drawString3(1.0, 3.0, 0.0, string8);
		drawString2(1.15, 2.0, 0.0, string);
		drawString2(1.55, 2.0, 0.0, score);
	}
	////////////////////////////////////////
	glFlush();
	glutSwapBuffers();
	if (start) {
		glutPostRedisplay();
	}
}

void resizeWindow(int w, int h) {
	double scale, center;
	double windowXmin, windowXmax, windowYmin, windowYmax;

	glViewport(0, 0, w, h);

	w = (w == 0) ? 1 : w;
	h = (h == 0) ? 1 : h;
	if ((Xmax - Xmin) / w < (Ymax - Ymin) / h) {
		scale = ((Ymax - Ymin) / h) / ((Xmax - Xmin) / w);
		center = (Xmax + Xmin) / 2;
		windowXmin = center - (center - Xmin)*scale;
		windowXmax = center + (Xmax - center)*scale;
		windowYmin = Ymin;
		windowYmax = Ymax;
	}
	else {
		scale = ((Xmax - Xmin) / w) / ((Ymax - Ymin) / h);
		center = (Ymax + Ymin) / 2;
		windowYmin = center - (center - Ymin)*scale;
		windowYmax = center + (Ymax - center)*scale;
		windowXmin = Xmin;
		windowXmax = Xmax;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(windowXmin, windowXmax, windowYmin, windowYmax, -1, 1);
}

int main(int argc, char** argv) {
	srand((unsigned)time(0));
	setActiveLines();
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Burger Time");
//	glutCreateWindow(argv[0]);
	initNine(filenameArray);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resizeWindow);
	glutKeyboardFunc(myKeyboardFunc);
	glutSpecialFunc(mySpecialKeyFunc);
	glutMainLoop();

	return(0);
}

