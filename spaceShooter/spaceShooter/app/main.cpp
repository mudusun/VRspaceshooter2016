#include <GL/glew.h>
#include <GL/GLU.h>
#include <GL/glut.h>
#include <windows.h>
#include <GL/freeglut.h>  
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <memory>
#include <iostream>
#include "Input.hpp"
#include "FpsCounter.hpp"
#include "GameManager.hpp"
#include "SpaceShip.hpp"
#include "glm/glm.hpp"


#include <iostream>

std::shared_ptr<GameManager> gm;
siut::FpsCounter counter;

int window;
float oldfps;

bool keyPressed[30];
int mousePosX, mousePosY; 
float moveX, moveY;

void init()
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);

  auto error_ = glewInit();
  std::cout << error_ << std::endl;

  counter.start();

  /* check the OpenGL version */
  char *buff = (char*)glGetString(GL_VERSION);
  std::cout << buff << std::endl;

  /* check the vendor and the graphics card */
  buff = (char*)glGetString(GL_VENDOR);
  std::cout << buff << std::endl;
  buff = (char*)glGetString(GL_RENDERER);
  std::cout << buff;

  gm.reset(new GameManager());
  gm->init();

  for(int i=0; i<30; i++)
    keyPressed[i]=false;
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  float startFps = glutGet(GLUT_ELAPSED_TIME);
  float deltaFps = startFps - oldfps;
  oldfps = startFps;
  gm->update(1/deltaFps*1000);
  gm->render();

  /* check for errors that may occur in OpenGL */
  GLenum err = glGetError();
  if (err != GL_NO_ERROR)
	 std::cout << "OpenGL error: " << gluErrorString(err) << std::endl;
  std::cout.flush();

 


  if(keyPressed[KEY_ID_W]==true)      gm->getCam()->moveForward();
  if(keyPressed[KEY_ID_A]==true)      gm->getCam()->moveLeft();
  if(keyPressed[KEY_ID_D]==true)      gm->getCam()->moveRight();
  if(keyPressed[KEY_ID_S]==true)      gm->getCam()->moveBackward();
  if(keyPressed[KEY_ID_X]==true)      gm->getCam()->moveUp();
  if(keyPressed[KEY_ID_C]==true)      gm->getCam()->moveDown();


  if (keyPressed[KEY_ID_RIGHT] == true)  gm->getShip()->moveRight();
  if (keyPressed[KEY_ID_LEFT] == true)   gm->getShip()->moveLeft();
  if (keyPressed[KEY_ID_UP] == true)     gm->getShip()->moveUp();
  if (keyPressed[KEY_ID_DOWN] == true)   gm->getShip()->moveDown();
  if ((keyPressed[KEY_ID_SPACE] == true)&& (gm->getShip()->getLife() > 0))
  {
	  gm->addBulletPlayer();
	  keyPressed[KEY_ID_SPACE] = false;
  }  

  glutSwapBuffers();
  glutPostRedisplay();

}

void keyDown(unsigned char key, int x, int y)
{
  switch (key) 
  {
    case 'q':
    case 27:
      glutDestroyWindow(window);
#ifndef _WIN32
      // Must use this with regular glut, since it never returns control to main().
      exit(0);
#endif
      break;
      
    case 'w':
      keyPressed[KEY_ID_W] = true;
      break;
    case 'a':
      keyPressed[KEY_ID_A] = true;
      break;
    case 's':
      keyPressed[KEY_ID_S] = true;
      break;
    case 'd':
      keyPressed[KEY_ID_D] = true;
      break;
    case 'x':
      keyPressed[KEY_ID_X] = true;
      break;
	case ' ':
		keyPressed[KEY_ID_SPACE] = true;
		break;
    case 'c':
      keyPressed[KEY_ID_C] = true;
      break;


    default:
      glutPostRedisplay();
  }
}

void keyUp(unsigned char key, int x, int y)
{
  switch (key) 
  {
    case 'w':
      keyPressed[KEY_ID_W] = false;
      break;
    case 'a':
      keyPressed[KEY_ID_A] = false;
      break;
    case 's':
      keyPressed[KEY_ID_S] = false;
      break;
    case 'd':
      keyPressed[KEY_ID_D] = false;
      break;
    case 'x':
      keyPressed[KEY_ID_X] = false;
      break;
	case ' ':
		keyPressed[KEY_ID_SPACE] = false;
		break;
    case 'c':
      keyPressed[KEY_ID_C] = false;
      break;
	case 'z':
		keyPressed[KEY_ID_Z] = false;
		break;
	case '1':
		keyPressed[KEY_ID_1] = false;
		break;
	case '2':
		keyPressed[KEY_ID_2] = false;
		break;
	case '3':
		keyPressed[KEY_ID_3] = false;
		break;
	case 'q':
		keyPressed[KEY_ID_Q] = false;
		break;

  }
}

void keyDownSpesial(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		keyPressed[KEY_ID_LEFT] = true;
		break;
	case GLUT_KEY_RIGHT:
		keyPressed[KEY_ID_RIGHT] = true;
		break;
	case GLUT_KEY_UP:
		keyPressed[KEY_ID_UP] = true;
		break;
	case GLUT_KEY_DOWN:
		keyPressed[KEY_ID_DOWN] = true;
		break;
	default:
		glutPostRedisplay();
	}
}

void keyUpSpesial(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_RIGHT:
		keyPressed[KEY_ID_RIGHT] = false;
		break;
	case GLUT_KEY_LEFT:
		keyPressed[KEY_ID_LEFT] = false;
		break;
	case GLUT_KEY_UP:
		keyPressed[KEY_ID_UP] = false;
		break;
	case GLUT_KEY_DOWN:
		keyPressed[KEY_ID_DOWN] = false;
		break;
	}
}

void mousePressed(int button, int state, int posX, int posY)
{
  if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
  {
    mousePosX = posX;
    mousePosY = posY;
    keyPressed[MOUSE_LEFT_BUTTON_DOWN] = true;
  }  
  if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    keyPressed[MOUSE_LEFT_BUTTON_DOWN] = false;
}

void mouseMoved(int posX, int posY)
{
  if(keyPressed[MOUSE_LEFT_BUTTON_DOWN])
  {
    int diffX = posX - mousePosX;
    mousePosX = posX;
    int diffY = posY - mousePosY;
    mousePosY = posY;
    
    // Implement quaternion based mouse move

  }
}

void addEnemy(int i) {
	gm->addEnemy();
	glutTimerFunc(2000, addEnemy, 0);
}

void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei) w, (GLsizei) h); 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
//  glOrtho(-50, 700, -50, 700, -50, 50);
  gluPerspective(60.0f, float(w)/float(h) ,0.5f, 5000.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
//  gluLookAt(0.0, 0.0, 10.0,     0.0, 0.0, 0.0,    0.0, 1.0, 0.0);
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);   // initialize glut
  // specify the display mode to be RGB and single buffering 
  // we use single buffering since this will be non animated 
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB); 
  glutInitWindowSize(700, 700);       // define the size 
  glutInitWindowPosition(10, 10);      // the position where the window will appear 
  window = glutCreateWindow("Space Shooter 3D");
  init();
  glutKeyboardFunc(keyDown);
  glutKeyboardUpFunc(keyUp);
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutMouseFunc(mousePressed);
  glutMotionFunc(mouseMoved);
  glutSpecialFunc(keyDownSpesial);
  glutSpecialUpFunc(keyUpSpesial);

  glutTimerFunc(20, addEnemy, 0);

  // Add other callback functions here..

  glutMainLoop();   // enter the main loop 
  return 0;
}
