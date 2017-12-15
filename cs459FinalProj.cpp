
////////////////////////////////////////////////////////
// Lab Exercise 06.cpp
// Uses glutTimerFunc() to smoothly start and stop animation
// Design: Reihaneh Rostami - The idea was adopted from
//Dr. Ichiro Suzuki's lab exercise 
///////////////////////////////////////////////////////


#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h> // for Sleep() 
#include <math.h> // for sin() and cos()
#include "funfunfunction.h"

static GLfloat angle1 = 0.0, angle2 = 0.0, angle3 = 0.0;

static boolean orb3 = true;
static boolean orb2 = true;
static boolean orb1 = true;
static boolean lPos = false;
static boolean on = true;
static int col0 = 0;
static int col1 = 0;
static int col2 = 0;
static float speed = 1.3;
static GLint flag = 0;//used for color change
static GLfloat position[] = {0.0, 0.0, 0.0, 1.0};
static GLdouble cpos[]    = {0.0, 10.0, 200.0};
static GLfloat none[]     = {0.0, 0.0, 0.0, 1.0};
static GLfloat white[]    = {1.0, 1.0, 1.0, 1.0};
static GLfloat red[]     = {1.0, 0.0, 0.0, 1.0}; 
static GLfloat green[]    = {0.0, 1.0, 0.0, 1.0};
static GLfloat orange[]      = {1.0, 0.5, 0.0, 1.0};
static GLfloat blue[]      = {0.0, 0.0, 1.0, 1.0};
static GLfloat yellow[]      = {1.0, 1.0, 0.0, 1.0};
static GLfloat purple[]      = {1.0, 0.0, 1.0, 1.0};

static GLint numVertices,numPolygons,numEdges;
static GLfloat **vdata;   //array for vertex data
static GLuint **pdata;    //array for polygon data (vertex indices)
static GLuint *psize;     //array for polygon size
static GLfloat **normals; //array for polygon normals
static GLfloat **cdata;//array for polygon color
static const GLfloat PI = 3.1415;
void writemessage()
{
	printf("\n\
		   lab exercise 06 By Your Name\n\
		   left mouse bottom --------- start animation\n\
		   right mouse button -------- stop animation\n\
		   w ------------------------- wireframe/fill toggle\n\
		   ESC ----------------------- exit\n\
		   \n");
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(8.0, (GLfloat) w / (GLfloat) h, 1.0, 250.0);
}
void drawOrbit(float radius) 
{
	glBegin(GL_LINE_LOOP);
	for(int i=0;i<360;i++)
	{
		float degInRad = i * (PI/180);
		glVertex3f(cos(degInRad)*radius,0,sin(degInRad)*radius);
	}
	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cpos[0], cpos[1], cpos[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	/*######################################     MIDDLE STATIONARY OBJECT	 ######################################*/
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, none);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
	for( int i = 0; i < numPolygons; ++i)
	{
		glNormal3fv(normals[i]);
        
		if (flag == 1 )
		{
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cdata[i]);
		}
        
		glBegin(GL_POLYGON);
        
		for ( int j = 0; j < psize[i]; ++j)
		{
			glVertex3f(vdata[pdata[i][j]][0]*2.5,vdata[pdata[i][j]][1]*2.5,vdata[pdata[i][j]][2]*2.5);
		}
        
		glEnd();
	}     // draw the cube at the center

	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, none);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blue);

	/*######################################      RIGHT STATIONARY OBJECT ######################################*/
	
	glTranslatef(7,0,0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, none);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
	for( int i = 0; i < numPolygons; ++i)
	{
		glNormal3fv(normals[i]);
        
		if (flag == 1 )
		{
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cdata[i]);
		}
        
		glBegin(GL_POLYGON);
        
		for ( int j = 0; j < psize[i]; ++j)
		{
			glVertex3f(vdata[pdata[i][j]][0]*2.0,vdata[pdata[i][j]][1]*2.0,vdata[pdata[i][j]][2]*2.0);
		}
        
		glEnd();
	}
	glTranslatef(-7,0,0);


	/*######################################      LEFT STATIONARY OBJECT ######################################*/
	
	glTranslatef(-7,0,0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, none);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
	for( int i = 0; i < numPolygons; ++i)
	{
		glNormal3fv(normals[i]);
        
		if (flag == 1 )
		{
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cdata[i]);
		}
        
		glBegin(GL_POLYGON);
        
		for ( int j = 0; j < psize[i]; ++j)
		{
			glVertex3f(vdata[pdata[i][j]][0]*2.0,vdata[pdata[i][j]][1]*2.0,vdata[pdata[i][j]][2]*2.0);
		}
        
		glEnd();
	}
	glTranslatef(7,0,0);

	/*######################################      INNER LEFT STATIONARY OBJECT ######################################*/
	
	glTranslatef(-15,0,0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, none);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
	for( int i = 0; i < numPolygons; ++i)
	{
		glNormal3fv(normals[i]);
        
		if (flag == 1 )
		{
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cdata[i]);
		}
        
		glBegin(GL_POLYGON);
        
		for ( int j = 0; j < psize[i]; ++j)
		{
			glVertex3f(vdata[pdata[i][j]][0]*2.7,vdata[pdata[i][j]][1]*2.7,vdata[pdata[i][j]][2]*2.7);
		}
        
		glEnd();
	}
	glTranslatef(15,0,0);

	/*######################################      INNER RIGHT STATIONARY OBJECT ######################################*/
	
	glTranslatef(15,0,0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, none);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
	for( int i = 0; i < numPolygons; ++i)
	{
		glNormal3fv(normals[i]);
        
		if (flag == 1 )
		{
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cdata[i]);
		}
        
		glBegin(GL_POLYGON);
        
		for ( int j = 0; j < psize[i]; ++j)
		{
			glVertex3f(vdata[pdata[i][j]][0]*2.7,vdata[pdata[i][j]][1]*2.7,vdata[pdata[i][j]][2]*2.7);
		}
        
		glEnd();
	}
	glTranslatef(-15,0,0);

	/*######################################      OUTER-ORBIT	 ######################################*/
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, green); 
	drawOrbit(21);

	
	glRotatef(angle3,0,1,0); 
	

	glTranslatef(21,0,0); 
	glLightfv(GL_LIGHT2, GL_POSITION, position);
	
	if(lPos)
	{
		glutSolidCube(1);
	}
	glPopMatrix(); 

	/*######################################      MIDDLE-ORBIT	 ######################################*/
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, green); 
	drawOrbit(12); 

	
	glRotatef(angle2,0,1,0); 
	

	glTranslatef(12,0,0); 
	glLightfv(GL_LIGHT1, GL_POSITION, position);
	
	if(lPos)
	{
		glutSolidCube(1);
	}
	glPopMatrix(); 
	
	/*######################################     INNER RIGHT ORBIT 	 ######################################*/
	glPopMatrix();

	glPushMatrix();
	glRotatef(30,0,0,1);	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, green); 
	drawOrbit(4); 

	
	glRotatef(angle1,0,1,0); 
	
	glTranslatef(4,0,0); 
	if(lPos)
	{
		glutSolidCube(1);
	}
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glPopMatrix();
	/*######################################     INNER LEFT ORBIT 	 ######################################*/

	
	glPushMatrix();
	glRotatef(-30,0,0,1);	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, green); 
	drawOrbit(4); 


	glRotatef(angle1,0,1,0); 
	
	glTranslatef(4,0,0); 
	if(lPos)
	{
		glutSolidCube(1);
	}
	glLightfv(GL_LIGHT4, GL_POSITION, position);
	glPopMatrix();

	/////////////////////////////////////////////////////////////////////////////////////

	glFlush();
	glutSwapBuffers();
}

void animate(void)
{
	if(orb1)
	{
		angle1 = angle1 + speed;
		if (angle1 > 360.0) angle1 = angle1 - 360.0;
	}
	if(orb2)
	{
		angle2 = angle2 + speed;
		if (angle2 > 360.0) angle2 = angle2 - 360.0;
	}
	if(orb3)
	{
		angle3 = angle3 + speed;
		if (angle3 > 360.0) angle3 = angle3 - 360.0; 
	}
	Sleep(10);
	glutPostRedisplay();  
}


void mouse(int button, int state, int x, int y) 
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(animate); 
		break;
	case GLUT_MIDDLE_BUTTON:
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(NULL);
		break;
	default:
		break;
	}
}

void keyboard(unsigned char key, int x, int y)
{
	static int polygonmode[2];

	switch (key) {
	case 'w':
		glGetIntegerv(GL_POLYGON_MODE,polygonmode);
		if (polygonmode[0]==GL_FILL) 
			glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		else glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		glutPostRedisplay();
		break;
	case '3':
		if(orb3 == true)
		{
			orb3 = false;
		}
		else
		{
			orb3 = true;
		}
		glutPostRedisplay();
		break;
	case '2':
		if(orb2 == true)
		{
			orb2 = false;
		}
		else
		{
			orb2 = true;
		}
		glutPostRedisplay();
		break;
	case '1':
		if(orb1 == true)
		{
			orb1 = false;
		}
		else
		{
			orb1 = true;
		}
		glutPostRedisplay();
		break;
	case 't':
		if(lPos == true)
		{
			lPos = false;
		}
		else
		{
			lPos = true;
		}
		glutPostRedisplay();
		break;
	case '!':
		if(col0 == 0)
		{
			glLightfv(GL_LIGHT0,GL_DIFFUSE,red);
			glLightfv(GL_LIGHT0,GL_SPECULAR,red);
			glLightfv(GL_LIGHT4,GL_DIFFUSE,blue);
			glLightfv(GL_LIGHT4,GL_SPECULAR,blue);
			col0++;
		}
		else if(col0 == 1)
		{
			glLightfv(GL_LIGHT0,GL_DIFFUSE,yellow);
			glLightfv(GL_LIGHT0,GL_SPECULAR,yellow);
			glLightfv(GL_LIGHT4,GL_DIFFUSE,red);
			glLightfv(GL_LIGHT4,GL_SPECULAR,red);
			col0++;
		}
		else if (col0 ==2)
		{
			glLightfv(GL_LIGHT0,GL_DIFFUSE,none);
			glLightfv(GL_LIGHT0,GL_SPECULAR,none);
			glLightfv(GL_LIGHT4,GL_DIFFUSE,none);
			glLightfv(GL_LIGHT4,GL_SPECULAR,none);
			col0++;
		}
		else
		{
			glLightfv(GL_LIGHT0,GL_DIFFUSE,blue);
			glLightfv(GL_LIGHT0,GL_SPECULAR,blue);
			glLightfv(GL_LIGHT4,GL_DIFFUSE,yellow);
			glLightfv(GL_LIGHT4,GL_SPECULAR,yellow);
			col0 = 0;
		}
		glutPostRedisplay();
		break;
	case '@':
		if(col1 == 0)
		{
			glLightfv(GL_LIGHT1,GL_DIFFUSE,yellow);
			glLightfv(GL_LIGHT1,GL_SPECULAR,yellow);
			col1++;
		}
		else if(col1 == 1)
		{
			glLightfv(GL_LIGHT1,GL_DIFFUSE,blue);
			glLightfv(GL_LIGHT1,GL_SPECULAR,blue);
			col1++;
		}
		else if (col1 ==2)
		{
			glLightfv(GL_LIGHT1,GL_DIFFUSE,none);
			glLightfv(GL_LIGHT1,GL_SPECULAR,none);
			col1++;
		}
		else
		{
			glLightfv(GL_LIGHT1,GL_DIFFUSE,red);
			glLightfv(GL_LIGHT1,GL_SPECULAR,red);
			col1 = 0;
		}
		glutPostRedisplay();
		break;
	case '#':
		if(col2 == 0)
		{
			glLightfv(GL_LIGHT2,GL_DIFFUSE,green);
			glLightfv(GL_LIGHT2,GL_SPECULAR,green);
			col2++;
		}
		else if(col2 == 1)
		{
			glLightfv(GL_LIGHT2,GL_DIFFUSE,orange);
			glLightfv(GL_LIGHT2,GL_SPECULAR,orange);
			col2++;
		}
		else if (col2 ==2)
		{
			glLightfv(GL_LIGHT2,GL_DIFFUSE,purple);
			glLightfv(GL_LIGHT2,GL_SPECULAR,purple);
			col2++;
		}
		else
		{
			glLightfv(GL_LIGHT2,GL_DIFFUSE,none);
			glLightfv(GL_LIGHT2,GL_SPECULAR,none);
			col2 = 0;
		}
		glutPostRedisplay();
		break;
	case '0':
		if(on == true)
		{
			glLightfv(GL_LIGHT0,GL_DIFFUSE,none);
			glLightfv(GL_LIGHT0,GL_SPECULAR,none);
			glLightfv(GL_LIGHT1,GL_DIFFUSE,none);
			glLightfv(GL_LIGHT1,GL_SPECULAR,none);
			glLightfv(GL_LIGHT2,GL_DIFFUSE,none);
			glLightfv(GL_LIGHT2,GL_SPECULAR,none);
			glLightfv(GL_LIGHT4,GL_DIFFUSE,none);
			glLightfv(GL_LIGHT4,GL_SPECULAR,none);

			on = false;
		}
		else
		{
			glLightfv(GL_LIGHT0,GL_DIFFUSE,blue);
			glLightfv(GL_LIGHT0,GL_SPECULAR,blue);
			glLightfv(GL_LIGHT1,GL_DIFFUSE,red);
			glLightfv(GL_LIGHT1,GL_SPECULAR,red);
			glLightfv(GL_LIGHT2,GL_DIFFUSE,red);
			glLightfv(GL_LIGHT2,GL_SPECULAR,red);
			glLightfv(GL_LIGHT4,GL_DIFFUSE,yellow);
			glLightfv(GL_LIGHT4,GL_SPECULAR,yellow);

			on = true;
		}
		glutPostRedisplay();
		break;
	case '+':
		if(speed+.3 >=12)
		{
			speed = 12;
		}
		else
		{
			speed = speed + .3;
		}
		glutPostRedisplay();
		break;
	case '=':
		if(speed-.3 <= 0)
		{
			speed = 0;
		}
		else
		{
			speed = speed - .3;
		}

		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1200, 800); 
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Jason Klein - CS459 - Final Project");

	glClearColor(0.5, 0.5, 0.5, 0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,blue);
	glLightfv(GL_LIGHT0,GL_SPECULAR,blue);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1,GL_DIFFUSE,red);
	glLightfv(GL_LIGHT1,GL_SPECULAR,red);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);

	glLightfv(GL_LIGHT2,GL_DIFFUSE,none);
	glLightfv(GL_LIGHT2,GL_SPECULAR,none);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT2);

	glLightfv(GL_LIGHT3,GL_DIFFUSE,none);
	glLightfv(GL_LIGHT3,GL_SPECULAR,none);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT3);

	glLightfv(GL_LIGHT4,GL_DIFFUSE,yellow);
	glLightfv(GL_LIGHT4,GL_SPECULAR,yellow);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT4);

	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	writemessage();

	readOFF();
    calculateNormal();
    setRandomColor();
	glutMainLoop();
	return 0;
}


void readOFF()//method to read .off format data. Borrowed partially form Dr. Zeyun Yu homework
//modified further to read polygons of any size
//nonconvex and nonflat polygons may not be rendered correctly
{
    int n,j;
    int a,b;
    float x,y,z;
    float resize;
    char line[256];
    
    FILE* fin;
    char filename[FILENAME_MAX];
    
    fin = NULL;
    while (fin == NULL) {
        printf("\n\nEnter an .off file name including extension (or press Enter to abort): ");
        int result=scanf("%99[^\n]%*c",filename);
        if(result!=1) exit(0);
        fin =  fopen(filename,"rb");
    };
    
    /* OFF format */
    while (fgets(line,256,fin) != NULL) {
        if (line[0]=='O' && line[1]=='F' && line[2]=='F')
            break;
    }
    fscanf(fin,"%d %d %d\n",&numVertices,&numPolygons,&numEdges);
    
    printf("Number of vertices  = %d\n",numVertices);
    printf("Number of polygons = %d\n",numPolygons);
    printf("Number of edges = %d\n",numEdges);
    printf("loading vedrtices and polygons... ");
    
    vdata=new GLfloat*[numVertices];
    for(int i=0;i<numVertices;i++)
        vdata[i]=new GLfloat[3];
    
    pdata=new GLuint*[numPolygons]; //array for storing polygon data (vertex indices)
    psize=new GLuint[numPolygons];  //array for storing polygon size
    
    resize = 0.0001;
    for (n = 0; n < numVertices; n++) { //read vertex data
        fscanf(fin,"%f %f %f\n",&x,&y,&z);
        vdata[n][0] = x;
        resize = max(resize,fabs(x));
        vdata[n][1] = y;
        resize = max(resize,fabs(y));
        vdata[n][2] = z;
        resize = max(resize,fabs(z));
    }
    
    for (n = 0; n < numVertices; n++) { //adjust vertex data
        vdata[n][0] = vdata[n][0]/resize;
        vdata[n][1] = vdata[n][1]/resize;
        vdata[n][2] = vdata[n][2]/resize;
    }
    
    for (n = 0; n < numPolygons; n++) {
        fscanf(fin,"%d",&a);
        psize[n] = a;  //store n-th polygon size in psize[n]
        pdata[n]=new GLuint[a];
        for (j = 0; j < a; j++) { //read and save vertices of n-th polygon
            fscanf(fin,"%d",&b);
            pdata[n][j] = b;
        }
    }
    fclose(fin);
    printf("done.\n");
    
}

void calculateNormal()//calculates the normal vector for every polygon
//using the first three vertices, assuming they occur in ccw order
{
    normals=new GLfloat*[numPolygons];
    for(int i=0;i<numPolygons;i++)
        normals[i]=new GLfloat[3];
    
    for(int i=0;i<numPolygons;i++){
        
        GLint t1=pdata[i][0],t2=pdata[i][1],t3=pdata[i][2];
        GLfloat v1[3]={vdata[t1][0],vdata[t1][1],vdata[t1][2]};
        GLfloat v2[3]={vdata[t2][0],vdata[t2][1],vdata[t2][2]};
        GLfloat v3[3]={vdata[t3][0],vdata[t3][1],vdata[t3][2]};
        
        GLfloat n1[3] = {v2[0] - v1[0],v2[1] - v1[1],v2[2] - v1[2]};
        GLfloat n2[3] = {v3[0] - v1[0],v3[1] - v1[1],v3[2] - v1[2]};
        
        float    normx = (n1[1] * n2[2]) - (n2[1] * n1[2]),
        normy = (n1[2] * n2[0]) - (n2[2] * n1[0]),
        normz = (n1[0] * n2[1]) - (n2[0] * n1[1]);
        
        float factor = sqrt(pow(normx,2) + pow(normy,2) + pow(normz,2));
        normx /= factor;
        normy /= factor;
        normz /= factor;
        normals[i][0]=normx;
        normals[i][1]=normy;
        normals[i][2]=normz;
        //---------------------------------------------------------------------
        
    }
}

void setRandomColor(){
    cdata=new GLfloat*[numPolygons];
    for(int i=0;i<numPolygons;i++)
        cdata[i]=new GLfloat[4];
    
    //%%%%%%%%%%%%%%%%%%%%%%%% STEP 2
    //call "rand()" to generate an integer number between 0 and RAND_MAX
    // scale the number to [0,1]
    //assign random numbers to r, g, and b channels of the "cdata" array
    //cdata is a 2D array with "numPolygons" number of rows and 4 columns. Make sure that the last column is always 1.0
    
    
    for (int i = 0; i < numPolygons; ++i)
    {
        cdata[i][0] = rand()/double(RAND_MAX);
        cdata[i][1] = rand()/double(RAND_MAX);
        cdata[i][2] = rand()/double(RAND_MAX);
        cdata[i][3] = 1.0;
        
    }
}