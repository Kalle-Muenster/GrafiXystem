#include <vector>
#include <iostream>

#include "projectGrafics.h"
#include "projectMacros.h"
#include "projectClasses.h"

int Data[5];
int window;
int controllpanel=-1;
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
void MainMenu(int);
void InitMenus(void);



// - The Assambley's entrypoint
int main(int argc, char** argv)
{
//	AUDIO->LoadeBackgroundAudio("testtrack.wav");


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowSize(SCREENWIDTH, SCREENHEIGHT);
	window = glutCreateWindow("-grafiXystem-");
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

	//InitMenus();

	LoadingFunction();
}

void InitMenus(void)
{
	glutCreateMenu(MainMenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutAddMenuEntry("ShowPanel",100);
	glutAddMenuEntry("EXIT",1000);
}

void testfunc(int line,ListenerData* data)
{
	serengetiYeti->MoveOnMusic(line,data);
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
	

	//testyeti uses IConnectable Components...
	serengetiYeti = new TestYeti("wendy_Scene.obi","tex_wendy.jpg",true);

	map = new Map("Landschaft.obi","Landschaft_Diffuse.jpg",true);
	map->move(Vector3(map->getTransform()->position.x,-0.2,map->getTransform()->position.z));

	SCENE->camera->transform.position.y=0.5;
	SCENE->camera->SetTarget(serengetiYeti);

	serengetiYeti->conXtor->GetConnected<AudioEmitter>()->PlayAudio();

	yeti->move(-1,yeti->transform.position.y,-1);
	serengetiYeti->move(-1,serengetiYeti->transform.position.y,1);

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

	//if(INPUT->Mouse.RIGHT.CLICK)
	//{
	//	if(yetiNumber==0)
	//	{
	//		SCENE->camera->SetFirstPerson((IGobject*)yeti);
	//		yetiNumber=1;
	//	}
	//	else
	//	{
	//		SCENE->camera->SetFirstPerson((IGobject*)serengetiYeti);
	//		yetiNumber=0;
	//	}
	//}

	UPDATE->DoAllTheUpdates();
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
		height = 1;

	INPUT->SaveViewportRectangle(0,0,width,height);
	SCENE->camera->Aspect((float)width/(float)height);
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

void MainMenu(int selection)
{
	switch (selection)
	{
	case 100:
		if(controllpanel == -1)
		{
			controllpanel=glutCreateSubWindow(window,50,50,100,100);
		}
		else 
		{
			glutDestroyWindow(controllpanel);
			controllpanel= -1;
		}
		
		break;
	case 1000:
		glutExit();
		break;
	}
}