
#include "projectGrafics.h"

#include <vector>
#include <iostream>

#include "projectMacros.h"
#include "Yeti.h"
#include "Map.h"
#include "Connectable.h"
#include "TestYeti.h"
#include "TestConectables.h"



Yeti* yeti;
TestYeti* serengetiYeti;
Map* map;

//TestYeti* yeti;

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
	AUDIO->LoadeBackgroundAudio("testtrack.wav");


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
	delete serengetiYeti;
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
	
	
	//Yeti without components...
	yeti = new Yeti("wendy_Scene.obi","tex_wendy_2.jpg",true);
	INPUT->attachKey(yeti);
	INPUT->attachMouseClick(yeti);
	INPUT->attachMouseMove(yeti);
	SCENE->camera->SetTarget(yeti);

	//testyeti uses IConnectable Components...
	serengetiYeti = new TestYeti("wendy_Scene.obi","tex_wendy.jpg",true);
	serengetiYeti->conXtor->AddConnectable<YetiInteractive>();
	serengetiYeti->conXtor->AddConnectable<CameraTargetRotator>();
	INPUT->attachKey(serengetiYeti->conXtor->GetConnected<YetiInteractive>());
	INPUT->attachMouseMove(serengetiYeti->conXtor->GetConnected<YetiInteractive>());	

	map = new Map("Landschaft.obi","Landschaft_Diffuse.jpg",true);
	map->move(glm::vec3(map->getTransform()->position.x,-0.2,map->getTransform()->position.z));

	SCENE->camera->transform.position.y=2;
	
	

	AUDIO->Play();
	

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
			printf("switcht to Yeti");
		}
		else
		{
			SCENE->camera->SetTarget(serengetiYeti);
			yetiNumber=0;
			printf("switcht to SerengetiYeti");
		}
	}
	if(INPUT->Mouse.MIDDLE.CLICK)
	{
		if(yetiNumber==0)
		{
			SCENE->camera->SetFirstPerson((IGobject*)yeti);
			yetiNumber=1;
		}
		else
		{
			SCENE->camera->SetFirstPerson((IGobject*)serengetiYeti);
			yetiNumber=0;
		}


		
	}
	UPDATE->DoAllTheUpdates();
//	if(INPUT->Mouse.RIGHT.CLICK)
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

