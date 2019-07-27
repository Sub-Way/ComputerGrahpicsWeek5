#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <GL\GLU.h>
#include <iostream>

int width = 640 * 2;
int height = 480 * 2;

void drawCoordinate()
{
	// 좌표 축
	glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(5.0, 0.0, 0.0);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 5.0, 0.0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 5.0);
	glEnd();
	glPopMatrix();
}

void drawCube(const float& Sx, const float& Sy, const float& Sz)
{
	// interleaved vertex array for glDrawElements() & glDrawRangeElements() ======
	// All vertex attributes (position, normal, color) are packed together as a
	// struct or set, for example, ((V,N,C), (V,N,C), (V,N,C),...).
	// It is called an array of struct, and provides better memory locality.
	GLfloat vertices[] = { 
		 1, 1, 1,   0, 0, 1,   1, 1, 0,              // v0 (front)
		-1, 1, 1,   0, 0, 1,   1, 1, 0,              // v1
		-1,-1, 1,   0, 0, 1,   1, 1, 0,              // v2
		 1,-1, 1,   0, 0, 1,   1, 1, 0,              // v3

		 1, 1, 1,   1, 0, 0,   0, 0, 1,              // v0 (right)
		 1,-1, 1,   1, 0, 0,   0, 0, 1,              // v3
		 1,-1,-1,   1, 0, 0,   0, 0, 1,              // v4
		 1, 1,-1,   1, 0, 0,   0, 0, 1,              // v5

		 1, 1, 1,   0, 1, 0,   0, 1, 0,              // v0 (top)
		 1, 1,-1,   0, 1, 0,   0, 1, 0,              // v5
		-1, 1,-1,   0, 1, 0,   0, 1, 0,              // v6
		-1, 1, 1,   0, 1, 0,   0, 1, 0,              // v1

		-1, 1, 1,  -1, 0, 0,   1, 0, 0,              // v1 (left)
		-1, 1,-1,  -1, 0, 0,   1, 0, 0,              // v6
		-1,-1,-1,  -1, 0, 0,   1, 0, 0,              // v7
		-1,-1, 1,  -1, 0, 0,   1, 0, 0,              // v2

		-1,-1,-1,   0,-1, 0,   1, 0, 1,              // v7 (bottom)
		 1,-1,-1,   0,-1, 0,   1, 0, 1,              // v4
		 1,-1, 1,   0,-1, 0,   1, 0, 1,              // v3
		-1,-1, 1,   0,-1, 0,   1, 0, 1,              // v2

		 1,-1,-1,   0, 0,-1,   0, 1, 1,              // v4 (back)
		-1,-1,-1,   0, 0,-1,   0, 1, 1,              // v7
		-1, 1,-1,   0, 0,-1,   0, 1, 1,              // v6
		 1, 1,-1,   0, 0,-1,   0, 1, 1 };            // v5

													 // index array of vertex array for glDrawElements() & glDrawRangeElement()
	GLubyte indices[] = { 
		 0, 1, 2,   2, 3, 0,      // front
		 4, 5, 6,   6, 7, 4,      // right
		 8, 9,10,  10,11, 8,      // top
		12,13,14,  14,15,12,      // left
		16,17,18,  18,19,16,      // bottom
		20,21,22,  22,23,20 };    // back

	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glNormalPointer(GL_FLOAT, 9 * sizeof(GLfloat), vertices + 3);
	glColorPointer(3, GL_FLOAT, 9 * sizeof(GLfloat), vertices+ 6);
	glVertexPointer(3, GL_FLOAT, 9 * sizeof(GLfloat), vertices);

	glPushMatrix();
	glScalef(Sx, Sy, Sz);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);

	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

int main()
{
	GLFWwindow* window;
	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(width, height, "week 5 sample", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return -1;
	}

	glClearColor(0.8f, 0.8f, 0.8f, 1);
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	const float aspect_ratio = (float)width / (float)height;
	glOrtho(-100.0 * aspect_ratio, 100.0 * aspect_ratio, -100.0, 100.0, -100.0, 100.0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	double i = 0;	

	while (!glfwWindowShouldClose(window))
	{
		i = i + 0.1;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		drawCoordinate();

		//첫번째 Cube
		glPushMatrix();
		glRotated(i, 1, 1, 1);
		drawCube(0.07, 0.07, 0.07);
		glPopMatrix();

		//두번째 Cube
		//glPushMatrix();
		//glRotated(i, 0, 1, 0);
		//glTranslated(0.3, 0, 0);
		//glPushMatrix();
		//glRotated(i, 1, 1, 1);
		//drawCube(0.05, 0.05, 0.05);
		//glPopMatrix();

		////세번째 Cube
		//glPushMatrix();
		//glRotated(i*2, 0.0, 1.0, 0.0);
		//glTranslated(0.1, 0, 0);
		//drawCube(0.01, 0.01, 0.01);
		//glPopMatrix();
		//glPopMatrix();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}