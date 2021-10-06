// funkcija za podesavanje statusa plavih, zelenih i cokoladnih linija
void setActiveLines();

// funkcija koja ogranicava kretanje figure, da bi se figura kretala po plavim merdevinama
bool checkYCoordBL(double xCoord, double yCoord);

// funkcija koja ogranicava kretanje figure, da bi se figura kretala po zelenim merdevinama
bool checkYCoordGL(double xCoord, double yCoord);

// funkcija koja ogranicava kretanje figure, da bi se figura kretala po cokoladnim linijama
bool checkXCoord(double xCoord, double yCoord);

// prva funkcija za prikazivanje niza karaktera na ekranu
void drawString(float x, float y, float z, char* string);

// druga funkcija za prikazivanje niza karaktera na ekranu
void drawString2(float x, float y, float z, char* string);

// treca funkcija za prikazivanje niza karaktera na ekranu
void drawString3(float x, float y, float z, char* string);

// funkcija za ucitavanje teksture iz bmp bitmap fajla
void loadTextureFromFile(char* filename);

// funkcija za ucitavanje svih potrebnih tekstura(devet), 
// tako sto radi ponovno pozivanje funkcije "loadTextureFromFile"
void initNine(char* filenames[]);

// funkcija za prikazivanje i-te teksture
void drawTextureQuad(int i, int j);

//	funkcija za iscrtavanje figure "Peter Pepper"
void peterPepperDraw();

//	funkcija za promenu vrednosti koordinata figura hvataca i za njihovo iscrtavanje
void moveCoordsGuard(double& xCoord, double& yCoord, int figureNumber, int randomNumbers[]);

// funkcija koja proverava da li je figura "Peter Pepper" presla preko nekog dela Burger-a
bool compareCoordsPeterPepperAndBurger(double burgerXcoord, double burgerYcoord);

// funkcija koja proverava da li je kraj igre
bool checkEndGame();

// funkcija koja proverava da li je figura hvatac uhvatila figuru "Peter Pepper" 
void compareCoordsPeterPepperAndGuard(double x, double y);

// funkcija koja radi sa tasterima(ENTER, SPACE, ESCAPE)
void myKeyboardFunc(unsigned char key, int x, int y);

// funkcija koja radi sa tasterima strelica 
// i koja menja koordinate figure "Peter Pepper" u zavisnosti od pritisnutog tastera strelice
void mySpecialKeyFunc(int key, int x, int y);

// funkcija koja crta zaglavlje, plave merdevine, zelene merdevine i cokoladne linije
void drawScene1();

// funkcija koja crta figuru "Peter Pepper", pozivanjem funkcije "peterPepperDraw"
void drawScene2();

// funkcija koja iscrtava sve delove svakog hamburgera
void drawScene3();

// funkcija koja iscrtava figure napadaca
void drawScene4();

// funkcija koja poziva sve funkcije "drawScene"
void drawScene();

// funkcija za promenu velicine prozora
void resizeWindow(int w, int h);

// glavna funkcija koja se prva poziva
int main(int argc, char** argv);

