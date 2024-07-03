// //Golf topu uygulaması
//

#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "getBMP.h"

# define PI 3.14159
static float R = 5.0;
static float Xaci = 0.0;
static float Yaci = 0.0;
static float Zaci = 0.0;
static unsigned int texture[2]; // Array of texture ids.
static float angle = 0.0; // Angle to rotate textured square.
static int id = 0; // Currently displayed texture id.



float radyan(float derece) {
	float rad = derece * PI / 180.0;
	return rad;
}

void loadTextures()
{
	// Local storage for image data.
	imageFile* image[1];

	// Load the image.
	image[0] = getBMP("Golf3.bmp");

	// Create texture object texture[0]. 
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	// Specify image data for currently active texture object.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[0]->width, image[0]->height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image[0]->data);

	// Set texture parameters for wrapping.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set texture parameters for filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}






void setup(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);

	// Create texture ids.
	glGenTextures(2, texture);

	// Load external texture. 
	loadTextures();

	// Load internal texture.
	//loadChessboardTexture();

	// Specify how texture values combine with current surface color values.
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	// Turn on OpenGL texturing.
	glEnable(GL_TEXTURE_2D);
}

void KubbeCiz(void) {
	int  i, j;
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -10.0);
	glRotatef(Xaci, 1.0, 0.0, 0.0);
	glRotatef(Yaci, 0.0, 1.0, 0.0);
	glRotatef(Zaci, 0.0, 0.0, 1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	float artim1 = 15.0;
	float artim2 = 15.0;
	float kubbenok[100][100][3];
	int sayac1 = 0;
	int sayac2 = 0;
	float alfaderece = 0.0;
	float tetaderece = 0.0;
	for (alfaderece = 0.0;alfaderece <= 360.0;alfaderece += artim2) {
		//(180 - artim1)
		for (tetaderece = -90;tetaderece <= 90;tetaderece += artim1) {
			kubbenok[sayac2][sayac1][0] = R * cos(radyan(tetaderece)) * cos(radyan(alfaderece));
			kubbenok[sayac2][sayac1][1] = R * sin(radyan(tetaderece));
			kubbenok[sayac2][sayac1][2] = -1.0 * R * cos(radyan(tetaderece)) * sin(radyan(alfaderece));
			sayac1++;
		}
		sayac2++;
		sayac1 = 0;
	}
	// Activate texture object.
	glBindTexture(GL_TEXTURE_2D, texture[id]);

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	for (i = 0;i < 12;i++) {
		for (j = 0;j < 24;j++) {
			glTexCoord2f(0.0, 0.0);	
			glVertex3fv(kubbenok[j][i]);
			glTexCoord2f(1.0, 0.0);
			glVertex3fv(kubbenok[j + 1][i]);
			glTexCoord2f(1.0, 1.0);
			glVertex3fv(kubbenok[j + 1][i + 1]);
			glTexCoord2f(0.0, 1.0);
			glVertex3fv(kubbenok[j][i + 1]);
		}
	}
	glEnd();
	glFlush();
}
void resize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;

	case 'x':
		Xaci += 5.0;
		if (Xaci > 360.0)Xaci -= 360.0;
		glutPostRedisplay();
		break;
	case 'X':
		Xaci -= 5.0;
		if (Xaci < 0.0) Xaci += 360.0;
		glutPostRedisplay();
		break;
	case 'y':
		Yaci += 5.0;
		if (Yaci > 360.0) Yaci -= 360.0;
		glutPostRedisplay();
		break;
	case 'Y':
		Yaci -= 5.0;
		if (Yaci < 0.0) Yaci += 360.0;
		glutPostRedisplay();
		break;
	case 'z':
		Zaci += 5.0;
		if (Zaci > 360.0) Zaci -= 360.0;
		glutPostRedisplay();
		break;
	case 'Z':
		Zaci -= 5.0;
		if (Zaci < 0.0) Zaci += 360.0;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Kubbe");
	glutDisplayFunc(KubbeCiz);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	setup();
	glutMainLoop();

}

