/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>



#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#define PI 3.1415926
#define CIRCLE_STEPS 60
static int slices = 16;
static int stacks = 16;

/* GLUT callback Handlers */

GLint x = 0,y = 0 , raio =100;
GLint altura = 256, largura = 256;
GLfloat Time;






static void resize(int width, int height)
{

    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 0.5, 50.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
    gluLookAt(0,0,2,
              0,0,0,
              1,0,0);
}
void cubo(){


        glutSolidCube(0.3);

}
void cubo2(){

        glutSolidCube(0.4);

}
///A ENGRENAGEM  ROSA
void engrenagem(double a){
    double   angulo;

        ///INICIO
        glPushMatrix();

        ///COLOR
            glColor3f(1,0,1);
        ///TRANSLADA O EIXO
            glTranslatef(0.5,0,0);
            //glRotated(0,1,0,0);
        ///velocidade de rota豫o
            glRotated(a*2,0,0,1);
        ///Muda a escala
            glScalef(-0.5,-0.5,0.5);

        ///DE FORMA COM CUBOS
            for(int i=0;i<360;i++){

                glPushMatrix();
                    angulo = i+1;
                   ///PARTE DE FORMA플O DA RODA
                    glTranslatef(0,0,0);
                    glRotatef(angulo,0,0,1);
                    glTranslatef(0.7,0,0);
                    cubo2();
                glPopMatrix();
            }


        ///De forma TORuS
        //glutSolidTorus(0.2,0.8,slices,stacks);

        glScalef(1.5,1.5,1);
        glTranslatef(1,0.0,0.0);
        ///DENTES

        for(int i=0;i<5;i++){

            glPushMatrix();
                angulo = i*70;
                ///PARTE DE FORMA플O DENTES
                glTranslatef(-1,0,0);
                glRotatef(angulo,0,0,1);
                glTranslatef(0.7,0,0);
                cubo2();
            glPopMatrix();
        }



        glPopMatrix();
}

void engrenagem2(double a){
   double   angulo;
   glPushMatrix();

            ///ENGRENAGEM GRANDE

            ///COILOR
            glColor3f(1,0,0);
            ///EIXO
            glTranslatef(1,1.5,0);


            ///ROTA플O
            glRotated(-a,0,0,1);

            for(int i=0;i<360;i++){

                glPushMatrix();
                    angulo = i+1;
                    ///FORMA플O DA RODA
                    glTranslatef(0,0,0);
                    glRotatef(angulo,0,0,1);
                    glTranslatef(0.7,0,0);
                    cubo2();
                glPopMatrix();
            }
        ///De forma TORuS
        //glutSolidTorus(0.2,0.8,slices,stacks);

        glTranslatef(1,0.0,0.0);
        ///Translada

        ///FORMA플O DOS DENTES
        for(int i=0;i<36;i++){

            glPushMatrix();
                angulo = i*36;
                glTranslatef(-1,0,0);
                glRotatef(angulo,0,0,1);
                glTranslatef(1,0,0);
                cubo();
            glPopMatrix();
        }



        glPopMatrix();



}

static void display(void)
{

    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);

    ///GRANDE
    engrenagem2(a);
///-------------------------------------------
    ///PEQUENA
    engrenagem(a);

    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

        case '+':
            slices++;
            stacks++;
            break;

        case '-':
            if (slices>3 && stacks>3)
            {
                slices--;
                stacks--;
            }
            break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return EXIT_SUCCESS;
}



