#define _CRT_SECURE_NO_DEPRECATE
#include<GL/Glut.h> //includes the opengl, glu, and glut header files
#include<stdlib.h> //includes the standard library header file
#include<iostream>
#include <stdio.h>
#include <share.h>
#include"TextureLoader.h"
#include<cmath>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;
float mario_vertices[] =
{
	-0.711155, -0.461412,
	-0.951618, -0.461412,
	-0.951618, -0.701876,
	-0.711155, -0.701876
};
float base_vertices[] =
{
	1, -0.7,
	-1, -.7,
	-1, -1,
	1, -1

};
float enemy_vertices[]{
	0.701876, -.5,
	0.951618,-.5,
	0.951618, -0.701876,
	0.701876, -0.701876
};

float cloud_vertices[]{
	0.701876, -.5,
	0.951618,-.5,
	0.951618, -0.701876,
	0.701876, -0.701876
};
GLuint mario_texture, base_textureid, enemy_texture, cloud_texture;
#pragma warning(diable:4996)
GLuint loadTexture(const char * filename)
{
	GLuint texture; 
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	unsigned char * data;
	int width, height;
	FILE * file;
	file = fopen(filename, "rb");
	if (!file)
	{
		printf("Image could not be opened\n");
		return NULL;
	}
	// Read the header, i.e. the 54 first bytes
	// If less than 54 byes are read, problem
	if (fread(header, 1, 54, file) != 54) {
		printf("Not a correct BMP file\n");
		return NULL;
	}
	// A BMP files always begins with "BM"
	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file\n");
		return NULL;
	}

	/*if (*(int*)&(header[0x1E]) != 0) { printf("Not a correct2 BMP file\n");    return false; }*/
	if (*(int*)&(header[0x1C]) != 24) { printf("Not a correct2 BMP file\n");    return NULL; }

	// Read the information about the image
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);
	if (imageSize == 0)    imageSize = width*height * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)      dataPos = 54; // The BMP header is done that way
	data = new unsigned char[imageSize];

	// Read the actual data from the file into the buffer
	fread(data, 1, imageSize, file);

	// Everything is in memory now, the file wan be closed
	fclose(file);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	return  texture;
}

void draw_mario(float vertices1[], GLuint texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glutSwapBuffers();
	glTexCoord2d(1, 1);
	glVertex2f(vertices1[0], vertices1[1]);
	glTexCoord2d(0, 1);
	glVertex2f(vertices1[2], vertices1[3]);
	glTexCoord2d(0, 0);
	glVertex2f(vertices1[4], vertices1[5]);
	glTexCoord2d(1, 0);
	glVertex2f(vertices1[6], vertices1[7]);
	glEnd();
}

void draw_base(float vertices1[], GLuint texture)
{
	/*glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);*/
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glutSwapBuffers();
	glTexCoord2d(9, 1);
	glVertex2f(vertices1[0], vertices1[1]);
	glTexCoord2d(0, 1);
	glVertex2f(vertices1[2], vertices1[3]);
	glTexCoord2d(0, 0);
	glVertex2f(vertices1[4], vertices1[5]);
	glTexCoord2d(9, 0);
	glVertex2f(vertices1[6], vertices1[7]);
	glEnd();
}

void draw_enemy(float vertices1[], GLuint texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glutSwapBuffers();
	glTexCoord2d(1, 1);
	glVertex2f(vertices1[0], vertices1[1]);
	glTexCoord2d(0, 1);
	glVertex2f(vertices1[2], vertices1[3]);
	glTexCoord2d(0, 0);
	glVertex2f(vertices1[4], vertices1[5]);
	glTexCoord2d(1, 0);
	glVertex2f(vertices1[6], vertices1[7]);
	glEnd();
}
void draw_cloud(float vertices1[], GLuint texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glutSwapBuffers();
	glTexCoord2d(1, 1);
	glVertex2f(vertices1[0], vertices1[1]);
	glTexCoord2d(0, 1);
	glVertex2f(vertices1[2], vertices1[3]);
	glTexCoord2d(0, 0);
	glVertex2f(vertices1[4], vertices1[5]);
	glTexCoord2d(1, 0);
	glVertex2f(vertices1[6], vertices1[7]);
	glEnd();
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor4f(1, 1, 1, 1);
	draw_base(base_vertices, base_textureid);
	draw_mario(mario_vertices,mario_texture);
	draw_enemy(enemy_vertices, enemy_texture);
	//draw_cloud(cloud_vertices, cloud_texture);
	glFlush();
	
}

void changeY(float x)
{
	float mario_right_boundry = mario_vertices[4] + x;
	float mario_left_boundry = mario_vertices[6] + x;

	if (mario_right_boundry >= 0) {
		for (int i = 0; i < 8; i++)
			mario_vertices[i] *= .2;
	}
	else if (mario_left_boundry >-.75545 && mario_right_boundry<.75545) {

		mario_vertices[0] += x;
		mario_vertices[2] += x;
		mario_vertices[4] += x;
		mario_vertices[6] += x;

		enemy_vertices[0] -= x;
		enemy_vertices[2] -= x;
		enemy_vertices[4] -= x;
		enemy_vertices[6] -= x;

		/*cout << vertices[0] << endl;
		cout << vertices[2] << endl;
		cout << vertices[4] << endl;
		cout << vertices[6] << endl;*/
		draw_mario(mario_vertices, mario_texture);
		draw_enemy(enemy_vertices, enemy_texture);
	}
}
void changeX(float x)
{
	float bottom_boundry = mario_vertices[7] + x;
	float top_boundry = mario_vertices[1] + x;
	if (bottom_boundry > -0.701876 &&top_boundry < 1) {
		mario_vertices[1] += x;
		mario_vertices[3] += x;
		mario_vertices[5] += x;
		mario_vertices[7] += x;
		/*cout << vertices[1] << endl;
		cout << vertices[3] << endl;
		cout << vertices[5] << endl;
		cout << vertices[7] << endl;*/
		draw_mario(mario_vertices, mario_texture);
	}
}
void scale(float x)
{
	for(int i = 0 ; i < 8 ; i++)
		mario_vertices[i] *= x;

	/*cout << vertices[0] << endl;
	cout << vertices[2] << endl;
	cout << vertices[4] << endl;
	cout << vertices[6] << endl;*/
	
}
void keyPressed(unsigned char key, int x, int y) {
	
	switch (key)
	{
	case 'B':
	case 'b':
		scale(1.2);
		cout << "Scale Big" << endl;
		break;
	case 'S':
	case 's':
		scale(0.8);
		cout << "Scale Small" << endl;
		break;
	case 'L':
	case 'w':
		changeX(0.1);
		cout << "UP"<<endl;
		break;
	/*case 'S':
	case 's':
		changeX(-0.1);
		cout << "DOWN" << endl;
		break;*/
	case 'A':
	case 'a':
		changeY(-0.1);
		cout << "LEFT"<< endl;
		break;
	case 'D':
	case 'd':
		changeY(0.1);
		cout << "RIGHT" << endl;
		break;
	}
}
void keypressSpecial(int key, int x, int y)
{
	//glutSetKeyRepeat(0);

	if (key == GLUT_KEY_UP) {
		changeX(0.1);
		//do something here
		cout << "up " << endl;
	}

	if (key == GLUT_KEY_DOWN) {
		changeX(-0.1);
		cout << "down" << endl;
	}

	if (key == GLUT_KEY_RIGHT) {
		changeY(0.1);
		cout << "right" << endl;
	}

	if (key == GLUT_KEY_LEFT) {
		changeY(-0.1);
		cout << "left" << endl;
	}
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(640, 640);   //sets the width and height of the window in pixels
	glutInitWindowPosition(20, 20);//sets the position of the window in pixels from top left corner 
	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//creates a single frame buffer of RGB color capacity.
	glutCreateWindow("Mario Game");//creates the window as specified by the user as above.
	glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed  
	glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
	//gluOrtho2D(-100, 100, -100, 100);
	glClearColor(.48, .46, .98, 0); // sets the backgraound color to white light
	glClear(GL_COLOR_BUFFER_BIT); // clears the frame buffer and set values defined in glClearColor() function call 

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	mario_texture = loadTexture("images/mario.bmp");
	base_textureid=loadTexture("images/newbase.bmp");
	enemy_texture=loadTexture("images/enemy.bmp");
	//cloud_texture = loadTexture("images/cloud1.bmp");
	glutDisplayFunc(Display);//links the display event with the display event handler(display)
	glutIdleFunc(Display);

	
	//unsigned char* data = loadBMPRaw("C:\\CMakeFiles\\castle.bmp", w, h, false);
	glutSpecialFunc(keypressSpecial);
	glutKeyboardFunc(keyPressed); // Tell GLUT to use the method "keyPressed" for key presses  
	glutMainLoop();//loops the current event
}
