/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "myBoard.h"
#include "myCube.h"
#include "constants.h"
#include "allmodels.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include <iomanip> 
#include <iostream> 
#include <queue>
#include <list>
#include "PacMan.h"
#include "Duszki.h"
#include <GLUT.h>

using namespace std;
using namespace glm;

bool przegrales = false;
float aspectRatio = 1, uplynelo1 = 0, uplynelo2 = 0;
float uplynelo_od_ruchu_duchow = 0;
float speed_x = 0;//[radiany/s]
float speed_y = 0;//[radiany/s]
int punkty = 0, strona = 0;


struct Duch {
	int kolor = 0;
	int x;
	int y;
	int kierunek = rand() % 4; 

	Duch(int x, int y, int kolor) {
		this->x = x;
		this->y = y;
		this->kolor = kolor;
	}
};

std::vector <Duch*> duszki;


bool czy_jest_duch_na_pozycji(int x, int y) {
	for (auto* duch : duszki) {
		if (duch->x == x && duch->y == y)
			return true;
	}
	return false;
}



int Planszak[12][24] =
{ {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,2,2,2,1,2,1,1,2,2,1,1,1,1,2,2,1,1,2,1,2,2,2,1},
{1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1},
{1,2,1,2,1,2,2,1,1,1,1,1,1,1,1,1,1,2,2,1,2,1,2,1},
{1,2,1,2,1,2,1,1,2,2,2,2,2,2,2,2,1,1,2,1,2,1,2,1},
{1,2,1,2,2,2,1,2,2,2,2,2,2,2,2,2,2,1,2,2,2,1,2,1},
{1,2,2,2,2,2,2,2,1,1,2,1,1,2,1,1,2,2,2,2,2,2,2,1},
{1,2,2,1,1,2,1,2,2,1,2,1,1,2,1,2,2,1,2,2,1,1,2,1},
{1,2,2,1,1,2,1,2,2,1,2,1,1,2,1,2,2,1,2,2,1,1,2,1},
{1,2,2,2,2,2,1,2,1,1,2,2,2,2,1,1,2,1,2,2,2,2,2,1},
{1,1,2,2,2,2,2,2,2,2,2,1,1,3,2,2,2,2,2,2,2,2,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };

int pozycja[2];
int pozdusz[3][2];
int ruch=0;
GLuint tex, scianat, planszat,pieniazekt,pacmant,duszek1, duszek2, duszek3;
float light[] = { 0, 0, -10, 1 };


void rusz_duchem(Duch* duch) {
	
	int sasiadujace_pola[] = {
		Planszak[duch->y][duch->x - 1],
		Planszak[duch->y + 1][duch->x],
		Planszak[duch->y][duch->x + 1],
		Planszak[duch->y - 1][duch->x]
	};

	// 0 - lewo, 1- gora, 2-prawo, 3 -dol
	
	while(sasiadujace_pola[duch->kierunek] == 1)
		duch->kierunek = rand() % 4;

	if (rand() % 10 < 4) {
		int inny_kierunek_1 = (duch->kierunek + 1) % 4;
		int inny_kierunek_2 = (duch->kierunek + 3) % 4;

		int inny_kierunek_1_pole = sasiadujace_pola[inny_kierunek_1];
		int inny_kierunek_2_pole = sasiadujace_pola[inny_kierunek_2];

		if (inny_kierunek_1_pole != 1 && inny_kierunek_2_pole != 1) {
			if (rand() % 2)
				duch->kierunek = inny_kierunek_1;
			else
				duch->kierunek = inny_kierunek_2;
		}else if(inny_kierunek_1_pole != 1)
			duch->kierunek = inny_kierunek_1;
		else if(inny_kierunek_2_pole != 1)
			duch->kierunek = inny_kierunek_2;
	}



	if (duch->kierunek == 0)
		duch->x--;
	else if (duch->kierunek == 1)
		duch->y++;
	else if (duch->kierunek == 2)
		duch->x++;
	else
		duch->y--;

	if (Planszak[duch->y][duch->x] == 3) {
		przegrales = true;
	}
}

//Do wczytania obrazka
GLuint readTexture(const char* filename) {
	GLuint tex;
	glActiveTexture(GL_TEXTURE0);

	//Wczytanie do pamięci komputera
	std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
	unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
	//Wczytaj obrazek
	unsigned error = lodepng::decode(image, width, height, filename);

	//Import do pamięci karty graficznej
	glGenTextures(1, &tex); //Zainicjuj jeden uchwyt
	glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
	//Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return tex;
}

//Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mod) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_LEFT) {
			speed_y = -PI;
		}
		if (key == GLFW_KEY_RIGHT) {
			speed_y = PI;
		}
		if (key == GLFW_KEY_UP) {
			speed_x = PI;
		}
		if (key == GLFW_KEY_DOWN) {
			speed_x = -PI;
		}
		if (key == GLFW_KEY_A) {
			ruch = 2;
		}
		if (key == GLFW_KEY_D) {
			ruch = 3;
		}
		if (key == GLFW_KEY_W) {
			ruch = 1;
		}
		if (key == GLFW_KEY_S) {
			ruch = 4;
		}
	}
	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT) {
			speed_y = 0;
		}
		if (key == GLFW_KEY_UP || key == GLFW_KEY_DOWN) {
			speed_x = 0;
		}
		if (key == GLFW_KEY_A) {
			ruch = 0;
		}
		if (key == GLFW_KEY_D) {
			ruch = 0;
		}
		if (key == GLFW_KEY_W) {
			ruch = 0;
		}
		if (key == GLFW_KEY_S) {
			ruch = 0;
		}
	}
}

void windowResizeCallback(GLFWwindow* window, int width, int height) {
	if (height == 0) return;
	aspectRatio = (float)width / (float)height;
	glViewport(0, 0, width, height);
}

//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
    initShaders();
	//************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
	glClearColor(0, 0, 0, 1); //Ustaw kolor czyszczenia bufora kolorów
	glEnable(GL_DEPTH_TEST); //Włącz test głębokości na pikselach
	glfwSetKeyCallback(window, key_callback);
	
}

//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
    freeShaders();
    //************Tutaj umieszczaj kod, który należy wykonać po zakończeniu pętli głównej************
	glDeleteTextures(1, &tex);
}

void pacman2(mat4 P, glm::mat4 V, glm::mat4 M, float x, float y) {
	spTextured->use(); //Aktyeuj program cieniujący



	M = glm::translate(M, glm::vec3(x, y, -0.15f));
	M = glm::scale(M, glm::vec3(0.1f, 0.1f, 0.05f));
	M = glm::rotate(M, radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	M = rotate(M, radians(90.0f * strona), vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(spTextured->u("P"), 1, false, glm::value_ptr(P)); //Załaduj do programu cieniującego macierz rzutowania
	glUniformMatrix4fv(spTextured->u("V"), 1, false, glm::value_ptr(V)); //Załaduj do programu cieniującego macierz widoku
	glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M)); //Załaduj do programu cieniującego macierz modelu
	//glUniform4fv(spTextured->u("lp"), 1, light);
	glEnableVertexAttribArray(spTextured->a("vertex"));
	glVertexAttribPointer(spTextured->a("vertex"), 4, GL_FLOAT, false, 0, PacManverts);

	glEnableVertexAttribArray(spTextured->a("texCoords"));
	glVertexAttribPointer(spTextured->a("texCoords"), 2, GL_FLOAT, false, 0, PacMantexCoords);

	//glEnableVertexAttribArray(spTextured->a("normal"));
	//glVertexAttribPointer(spTextured->a("normal"), 4, GL_FLOAT, false, 0, PacMannormals);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, pacmant);
	glUniform1i(spTextured->u("tex"), 0);

	glDrawArrays(GL_TRIANGLES, 0, PacManvertexCount);

	glDisableVertexAttribArray(spTextured->a("vertex"));
	glDisableVertexAttribArray(spTextured->a("texCoords"));
	//glDisableVertexAttribArray(spTextured->a("normal"));
}

void duszki2(mat4 P, glm::mat4 V, glm::mat4 M, float x, float y, int kolor) {
	spTextured->use(); //Aktyeuj program cieniujący



	M = glm::translate(M, glm::vec3(x, y, -0.15f));
	M = glm::scale(M, glm::vec3(0.05f, 0.05f, 0.05f));
	M = glm::rotate(M, radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::rotate(M, radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(spTextured->u("P"), 1, false, glm::value_ptr(P)); //Załaduj do programu cieniującego macierz rzutowania
	glUniformMatrix4fv(spTextured->u("V"), 1, false, glm::value_ptr(V)); //Załaduj do programu cieniującego macierz widoku
	glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M)); //Załaduj do programu cieniującego macierz modelu
	//glUniform4fv(spTextured->u("lp"), 1, light);
	glEnableVertexAttribArray(spTextured->a("vertex"));
	glVertexAttribPointer(spTextured->a("vertex"), 4, GL_FLOAT, false, 0, Duszkiv);

	glEnableVertexAttribArray(spTextured ->a("texCoords"));
	glVertexAttribPointer(spTextured->a("texCoords"), 2, GL_FLOAT, false, 0, Duszkitc);

	//glEnableVertexAttribArray(spTextured->a("normal"));
	//glVertexAttribPointer(spTextured->a("normal"), 4, GL_FLOAT, false, 0, Duszkin);

	glActiveTexture(GL_TEXTURE0);
	switch (kolor)
	{
	case 10:
		glBindTexture(GL_TEXTURE_2D, duszek1);
		break;
	case 11:
		glBindTexture(GL_TEXTURE_2D, duszek2);
		break;
	case 12:
		glBindTexture(GL_TEXTURE_2D, duszek3);
		break;
	default:
		break;
	}
	glUniform1i(spTextured->u("tex"), 0);

	glDrawArrays(GL_TRIANGLES, 0, DuszkivertexCount);

	glDisableVertexAttribArray(spTextured->a("vertex"));
	glDisableVertexAttribArray(spTextured->a("texCoords"));
	glDisableVertexAttribArray(spTextured->a("normal"));
}

//Rysowanie planszy
void plansza(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
	spTextured->use(); //Aktyeuj program cieniujący


	M = scale(M, vec3(1.15f, 1.15f, 1.0f));
	glUniformMatrix4fv(spTextured->u("P"), 1, false, glm::value_ptr(P)); //Załaduj do programu cieniującego macierz rzutowania
	glUniformMatrix4fv(spTextured->u("V"), 1, false, glm::value_ptr(V)); //Załaduj do programu cieniującego macierz widoku
	glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M)); //Załaduj do programu cieniującego macierz modelu
	glUniform4fv(spTextured->u("lp"), 1, light);


	glEnableVertexAttribArray(spTextured->a("vertex"));
	glVertexAttribPointer(spTextured->a("vertex"), 4, GL_FLOAT, false, 0, myBoardVertices); //Współrzędne wierzchołków bierz z tablicy myCubeVertices

	glEnableVertexAttribArray(spTextured->a("texCoord"));
	glVertexAttribPointer(spTextured->a("texCoord"), 2, GL_FLOAT, false, 0, myBoardtex); //Współrzędne teksturowania bierz z tablicy myCubeTexCoords

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, planszat);
	glUniform1i(spTextured->u("tex"), 0);

	glDrawArrays(GL_TRIANGLES, 0, myBoardVertexCount);


	glDisableVertexAttribArray(spTextured->a("vertex"));
	glDisableVertexAttribArray(spTextured->a("texCoord"));
}

//Rysowanie kulki
void sciana(glm::mat4 P, glm::mat4 V, glm::mat4 M, float x, float y) {
	spLambertTextured->use(); //Aktyeuj program cieniujący
	// wybór koloru/textury

	M = glm::translate(M, glm::vec3(x, y,-0.05f));
	M = glm::scale(M, glm::vec3(0.1f, 0.2f, 0.1f)); 

	//glUniform4f(spTextured->u("color"), 0, 0, 1, 1); //Ustaw kolor rysowania obiektu
	glUniformMatrix4fv(spLambertTextured->u("P"), 1, false, glm::value_ptr(P)); //Załaduj do programu cieniującego macierz rzutowania
	glUniformMatrix4fv(spLambertTextured->u("M"), 1, false, glm::value_ptr(M));
	glUniformMatrix4fv(spLambertTextured->u("V"), 1, false, glm::value_ptr(V));//Załaduj do programu cieniującego macierz modelu
	glUniform4fv(spLambertTextured->u("lp"), 1, light);

	glEnableVertexAttribArray(spLambertTextured->a("vertex"));
	glVertexAttribPointer(spLambertTextured->a("vertex"), 4, GL_FLOAT, false, 0, Models::CubeInternal::vertices); //Współrzędne wierzchołków bierz z tablicy myCubeVertices

	glEnableVertexAttribArray(spLambertTextured->a("normal"));
	glVertexAttribPointer(spLambertTextured->a("normal"), 4, GL_FLOAT, false, 0, Models::CubeInternal::normals); //Współrzędne wierzchołków bierz z tablicy myCubeVertices

	glEnableVertexAttribArray(spLambertTextured->a("texCoord"));
	glVertexAttribPointer(spLambertTextured->a("texCoord"), 2, GL_FLOAT, false, 0, Models::CubeInternal::texCoords); //Współrzędne teksturowania bierz z tablicy myCubeTexCoords

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, scianat);
	//glUniform1i(spColored->u("tex"), 0);
	glUniform1i(spLambertTextured->u("texCoords"), 0);

	glDrawArrays(GL_TRIANGLES, 0, Models::CubeInternal::vertexCount);

	glDisableVertexAttribArray(spLambertTextured->a("vertex"));
	glDisableVertexAttribArray(spLambertTextured->a("texCoord"));
	glDisableVertexAttribArray(spLambertTextured->a("normal"));
	//Models::cube.drawSolid(); //Narysuj obiekt
}

void pieniazek(glm::mat4 P, glm::mat4 V, glm::mat4 M, float x, float y) {
	spLambertTextured->use(); //Aktyeuj program cieniujący
	// wybór koloru/textury

	M = glm::translate(M, glm::vec3(x, y, -0.15f));
	M = glm::scale(M, glm::vec3(0.05f, 0.05f, 0.05f));

	//glUniform4f(spTextured->u("color"), 0, 0, 1, 1); //Ustaw kolor rysowania obiektu
	glUniformMatrix4fv(spLambertTextured->u("P"), 1, false, glm::value_ptr(P)); //Załaduj do programu cieniującego macierz rzutowania
	glUniformMatrix4fv(spLambertTextured->u("M"), 1, false, glm::value_ptr(M)); //Załaduj do programu cieniującego macierz modelu
	glUniform4fv(spLambertTextured->u("lp"), 1, light);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, pieniazekt);
	glUniform1i(spLambertTextured->u("texCoords"), 0);

	Models::sphere.drawSolid(); //Narysuj obiekt
}


void print(int x, int y, int z, char* string)
{
	//set the position of the text in the window using the x and y coordinates
	glRasterPos3f(x, y, z);
	//get the length of the string to display
	int len = (int)strlen(string);

	//loop to display character by character
	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
};

/*void duszek(glm::mat4 P, glm::mat4 V, glm::mat4 M, float x, float y, int kolor) {

	spTextured->use(); //Aktyeuj program cieniujący
	// wybór koloru/textury

	M = glm::translate(M, glm::vec3(x, y, -0.15f));
	M = glm::scale(M, glm::vec3(0.075f, 0.075f, 0.075f));

	//glUniform4f(spTextured->u("color"), 0, 0, 1, 1); //Ustaw kolor rysowania obiektu
	glUniformMatrix4fv(spTextured->u("P"), 1, false, glm::value_ptr(P)); //Załaduj do programu cieniującego macierz rzutowania
	glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M)); //Załaduj do programu cieniującego macierz modelu
	glUniform4fv(spTextured->u("lp"), 1, light);

	glActiveTexture(GL_TEXTURE0);
	switch (kolor)
	{
		case 10:
			glBindTexture(GL_TEXTURE_2D, duszek1);
			break;
		case 11:
			glBindTexture(GL_TEXTURE_2D, duszek2);
			break;
		case 12:
			glBindTexture(GL_TEXTURE_2D, duszek3);
			break;
	default:
		break;
	}
	
	glUniform1i(spTextured->u("tex"), 0);

	Models::sphere.drawSolid(); //Narysuj obiekt
}*/

/*void pacman(glm::mat4 P, glm::mat4 V, glm::mat4 M, float x, float y) {

	spTextured->use(); //Aktyeuj program cieniujący
	// wybór koloru/textury

	M = glm::translate(M, glm::vec3(x, y, -0.15f));
	M = glm::scale(M, glm::vec3(0.1f, 0.1f, 0.1f));

	//glUniform4f(spTextured->u("color"), 0, 0, 1, 1); //Ustaw kolor rysowania obiektu
	glUniformMatrix4fv(spTextured->u("P"), 1, false, glm::value_ptr(P)); //Załaduj do programu cieniującego macierz rzutowania
	glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M)); //Załaduj do programu cieniującego macierz modelu

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, pacmant);
	glUniform1i(spTextured->u("tex"), 0);

	Models::sphere.drawSolid(); //Narysuj obiekt
}*/

//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window, float angle_x, float angle_y, float angle_z) {
	glfwSetTime(0);
	//************Tutaj umieszczaj kod rysujący obraz******************l
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Wyczyść bufor koloru i bufor głębokości

	glm::mat4 I = glm::mat4(1.0f); //Zainicjuj macierz modelu macierzą jednostkową
	glm::mat4 M = glm::rotate(I, angle_x, glm::vec3(1.0f, 0.0f, 0.0f)); //Pomnóż macierz modelu razy macierz obrotu o kąt angle wokół osi X
	M = glm::rotate(M, angle_y, glm::vec3(0.0f, 0.0f, 1.0f)); //Pomnóż macierz modelu razy macierz obrotu o kąt angle wokół osi Y
	glm::mat4 V = glm::lookAt(glm::vec3(0.0f, 0.0f, -6.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //Wylicz macierz widoku
	glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f); //Wylicz macierz rzutowania

	if (przegrales == false) {
		plansza(P, V, M);
		float x, y;
		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 24; j++) {
				if (Planszak[i][j] == 1)
					//cout << "";
					sciana(P, V, M, (2.2f - j * 0.2f), 2.2f - i * 0.4f);
				else if (Planszak[i][j] == 2) {
					//cout << "";
					pieniazek(P, V, M, (2.2f - j * 0.2f), 2.2f - i * 0.4f);
				}
				else if (Planszak[i][j] == 3) {
					//cout << "";
					pacman2(P, V, M, (2.2f - j * 0.2f), 2.2f - i * 0.4f);
					pozycja[0] = i;
					pozycja[1] = j;
				}
			}

			for (auto* duch : duszki) {
				duszki2(P, V, M, (2.2f - duch->x * 0.2f), 2.2f - duch->y * 0.4f, duch->kolor);
			}

		}
	}
	else
	{
		
	}
	//duszki2(P, V, M, 0, 0);
	glfwSwapBuffers(window); //Skopiuj bufor tylny do bufora przedniego
	uplynelo1 = uplynelo1 + glfwGetTime();
	uplynelo2 = uplynelo2 + glfwGetTime();
	uplynelo_od_ruchu_duchow += glfwGetTime();
	//for (int i = 0; i < 3; i++)
	//	for (int j = 0; i < 2; i++)
	//		cout << pozdusz[i][j];
	//cout << uplynelo << endl;
	//cout << punkty << endl;
}

int main(void)
{
	GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno

	glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

	duszki.push_back(new Duch(10, 2, 10));
	duszki.push_back(new Duch(11, 2, 11));
	duszki.push_back(new Duch(12, 2, 12));

	if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(1000, 1000, "OpenGL", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!window) //Jeżeli okna nie udało się utworzyć, to zamknij program
	{
		fprintf(stderr, "Nie można utworzyć okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekę GLEW
		fprintf(stderr, "Nie można zainicjować GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Operacje inicjujące
	//Główna pętla
	float angle_x = 0; //zadeklaruj zmienną przechowującą aktualny kąt obrotu
	float angle_y = 0;
	float angle_z = 0;//zadeklaruj zmienną przechowującą aktualny kąt obrotu
	glfwSetTime(0); //Wyzeruj licznik czasu
	

	scianat = readTexture("sciana.png");
	planszat = readTexture("bricks.png");
	pieniazekt = readTexture("niebieski.png");
	pacmant = readTexture("zolty.png");
	duszek1 = readTexture("zielony.png");
	duszek2 = readTexture("czerwony.png");
	duszek3 = readTexture("fioletowy.png");
	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
		//cout << glfwGetTime();
		angle_x += speed_x * glfwGetTime(); //Oblicz kąt o jaki obiekt obrócił się podczas poprzedniej klatki
		angle_y += speed_y * glfwGetTime();
		angle_z += PI/2 * glfwGetTime();
		glfwSetTime(0); //Wyzeruj licznik czasu

		switch (ruch)
			{
			case 1:
				if (uplynelo1 > 0.1) {
					uplynelo1 = 0;
					if (Planszak[pozycja[0] - 1][pozycja[1]] != 1)
					{
						strona = 1;
						if (Planszak[pozycja[0] - 1][pozycja[1]] == 2)
						{
							Planszak[pozycja[0]][pozycja[1]] = 0;
							Planszak[pozycja[0] - 1][pozycja[1]] = 3;
							punkty++;
						}
						else if (Planszak[pozycja[0] - 1][pozycja[1]] == 0) {
							Planszak[pozycja[0]][pozycja[1]] = 0;
							Planszak[pozycja[0] - 1][pozycja[1]] = 3;
						}

						if(czy_jest_duch_na_pozycji(pozycja[1], pozycja[0] - 1 ))
							przegrales = true;

					}
				}
				break;
			case 2:
				if (uplynelo2 > 0.05) {
					uplynelo2 = 0;
					strona = 2;
					if (Planszak[pozycja[0]][pozycja[1] - 1] != 1)
					{
						if (Planszak[pozycja[0]][pozycja[1] - 1] == 2)
						{
							Planszak[pozycja[0]][pozycja[1]] = 0;
							Planszak[pozycja[0]][pozycja[1] - 1] = 3;
							punkty++;
						}
						else if (Planszak[pozycja[0]][pozycja[1] - 1] == 0) {
							Planszak[pozycja[0]][pozycja[1]] = 0;
							Planszak[pozycja[0]][pozycja[1] - 1] = 3;
						}
					
						if (czy_jest_duch_na_pozycji(pozycja[1]-1, pozycja[0]))
							przegrales = true;
					}
				}
				break;
			case 3:
				if (uplynelo2 > 0.05) {
					uplynelo2 = 0;
					strona = 4;
					if (Planszak[pozycja[0]][pozycja[1] + 1] != 1)
					{
						if (Planszak[pozycja[0]][pozycja[1] + 1] == 2)
						{
							Planszak[pozycja[0]][pozycja[1]] = 0;
							Planszak[pozycja[0]][pozycja[1] + 1] = 3;
							punkty++;
						}
						else if (Planszak[pozycja[0]][pozycja[1] + 1] == 0) {
							Planszak[pozycja[0]][pozycja[1]] = 0;
							Planszak[pozycja[0]][pozycja[1] + 1] = 3;
						}
						if (czy_jest_duch_na_pozycji(pozycja[1] + 1, pozycja[0]))
							przegrales = true;
					}
				}
				break;
			case 4:
				if (uplynelo1 > 0.1) {
					uplynelo1 = 0;
					strona = 3;
					if (Planszak[pozycja[0] + 1][pozycja[1]] != 1)
					{
						if (Planszak[pozycja[0] + 1][pozycja[1]] == 2)
						{
							Planszak[pozycja[0]][pozycja[1]] = 0;
							Planszak[pozycja[0] + 1][pozycja[1]] = 3;
							punkty++;
						}
						else if (Planszak[pozycja[0] + 1][pozycja[1]] == 0) {
							Planszak[pozycja[0]][pozycja[1]] = 0;
							Planszak[pozycja[0] + 1][pozycja[1]] = 3;
						}

						if (czy_jest_duch_na_pozycji(pozycja[1], pozycja[0] + 1))
							przegrales = true;
					}
				}
				break;
			default:
				break;
			}
		
	    
		if (uplynelo_od_ruchu_duchow >= 0.5) {
			uplynelo_od_ruchu_duchow = 0;
			for (auto* duch : duszki) {
				rusz_duchem(duch);
			}
		}
		

		drawScene(window, angle_x, angle_y, angle_z);
		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
		//cout << glfwGetTime() << "PETLA" << endl;

	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}
