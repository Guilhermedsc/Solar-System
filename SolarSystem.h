#include <SDL/SDL.h>
#include "SDL/SDL_opengl.h"
#include "SDL/SDL_image.h"
#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <SOIL/SOIL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <math.h>

typedef struct{
	float Translacao;
	float Rotacao;
	int Faces;
	int TamanhoTranslacao;
	GLuint Texture;
	bool Estado;
}Corpo;

typedef struct{
	int X;
	int Y;
	int Z;
}EixoINT;

typedef struct{
	float X;
	float Y;
	float Z;
}EixoFLOAT;

typedef struct{
	float Largura;
	float Altura;
}Janela;

Corpo space;
Corpo sun;
Corpo mercury;
Corpo venus;
Corpo earth;
Corpo mars;
Corpo jupiter;
Corpo uranus;
Corpo neptune;
Corpo saturn;

//Variaveis de Luz
float difusa;
float especular;
float posicional;
float global;
float matrizAD[] = {1.0, 1.0, 1.0, 1.0};
float matrizEspecular[] = {1.0, 1.0, 1,0, 1.0};
float matrizBrilho[] = {50};
EixoFLOAT luzBranca;

//Variaveis de Controle
int horizonteEventos = 1;
EixoINT cursor;
EixoINT mouse;
Janela janela;
bool podeBrilhar = true;
bool podeOrbitar = false;

//Variaveis da Camera
int modoCamera = 1;
float anguloCameraA = 90;
float anguloCameraB = 0;
EixoFLOAT camera;