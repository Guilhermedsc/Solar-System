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
    glutCreateWindow("Sistema Solar");

    //Chamada de funções
    glutReshapeFunc(confJanela);
    
    // Início do loop do OpenGL
    glutMainLoop();

    // Finalização do SDL
    SDL_Quit();

    return 0;
}