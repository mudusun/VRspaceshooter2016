#pragma once

#include <GL/glew.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SceneObject.hpp"
#include "glm/glm.hpp"

class BitmapText : public SceneObject
{
	public:
		BitmapText();
		~BitmapText();
		void drawBitmapText(const char *string, float x, float y);

  protected:
	  
	 // void drawStrokeText(char*string, int x, int y, int z);
	 // void reshape(int w, int h);
      void privateInit();
	  void privateRender();
	  //void privateUpdate();
		

	private:
	  

};

