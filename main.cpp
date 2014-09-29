
#include "projectGrafics.h"

#include <vector>
#include <iostream>
#include "IrrAudio.h"
#include "projectMacros.h"
#include "Yeti.h"
#include "Map.h"

#define AUDIO irrAudio::GetInstance()

Yeti* yeti;
Yeti* serengetiYeti;
Map* map;



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
void LoadingFunction(void);
void UpdateFunction(void);
void WriteText(char* string,int x,int y,int z);


// - The Assambley's entrypoint
int main(int argc, char** argv)
{


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowSize(SCREENWIDTH, SCREENHEIGHT);
	glutCreateWindow("-grafiXystem-");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	glutMotionFunc(MouseMoveFunc);
	glutPassiveMotionFunc(MouseMoveFunc);
	glutMouseFunc(MouseClicks);
	glutMouseWheelFunc(MouseWheelFunc);
	glutSpecialFunc(processSpecialKeys);
	glutKeyboardFunc(keyboardInput);
	

	glewInit();
	init();
	glutMainLoop();
	
	
//	audio->SwitchOff();
	delete yeti;
	delete map;
	
//	delete audio;
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

	LoadingFunction();
}

// -- Here everything what have to be loadet befor entering the MeinLoop could be done here.....
void LoadingFunction()
{
	INPUT->attachMouseWheel(SCENE->camera);

	yeti = new Yeti("wendy_Scene.obi","tex_wendy_2.jpg",true);
	INPUT->attachKey(yeti);
	INPUT->attachMouseMove(yeti);
	
	
	serengetiYeti = new Yeti("wendy_Scene.obi","tex_wendy.jpg",true);
	SCENE->camera->SetTarget(serengetiYeti);
	//INPUT->attachKey(serengetiYeti);
	INPUT->attachMouseMove(serengetiYeti);

	map = new Map("Landschaft.obi","Landschaft_Diffuse.jpg",true);
	map->move(glm::vec3(map->getTransform()->position.x,-0.2,map->getTransform()->position.z));

	SCENE->camera->transform.position.z=1;

	
//	audio.OpenAudioFile("testtrack.wav");
	//audio->LoadAudioFile("testtrack.wav");
	//
	//audio->SetVolume(0.8f);

}

int yetiNumber=0;
// the main Update-Cycle.....
void UpdateFunction(void)
{ 
	if(INPUT->Mouse.LEFT.CLICK)
	{
		
		if(yetiNumber==0)
		{
			SCENE->camera->SetTarget(yeti);
			yetiNumber=1;
		//	AUDIO.Loade("hallo");
		}
		else
		{
			SCENE->camera->SetTarget(serengetiYeti);
			yetiNumber=0;
		}
	}

	//if(INPUT->Mouse.RIGHT.CLICK)
	//	audioControls->setIsPaused(false);
}


// The Main Render-Cycle.....
void Render()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

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


void display()
{
	
	UpdateFunction();
	Render();
	INPUT->PerFrameReset();
}
void idle()
{
//	glutPostRedisplay();
	
	UpdateFunction();
	Render();
	INPUT->PerFrameReset();
}
void keyboardInput(unsigned char key, int x, int y)
{
	if(key=='q')
	{
		glutExit();
	//	audio->SwitchOff();
	}
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
	INPUT->UpdateMouseButtons(button,state,x,y);
}

void MouseWheelFunc(int wheel,int state,int x,int y)
{
	INPUT->UpdateMouseWheel(wheel,state,x,y);
}

