#include<iostream>
#include<cstdlib>
#include <GL\freeglut.h>
using namespace std;

float x = 1, y = 1;
bool isYellow1= false;
bool isYellow2 = false;
bool isYellow3 = false;
float r = 0.0f;
float g = 0.0f;
float b = 0.0f;

float r1 = 0.0f;
float g1 = 0.0f;
float b1 = 0.0f;
float r2 = 0.0f;
float g2 = 0.0f;
float b2 = 0.0f;
void init(void) {


	glClearColor(239.0f / 255, 239.0f / 255, 187.0f / 255,0.0f);

}

void KeysFun(unsigned char key, int xpos, int ypos) {

    if (key == 27) {

	cout << "Escape key is press Now Exit" << endl;
	exit(EXIT_SUCCESS);
   }

	}


void MouseButton(int button,int action,int xPixel,int yPixel) {

	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {



		yPixel = glutGet(GLUT_WINDOW_HEIGHT) - yPixel;

		cout << "Default XPixel : " << xPixel << " Default YPixel :" << yPixel << endl;


		int * index = new int[1];



		glReadPixels(xPixel, yPixel, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, index);
		cout << "Read Pixels : " << xPixel << " Y pixel:" << yPixel << " index : " << index << endl;


		if (index[0] == 1) {

			isYellow1 = !isYellow1;
			if (isYellow1) {
				r = 255.0f / 255;
				g = 255.0f / 255;
			}


			else {
				r = 0.0f;
				g = 0.0f;
			}

		}
		else if (index[0] == 2) {

			isYellow2 = !isYellow2;
			if (isYellow2) {

				r1 = 255.0f / 255;
				g1 = 255.0f / 255;

			}

			else {
				r1 = 0.0f;
				g1 = 0.0f;
			}

		}//else if close
	
		else if (index[0] == 3) {
			isYellow3 = !isYellow3;
			if (isYellow3) {

				r2 = 255.0f / 255;
				g2 = 255.0f / 255;

			}

			else {
				r2 = 0.0f;
				g2 = 0.0f;
			}

		}//else if close

		delete index;


	}//Button Click if CLOSE

		glutPostRedisplay();
	}
	

void Rectangle1(void) {

	glStencilFunc(GL_ALWAYS, 1, -1);


	glBegin(GL_POLYGON);

	glColor3f(r, g, b);
	glVertex2f(-0.1f, 0.1f);
	glVertex2f(-0.1f, -0.1f);
	glVertex2f(0.1f, -0.1f);
	glVertex2f(0.1f, 0.1f);
	glEnd();

	glStencilFunc(GL_ALWAYS, 2, -1);
	glBegin(GL_POLYGON);

	glColor3f(r1, g1, b1);
	//left above
	glVertex2f(0.66f, 0.84f);
	//right above
	glVertex2f(0.87f, 0.84f);

	//right bottom
	glVertex2f(0.87f, 0.66f);
	//left bottom
	glVertex2f(0.66f, 0.66f);
	glEnd();

	glStencilFunc(GL_ALWAYS, 3, -1);
	glBegin(GL_POLYGON);
	
	
	glColor3f(r2, g2, b2);
	//left above
	glVertex2f(-0.82f, -0.7f);
		//right above
		glVertex2f(-0.65f, -0.7f);

	//right bottom
	glVertex2f(-0.65f, -0.86f);
	//left bottom
	glVertex2f(-0.82f, -0.86f);
	
	glEnd();



}

void Display(void) {
		glClearStencil(0);
		glClear(GL_COLOR_BUFFER_BIT |GL_STENCIL_BUFFER_BIT);
		glEnable(GL_STENCIL_TEST);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		Rectangle1();
		glFlush();
	}

void reshapeFunc(int width, int height) {

	if (height == 0) {
		height = 1;

	}
	else {
		height = height;
	}


	float aspectRatio = (GLfloat)width / (GLfloat)height;


	glViewport(0, 0, width, height);


	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	if (width <= height)
		//xleft xright,ytop , ybottom , znear , zfar
		//IN 2D Pixel 
		//xleft xright=width,ytop=height , ybottom , znear , zfar
		glOrtho(-x, x, -y / aspectRatio, y / aspectRatio, -1.0, 1.0);
	else
		glOrtho(-x*aspectRatio, x*aspectRatio, -y, y, -1.0, 1.0);
}

int main(int argc, char**argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_STENCIL);
	glutInitWindowSize(600, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Mouse");
	init();
	glutDisplayFunc(&Display);
	glutReshapeFunc(&reshapeFunc);
	glutMouseFunc(&MouseButton);
	glutKeyboardFunc(&KeysFun);
	glutMainLoop();

	return EXIT_SUCCESS;


}