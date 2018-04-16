#include <windows.h>
#include <GL/glut.h>
int x_rotation, y_rotation, z_rotation;

// vertex coords array
GLfloat vertices[] = { 1,1,1,  -1,1,1,  -1,-1,1,  1,-1,1,        // v0-v1-v2-v3
1,1,1,  1,-1,1,  1,-1,-1,  1,1,-1,        // v0-v3-v4-v5
1,1,1,  1,1,-1,  -1,1,-1,  -1,1,1,        // v0-v5-v6-v1
-1,1,1,  -1,1,-1,  -1,-1,-1,  -1,-1,1,    // v1-v6-v7-v2
-1,-1,-1,  1,-1,-1,  1,-1,1,  -1,-1,1,    // v7-v4-v3-v2
1,-1,-1,  -1,-1,-1,  -1,1,-1,  1,1,-1 };   // v4-v7-v6-v5

										   // normal array
GLfloat normals[] = { 0,0,1,  0,0,1,  0,0,1,  0,0,1,             // v0-v1-v2-v3
1,0,0,  1,0,0,  1,0,0, 1,0,0,              // v0-v3-v4-v5
0,1,0,  0,1,0,  0,1,0, 0,1,0,              // v0-v5-v6-v1
-1,0,0,  -1,0,0, -1,0,0,  -1,0,0,          // v1-v6-v7-v2
0,-1,0,  0,-1,0,  0,-1,0,  0,-1,0,         // v7-v4-v3-v2
0,0,-1,  0,0,-1,  0,0,-1,  0,0,-1 };        // v4-v7-v6-v5
											// color array
GLfloat colors[] = { 1,1,1,  1,1,1,  1,1,1,  1,1,1,              // v0-v1-v2-v3
1,1,0,  1,1,0,  1,1,0,  1,1,0,              // v0-v3-v4-v5
1,0,1,  1,0,1,  1,0,1,  1,0,1,              // v0-v5-v6-v1
0,1,0,  0,1,0,  0,1,0,  0,1,0,              // v1-v6-v7-v2
0,1,1,  0,1,1,  0,1,1,  0,1,1,              // v7-v4-v3-v2
0,0,1,  0,0,1,  0,0,1,  0,0,1 };             // v4-v7-v6-v5

void drawDECube(void)
{
	///////////////////////////////////////////////////////////////////////////////
	// draw cube with glDrawArrays
	///////////////////////////////////////////////////////////////////////////////

	// enble and specify pointers to vertex arrays
	glEnableClientState(GL_NORMAL_ARRAY); //for lighting....
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normals);
	glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_QUADS, 0, 24);
	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	//-------------------------------------
}

void init(void)
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 100.0 };
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	GLfloat light_position[] = { 5.0, 5.0, 5.0, 1.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);;
	glEnable(GL_DEPTH_TEST);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix(); //main push

	glRotatef((GLfloat)x_rotation, 1, 0, 0);
	glRotatef((GLfloat)y_rotation, 0, 1, 0);
	glRotatef((GLfloat)z_rotation, 0, 0, 1);
	glTranslatef(0, 0, 0);
	glScalef(4, 2, 3);
	drawDECube();
	
	
	//head
	glPushMatrix();
	glTranslatef(0, 1.5, 0);
	glScalef(1.1, 1, 1.1 );
	drawDECube();
	glPopMatrix();

	//otherhead
	glPushMatrix();
	glTranslatef(1, 1.5, 0);
	glScalef(0.2, 1, 1);
	drawDECube();
	glPopMatrix();


	glPopMatrix(); /// main pop

	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glNormal3f(-6, -1.1, -6);
	glVertex3f(-6, -1.1, -6);
	glVertex3f(-6, -1.1, 6);
	glVertex3f(6, -1.1, 6);
	glVertex3f(6, -1.1, -6);
	glEnd();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); //clear the main matrix
	gluLookAt(8, 8, 8, 0, 0, 0, 0, 1, 0);
}



void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'x':
		x_rotation++;
		// y_rotation = 0;
		glutPostRedisplay();
		break;
	case 'y':
		y_rotation++;
		//x_rotation = 0;
		glutPostRedisplay();
		break;

	case 'z':
		z_rotation++;
		//x_rotation = 0;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Bank of Guyana - Assingment 4");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
