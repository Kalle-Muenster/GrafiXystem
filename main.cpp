
#include "projectGrafics.h"

#include <vector>
#include <iostream>
#include "projectMacros.h"
#include "Yeti.h"

Yeti* yeti;

void init(void);
void display(void);
void MouseClicks(int,int,int,int);
void reshape(GLsizei, GLsizei);
void idle(void);
void Render(void);
void keyboardInput(unsigned char, int, int);
void processSpecialKeys(int, int, int);
void MouseMoveFunc(int, int);
void MouseWheelFunc(int,int,int,int);
void GenerateObjects(void);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowSize(SCREENWIDTH, SCREENHEIGHT);
	glutCreateWindow("-grafiXystem-");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	glutPassiveMotionFunc(MouseMoveFunc);
	glutMouseFunc(MouseClicks);
	glutMouseWheelFunc(MouseWheelFunc);
	glutSpecialFunc(processSpecialKeys);
	glutKeyboardFunc(keyboardInput);
	
	glewInit();
	init();
	glutMainLoop();

	return 0;
}  


void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	GenerateObjects();
}

void display()
{
	Render();

}

void Render()
{
	INPUT->PerFrameReset();
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	SCENE->camera->transform.position.y+=0.001;
	SCENE->DrawAll();

	glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height)
{
	if(height == 0)
	{
		height = 1;
	}

	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45, aspect, 0.1f, 100.0f);
}

void idle()
{
	//glutPostRedisplay();
	Render();
}

void keyboardInput(unsigned char key, int x, int y)
{
	INPUT->notifyKey(key);
}

void processSpecialKeys(int key, int xx, int yy) 
{
	INPUT->notifySpecialKey(key);
}

void MouseMoveFunc(int x, int y)
{
	INPUT->notifyMouse(x,y);
}

void MouseClicks(int button,int state,int x,int y)
{
	INPUT->UbdateMouseButtons(button,state,x,y);
}

void MouseWheelFunc(int wheel,int state,int x,int y)
{
	INPUT->UpdateMouseWheel(wheel,state,x,y);
}


void GenerateObjects()
{
	yeti = new Yeti("wendy_Scene.obj","tex_wendy_2.jpg",true);
	INPUT->attachMouseMove((IObserver*)yeti);
	SCENE->camera->SetTarget(yeti);
}