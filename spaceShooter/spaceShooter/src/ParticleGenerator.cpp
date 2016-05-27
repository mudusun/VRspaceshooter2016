
#include "ParticleGenerator.h"



ParticleGenerator::ParticleGenerator(int mode, glm::mat4 matrix)
{
	mode_ = mode;
	this->matrix_ = matrix;
	if (mode_ == 1)
	{
		matrix_ = glm::translate(glm::mat4(), glm::vec3(0.0f, 5.0f, 0.0f));
	}
	else if (mode_ == 0)
	{
	}


	GLfloat colorsR[12][3] =		// Rainbow Of Colors
	{
		{ 1.0f,0.5f,0.5f },{ 1.0f,0.75f,0.5f },{ 1.0f,1.0f,0.5f },{ 0.75f,1.0f,0.5f },
		{ 0.5f,1.0f,0.5f },{ 0.5f,1.0f,0.75f },{ 0.5f,1.0f,1.0f },{ 0.5f,0.75f,1.0f },
		{ 0.5f,0.5f,1.0f },{ 0.75f,0.5f,1.0f },{ 1.0f,0.5f,1.0f },{ 1.0f,0.5f,0.75f }
	};

	memcpy(colors, colorsR, sizeof(colors));
	privateInit();
}

ParticleGenerator::~ParticleGenerator()
{
	

}

void ParticleGenerator::privateInit()      //All setup for openGL goes here
{
	/* load an image file directly as a new OpenGL texture */
	tex_id = SOIL_load_OGL_texture
		(
			"../spaceShooter/texturePictures/Particle.bmp",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

	/* check for an error during the load process */
	if (0 == tex_id)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}


	for (int loop = 0; loop<MAX_PARTICLES; loop++)				// Initials All The Textures
	{
		particle[loop].active = true;								// Make All The Particles Active
		particle[loop].life = 1.0f;								// Give All The Particles Full Life
		particle[loop].fade = float(rand() % 100) / 1000.0f + 0.003f;	// Random Fade Speed
		particle[loop].r = colors[loop*(12 / MAX_PARTICLES)][0];	// Select Red Rainbow Color
		particle[loop].g = colors[loop*(12 / MAX_PARTICLES)][1];	// Select Red Rainbow Color
		particle[loop].b = colors[loop*(12 / MAX_PARTICLES)][2];	// Select Red Rainbow Color
		particle[loop].xi = float((rand() % 50) - 26.0f)*10.0f;		// Random Speed On X Axis
		particle[loop].yi = float((rand() % 50) - 25.0f)*10.0f;		// Random Speed On Y Axis
		particle[loop].zi = float((rand() % 50) - 25.0f)*10.0f;		// Random Speed On Z Axis
		particle[loop].xg = 0.0f;									// Set Horizontal Pull To Zero
		particle[loop].yg = -0.8f;								// Set Vertical Pull Downward
		particle[loop].zg = 0.0f;									// Set Pull On Z Axis To Zero
	}

	
}



void ParticleGenerator::privateRender()
{
	
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearDepth(1.0f);									// Depth Buffer Setup
	glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
	glEnable(GL_BLEND);									// Enable Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);					// Type Of Blending To Perform
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);				// Really Nice Point Smoothing
	
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	glBindTexture(GL_TEXTURE_2D, tex_id);			// Select Our Texture

	for (int loop = 0; loop<MAX_PARTICLES; loop++)					// Loop Through All The Particles
	{
		if (particle[loop].active)							// If The Particle Is Active
		{
			float x = particle[loop].x;						// Grab Our Particle X Position
			float y = particle[loop].y;						// Grab Our Particle Y Position
			float z = particle[loop].z;					// Particle Z Pos 

																// Draw The Particle Using Our RGB Values, Fade The Particle Based On It's Life
			glColor4f(particle[loop].r, particle[loop].g, particle[loop].b, particle[loop].life);

			glBegin(GL_QUADS);						// Build Quad From A Triangle Strip
			glTexCoord2d(0, 0); glVertex3f(x - 0.5f, y - 0.5f, z); // Bottom Left
			glTexCoord2d(1, 0); glVertex3f(x + 0.5f, y - 0.5f, z); // Bottom Right
			glTexCoord2d(1, 1); glVertex3f(x + 0.5f, y + 0.5f, z); // Top Right
			glTexCoord2d(0, 1); glVertex3f(x - 0.5f, y + 0.5f, z); // Top Left
			glEnd();										// Done Building Triangle Strip

			particle[loop].x += particle[loop].xi / (slowdown * 1000);// Move On The X Axis By X Speed
			particle[loop].y += particle[loop].yi / (slowdown * 1000);// Move On The Y Axis By Y Speed
			particle[loop].z += particle[loop].zi / (slowdown * 1000);// Move On The Z Axis By Z Speed

			particle[loop].xi += particle[loop].xg;			// Take Pull On X Axis Into Account
			particle[loop].yi += particle[loop].yg;			// Take Pull On Y Axis Into Account
			particle[loop].zi += particle[loop].zg;			// Take Pull On Z Axis Into Account
			particle[loop].life -= particle[loop].fade;		// Reduce Particles Life By 'Fade'

			if (particle[loop].life<0.0f)					// If Particle Is Burned Out
			{
				particle[loop].life = 1.0f;					// Give It New Life
				particle[loop].fade = float(rand() % 100) / 1000.0f + 0.003f;	// Random Fade Value
				particle[loop].x = 0.0f;						// Center On X Axis
				particle[loop].y = 0.0f;						// Center On Y Axis
				particle[loop].z = 0.0f;						// Center On Z Axis
				//particle[loop].xi = 100 + float((rand() % 60) - 32.0f);	// X Axis Speed And Direction
				//particle[loop].yi = 100 + float((rand() % 60) - 30.0f);	// Y Axis Speed And Direction
				particle[loop].zi = 500+ float((rand() % 60) - 30.0f);	// Z Axis Speed And Direction
				particle[loop].r = colors[0][0];			// Select Red From Color Table
				particle[loop].g = colors[0][1];			// Select Green From Color Table
				particle[loop].b = colors[0][2];			// Select Blue From Color Table
			}

		}
	}

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

void ParticleGenerator::privateUpdate()
{

}







