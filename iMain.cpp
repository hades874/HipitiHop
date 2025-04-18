#include "iGraphics.h"
#include"bitmap_loader.h"
#include<iostream>
#include<sstream>
#include<string>

using namespace std;
std::string;

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::VARIABLES HERE::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

int s = 0;
int dx, dy = 7;
int mx, my = 0;
int showFreddy;
int timerFreddy, timerBG, timerEvilSc, timerGoodSc, timerApple, timerApple2, timerPin1;
bool musicOn = true;

int iniPos_x = 80, iniPos_y = 60;	//position of freddy
int win_b = 1280, win_l = 718;		//window breadth and length size in pixels 
int width = 40, width1 = 2000, appleCall = 30, goodScCall = 200, pin1Call = 16;	//distance of calling different objects
int freddyIndex = 0;

//arrays containing various pictures ->
char arr[32][50] = { "pics\\bg\\bg_01.bmp", "pics\\bg\\bg_02.bmp", "pics\\bg\\bg_03.bmp", "pics\\bg\\bg_04.bmp", "pics\\bg\\bg_05.bmp", "pics\\bg\\bg_06.bmp", "pics\\bg\\bg_07.bmp", "pics\\bg\\bg_08.bmp", "pics\\bg\\bg_09.bmp", "pics\\bg\\bg_10.bmp", "pics\\bg\\bg_11.bmp", "pics\\bg\\bg_12.bmp", "pics\\bg\\bg_13.bmp", "pics\\bg\\bg_14.bmp", "pics\\bg\\bg_15.bmp", "pics\\bg\\bg_16.bmp", "pics\\bg\\bg_17.bmp", "pics\\bg\\bg_18.bmp", "pics\\bg\\bg_19.bmp", "pics\\bg\\bg_20.bmp", "pics\\bg\\bg_21.bmp", "pics\\bg\\bg_22.bmp", "pics\\bg\\bg_23.bmp", "pics\\bg\\bg_24.bmp", "pics\\bg\\bg_25.bmp", "pics\\bg\\bg_26.bmp", "pics\\bg\\bg_27.bmp", "pics\\bg\\bg_28.bmp", "pics\\bg\\bg_29.bmp", "pics\\bg\\bg_30.bmp", "pics\\bg\\bg_31.bmp", "pics\\bg\\bg_32.bmp" };
char evil[16][50] = {"pics\\characters\\evilscientistnet.bmp", "pics\\characters\\evilscientistnet.bmp", "pics\\characters\\evilscientistnet.bmp", "pics\\characters\\evilscientistnet.bmp", "pics\\characters\\evilscientistnet.bmp", "pics\\characters\\evilscientistnet.bmp" };
char good[16][50] = {"pics\\characters\\goodscientist.bmp", "pics\\characters\\goodscientist.bmp", "pics\\characters\\goodscientist.bmp"};
char apple[16][50] = {"pics\\apple.bmp", "pics\\apple.bmp", "pics\\apple.bmp", "pics\\apple.bmp", "pics\\apple.bmp"};
char pin[16][50] = { "pics\\obs\\pinS.bmp", "pics\\obs\\pinS.bmp", "pics\\obs\\pinS.bmp", "pics\\obs\\pinS.bmp", "pics\\obs\\pinS.bmp", "pics\\obs\\pinS.bmp", "pics\\obs\\pinS.bmp", "pics\\obs\\pinS.bmp", "pics\\obs\\pinS.bmp", "pics\\obs\\pinS.bmp", "pics\\obs\\pinS.bmp", "pics\\obs\\pinS.bmp" };
char movingFreddy[16][50] = { "pics\\characters\\freddy\\f1.bmp", "pics\\characters\\freddy\\f2.bmp", "pics\\characters\\freddy\\f3.bmp", "pics\\characters\\freddy\\f4.bmp" };

char sc[1000] = "0";
int point = 0;
//int pointCount = point;
//FILE *fp;
//int highscore = 0;

char pName[50];		//for player name
char str1[50];
int index = 0;

//codes for menu system (start)

void mainMenu()
{
	iShowBMP(0, 0, "pics\\menu\\mainMenu.bmp");
}

void start()
{
	if (s == 1){
		void bgMove();
	}
}

void scoreBoard()
{
	if (s == 2)
	{
		iShowBMP(0, 0, "pics\\menu\\scoreBoard.bmp");
	}

}

void credits()
{
	if (s == 3)
	{
		iShowBMP(0, 0, "pics\\menu\\credits.bmp");
	}

}

void story()
{
	if (s == 4)
	{
		iShowBMP(0, 0, "pics\\menu\\story.bmp");
	}

}

void tutorials()
{
	if (s == 5)
	{
		iShowBMP(0, 0, "pics\\menu\\tutorials.bmp");
	}
	
}

void settings()
{
	if (s == 6)
	{
		iShowBMP(0, 0, "pics\\menu\\settings.bmp");
	}

	if (s == 7)
	{
		iShowBMP(0, 0, "pics\\menu\\nomusic.bmp");
		if (musicOn){
			musicOn = false;
			PlaySound(0, 0, 0);
		}
	}
	
	if (s == 8)
	{
		iShowBMP(0, 0, "pics\\menu\\nosound.bmp");
	}
	
	if (s == 9)
	{
		iShowBMP(0, 0, "pics\\menu\\none.bmp");
		
	}

}

void pauseMenu()
{
	if (s == 10)
		iShowBMP(0, 0, "pics\\menu\\pause.bmp");
}
/*
void gameOver(){

	if (s == 16){
		iShowBMP(0, 0, "pics\\menu\\gameover.bmp");
		iSetColor(0, 0, 0);
		iText(560, 295, "Score: ", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(640, 295, scoreBoard, GLUT_BITMAP_TIMES_ROMAN_24);				//fix the co-ordinates of score display after game-over
		iShowBMPAlternativeSkipBlack(685, 295, "pics\\appleScore.bmp");
	}
	
}
*/

int exit()
{
	if (s == 15){
		exit(0);
	}
}	
//codes for menu system (end)


//codes for displaying the character and character fall (start)
void freddyMovement(){

	if (s == 1){
		iShowBMP2(iniPos_x, iniPos_y, movingFreddy[freddyIndex], 0);
		
		if (iniPos_y > 54)
			iniPos_y -= dy;
	}
}

void freddyChange(){
	freddyIndex++;

	if (freddyIndex >= 4){
		freddyIndex = 0;
	}
}
//codes for displaying the character and character fall(end)

//-----------------------------------------------------------graphics rendering (start)-----------------------------------------------------//

//apple display in bunch of 3 (start)
struct appleDis{			//appleDis = apple display
	int x;
	int y;
	bool show = true;
};
appleDis pos3[16];

void posApple(){
	int mx = 1280;
	int my = 470;

	for (int i = 0; i < 3; i++){
		pos3[i].x = mx;
		pos3[i].y = my;
		mx += appleCall;
	}

}

void changeApple(){
	for (int i = 0; i < 3; i++){
		pos3[i].x -= appleCall;

		if (pos3[i].x < 0){
			pos3[i].x = win_b - appleCall;
		}
	}
}

void appleDisplay(){

	for (int i = 0; i < 3; i++){
		if (s == 1 && pos3[i].show == true){
			iShowBMPAlternativeSkipBlack(pos3[i].x, pos3[i].y, apple[i]);
		}

	}
}
//apple display in bunch of 3 (end)

//apple display in bunch of 5 (start)
struct appleDis2{
	int x;
	int y;
	bool show = true;
};
appleDis2 pos4[16];

void posApple2(){
	int mx = 1700;
	int my = 320;

	for (int i = 0; i < 5; i++){
		pos4[i].x = mx;
		pos4[i].y = my;
		mx += appleCall;
	}

}

void changeApple2(){
	for (int i = 0; i < 5; i++){
		pos4[i].x -= appleCall;

		if (pos4[i].x < 0){
			pos4[i].x = win_b - appleCall;
		}
	}
}

void appleDisplay2(){
	if (s == 1){
		for (int i = 0; i < 5; i++){
			if (s == 1 && pos4[i].show == true){
			iShowBMPAlternativeSkipBlack(pos4[i].x, pos4[i].y, apple[i]);
			}
		}
	}
}
//apple display in bunch of 5 (end)

//codes for moving the background image (start)
struct imagePosition{
	int x;
	int y;
};
imagePosition pos[32];

void imgPos(){
	int mx = 0;
	for (int i = 0; i < 32; i++){
		
		pos[i].x = mx;
		pos[i].y = my;
		mx += width;
	}
}

void change(){
	
	for (int i = 0; i < 32; i++){
		pos[i].x -= width;

		if (pos[i].x < 0){
			pos[i].x = win_b - width;
		}
		
		if (pos[0].x == 1200){
				for (int i = 0; i < 3; i++){
					pos3[i].show = true;
				}
			}
		if (pos[0].x == 1200){
			for (int i = 0; i < 5; i++){
				pos4[i].show = true;
			}
		}
	}
}

void bgMove(){
	if (s == 1){
		for (int i = 0; i < 32; i++){
			iShowBMP(pos[i].x, pos[i].y, arr[i]);
		}
	}
}
//codes for moving the background images (end)


//codes of obstacles and objects start here ->
//good scientist (start)
struct goodSc{
	int x;
	int y;
};
goodSc pos1[16];

void posGoodSc(){
	int mx = 500;
	for (int i = 0; i < 6; i++){
		pos1[i].x = mx;
		pos1[i].y = 42;
		mx += goodScCall;
	}
}

void changeGoodSc(){
	for (int i = 0; i < 6; i++){
		pos1[i].x -= 10;

		if (pos1[i].x < 0){
			pos1[i].x = win_b - 10;
		}
	}
}

void goodScientist(){
	if (s == 1){
		for (int i = 0; i < 1; i++){
			iShowBMP2(pos1[i].x, pos1[i].y, good[i], 0);
		}
	}
	
}
//good scientist (end)
	
//evil scientist (start)
struct evilSc{
	int x;
	int y;
};
evilSc pos2[16];

void posEvilSc(){
	int mx = 2500;
	for (int i = 0; i < 2; i++){
		pos2[i].x = mx;
		pos2[i].y = 45;
		mx += width1;
	}
}

void changeEvilSc(){
	for (int i = 0; i < 2; i++){
		pos2[i].x -= 10;

		if (pos2[i].x < 0){
			pos2[i].x = win_b - 100;
		}
	}
}

void evilScientist(){
	if (s == 1){
		for (int i = 0; i < 2; i++){
		iShowBMPAlternativeSkipBlack(pos2[i].x, pos2[i].y, evil[i]);
		}
	}
}
//evil scientist (end)

//pin1 display (start)
struct pin1{
	int x;
	int y;
};
pin1 pos5[16];

void posPin1(){
	int mx = 2000;
	int my = 400;

	for (int i = 0; i < 12; i++){
		pos5[i].x = mx;
		pos5[i].y = my;
		mx += pin1Call;
	}

}

void changePin1(){
	for (int i = 0; i < 12; i++){
		pos5[i].x -= pin1Call;

		if (pos5[i].x < 0){
			pos5[i].x = win_b - 20;
		}
	}
}

void pinDisplay1(){
	if (s == 1){
		for (int i = 0; i < 12; i++){
			iShowBMPAlternativeSkipBlack(pos5[i].x, pos5[i].y, pin[i]);
		}
	}
}
//pin1 display (end)

//collision (start)
//void saveScore();
void collision(){
	//for apple in bunch of 3
	for (int i = 0; i < 3; i++){

		if (iniPos_x >= pos3[i].x && iniPos_x <= (pos3[i].x + 28) && iniPos_y >= pos3[i].y && iniPos_y <= (pos3[i].y + 28)){
			pos3[i].show = false;
			pos3[i].x = 2500;
			pos3[i].y = 600;
			point++;

		}
		if ((iniPos_x + 80) >= pos3[i].x && (iniPos_x + 80) <= (pos3[i].x + 28) && (iniPos_y + 80) >= pos3[i].y && (iniPos_y + 80) <= (pos3[i].y + 28)){
			pos3[i].show = false;
			pos3[i].x = 2500;
			pos3[i].y = 600;
			point++;
		}
	}
	
	//for apple in bunch of 5
	for (int i = 0; i < 5; i++){

		if (iniPos_x >= pos4[i].x && iniPos_x <= (pos4[i].x + 28) && iniPos_y >= pos4[i].y && iniPos_y <= (pos4[i].y + 28)){
			pos4[i].show = false;
			point++;
		}
		if ((iniPos_x + 80) >= pos4[i].x && (iniPos_x + 80) <= (pos4[i].x + 28) && (iniPos_y + 80) >= pos4[i].y && (iniPos_y + 80) <= (pos4[i].y + 28)){
			pos4[i].show = false;
			point++;
		}
	}

	//for pin
	for (int i = 0; i < 3; i++){

		if (iniPos_x >= pos5[i].x && iniPos_x <= (pos5[i].x + 384) && iniPos_y >= pos5[i].y && iniPos_y <= (pos5[i].y + 32)){
			s = 16;
			//saveScore();

		}
		if ((iniPos_x + 80) >= pos5[i].x && (iniPos_x + 80) <= (pos5[i].x + 384) && (iniPos_y + 80) >= pos5[i].y && (iniPos_y + 80) <= (pos5[i].y + 32)){
			s = 16;
			//saveScore();

		}
	}

	//for evilSc
	for (int i = 0; i < 1; i++){

		if (iniPos_x >= pos2[i].x && iniPos_x <= (pos2[i].x + 80) && iniPos_y >= pos2[i].y && iniPos_y <= (pos2[i].y + 180)){
			s = 16;
		}
		if ((iniPos_x + 80) >= pos2[i].x && (iniPos_x + 80) <= (pos2[i].x + 80) && (iniPos_y + 80) >= pos2[i].y && (iniPos_y + 80) <= (pos2[i].y + 180)){
			s = 16;
		}
	}
}
//collision (end)

//music (start)
void music(){
	if (s == 1 && musicOn == false){
		iShowBMPAlternativeSkipBlack(1150, 600, "pics\\sound.bmp");
	}
}
//music (end)

//-----------------------------------------------------------graphics rendering (end)-----------------------------------------------------

//-----------------------------------------------------------score and score sort (start)-----------------------------------------------------


//old score
/*
//score (start)
int numberArray[100];
int arrayIndex = 0;
int numberIndex = 0;

void scoreMechanism(){
	if (s == 1){
	for (int i=0; i < 3; i++){				//point of apples in bunch of 3
		if (pos3[i].show == false){
			point += 1;
		}
	}
	for (int i = 0; i < 5; i++){			//point of apples in bunch of 5
		if (pos4[i].show == false){
			point += 1;
		}
	}
	}
}

void scoreBoardDisplay(){
	itoa(point, score, 10);
	if (s == 2){
		iShowBMP(0, 0, "pics\\menu\\scoreBoard.bmp");
	}
	if (s == 1){
	iSetColor(0, 0, 0);
	iText(135, 635, score, GLUT_BITMAP_TIMES_ROMAN_24);
	}
}

void appendHighScore(int n){
	FILE *fp = fopen("score.txt", "a");	
	if (s == 1){
	if (fp != NULL){
		fprintf(fp, "%d\n", n);
	}
	fclose(fp);
	}
}

void readHighScore(){
	FILE *fp = fopen("score.txt", "r");
	char str[100];

	if (fp != NULL){
		while (fgets(str, 15, fp) != NULL){
			numberArray[arrayIndex++] = atoi(str);
		}
	}
	fclose(fp);
}

void sortingHighScore(){
	int temp;
	if (s == 2){
	for (int i = 0; i < arrayIndex - 1; i++){
		for (int j = 0; j < arrayIndex - 1; j++){
			if (numberArray[j] < numberArray[j + 1]){
				temp = numberArray[j];
				numberArray[j] = numberArray[j + 1];
				numberArray[j + 1] = temp;
			}
		}
	}
	}
}
//score (end)
*/

//new score (start)
void scoreMechanism(){
	if (s == 1){
		for (int i = 0; i < 3; i++){				//point of apples in bunch of 3
			if (pos3[i].show == false){
				//point += 1;
				//break;
			}
		}
		for (int i = 0; i < 5; i++){				//point of apples in bunch of 5
			if (pos4[i].show == false){
				//point += 1;
				//break;
			}
		}
	}
}

struct Score{
	char pName[100];
	char name[1000][100];
	//char scoreDis[100];
	int score[1000];
	char score2[1000][100];
	int count, scoreIndex;

	Score(){
		;
	}
	
	//code for player name promt (start)
	void playerName()
	{
		if (s == 100)
		{
			iShowBMP(0, 0, "pics\\menu\\playerName.bmp");
			iSetColor(255, 255, 255);
			iText(835, 420, pName, GLUT_BITMAP_TIMES_ROMAN_24);
		}
	}
	//code for player name promt (end)

	void saveName(char *name){
		FILE *playerName = fopen("playerName.txt", "a");
		name = pName;
		strcpy(this->name[count], name);
		fprintf(playerName, "%s\n", this->name[count]);
		count++;
		fclose(playerName);
	}

	void sortScore(){
		int totalElement = 0;
		int n;

		FILE *scoreBoard = fopen("scoreBoard.txt", "r");
		while (fscanf(scoreBoard, "%d", &scoreBoard[totalElement]) != EOF){
			totalElement++;
		}
		fclose(scoreBoard);

		FILE *playerName = fopen("playerName.txt", "r");
		for (int i = 0; i < totalElement; i++){
			fscanf(playerName, "%s", &name[i]);
		}
		fclose(playerName);

		char temp[1000];
		int swap;
		for (int c = 0; c < totalElement - 1; c++)
		{
			for (int d = 0; d < totalElement - c - 1; d++)
			{
				if (score[d] < score[d+1])
				{
					swap = score[d];
					score[d] = score[d + 1];
					score[d + 1] = swap;
					strcpy(temp, name[d]);
					strcpy(name[d], name[d + 1]);
					strcpy(name[d + 1], temp);
				}
			}
		}
		for (int i = 0; i<totalElement; i++)
		{
			sprintf(score2[i], "%d", score[i]);
		}

	}
};
Score score;

void highScoreDisplay(){
	if (s == 2){

		score.sortScore();												//sorting the scores saved in the file
		iText(552, 450, score.name[0], GLUT_BITMAP_TIMES_ROMAN_24);    //For Showing names
		iText(552, 370, score.name[1], GLUT_BITMAP_TIMES_ROMAN_24);
		iText(552, 290, score.name[2], GLUT_BITMAP_TIMES_ROMAN_24);
		iText(552, 210, score.name[3], GLUT_BITMAP_TIMES_ROMAN_24);
		iText(552, 130, score.name[4], GLUT_BITMAP_TIMES_ROMAN_24);

		iText(860, 450, score.score2[0], GLUT_BITMAP_TIMES_ROMAN_24);    //For Showing scores
		iText(860, 370, score.score2[1], GLUT_BITMAP_TIMES_ROMAN_24);
		iText(860, 290, score.score2[2], GLUT_BITMAP_TIMES_ROMAN_24);
		iText(860, 210, score.score2[3], GLUT_BITMAP_TIMES_ROMAN_24);
		iText(860, 130, score.score2[4], GLUT_BITMAP_TIMES_ROMAN_24);
	}
}

//new score (end)

//codes for the score display in the top left corner (start)
void scoreDisplay(){

	if (s == 1){
		iSetColor(0, 0, 0);
		iText(70, 635, "Score: ", GLUT_BITMAP_TIMES_ROMAN_24);
		iShowBMPAlternativeSkipBlack(180, 635, "pics\\appleScore.bmp");
	}
}

void scoreBoardDisplay(){
	itoa(point, sc, 10);
	if (s == 1){
		iSetColor(0, 0, 0);
		iText(135, 635, sc, GLUT_BITMAP_TIMES_ROMAN_24);
	}
}
//codes for the score display in the top right corner (end)


//-----------------------------------------------------------score and score sort(end)-----------------------------------------------------

//code for gameover (start)
void gameOver(){

	if (s == 16){
		iShowBMP(0, 0, "pics\\menu\\gameover.bmp");
		iSetColor(0, 0, 0);
		iText(560, 295, "Score: ", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(640, 295, sc, GLUT_BITMAP_TIMES_ROMAN_24);
		iShowBMPAlternativeSkipBlack(685, 295, "pics\\appleScore.bmp");
	}

}
//code for gameover (end)
/*
void saveScore(){
	if (s == 16){
	FILE *scoreBoard = fopen("scoreBoard.txt", "a");
	fprintf(scoreBoard, "%d\n", sc);
	fclose(scoreBoard);

	}
}
*/

//restart (start)
void restart(){
	s = 1;
	point = 0;

	appleDisplay();
	appleDisplay2();
	bgMove();
	goodScientist();
	evilScientist();
	freddyMovement();
	pinDisplay1();


	iResumeTimer(timerApple);
	iResumeTimer(timerApple2);
	iResumeTimer(timerBG);
	iResumeTimer(timerEvilSc);
	iResumeTimer(timerFreddy);
	iResumeTimer(timerGoodSc);
	iResumeTimer(timerPin1);
}
//restart (end)


//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Idraw Here::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

void iDraw()
{
	iClear();
		
	mainMenu();
	start();
	bgMove();			
	appleDisplay();			
	appleDisplay2();		
	goodScientist();
	evilScientist();
	pinDisplay1();
	
	scoreBoard();
	credits();
	story();
	tutorials();
	settings();
	pauseMenu();
	freddyMovement();
	collision();
	music();
	gameOver();

	score.playerName();
	score.sortScore();
	scoreMechanism();
	scoreBoardDisplay();
	highScoreDisplay();
	scoreDisplay();
	//saveScore();
	
	exit();

}


/*function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/


void iMouseMove(int mx, int my)
{
	
}
//*******************************************************************ipassiveMouse***********************************************************************//


void iPassiveMouseMove(int mx, int my)
{
	printf("x = %d y = %d \n", mx, my);
}

void iMouse(int button, int state, int mx, int my)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//start
		if ((mx >= 186) && (mx <= 459) && (my >= 436) && (my <= 497) && (s == 0))
		{
			s = 100;
		}
		if ((mx >= 1193) && (mx <= 1224) && (my >= 622) && (my <= 646) && (s == 1))
		{
			s = 0;
		}

		//scoreboard
		if ((mx >= 186) && (mx <= 459) && (my >= 346) && (my <= 409) && (s == 0))
		{
			s = 2;
		}
		if ((mx >= 17) && (mx <= 67) && (my >= 17) && (my <= 60) && (s == 2))
		{
			s = 0;
		}

		//credits
		if ((mx >= 186) && (mx <= 459) && (my >= 259) && (my <= 320) && (s == 0))
		{
			s = 3;
		}
		if ((mx >= 17) && (mx <= 67) && (my >= 17) && (my <= 60) && (s == 3))
		{
			s = 0;
		}
		//story
		if ((mx >= 186) && (mx <= 459) && (my >= 171) && (my <= 233) && (s == 0))
		{
			s = 4;
		}
		if ((mx >= 17) && (mx <= 67) && (my >= 17) && (my <= 60) && (s == 4))
		{
			s = 0;
		}
		//tutorials
		if ((mx >= 186) && (mx <= 459) && (my >= 85) && (my <= 145) && (s == 0))
		{
			s = 5;
		}
		if ((mx >= 17) && (mx <= 67) && (my >= 17) && (my <= 60) && (s == 5))
		{
			s = 0;
		}
		//settings
		if ((mx >= 1200) && (mx <= 1259) && (my >= 108) && (my <= 166) && (s == 0))
		{
			s = 6;
		}
		if ((mx >= 698) && (mx <= 728) && (my >= 437) && (my <= 461) && (s == 6))
		{
			s = 7;
		}
		else if ((mx >= 698) && (mx <= 728) && (my >= 437) && (my <= 461) && (s == 7))
		{
			s = 6;
		}
		if ((mx >= 704) && (mx <= 728) && (my >= 345) && (my <= 373) && (s == 6))
		{
			s = 8;
		}
		else if ((mx >= 704) && (mx <= 728) && (my >= 345) && (my <= 373) && (s == 8))
		{
			s = 6;
		}
		if ((mx >= 704) && (mx <= 728) && (my >= 345) && (my <= 373) && (s == 7))
		{
			s = 9;
		}
		else if ((mx >= 704) && (mx <= 728) && (my >= 345) && (my <= 373) && (s == 9))
		{
			s = 7;
		}
		if ((mx >= 698) && (mx <= 728) && (my >= 437) && (my <= 461) && (s == 9))
		{
			s = 8;
		}
		if ((mx >= 608) && (mx <= 664) && (my >= 208) && (my <= 264) && (s == 6))
		{
			s = 0;
		}
		if ((mx >= 608) && (mx <= 664) && (my >= 208) && (my <= 264) && (s == 7))
		{
			s = 0;
		}
		if ((mx >= 608) && (mx <= 664) && (my >= 208) && (my <= 264) && (s == 8))
		{
			s = 0;
		}
		if ((mx >= 608) && (mx <= 664) && (my >= 208) && (my <= 264) && (s == 9))
		{
			s = 0;
		}
		//exit
		if ((mx >= 1200) && (mx <= 1259) && (my >= 27) && (my <= 81) && (s == 0))
		{
			s = 15;
		}
		//pause
		if ((mx >= 527) && (mx <= 751) && (my >= 422) && (my <= 482) && (s == 10))
		{
			iResumeTimer(timerFreddy);
			iResumeTimer(timerBG);
			iResumeTimer(timerEvilSc);
			iResumeTimer(timerGoodSc);
			iResumeTimer(timerApple);
			iResumeTimer(timerApple2);

			s = 1;
		}
		if ((mx >= 527) && (mx <= 751) && (my >= 322) && (my <= 382) && (s == 10))
		{
			s = 6;
		}
		if ((mx >= 527) && (mx <= 751) && (my >= 222) && (my <= 282) && (s == 10))
		{
			s = 0;
		}
		//gameover
		if ((mx >= 502) && (mx <= 766) && (my >= 177) && (my <= 256) && (s == 16))
		{
			restart();
			/*
			for (int i = 0; i < 32; i++){        //bg move
				iShowBMP(pos[i].x, pos[i].y, arr[i]);
			}

			for (int i = 0; i < 1; i++){        //goodSc
				iShowBMP2(pos1[i].x, pos1[i].y, good[i], 0);
			}

			for (int i = 0; i < 2; i++){        //evilSc
				iShowBMPAlternativeSkipBlack(pos2[i].x, pos2[i].y, evil[i]);
			}

			for (int i = 0; i < 3; i++){        //apple 3
				iShowBMPAlternativeSkipBlack(pos3[i].x, pos3[i].y, apple[i]);
			}

			for (int i = 0; i < 5; i++){            //apple 5
				iShowBMPAlternativeSkipBlack(pos4[i].x, pos4[i].y, apple[i]);
			}
			for (int i = 0; i < 12; i++){				//pin display
				iShowBMPAlternativeSkipBlack(pos5[i].x, pos5[i].y, pin[i]);
			}
			s = 1;
			*/
		}
		if ((mx >= 502) && (mx <= 766) && (my >= 77) && (my <= 156) && (s == 16))
		{
			s = 0;
		}

	}
}

	/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/

	void iKeyboard(unsigned char key)
	{
		if (s == 1){
			if (key == 'f' && iniPos_y < 550){
				iniPos_y += 50;
			}

			if (key == 'p'){

				iPauseTimer(timerFreddy);
				iPauseTimer(timerBG);
				iPauseTimer(timerEvilSc);
				iPauseTimer(timerGoodSc);
				iPauseTimer(timerApple);
				iPauseTimer(timerApple2);

				s = 10;
			}
			if (key == 'm'){

				if (musicOn == true)
				{

					musicOn = false;
					PlaySound(0, 0, 0);

				}
				else if (musicOn == false)
				{
					musicOn = true;
					PlaySound("music\\videoplayback.wav", NULL, SND_LOOP | SND_ASYNC);

				}

			}
		}

		if (s == 10 && key == 'r'){

			iResumeTimer(timerFreddy);
			iResumeTimer(timerBG);
			iResumeTimer(timerEvilSc);
			iResumeTimer(timerGoodSc);
			iResumeTimer(timerApple);
			iResumeTimer(timerApple2);

			s = 1;
		}

		if (s == 100 && key == 13){
			s = 1;
		}

		if (s == 100){

			if (key != '\b'){

				pName[index] = key;
				pName[index + 1] = '\0';
				index++;
			}
			else
			{
				if (index >= 0)
				{
					pName[index - 1] = '\0';
					index--;
				}
				else
					index = 0;
			}
			strcpy(pName, str1);
			score.saveName(pName);


		}

	}
/*
function iSpecialKeyboard() is called whenver user hits special keys like-
function keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/


void iSpecialKeyboard(unsigned char key)
{
	if (key == GLUT_KEY_DOWN)
	{
		exit(0);
	}
}


int main()
{
	freddyMovement();
	timerFreddy = iSetTimer(50, freddyChange);

	imgPos();										//calling all background images
	timerBG = iSetTimer(150, change);

	posEvilSc();									//calling evil scientist
	timerEvilSc = iSetTimer(200, changeEvilSc);

	posApple();										//calling the apples (in bunch of 3)
	timerApple = iSetTimer(200, changeApple);

	posApple2();									//calling the apples (in bunch of 5)
	timerApple2 = iSetTimer(200, changeApple2);

	posGoodSc();									//calling good scientists
	timerGoodSc = iSetTimer(200, changeGoodSc);

	posPin1();										//calling pin
	timerPin1 = iSetTimer(300, changePin1);


	//music ->
	if (musicOn){
		PlaySound("music\\videoplayback.wav", NULL, SND_LOOP | SND_ASYNC);
	}


	iInitialize(1280, 718, "HIPITIHOP");

	iStart();

	return 0;
}