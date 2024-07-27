#include "SolarSystem.h"

// Função para configurar a janela
void confJanela(int w, int h){
    janela.Largura = w;
    janela.Altura = h;

    glEnable(GL_DEPTH_TEST);
    glViewport (0, 0, w, h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w/(float)h, 0.2, 2147483647.0);
    glMatrixMode(GL_MODELVIEW);
}

void exibeCamera(){
	camera.X = 800 * sin(anguloCameraA) * cos(anguloCameraB);
    camera.Y = 800 * sin(anguloCameraA);
    camera.Z = 800 * cos(anguloCameraA) * sin(anguloCameraB);
    switch(modoCamera){
    	case 1:
    		 gluLookAt(cursor.X+camera.X, camera.Y, cursor.Z+camera.Z, cursor.X+0, 0, cursor.Z+0, 0, 1, 0);
    	break;
    	case 2:
    		gluLookAt(0, 0, 1080, 0, 0, 0, 0, 1, 0);
    	break;
    }
}

GLuint carregaTextura(const char* arquivo) {
  GLuint idTextura = SOIL_load_OGL_texture(
                     arquivo,
                     SOIL_LOAD_AUTO,
                     SOIL_CREATE_NEW_ID,
                     SOIL_FLAG_INVERT_Y
                    );

  if (idTextura == 0) {
    printf("Erro do SOIL: '%s' - '%s'\n", arquivo, SOIL_last_result());
  }

  return idTextura;
}

void criaSphere(float radius, int stacks, int columns){
    GLUquadric* quadObj = gluNewQuadric();
    gluQuadricDrawStyle(quadObj, GLU_FILL);
    gluQuadricNormals(quadObj, GLU_SMOOTH);
    gluQuadricTexture(quadObj, GL_TRUE);
    gluSphere(quadObj, radius, stacks, columns);
    gluDeleteQuadric(quadObj);
}

void renderizaSol(){
	glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, sun.Texture);
    	glPushMatrix();
	        glRotatef(sun.Translacao, 0, 1, 0);
	        glRotatef(90, 1, 0, 0);
	        criaSphere(100 , sun.Faces, sun.Faces);
   		 glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Luz(){
	if(podeBrilhar){
		float luzAmbiente[] = {0.0, 0.0, 0.0, 1.0};
	    float luzDifusa0[] = {difusa, difusa, difusa, 1.0};
	    float luzEpecular0[] = {especular, especular, especular, 1.0};
	    float luzPosicional0[] = {0.0, 0.0, 3.0, posicional};
	    float luzDE[] = {0.0, 1.0, 0.0, 1.0};
	    float luzPosicional1[] = {1.0, 2.0, 0.0, 1.0};
	    float luzGlobal[] = {global, global, global, 1.0};

	    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa0);
	    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEpecular0);

	    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobal);
	    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, false);
	    glEnable(GL_LIGHT0);
	    glDisable(GL_LIGHTING);
	    glPushMatrix();
	        glRotatef(luzBranca.X, 1.0, 0.0, 0.0);
	        glRotatef(luzBranca.Y, 0.0, 1.0, 0.0);
	        glLightfv(GL_LIGHT0, GL_POSITION, luzPosicional0);
	        glTranslatef(luzPosicional0[0], luzPosicional0[1], luzPosicional0[2]);
	        glColor3f(difusa, difusa, difusa);
	        renderizaSol();
	    glPopMatrix();
	}else{
		glDisable(GL_LIGHT0);
	}

	glEnable(GL_LIGHTING);
}

void renderizaCorpos(){
	glEnable(GL_TEXTURE_2D);
		//Espaço
		glBindTexture(GL_TEXTURE_2D, space.Texture);
	    glPushMatrix();
	        glTranslatef(cursor.X, cursor.Y, cursor.Z); 
	        criaSphere(7000, sun.Faces, sun.Faces);
	    glPopMatrix();
		//Mercurio
		glBindTexture(GL_TEXTURE_2D, mercury.Texture);
		glPushMatrix();
	        glRotatef(mercury.Translacao, 0, 1, 0);
	        glTranslatef(mercury.TamanhoTranslacao, 0.0, 0);
	        glRotatef(mercury.Rotacao, 0, 1, 0);
	        glRotatef(97, 1, 0, 0); 
	        criaSphere(0.5 * horizonteEventos, mercury.Faces, mercury.Faces);
	    glPopMatrix();
		//Venus
	    glBindTexture(GL_TEXTURE_2D, venus.Texture);   
	    glPushMatrix();
	        glRotatef(venus.Translacao, 0, 1, 0);
	        glTranslatef(venus.TamanhoTranslacao, 0.0, 0);
	        glRotatef(venus.Rotacao, 0, 1, 0);
	        glRotatef(-267, 1, 0, 0);        
	        criaSphere(0.95 * horizonteEventos, venus.Faces, venus.Faces);
	    glPopMatrix();
		//Terra
	    glBindTexture(GL_TEXTURE_2D, earth.Texture);   
	    glPushMatrix();
	        glRotatef(earth.Translacao, 0, 1, 0);
	        glTranslatef(earth.TamanhoTranslacao, 0.0, 0);
	        glRotatef(earth.Rotacao, 0, 1, 0);
	        glRotatef(-133.5, 1, 0, 0);        
	        criaSphere(1 * horizonteEventos, earth.Faces, earth.Faces);
	    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void estadoExecucao(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    exibeCamera();
   	glMaterialfv(GL_FRONT, GL_SHININESS, matrizBrilho);
    glColor3f(1, 1, 1);
    Luz();
    renderizaCorpos();
    //exibeOrbitas();
    glutSwapBuffers();
}

void estadoAtualizacao(int time){
	glutPostRedisplay();
    glutTimerFunc(time, estadoAtualizacao, time);
}

/*Define estado inicial dos componentes*/
void defineBase(){
	glClearColor(0,0,0, 0.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /*Configurações da Luz*/
    difusa = 1;
	especular = 1;
	posicional = 1;
	global = 0.2;
	luzBranca.X = 0;
	luzBranca.Y = 0;

	/*Configurações do Cursor*/
	cursor.X = 0;
	cursor.Y = 0;
	cursor.Z = 0;

	/*Configurações do Mouse*/
	mouse.X = 0;
	mouse.Y = 0;
	mouse.Z = 0;

    /*Configurações dos Corpos*/
	//Espaço
	space.Texture = carregaTextura("textures/space.jpg");

    //SOL
	sun.Texture = carregaTextura("textures/sun.jpg");
	sun.Translacao = 0;
	sun.Faces = 200;
	sun.Estado = true;
	sun.Rotacao = 0;

	//MERCURIO
	mercury.Texture = carregaTextura("textures/mercury.jpg");
	mercury.Translacao = 90;
	mercury.Rotacao = 10;
	mercury.TamanhoTranslacao = 126;
	mercury.Faces = 200;
	mercury.Estado = true;

	//VENUS
	venus.Texture = carregaTextura("textures/venus.jpg");
	venus.Translacao = 30;
	venus.Rotacao = 10;
	venus.TamanhoTranslacao = 166;
	venus.Faces = 200;
	venus.Estado = true;

	//TERRA
	earth.Texture = carregaTextura("textures/earth.jpg");
	earth.Translacao = 90;
	earth.Rotacao = 90;
	earth.TamanhoTranslacao = 200;
	earth.Faces = 200;
	earth.Estado = true;

	/*Configurações do Material*/
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matrizAD);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matrizEspecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matrizBrilho);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void estadoTeclado(unsigned char key, int x, int y){
	switch(key){
		case '1':
			modoCamera = 1;
		break;
		case '2':
			modoCamera = 2;
		break;
		case 27:
			exit(0);
		break;
		case 'w':
			cursor.X--;
		break;
		case 'W':
			cursor.X--;
		break;
		case 's':
			cursor.X++;
		break;
		case 'S':
			cursor.X++;
		break;
		case 'a':
			cursor.Z--;
		break;
		case 'A':
			cursor.Z--;
		break;
		case 'd':
			cursor.Z++;
		break;
		case 'D':
			cursor.Z++;
		break;
		case 'f':
			podeBrilhar = !podeBrilhar;
		break;
		case 'F':
			podeBrilhar 	= !podeBrilhar;
		break;
		case 'e':
			if(horizonteEventos == 1){
				horizonteEventos = 10;
			} else{
				horizonteEventos = 1;
			}
		break;
		case 'E':
			if(horizonteEventos == 1){
				horizonteEventos = 10;
			} else{
				horizonteEventos = 1;
			}
		break;
		case 'v':
			podeOrbitar = !podeOrbitar;
		break;
		case 'V':
			podeOrbitar = !podeOrbitar;
		break;
	}
}

/*Define as configurações da camera*/
void confCamera(int x, int y){
	float altX = x - mouse.X;
	float altY = y - mouse.Y;

	anguloCameraA = anguloCameraA + altX/150;
	anguloCameraB = anguloCameraB + altY/150;

	if(anguloCameraB > 180){
		anguloCameraB = 180;
	}

	mouse.X = x;
	mouse.Y = y;
}

void estadoRotacao(){
	sun.Rotacao = sun.Rotacao + 0.1f;
	mercury.Rotacao = mercury.Rotacao + 0.04f;
	venus.Rotacao = venus.Rotacao + 0.01f;
	earth.Rotacao = earth.Rotacao + 2.4f;

	glutPostRedisplay();
}

void estadoTranslacao(){
	mercury.Translacao = mercury.Translacao + 0.16f;
	venus.Translacao = venus.Translacao + 0.12f;
	earth.Translacao = earth.Translacao + 0.1f;
	
	estadoRotacao();
	glutPostRedisplay();
}

int main(int argc, char* args[]) {
    // Inicialização do SDL e outras bibliotecas
    SDL_Init(SDL_INIT_EVERYTHING);
    glutInit(&argc, args);
    glutInitContextVersion(1, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    // Criação da janela
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); //Modo
    glutInitWindowSize(1350, 720);//Dimensão
    glutInitWindowPosition (0, 0);//Posição
    glutCreateWindow("Solar System");

    //Chamada de funções
    glutReshapeFunc(confJanela);
    glutDisplayFunc(estadoExecucao);
    glutTimerFunc(10, estadoAtualizacao, 10);
	glutKeyboardFunc(estadoTeclado);
    glutPassiveMotionFunc(confCamera);
	glutIdleFunc(estadoTranslacao);
	defineBase();
    
    // Início do loop do OpenGL
    glutMainLoop();

    // Finalização do SDL
    SDL_Quit();

    return 0;
}