#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <math.h>
#include<bits/stdc++.h>
# define M_PI 3.14159
using namespace std;

GLUquadric *quad;
double Txval=0,Tyval=0,Tzval=0;
double windowHeight=1800, windowWidth=1000;
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0;
GLfloat Exval = -5, Eyval = 0, Ezval = -30;
//GLfloat Exval = -20, Eyval = 5, Ezval = 10;
GLfloat xref = -5, yref = 0, zref = 0;
GLfloat xdir = 0, ydir = 1, zdir = 0;
GLfloat pitch = 0, yaw = 0, roll = 0;
GLfloat dx = 0, dy = 0;
GLfloat l = 0, r = 0, b = 0,t = 0,n = 0;
GLfloat skyDropPos = 0.0;
GLfloat scaleX = 1,scaleY = 1,scaleZ = 1;
unsigned int ID[40];
GLdouble ttx,tty,ttz=0;
const int GWHEEL_RING=1,GWHEEL_TROLLEY=2, GWHEEL_TOP=3;
int gwheel_ring_color=0, gwheel_trolley_color=0;

GLboolean bRotate = false, uRotate = false, chk = false,chkw = false,chkww = false,skyDropFlag = false, upFlag = true, downFlag1 = true,downFlag2 = false, downFlag3 = false;
GLboolean bR = false,fan_rotate = false,light_0_on = false, light_1_on = false, light_2_on = false,light_3_on = false, fr_on = false, fr_don = false;
GLboolean amb_light = true, dif_light = true, spec_light = true;
GLboolean swing_rotate = false,vm = false;
GLfloat spin = 0, spinw = 0, spins = 0,spind = 0,vm_door = 0;

static GLfloat cube_ordinates[8][3] =
{
    {0.0, 0.0, 0.0},
    {1.0, 0.0, 0.0},
    {1.0, 1.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 0.0, -1.0},
    {1.0, 0.0, -1.0},
    {1.0, 1.0, -1.0},
    {0.0, 1.0, -1.0}

//    {0.0, 0.0, 0.0}, //0
//    {0.0, 0.0, 3.0}, //1
//    {3.0, 0.0, 3.0}, //2
//    {3.0, 0.0, 0.0}, //3
//    {0.0, 3.0, 0.0}, //4
//    {0.0, 3.0, 3.0}, //5
//    {3.0, 3.0, 3.0}, //6
//    {3.0, 3.0, 0.0}  //7
};

static GLubyte quadIndices[6][4] =
{
    {0, 1, 2, 3},
    {1, 5, 6, 2},
    {3, 2, 6, 7},
    {7, 6, 5, 4},
    {4, 5, 1, 0},
    {7, 4, 0, 3}

//    {0,2,3,1},
//    {0,2,6,4},
//    {2,3,7,6},
//    {1,3,7,5},
//    {1,5,4,0},
//    {6,7,5,4}
};
static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}
void drawcube(GLfloat r, GLfloat g, GLfloat b)// GLfloat a,GLfloat c,GLfloat d,GLfloat e,GLfloat f,GLfloat h,GLfloat j,GLfloat k)
{
    //glColor3f(r,g,b);
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};
    //GLfloat mat_em[] = {1.0,1.0,1.0,1.0};
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    //if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    //else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(cube_ordinates[quadIndices[i][0]][0], cube_ordinates[quadIndices[i][0]][1], cube_ordinates[quadIndices[i][0]][2],
                    cube_ordinates[quadIndices[i][1]][0], cube_ordinates[quadIndices[i][1]][1], cube_ordinates[quadIndices[i][1]][2],
                    cube_ordinates[quadIndices[i][2]][0], cube_ordinates[quadIndices[i][2]][1], cube_ordinates[quadIndices[i][2]][2]);

        glVertex3fv(&cube_ordinates[quadIndices[i][0]][0]);glTexCoord2f(1,1);
        glVertex3fv(&cube_ordinates[quadIndices[i][1]][0]);glTexCoord2f(1,0);
        glVertex3fv(&cube_ordinates[quadIndices[i][2]][0]);glTexCoord2f(0,0);
        glVertex3fv(&cube_ordinates[quadIndices[i][3]][0]);glTexCoord2f(0,1);
    }
//    for (GLint i = 0; i <6; i++)
//    {
//        //glColor3f(colors[4][0],colors[4][1],colors[4][2]);
//        getNormal3p(cube_ordinates[quadIndices[i][0]][0], cube_ordinates[quadIndices[i][0]][1], cube_ordinates[quadIndices[i][0]][2],
//                    cube_ordinates[quadIndices[i][1]][0], cube_ordinates[quadIndices[i][1]][1], cube_ordinates[quadIndices[i][1]][2],
//                    cube_ordinates[quadIndices[i][2]][0], cube_ordinates[quadIndices[i][2]][1], cube_ordinates[quadIndices[i][2]][2]);
//
//        glVertex3fv(&cube_ordinates[quadIndices[i][0]][0]);glTexCoord2f(a,c);
//        glVertex3fv(&cube_ordinates[quadIndices[i][1]][0]);glTexCoord2f(d,e);
//        glVertex3fv(&cube_ordinates[quadIndices[i][2]][0]);glTexCoord2f(f,h);
//        glVertex3fv(&cube_ordinates[quadIndices[i][3]][0]);glTexCoord2f(j,k);
//    }
    glEnd();
}
static GLfloat cube_ordinates1[8][3] =
        {
                {0.0, 0.0, 0.0}, //0
                {0.0, 0.0, 3.0}, //1
                {3.0, 0.0, 3.0}, //2
                {3.0, 0.0, 0.0}, //3
                {0.0, 3.0, 0.0}, //4
                {0.0, 3.0, 3.0}, //5
                {3.0, 3.0, 3.0}, //6
                {3.0, 3.0, 0.0}  //7
        };

static GLubyte quadIndices1[6][4] =
        {
                {0, 1, 2, 3}, //bottom
                {4, 5, 6, 7}, //top
                {5, 1, 2, 6}, //front
                {3, 7, 4, 0}, // back
                {2, 3, 7, 6}, //right
                {0, 4, 5,1}  //left
        };

void drawCube1(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX=0, GLfloat ambY=0, GLfloat ambZ=0, GLfloat shine=50)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glBegin(GL_QUADS);

    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(cube_ordinates1[quadIndices1[i][0]][0], cube_ordinates1[quadIndices1[i][0]][1], cube_ordinates1[quadIndices1[i][0]][2],
                    cube_ordinates1[quadIndices1[i][1]][0], cube_ordinates1[quadIndices1[i][1]][1], cube_ordinates1[quadIndices1[i][1]][2],
                    cube_ordinates1[quadIndices1[i][2]][0], cube_ordinates1[quadIndices1[i][2]][1], cube_ordinates1[quadIndices1[i][2]][2]);
        glVertex3fv(&cube_ordinates1[quadIndices1[i][0]][0]);
        glVertex3fv(&cube_ordinates1[quadIndices1[i][1]][0]);
        glVertex3fv(&cube_ordinates1[quadIndices1[i][2]][0]);
        glVertex3fv(&cube_ordinates1[quadIndices1[i][3]][0]);
    }
    glEnd();
}
void LoadBMP(const char *fileName,GLuint num)
{
	FILE *file;
	unsigned char header[54],*data;
	unsigned int dataPos,size,width, height;
	file = fopen(fileName, "rb");
	fread(header, 1, 54, file);				//Windows BMP begin with 54 byte header
	dataPos		= *(int*)&(header[0x0A]);	//dec10, Actual BMP data
	size		= *(int*)&(header[0x22]);	//dec34, BMP Size
	width		= *(int*)&(header[0x12]);	//dec18, Image Width
	height		= *(int*)&(header[0x16]);	//dec22, Image Height
	if (size == NULL)
		size = width * height * 3;
	if (dataPos == NULL)
		dataPos = 54;
	data = new unsigned char[size];
	fread(data, 1, size, file);
	fclose(file);
	//GLuint texture;
	glGenTextures(1, &ID[num]);				//Generate (allocate) 1 texture name
	glBindTexture(GL_TEXTURE_2D, ID[num]);	//Bind the 2D texture



	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	//MAG filter
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	//MIN filter

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data); //target, level, internalFormat, width, height,border, format, type, data
	//return texture;
}

void light(double x, double y, double z, GLenum L, bool light_on, bool spot)
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]  = { 0.6, 0.6, 0.6, 1.0 };
    GLfloat light_specular[] = { 0.6, 0.6, 0.6, 1.0 };
    GLfloat light_position[] = { x, y, z, 1.0 };

    glEnable(L);

    if(light_on){
        if(amb_light) glLightfv( L, GL_AMBIENT, light_ambient);
        else glLightfv( L, GL_AMBIENT, no_light);

        if(dif_light) glLightfv( L, GL_DIFFUSE, light_diffuse);
        else glLightfv( L, GL_DIFFUSE, no_light);

        if(spec_light) glLightfv( L, GL_SPECULAR, light_specular);
        else glLightfv( L, GL_SPECULAR, no_light);

        glLightfv( L, GL_POSITION, light_position);
    }

    else{
        glLightfv( L, GL_AMBIENT, no_light);
        glLightfv( L, GL_DIFFUSE, no_light);
        glLightfv( L, GL_SPECULAR, no_light);
        glLightfv( L, GL_POSITION, no_light);
    }

    if(spot){
        GLfloat spot_direction[] = { -1.0, 0.0, 0.0 };
        glLightfv(L, GL_SPOT_DIRECTION, spot_direction);
        glLightf( L, GL_SPOT_CUTOFF, 55);
    }

}
void ground2()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, 3);

    glPushMatrix();
    //materialProperty1();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1,-1.9,1);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1,-1.8,-1);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1,-1.8,-1);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1,-1.8,1);
    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}
void materialProperty(GLfloat r,GLfloat g,GLfloat b)
{
    //glColor3f(1,1,1);
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}
void materialProperty1()
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}
void ground()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,32);
    glPushMatrix();
    //glTranslatef(ttx,0,ttz);
    glTranslatef(-20,-5,2);
    //glScalef(50,0.01,50);
    glScalef(40,0.01,30);
    drawcube(0.2,1.0,0.2);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void gate()
{
    glPushMatrix();
    glTranslatef(-0.1,0,-4.5);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    //glTranslatef(0,0.2,0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    materialProperty(1.0,1.0,0.0);
    gluCylinder(quadratic,0.1,0.1,1.8,32,32);
    glPopMatrix();
    glDeleteTextures(1, &ID[1]);

    glPushMatrix();
    glTranslatef(1.0,0,0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    materialProperty(1.0,1.0,0.0);
    gluCylinder(quadratic,0.1,0.1,1.8,32,32);

    glPushMatrix();
    glTranslatef(-0.9,0.0,0.5);
    glScalef(0.8,0.2,0.5);
    drawcube(0.5,0.0,0.5);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}
void shooting_range()
{
    glPushMatrix();
    glTranslatef(-1.0,-1.5,-0.3);
    glScalef(0.7,0.5,0.3);
    drawcube(1.0,0.7,1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1,-1.0,-0.3);
    glScalef(0.7,0.5,0.3);
    drawcube(1.0,0.7,0.7);
    glPopMatrix();
}
void chair()
{
    glPushMatrix();
        glPushMatrix();
        glScalef(0.3,0.1,0.5);
        drawcube(0.3,0.7,0.5);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,0.4,0);
        glRotatef(-90,0,0,1);
        glScalef(0.3,0.1,0.5);
        drawcube(0.5,0.7,0.5);
        glPopMatrix();

        glPushMatrix();
        glScalef(0.3,0.2,0.1);
        drawcube(0.5,0.7,0.5);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,0,-0.4);
        glScalef(0.3,0.2,0.1);
        drawcube(0.5,0.7,0.5);
        glPopMatrix();
    glPopMatrix();
}
void ride1()
{
    glPushMatrix();
    glTranslatef(0,0.9,0);
    glScalef(1.0,0.3,1.0);
    materialProperty(1.0,1.0,1.0);
    glutSolidSphere(0.5,10,10);
    glPopMatrix();

    glPushMatrix();
    quad = gluNewQuadric();
    glTranslatef(0,0.8,0);
    glRotatef(90,1,0,0);
    materialProperty(1.0,1.0,1.0);
    gluCylinder(quad,0.25,0.25,3,10,10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-0.4,0);
    //glScalef(0.3,0.5,0.5);
    ground2();
    glPopMatrix();

    ///cones shuru
    ///rotation
    glPushMatrix();
    glTranslatef(0,0.6,0.2);
    glRotatef(spin,0,1,0);
    glTranslatef(0,-0.6,-0.2);

    glPushMatrix();
    glTranslatef(0,-0.1,-0.1);
    glPushMatrix();
    glTranslatef(0,1.5,0);
    materialProperty(0.5,0.5,1.0);
    glutSolidCone(0.5,2.0,4,12);
    glPopMatrix();

    for(float i = -0.5,j=90,k=0.5;i<1.0;i+=0.5,j+=90,k-=0.5)
        {
            glPushMatrix();
            if( k == 0){
                glTranslatef(0,1.5,0.5);
            }
            else if(i!= 0.5){
                glTranslatef(i+0.5,1.5,k-0.1);
            }
            else if(i == 0.5){
                glTranslatef(i-0.5,1.5,k+0.9);
            }
            glRotatef(-j,0,1,0);
            materialProperty(0.5,0.5,1.0);
            glutSolidCone(0.5,2.0,4,12);
            glPopMatrix();
        }
    //glPopMatrix();
    //cones shesh

    //ropes
    glPushMatrix();

    glPushMatrix();
    quad = gluNewQuadric();
    glTranslatef(0,-0.5,-0.5);
    glRotatef(-90,1,0,0);
    materialProperty(0.2,0.5,0.5);
    gluCylinder(quad,0.01,0.01,2.0,10,20);
    glPopMatrix();

    glPushMatrix();
    quad = gluNewQuadric();
    glTranslatef(0,-0.5,-1.0);
    glRotatef(-90,1,0,0);
    materialProperty(0.2,0.5,0.5);
    gluCylinder(quad,0.01,0.01,2.0,10,20);
    glPopMatrix();
        for(float i = -0.5,j=90,k=0.5;i<1.0;i+=0.5,j+=90,k-=0.5)
        {
            glPushMatrix();
            if( k == 0){
                glTranslatef(0,-0.5,0.5);
            }
            else if(i!= 0.5){
                glTranslatef(i+0.5,-0.5,k-0.1);
            }
            else if(i == 0.5){
                glTranslatef(i-0.5,-0.5,k+0.9);
            }
            glRotatef(-j,0,1,0);
            quad = gluNewQuadric();
            glTranslatef(0,0,-0.5);
            glRotatef(-90,1,0,0);
            materialProperty(0.2,0.5,0.5);
            gluCylinder(quad,0.01,0.01,2.0,10,20);
            glPopMatrix();
        }

        for(float i = -0.5,j=90,k=0.5;i<1.0;i+=0.5,j+=90,k-=0.5)
        {
            glPushMatrix();
            if( k == 0){
                glTranslatef(0,-0.5,1.5);
            }
            else if(i!= 0.5){
                glTranslatef(i+1.5,-0.5,k-0.1);
            }
            else if(i == 0.5){
                glTranslatef(i-1.5,-0.5,k+0.9);
            }
            glRotatef(-j,0,1,0);
            quad = gluNewQuadric();
            glRotatef(-90,1,0,0);
            materialProperty(0.2,0.5,0.5);
            gluCylinder(quad,0.01,0.01,2.0,10,20);
            glPopMatrix();
        }

    glPopMatrix();
    //ropes shesh

    //chairs
    ///1st
    glPushMatrix();
        glTranslatef(-0.5,-0.8,0.4);
        //glTranslatef(ttx,ttz,0.4);
        glRotatef(90,0,1,0);
        chair();
    glPopMatrix();
    ///1shesh
    ///2nd
    glPushMatrix();
        glTranslatef(1.0,-0.8,0.3);
        glRotatef(90,0,1,0);
        chair();
    glPopMatrix();
    ///2shesh
    ///3rd
    glPushMatrix();
        glTranslatef(0,-0.8,0.9);
        glRotatef(180,0,1,0);
        chair();
    glPopMatrix();
    ///3shesh
    ///4th
    glPushMatrix();
        glTranslatef(0,-0.8,-0.6);
        //glRotatef(90,0,1,0);
        chair();
    glPopMatrix();
    ///4shesh
///chairs shesh
    glPopMatrix();
}

void drawCylinder(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine=90)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    gluCylinder(quadratic, 1.5, 1.5, 19, 32, 32);

}
void ground_skydrop()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, 3);

    glPushMatrix();
    //materialProperty1();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(10,-19.8,10);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(10,-19.8,-10);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-10,-19.8,-10);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-10,-19.8,10);
    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}
void skyDropStructure()
{
    for(float i = 0; i<=90; i+=2.8)
    {
        glPushMatrix();
        glTranslatef(0, i, 0);
        glScalef(0.1, 0.1, -1.5);
        drawCube1(1, 0, 0, 0.5,0,0);
        glPopMatrix();
    }

    for(float i = 0; i<=87.2; i+=2.8)
    {
        glPushMatrix();
        glTranslatef(0, i, 0);
        glRotatef(32, 1, 0, 0);
        glScalef(0.1, 0.1, -1.8);
        drawCube1(1, 0, 0, 0.5,0,0);
        glPopMatrix();
    }


    for(float i = 2.8; i<=90; i+=2.8)
    {
        glPushMatrix();
        glTranslatef(0, i, 0);
        glRotatef(-32, 1, 0, 0);
        glScalef(0.1, 0.1, -1.8);
        drawCube1(1, 0, 0, 0.5,0,0);
        glPopMatrix();
    }
}

void skyDropSeat()
{
    glPushMatrix();
    glTranslatef(-6, 3.2, 1);

    glPushMatrix();
    glScalef(6, 1.8, 0.2);
    drawCube1(1,0.5,1, 0.5,0.5,0);
    glPopMatrix();

    glPushMatrix();
    glScalef(6, 0.2, 1.2);
    drawCube1(1,1,0, 0.5,0.5,0.5);
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5, 2, 0);
    glScalef(2.2, 0.4, 0.5);
    drawCube1(1,0,1, 0.5,0.5,0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5, 0.5, 0);
    glScalef(0.3, 3, 0.5);
    drawCube1(0,0,1, 0,0.5,0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5.2, 0.5, 0);
    glScalef(0.3, 3, 0.5);
    drawCube1(0,0,1, 0,0.5,0.5);
    glPopMatrix();

    for(float i = -5.5; i<= 13; i+=2.1)
    {
        glPushMatrix();
        glTranslatef(i, 8, 1.5);
        glRotatef(25, 1, 0, 0);
        glScalef(0.1, 0.1, 0.15);
        drawCylinder(0.412, 0.412, 0.412, 0.2, 0.2, 0.2);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(i, 6.8, 4);
        glRotatef(90, 1, 0, 0);
        glScalef(0.1, 0.1, 0.19);
        drawCylinder(0.412, 0.412, 0.412, 0.2, 0.2, 0.2);
        glPopMatrix();
    }
}

void skyDropTexture()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, 2);
    glPushMatrix();
    materialProperty1();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0,0,0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(2,0,0);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(2,20,0);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0,20,0);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void skyDropLogo()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, ID[1]);
    glPushMatrix();
    materialProperty1();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0,0,0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(3,0,0);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(3,5,0);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0,5,0);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void skyDrop()
{
    for(float i = 0; i <=5; i+=5)
    {
        glPushMatrix();
        glTranslatef(i, 0, 0);
        glScalef(0.2, 30, 0.2);
        drawCube1(0, 0, 1, 0,0,0.5);
        glPopMatrix();
    }

    for(float i = 0; i <=5; i+=5)
    {
        glPushMatrix();
        glTranslatef(i, 0, -5);
        glScalef(0.2, 30, 0.2);
        drawCube1(0, 0, 1, 0,0,0.5);
        glPopMatrix();
    }


    skyDropStructure();

    glPushMatrix();
    glTranslatef(5, 0, 0);
    skyDropStructure();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.7, 0, -5);
    glRotatef(-90, 0, 1, 0);
    skyDropStructure();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, skyDropPos, 0);
    skyDropSeat();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.8, 0, 0);
    glScalef(2, 4.5, 1);
    skyDropTexture();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5, 90, 1);
    glScalef(2.5, 2, 1);
    skyDropLogo();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3, 20, 0);
    ground_skydrop();
    glPopMatrix();
}
//void wheelseat()
//{
//    glPushMatrix();
////    glTranslatef(9,-1.5,0);
////    glRotatef(spinw,0,0,1);
//////    for(int i=0;i<12;i++){
//////    glRotatef(-spinw-(360*i/12)-sin(spinw/10.0)*10.0, 0.0, 0.0, 1.0);
//////    }
////    glTranslatef(-9,1.5,0);
//        ///cone
//        glPushMatrix();
//        glTranslatef(9,-1.2,2.3);
//        glRotatef(90,0,1,0);
//        materialProperty(0.7,0.7,1.0);
//        glutSolidCone(0.4,0.3,20,20);
//        glPopMatrix();
//        ///fence
//        ///right 2 back
//        glPushMatrix();
//        glTranslatef(8.4,-1.1,2.5);
//        glScalef(0.7,0.01,0.05);
//        drawcube(0.6,0.7,1.0);
//        glPopMatrix();
//
//        glPushMatrix();
//        glTranslatef(8.4,-1.0,2.5);
//        glScalef(0.6,0.01,0.05);
//        drawcube(0.7,0.7,1.0);
//        glPopMatrix();
//        ///right 2 front
//        glPushMatrix();
//        glTranslatef(8.4,-1.1,2);
//        glScalef(0.6,0.01,0.05);
//        drawcube(0.7,0.7,1.0);
//        glPopMatrix();
//
//        glPushMatrix();
//        glTranslatef(8.4,-1.0,2);
//        glScalef(0.6,0.01,0.05);
//        drawcube(0.7,0.7,1.0);
//        glPopMatrix();
//        ///left 2 back
//        glPushMatrix();
//        glTranslatef(8.4,-1.3,2.5);
//        glScalef(0.7,0.01,0.05);
//        drawcube(0.6,0.7,1.0);
//        glPopMatrix();
//
//        glPushMatrix();
//        glTranslatef(8.4,-1.4,2.5);
//        glScalef(0.6,0.01,0.05);
//        drawcube(0.7,0.7,1.0);
//        glPopMatrix();
//        ///left 2 front
//        glPushMatrix();
//        glTranslatef(8.4,-1.3,2);
//        glScalef(0.6,0.01,0.05);
//        drawcube(0.7,0.7,1.0);
//        glPopMatrix();
//
//        glPushMatrix();
//        glTranslatef(8.4,-1.4,2);
//        glScalef(0.6,0.01,0.05);
//        drawcube(0.7,0.7,1.0);
//        glPopMatrix();
//        ///back
//        glPushMatrix();
//        glTranslatef(8.4,-1.4,2.2);
//        glScalef(0.6,0.01,0.05);
//        drawcube(0.7,0.7,1.0);
//        glPopMatrix();
//
//        glPushMatrix();
//        glTranslatef(8.4,-1.4,2.3);
//        glScalef(0.6,0.01,0.05);
//        drawcube(0.7,0.7,1.0);
//        glPopMatrix();
//        ///plane
//        glPushMatrix();
//        glTranslatef(8.4,-1.4,2.5);
//        glScalef(0.1,0.5,0.5);
//        drawcube(0.2,0.2,1.0);
//        glPopMatrix();
//        ///chair
//        glPushMatrix();
//        glTranslatef(8.5,-1.3,2.5);
//        glScalef(0.1,0.2,0.5);
//        drawcube(1.0,1.0,1.0);
//        glPopMatrix();
//
//        glPushMatrix();
//        glTranslatef(8.5,-1.3,2.5);
//        glRotatef(-90,0,0,1);
//        glScalef(0.1,0.3,0.5);
//        drawcube(1.0,1.0,1.0);
//        glPopMatrix();
//    glPopMatrix();
//}
//void wheelstructure()
//{
//    glPushMatrix();
////        glTranslatef(6,-1,0);
////        glRotatef(spinw,0,0,1);
////        glTranslatef(-6,1,0);
//        ///cylinder left
//        glPushMatrix();
//        quad = gluNewQuadric();
//        glTranslatef(6,2,2);
//        glRotatef(90,1,0,0);
//        materialProperty(1.0,1.0,0);
//        gluCylinder(quad,0.04,0.04,6,20,100);
//        glPopMatrix();
//        ///cylinder right
//        glPushMatrix();
//        quad = gluNewQuadric();
//        glTranslatef(6,2,2.5);
//        glRotatef(90,1,0,0);
//        materialProperty(1.0,1.0,0);
//        gluCylinder(quad,0.04,0.04,6,20,100);
//        glPopMatrix();
//        ///cylinder up
//        glPushMatrix();
//        quad = gluNewQuadric();
//        glTranslatef(6,2,2);
//        materialProperty(1.0,1.0,0);
//        gluCylinder(quad,0.04,0.04,0.5,20,100);
//        glPopMatrix();
//        ///cylinder bottom
//        glPushMatrix();
//        quad = gluNewQuadric();
//        glTranslatef(6,-4,2);
//        materialProperty(1.0,1.0,0);
//        gluCylinder(quad,0.04,0.04,0.5,20,100);
//        glPopMatrix();
//    glPopMatrix();
//}
//void ferris_wheel()
//{
//    glPushMatrix();
//        ///smaller sphere left
//        glPushMatrix();
//        glTranslatef(6,-1,2);
//        glScalef(0.5,1,0.001);
//        materialProperty(1.0,1.0,0);
//        glutSolidSphere(0.5,100,100);
//        glPopMatrix();
//        ///sphere left
//        glPushMatrix();
//        glTranslatef(6,-1,2);
//        //glScalef(0.5,1,1);
//        materialProperty(1.0,1.0,0);
//        glutSolidTorus(0.10,2.5,5,100);
//        glPopMatrix();
//        ///smaller sphere right
//        glPushMatrix();
//        glTranslatef(6,-1,2.5);
//        glScalef(0.5,1,0.001);
//        materialProperty(1.0,1.0,0);
//        glutSolidSphere(0.5,100,100);
//        glPopMatrix();
//        ///sphere right
//        glPushMatrix();
//        glTranslatef(6,-1,2.5);
//        //glScalef(0.5,1,1);
//        materialProperty(1.0,1.0,0);
//        glutSolidTorus(0.10,2.5,5,100);
//        glPopMatrix();
//        ///cylinder base left
//        glPushMatrix();
//        quad = gluNewQuadric();
//        glTranslatef(6,-0.9,2);
//        glRotatef(-240,1,0,0);
//        materialProperty(1.0,1.0,0);
//        gluCylinder(quad,0.08,0.08,4.6,20,100);
//        glPopMatrix();
//
//        glPushMatrix();
//        glTranslatef(6.2,-3.1,0);
//        glScalef(1,1,0.5);
//        ground2();
//        glPopMatrix();
//        ///cylinder base right
//        glPushMatrix();
//        quad = gluNewQuadric();
//        glTranslatef(6,-0.7,2.5);
//        glRotatef(60,1,0,0);
//        materialProperty(1.0,1.0,0);
//        gluCylinder(quad,0.08,0.08,4.6,20,100);
//        glPopMatrix();
//
//        glPushMatrix();
//        glTranslatef(6,-2.8,4.4);
//        glScalef(1,1,0.5);
//        ground2();
//        glPopMatrix();
//
//        glTranslatef(6,-1,0);
//        glRotatef(spinw,0,0,1);
//        glTranslatef(-6,1,0);
//
//        glPushMatrix();
//        glTranslatef(7.4,-10,-0.2);
//        glRotatef(90,0,0,1);
//        wheelseat();
//        glPopMatrix();
//        glPushMatrix();
//        glTranslatef(1.8,-10,-0.2);
//        glRotatef(90,0,0,1);
//        wheelseat();
//        glPopMatrix();
//        wheelstructure();
//
//        glPushMatrix();
//        glRotatef(90,0,0,1);
//        glTranslatef(-13,-4.8,0);
//        wheelseat();
//        glPopMatrix();
//        glPushMatrix();
//        glRotatef(90,0,0,1);
//        glTranslatef(-7,-4.8,0);
//        wheelseat();
//        wheelstructure();
//        glPopMatrix();
//
//        glPushMatrix();
//        glRotatef(90,0,0,1);
//        glTranslatef(-11.4,-7.4,0);
//        wheelseat();
//        glPopMatrix();
//        glPushMatrix();
//        glRotatef(90,0,0,1);
//        glTranslatef(-8.4,-2.2,0);
//        wheelseat();
//        glPopMatrix();
//        glPushMatrix();
//        glRotatef(60,0,0,1);
//        glTranslatef(-3.8,-4.6,0);
//        wheelstructure();
//        glPopMatrix();
//
//        glPushMatrix();
//        glRotatef(90,0,0,1);
//        glTranslatef(-7.4,-3.4,0);
//        wheelseat();
//        glPopMatrix();
//        glPushMatrix();
//        glRotatef(90,0,0,1);
//        glTranslatef(-12.4,-6.4,0);
//        wheelseat();
//        glPopMatrix();
//        glPushMatrix();
//        glRotatef(30,0,0,1);
//        glTranslatef(-1.2,-2.8,0);
//        wheelstructure();
//        glPopMatrix();
//
//        glPushMatrix();
//        glRotatef(90,0,0,1);
//        glTranslatef(-8.5,-7.3,0);
//        wheelseat();
//        glPopMatrix();
//        glPushMatrix();
//        glRotatef(90,0,0,1);
//        glTranslatef(-11.4,-2,0);
//        wheelseat();
//        glPopMatrix();
//        glPushMatrix();
//        glRotatef(120,0,0,1);
//        glTranslatef(-9.8,-3.6,0);
//        wheelstructure();
//        glPopMatrix();
//
//        glPushMatrix();
//        glRotatef(90,0,0,1);
//        glTranslatef(-7.4,-6.2,0);
//        wheelseat();
//        glPopMatrix();
//        glPushMatrix();
//        glRotatef(90,0,0,1);
//        glTranslatef(-12.6,-3.2,0);
//        wheelseat();
//        glPopMatrix();
//        glPushMatrix();
//        glRotatef(150,0,0,1);
//        glTranslatef(-11.6,-1,0);
//        wheelstructure();
//        glPopMatrix();
//
//    glPopMatrix();
//}

void wheelseat()
{
    glPushMatrix();
    glTranslatef(7+1.8,0-1.3,0);
    glRotatef(spins,0,0,1);
    glTranslatef(-7-1.8,0+1.3,0);
    glPushMatrix();
        ///cone
        glPushMatrix();
            glTranslatef(9,-1.2,2.3);
            glRotatef(90,0,1,0);
            materialProperty(0.7,0.7,1.0);
            glutSolidCone(0.4,0.3,20,20);
        glPopMatrix();
        ///fence
        ///right 2 back
        glPushMatrix();
            glTranslatef(8.4,-1.1,2.5);
            glScalef(0.7,0.01,0.05);
            drawcube(0.6,0.7,1.0);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(8.4,-1.0,2.5);
            glScalef(0.6,0.01,0.05);
            drawcube(0.7,0.7,1.0);
        glPopMatrix();
        ///right 2 front
        glPushMatrix();
            glTranslatef(8.4,-1.1,2);
            glScalef(0.6,0.01,0.05);
            drawcube(0.7,0.7,1.0);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(8.4,-1.0,2);
            glScalef(0.6,0.01,0.05);
            drawcube(0.7,0.7,1.0);
        glPopMatrix();
        ///left 2 back
        glPushMatrix();
            glTranslatef(8.4,-1.3,2.5);
            glScalef(0.7,0.01,0.05);
            drawcube(0.6,0.7,1.0);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(8.4,-1.4,2.5);
            glScalef(0.6,0.01,0.05);
            drawcube(0.7,0.7,1.0);
        glPopMatrix();
        ///left 2 front
        glPushMatrix();
            glTranslatef(8.4,-1.3,2);
            glScalef(0.6,0.01,0.05);
            drawcube(0.7,0.7,1.0);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(8.4,-1.4,2);
            glScalef(0.6,0.01,0.05);
            drawcube(0.7,0.7,1.0);
        glPopMatrix();
        ///back
        glPushMatrix();
            glTranslatef(8.4,-1.4,2.2);
            glScalef(0.6,0.01,0.05);
            drawcube(0.7,0.7,1.0);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(8.4,-1.4,2.3);
            glScalef(0.6,0.01,0.05);
            drawcube(0.7,0.7,1.0);
        glPopMatrix();
        ///plane
        glPushMatrix();
            glTranslatef(8.4,-1.4,2.5);
            glScalef(0.1,0.5,0.5);
            drawcube(0.2,0.2,1.0);
        glPopMatrix();
        ///chair
        glPushMatrix();
            glTranslatef(8.5,-1.3,2.5);
            glScalef(0.1,0.2,0.5);
            drawcube(1.0,1.0,1.0);
        glPopMatrix();
glPushMatrix();
            glTranslatef(8.5,-1.3,2.5);
            glRotatef(-90,0,0,1);
            glScalef(0.1,0.3,0.5);
            drawcube(1.0,1.0,1.0);
        glPopMatrix();
    glPopMatrix();
    glPopMatrix();
}
void wheelstructure()
{
    glPushMatrix();
//        glTranslatef(6,-1,0);
//        glRotatef(spinw,0,0,1);
//        glTranslatef(-6,1,0);
        ///cylinder left
        glPushMatrix();
        quad = gluNewQuadric();
        glTranslatef(6,2,2);
        glRotatef(90,1,0,0);
        materialProperty(1.0,1.0,0);
        gluCylinder(quad,0.04,0.04,6,20,100);
        glPopMatrix();
        ///cylinder right
        glPushMatrix();
        quad = gluNewQuadric();
        glTranslatef(6,2,2.5);
        glRotatef(90,1,0,0);
        materialProperty(1.0,1.0,0);
        gluCylinder(quad,0.04,0.04,6,20,100);
        glPopMatrix();
        ///cylinder up
        glPushMatrix();
        quad = gluNewQuadric();
        glTranslatef(6,2,2);
        materialProperty(1.0,1.0,0);
        gluCylinder(quad,0.04,0.04,0.5,20,100);
        glPopMatrix();
        ///cylinder bottom
        glPushMatrix();
        quad = gluNewQuadric();
        glTranslatef(6,-4,2);
        materialProperty(1.0,1.0,0);
        gluCylinder(quad,0.04,0.04,0.5,20,100);
        glPopMatrix();
    glPopMatrix();
}
void ferris_wheel()
{
    glTranslatef(0,2.6,0);
    glPushMatrix();
        ///smaller sphere left
        glPushMatrix();
        glTranslatef(6,-1,2);
        glScalef(0.5,1,0.001);
        materialProperty(1.0,1.0,0);
        glutSolidSphere(0.5,100,100);
        glPopMatrix();
        ///sphere left
        glPushMatrix();
        glTranslatef(6,-1,2);
        //glScalef(0.5,1,1);
        materialProperty(1.0,1.0,0);
        glutSolidTorus(0.10,2.5,5,100);
        glPopMatrix();
        ///smaller sphere right
        glPushMatrix();
        glTranslatef(6,-1,2.5);
        glScalef(0.5,1,0.001);
        materialProperty(1.0,1.0,0);
        glutSolidSphere(0.5,100,100);
        glPopMatrix();
        ///sphere right
        glPushMatrix();
        glTranslatef(6,-1,2.5);
        //glScalef(0.5,1,1);
        materialProperty(1.0,1.0,0);
        glutSolidTorus(0.10,2.5,5,100);
        glPopMatrix();
        ///cylinder base left
        glPushMatrix();
        quad = gluNewQuadric();
        glTranslatef(6,-1,2);
        glRotatef(-240,1,0,0);
        materialProperty(1.0,1.0,0);
        gluCylinder(quad,0.08,0.08,4.6,20,100);
        glPopMatrix();
        ///cylinder base right
        glPushMatrix();
        quad = gluNewQuadric();
        glTranslatef(6,-0.8,2.5);
        glRotatef(60,1,0,0);
        materialProperty(1.0,1.0,0);
        gluCylinder(quad,0.08,0.08,4.6,20,100);
        glPopMatrix();

        glTranslatef(6,-1,0);
        glRotatef(spinw,0,0,1);
        glTranslatef(-6,1,0);

        ///seat and structure

    glPushMatrix();
        glPushMatrix();
        ///4.2
            glTranslatef(7.6,-10,-0.2);
            glRotatef(90,0,0,1);
            wheelseat();
        glPopMatrix();

        glPushMatrix();
        ///4.1
            glTranslatef(1.4,-10,-0.2);
            glRotatef(90,0,0,1);
            wheelseat();
        glPopMatrix();

        glPushMatrix();
        ///4
            glTranslatef(4.8,-7,0);
            glRotatef(90,0,0,1);
            wheelstructure();
        glPopMatrix();

        glPushMatrix();
        ///1.1
            glTranslatef(-13+17.8,-7,0);
            glRotatef(90,0,0,1);
            wheelseat();
        glPopMatrix();

        glPushMatrix();
        ///1.2
            glTranslatef(-7+11.8,-13,0);
            glRotatef(90,0,0,1);
            wheelseat();
        glPopMatrix();

        glPushMatrix();
        ///1
            wheelstructure();
        glPopMatrix();


        glPushMatrix();
        ///3.2
            glTranslatef(-11.4+18.8,-11.4,0);
            glRotatef(90,0,0,1);
            wheelseat();
        glPopMatrix();

        glPushMatrix();
        ///3.1
            glTranslatef(-8.4+10.6,-8.4,0);
            glRotatef(90,0,0,1);
            wheelseat();
        glPopMatrix();

        glPushMatrix();
        ///3
            glRotatef(60,0,0,1);
            glTranslatef(-3.8,-4.6,0);
            wheelstructure();
        glPopMatrix();

        glPushMatrix();
        ///2.2
            glTranslatef(3.2,-7.2,0);
            glRotatef(90,0,0,1);
            wheelseat();
        glPopMatrix();

        glPushMatrix();
        ///2.1
            glTranslatef(6.4,-12.4,0);
            glRotatef(90,0,0,1);
            wheelseat();
        glPopMatrix();

        glPushMatrix();
        ///2
            glRotatef(30,0,0,1);
            glTranslatef(-1.2,-2.8,0);
            wheelstructure();
        glPopMatrix();

        glPushMatrix();
        ///5.2
            glTranslatef(2,-11.4,0);
            glRotatef(90,0,0,1);
            wheelseat();
        glPopMatrix();

        glPushMatrix();
        ///5.1
            glTranslatef(7.4,-8.4,0);
            glRotatef(90,0,0,1);
            wheelseat();
        glPopMatrix();

        glPushMatrix();
        ///5
            glRotatef(120,0,0,1);
            glTranslatef(-9.8,-3.6,0);
            wheelstructure();
        glPopMatrix();

        glPushMatrix();
        ///6.2
            glTranslatef(6.2,-7.4,0);
            glRotatef(90,0,0,1);
            wheelseat();
        glPopMatrix();

        glPushMatrix();
        ///6.1
            glTranslatef(3.2,-12.6,0);
            glRotatef(90,0,0,1);
            wheelseat();
        glPopMatrix();

        glPushMatrix();
        ///6
            glRotatef(150,0,0,1);
            glTranslatef(-11.6,-1,0);
            wheelstructure();
        glPopMatrix();
        glPopMatrix();

    glPopMatrix();
}
static GLfloat v_pyramid[6][3] =
{
    {0.0, 0.0, 0.0},
    {2.0, 0.0, 0.0},
    {2.0, 0.0, 2.0},
    {0.0, 0.0, 2.0},
    {1.0, 2.0, 0.0},
    {1.0, 2.0, 2.0}
};

static GLubyte tri_Indices[2][3] =
{
    {0, 4, 1},
    {3, 5, 2}
};

static GLubyte pyramidquadIndices[3][4] =
{
    {0, 1, 2, 3},
    {1, 4, 5, 2},
    {0, 4, 5, 3}
};
static GLfloat colors[5][3] =
{
    {0.0, 0.0, 1.0},
    {0.5, 0.0, 1.0},
    {0.0, 1.0, 0.0},
    {0.0, 1.0, 1.0},
    {0.0, 0.0, 1.0}
};

void drawpyramid()
{
    //glColor3f(1,0,0);
    glBegin(GL_TRIANGLES);
    for (GLint i = 0; i <2; i++)
    {
        getNormal3p(v_pyramid[tri_Indices[i][0]][0], v_pyramid[tri_Indices[i][0]][1], v_pyramid[tri_Indices[i][0]][2],
                    v_pyramid[tri_Indices[i][1]][0], v_pyramid[tri_Indices[i][1]][1], v_pyramid[tri_Indices[i][1]][2],
                    v_pyramid[tri_Indices[i][2]][0], v_pyramid[tri_Indices[i][2]][1], v_pyramid[tri_Indices[i][2]][2]);
        glColor3f(colors[i][0],colors[i][1],colors[i][2]);
        glVertex3fv(&v_pyramid[tri_Indices[i][0]][0]);
        glVertex3fv(&v_pyramid[tri_Indices[i][1]][0]);
        glVertex3fv(&v_pyramid[tri_Indices[i][2]][0]);
    }
    glEnd();

    glBegin(GL_QUADS);
    for (GLint i = 0; i <3; i++)
    {
        glColor3f(colors[4][0],colors[4][1],colors[4][2]);
        glVertex3fv(&v_pyramid[pyramidquadIndices[i][0]][0]);
        glVertex3fv(&v_pyramid[pyramidquadIndices[i][1]][0]);
        glVertex3fv(&v_pyramid[pyramidquadIndices[i][2]][0]);
        glVertex3fv(&v_pyramid[pyramidquadIndices[i][3]][0]);
    }
    glEnd();
}

void veggieshop()
{
      glPushMatrix();
      //glRotatef(45,0,1,0);
      drawpyramid();
      glPopMatrix();
    ///right wall
    glPushMatrix();
    glTranslatef(0.1,-1.8,2);
    glScalef(0.1,2,2);
    drawcube(0.2,0.7,0.2);
    glPopMatrix();
    ///left wall
    glPushMatrix();
    glTranslatef(1.8,-1.8,2);
    glScalef(0.1,2,2);
    drawcube(0.2,0.7,0.2);
    glPopMatrix();
    ///back wall
    glPushMatrix();
    glTranslatef(0.2,-1.8,1.9);
    glRotatef(-90,0,1,0);
    glScalef(0.1,2,1.6);
    drawcube(0.2,0.7,0.2);
    glPopMatrix();
//    ///front wall
//    glPushMatrix();
//    glTranslatef(0.2,-1.8,0);
//    glRotatef(-90,0,1,0);
//    glScalef(0.1,2,1.6);
//    drawcube(0.2,0.7,0.2);
//    glPopMatrix();
    ///floor
    glPushMatrix();
    glTranslatef(1.9,-1.8,1.8);
    glRotatef(90,0,0,1);
    glScalef(0.1,1.8,1.7);
    drawcube(0.2,0.7,0.2);
    glPopMatrix();
}
static GLfloat diamond[7][3] =
{
    {1.0, 1.0, 2.0},
    {0.5, 2.0, 0.0},
    {0.0, 1.0, 0.0},
    {1.0, 0.0, 0.0},
    {2.0, 1.0, 0.0},
    {1.5, 2.0, 0.0},
    {1.0, 1.0, 0.0}
};

static GLubyte dia_Indices[10][3] =
{
    {2, 3, 0},
    {0, 3, 4},
    {0, 1, 2},
    {0, 5, 1},
    {4, 5, 0},
    {3, 2, 6},
    {4, 3, 6},
    {5, 4, 6},
    {1, 5, 6},
    {2, 1, 6}
};

static GLfloat diacolors[10][3] =
{
    {0.0, 0.0, 1.0},
    {0.5, 0.0, 1.0},
    {0.0, 1.0, 0.0},
    {0.0, 1.0, 1.0},
    {0.8, 0.0, 0.0},
    {0.2, 0.0, 1.0},
    {0.0, 0.8, 0.0},
    {0.5, 0.2, 0.0},
    {0.2, 0.8, 1.0},
    {0.0, 0.0, 1.0}
};

void drawdiamond()
{
    glColor3f(1,0,0);
    glBegin(GL_TRIANGLES);
    for (GLint i = 0; i <10; i++)
    {
        getNormal3p(diamond[dia_Indices[i][0]][0], diamond[dia_Indices[i][0]][1], diamond[dia_Indices[i][0]][2],
                    diamond[dia_Indices[i][1]][0], diamond[dia_Indices[i][1]][1], diamond[dia_Indices[i][1]][2],
                    diamond[dia_Indices[i][2]][0], diamond[dia_Indices[i][2]][1], diamond[dia_Indices[i][2]][2]);
        glColor3f(diacolors[i][0],diacolors[i][1],diacolors[i][2]);
        glVertex3fv(&diamond[dia_Indices[i][0]][0]);
        glVertex3fv(&diamond[dia_Indices[i][1]][0]);
        glVertex3fv(&diamond[dia_Indices[i][2]][0]);
    }
    glEnd();
}
void cartwheel(GLfloat r,GLfloat g,GLfloat b)
{
    glPushMatrix();
    glScalef(0.5,1,1);
    glPushMatrix();
    materialProperty(r,g,b);
    glScalef(0.4,0.4,0.4);
    glutSolidTorus(0.15,1,50,100);
    glPopMatrix();

    glPushMatrix();
    materialProperty(r,g,b);
    glScalef(0.25,0.25,0.25);
    glutWireTorus(0.75,1,2,25);
    glPopMatrix();
    glPopMatrix();

}
void hotdogvan()
{
    glPushMatrix();
    glRotatef(-90,1,0,0);
    glTranslatef(0.3,0.2,0.2);
    glScalef(0.8,0.8,0.8);
    materialProperty(1.0,1.0,0);
    drawdiamond();
    glPopMatrix();
    ///base and top
    glPushMatrix();
    glTranslatef(0.5,-2,-0.8);
    glScalef(1.2,0.1,0.5);
    //drawcube(0.2,0.5,0.5);
    drawcube(0.7,0.5,0.2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5,-0.9,-0.8);
    glScalef(1.2,0.1,0.5);
    drawcube(0.7,0.5,0.2);
    glPopMatrix();
    ///body
    glPushMatrix();
    glTranslatef(0.6,-1.9,-0.8);
    glScalef(1,1,0.5);
    drawcube(1,1,1);
    glPopMatrix();
    ///yellow long
    glPushMatrix();
    glTranslatef(0.6,-1.9,-1.3);
    glScalef(1,0.1,0.01);
    drawcube(1,1,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.6,-1.9,-0.79);
    glScalef(1,0.1,0.01);
    drawcube(1,1,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.6,-1.0,-1.3);
    glScalef(1,0.1,0.01);
    drawcube(1,1,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.6,-1.0,-0.79);
    glScalef(1,0.1,0.01);
    drawcube(1,1,0);
    glPopMatrix();

    ///yellow short
    glPushMatrix();
    glTranslatef(0.59,-1.9,-1.3);
    glRotatef(-90,0,1,0);
    glScalef(0.5,0.1,0.01);
    drawcube(1,1,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.61,-1.9,-0.79);
    glRotatef(90,0,1,0);
    glScalef(0.5,0.1,0.01);
    drawcube(1,1,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.6,-1.0,-0.79);
    glRotatef(90,0,1,0);
    glScalef(0.5,0.1,0.01);
    drawcube(1,1,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.61,-1.0,-0.79);
    glRotatef(90,0,1,0);
    glScalef(0.5,0.1,0.01);
    drawcube(1,1,0);
    glPopMatrix();

    ///red
    glPushMatrix();
    glTranslatef(0.6,-1.8,-1.3);
    glScalef(1,0.05,0.01);
    drawcube(1,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.6,-1.05,-1.3);
    glScalef(1,0.05,0.01);
    drawcube(1,0,0);
    glPopMatrix();

    ///wheel
    glPushMatrix();
    glTranslatef(0.8,-2,-1.4);
    cartwheel(0.1,0.1,0.1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.8,-2,-0.75);
    cartwheel(0.1,0.1,0.1);
    glPopMatrix();

    ///texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 4);

    glPushMatrix();
    glTranslatef(0.6,-0.8,-0.8);
    glScalef(1,1,0.01);
    drawcube(1,1,1);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(0.6,-0.8,-0.79);
    glScalef(1,1,0.01);
    drawcube(0.5,0.2,0.5);
    glPopMatrix();
}
void popcorn_corner()
{
    glPushMatrix();
    glRotatef(-90,1,0,0);
    glTranslatef(0.3,0.2,0.2);
    glScalef(0.8,0.8,0.8);
    materialProperty(0.7,0.3,0.3);
    drawdiamond();
    glPopMatrix();

    glPushMatrix();
    quad = gluNewQuadric();
    materialProperty(1,1,1);
    glTranslatef(1.1,1,-0.9);
    glRotatef(90,1,0,0);
    gluCylinder(quad,0.05,0.05,2,100,100);
    glPopMatrix();
    ///base and top
    glPushMatrix();
    glTranslatef(0.6,-2,-0.8);
    glScalef(1,0.1,0.5);
    //drawcube(0.2,0.5,0.5);
    drawcube(0.7,0.2,0.2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.6,-0.9,-0.8);
    glScalef(1,0.1,0.5);
    drawcube(0.7,0.2,0.2);
    glPopMatrix();
    ///body
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 5);

    glPushMatrix();
    glTranslatef(0.6,-1.9,-1.3);
    glScalef(1,1,0.01);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(0.6,-1.9,-0.8);
    glScalef(1,1,0.01);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.59,-1.9,-0.79);
    glRotatef(90,0,1,0);
    glScalef(0.5,1,0.01);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.61,-1.9,-1.29);
    glRotatef(-90,0,1,0);
    glScalef(0.5,1,0.01);
    drawcube(1,1,1);
    glPopMatrix();

    ///wheel
    glPushMatrix();
    glTranslatef(0.8,-2,-1.4);
    cartwheel(0.1,0.1,0.1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.8,-2,-0.75);
    cartwheel(0.1,0.1,0.1);
    glPopMatrix();

    ///texture
    ///front
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 6);

    glPushMatrix();
    glTranslatef(1.1,-0.8,-1.2);
    glScalef(0.4,0.4,0.01);
    drawcube(1,1,1);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    ///back
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 7);

    glPushMatrix();
    glTranslatef(1.1,-0.8,-1.19);
    glScalef(0.4,0.4,0.01);
    drawcube(1,1,1);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    ///2nd_one_front
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 8);

    glPushMatrix();
    glTranslatef(0.7,-0.8,-1.2);
    glScalef(0.4,0.6,0.01);
    drawcube(1,1,1);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    ///2nd_one_back
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 9);

    glPushMatrix();
    glTranslatef(0.7,-0.8,-1.19);
    glScalef(0.4,0.6,0.01);
    drawcube(1,1,1);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}
void coffeestall()
{
    ///base and top
    glPushMatrix();
    glTranslatef(0.6,-2,-0.8);
    glScalef(1,0.3,0.5);
    //drawcube(0.2,0.5,0.5);
    drawcube(0.6,0.5,0.3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.65,-0.9,-0.8);
    glScalef(0.9,0.2,0.5);
    drawcube(0.6,0.5,0.3);
    glPopMatrix();
    ///body
    glPushMatrix();
    glTranslatef(0.6,-1.9,-0.8);
    glScalef(1,1,0.5);
    drawcube(0.9,0.7,0.5);
    glPopMatrix();
    ///border long
    glPushMatrix();
    glTranslatef(0.6,-1.9,-1.3);
    glScalef(1,0.1,0.01);
    drawcube(0.3,0.2,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.6,-1.9,-0.79);
    glScalef(1,0.1,0.01);
    drawcube(0.3,0.2,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.6,-1.0,-1.3);
    glScalef(1,0.1,0.01);
    drawcube(0.3,0.2,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.6,-1.0,-0.79);
    glScalef(1,0.1,0.01);
    drawcube(0.3,0.2,0);
    glPopMatrix();

    ///border short
    glPushMatrix();
    glTranslatef(0.59,-1.9,-1.3);
    glRotatef(-90,0,1,0);
    glScalef(0.5,0.1,0.01);
    drawcube(0.3,0.2,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.61,-1.9,-0.79);
    glRotatef(90,0,1,0);
    glScalef(0.5,0.1,0.01);
    drawcube(0.3,0.2,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.6,-1.0,-0.79);
    glRotatef(90,0,1,0);
    glScalef(0.5,0.1,0.01);
    drawcube(0.3,0.2,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.61,-1.0,-0.79);
    glRotatef(90,0,1,0);
    glScalef(0.5,0.1,0.01);
    drawcube(0.3,0.2,0);
    glPopMatrix();
    ///wheel
    glPushMatrix();
    glTranslatef(1.1,-2,-1.4);
    cartwheel(0.1,0.1,0.1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.1,-2,-0.75);
    cartwheel(0.1,0.1,0.1);
    glPopMatrix();

    ///texture
    ///front
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 10);

    glPushMatrix();
    glTranslatef(1.3,-0.7,-1.2);
    glScalef(0.3,1.2,0.01);
    drawcube(1,1,1);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    ///back
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 11);

    glPushMatrix();
    glTranslatef(1.3,-0.7,-1.19);
    glScalef(0.3,1.2,0.01);
    drawcube(1,1,1);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 14);

    glPushMatrix();
    glTranslatef(0.85,-0.7,-1.2);
    glScalef(0.4,0.5,0.01);
    drawcube(1,1,1);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 15);

    glPushMatrix();
    glTranslatef(0.85,-0.7,-1.19);
    glScalef(0.4,0.5,0.01);
    drawcube(1,1,1);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(0.8,-0.7,-1.2);
    glScalef(0.05,1.2,0.01);
    drawcube(0.9,0.7,0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.8,-0.7,-1.2);
    glScalef(0.05,1.2,0.01);
    drawcube(0.9,0.7,0.5);
    glPopMatrix();
    ///banner_front
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 12);

    glPushMatrix();
    glTranslatef(0.7,0.5,-1.2);
    glScalef(1,0.5,0.01);
    drawcube(1,1,1);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    ///banner_back
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 13);

    glPushMatrix();
    glTranslatef(0.7,0.5,-1.19);
    glScalef(1,0.5,0.01);
    drawcube(1,1,1);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}
void pizzeria()
{
     ///body
    glPushMatrix();
    glTranslatef(0.6,-1.9,-0.8);
    glScalef(1,0.7,0.5);
    drawcube(0.2,0.2,0.2);
    glPopMatrix();

    glPushMatrix();
    quad = gluNewQuadric();
    materialProperty(1,1,1);
    glTranslatef(1.1,0.6,-0.7);
    glRotatef(90,1,0,0);
    gluCylinder(quad,0.025,0.025,2,100,100);
    glPopMatrix();

    ///yellow long
    glPushMatrix();
    glTranslatef(0.6,-1.9,-1.3);
    glScalef(1,0.2,0.01);
    drawcube(1,1,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.6,-1.9,-0.79);
    glScalef(1,0.2,0.01);
    drawcube(1,1,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.6,-1.3,-1.3);
    glScalef(1,0.1,0.01);
    drawcube(1,1,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.6,-1.3,-0.79);
    glScalef(1,0.1,0.01);
    drawcube(1,1,0);
    glPopMatrix();

    ///yellow short
    glPushMatrix();
    glTranslatef(0.59,-1.9,-1.3);
    glRotatef(-90,0,1,0);
    glScalef(0.5,0.2,0.01);
    drawcube(1,1,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.61,-1.9,-0.79);
    glRotatef(90,0,1,0);
    glScalef(0.5,0.2,0.01);
    drawcube(1,1,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.6,-1.3,-0.79);
    glRotatef(90,0,1,0);
    glScalef(0.5,0.1,0.01);
    drawcube(1,1,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.61,-1.3,-0.79);
    glRotatef(90,0,1,0);
    glScalef(0.5,0.1,0.01);
    drawcube(1,1,0);
    glPopMatrix();
    ///white
    glPushMatrix();
    glTranslatef(0.6,-1.45,-1.3);
    glScalef(1,0.05,0.01);
    drawcube(1,1,1);
    glPopMatrix();
    ///texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 16);

    glPushMatrix();
    glTranslatef(0.6,-1.2,-0.8);
    glScalef(1,1,0.01);
    drawcube(1,1,1);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(0.6,-1.9,-0.7);
    glScalef(1,1.7,0.1);
    drawcube(0.2,0.2,0.2);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 17);

    glPushMatrix();
    glTranslatef(0.6,-0.2,-0.8);
    glScalef(1,0.4,0.01);
    drawcube(1,1,1);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(0.6,-0.2,-0.7);
    glScalef(1,0.4,0.1);
    drawcube(1,1,0);
    glPopMatrix();


    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glBindTexture(GL_TEXTURE_2D, 18);
    glPushMatrix();
    glTranslatef(1.1,0.8,-0.725);
    glScalef(0.5,1,0.01);
    materialProperty(1,1,1);
    glutSolidSphere(0.5,50,50);
    glPopMatrix();
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(1.1,0.8,-0.675);
    glScalef(0.6,1.2,0.1);
    materialProperty(0.5,0.3,0);
    glutSolidSphere(0.5,50,50);
    glPopMatrix();

    ///wheel
    glPushMatrix();
    glTranslatef(1.1,-2,-1.4);
    cartwheel(0.1,0.1,0.1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.1,-2,-0.75);
    cartwheel(0.1,0.1,0.1);
    glPopMatrix();
}
void icecreambar()
{
    glPushMatrix();
    quad = gluNewQuadric();
    materialProperty(0.259,0.659,0.196);
    glTranslatef(1.5,0.1,-0.9);
    glRotatef(90,1,0,0);
    gluCylinder(quad,0.025,0.025,1.3,100,100);
    glPopMatrix();

    glPushMatrix();
    quad = gluNewQuadric();
    materialProperty(0.259,0.659,0.196);
    glTranslatef(0.7,0.1,-0.9);
    glRotatef(90,1,0,0);
    gluCylinder(quad,0.025,0.025,1.3,100,100);
    glPopMatrix();
    ///base and top
    glPushMatrix();
    glTranslatef(0.6,-2,-0.8);
    glScalef(1,0.1,0.5);
    //drawcube(0.2,0.5,0.5);
    drawcube(0.259,0.659,0.196);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.6,-1.2,-0.8);
    glRotatef(-15,1,0,0);
    glScalef(1,0.1,0.5);
    drawcube(0.259,0.659,0.196);
    glPopMatrix();
    ///body
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 19);

    glPushMatrix();
    glTranslatef(0.6,-1.9,-1.3);
    glScalef(1,0.6,0.01);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(0.6,-1.9,-0.8);
    glScalef(1,0.7,0.01);
    drawcube(0.839,0.722,0.404);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.59,-1.9,-0.79);
    glRotatef(90,0,1,0);
    glScalef(0.5,0.7,0.01);
    drawcube(0.839,0.722,0.404);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.61,-1.9,-1.29);
    glRotatef(-90,0,1,0);
    glScalef(0.5,0.7,0.01);
    drawcube(0.839,0.722,0.404);
    glPopMatrix();

    ///wheel
    glPushMatrix();
    glTranslatef(1.1,-2,-1.4);
    glScalef(0.7,0.7,0.7);
    cartwheel(0.1,0.1,0.1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.1,-2,-0.75);
    glScalef(0.7,0.7,0.7);
    cartwheel(0.1,0.1,0.1);
    glPopMatrix();

    ///texture
    ///banner
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 20);
    glPushMatrix();
    glTranslatef(0.6,-0.3,-1.0);
    glScalef(1,0.4,0.01);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(0.6,-0.3,-0.89);
    glScalef(1,0.4,0.1);
    drawcube(0.839,0.722,0.404);
    glPopMatrix();
    ///front
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 21);

    glPushMatrix();
    glTranslatef(1.1,-1.2,-1.1);
    glScalef(0.4,0.4,0.01);
    drawcube(1,1,1);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    ///back
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 22);

    glPushMatrix();
    glTranslatef(1.1,-1.2,-1.09);
    glScalef(0.4,0.4,0.01);
    drawcube(1,1,1);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    ///2nd_one_front
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 23);

    glPushMatrix();
    glTranslatef(0.7,-1.2,-1.2);
    glScalef(0.3,0.8,0.01);
    drawcube(1,1,1);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    ///2nd_one_back
    glPushMatrix();
    glTranslatef(0.7,-1.2,-1.09);
    glScalef(0.3,0.8,0.1);
    drawcube(0.878,0.663,0.063);
    glPopMatrix();
}
void dolna_stand()
{
    glPushMatrix();
    quad = gluNewQuadric();
    glRotatef(-240,1,0,0);
    materialProperty(0.408,0.725,0.851);
    gluCylinder(quad,0.25,0.25,5,50,100);
    glPopMatrix();

    glPushMatrix();
    quad = gluNewQuadric();
    glRotatef(60,1,0,0);
    materialProperty(0.408,0.725,0.851);
    gluCylinder(quad,0.25,0.25,5,50,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-3.4,2.2);
    glScalef(0.6,0.5,0.6);
    ground2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-3.4,-2.4);
    glScalef(0.6,0.5,0.6);
    ground2();
    glPopMatrix();
}
void dolna_seat()
{
    glPushMatrix();
    glRotatef(spind,1,0,0);
    glPushMatrix();
    glTranslatef(-2.1,-3.4,0.2);
    glRotatef(-20,1,0,0);
    glScalef(1.2,0.2,1);
    drawcube(0.929,0.384,0.047);
    glPopMatrix();
    ///back ropes
    glPushMatrix();
    quad = gluNewQuadric();
    glTranslatef(-1,0,-0.1);
    glRotatef(90,1,0,0);
    materialProperty(0.31,0.369,0.141);
    gluCylinder(quad,0.04,0.02,3.5,50,100);
    glPopMatrix();

    glPushMatrix();
    quad = gluNewQuadric();
    glTranslatef(-2,0,-0.1);
    glRotatef(90,1,0,0);
    materialProperty(0.31,0.369,0.141);
    gluCylinder(quad,0.04,0.02,3.5,50,100);
    glPopMatrix();
    ///front ropes
    glPushMatrix();
    quad = gluNewQuadric();
    glTranslatef(-1,0,-0.1);
    glRotatef(-260,1,0,0);
    materialProperty(0.31,0.369,0.141);
    gluCylinder(quad,0.04,0.02,3.7,50,100);
    glPopMatrix();

    glPushMatrix();
    quad = gluNewQuadric();
    glTranslatef(-2,0,-0.1);
    glRotatef(-260,1,0,0);
    materialProperty(0.31,0.369,0.141);
    gluCylinder(quad,0.04,0.02,3.7,50,100);
    glPopMatrix();
    glPopMatrix();
}
void dolnaaa()
{

    glPushMatrix();
    dolna_stand();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-5,0,0);
    dolna_stand();
    glPopMatrix();
    ///horizontal cylinder
    glPushMatrix();
    quad = gluNewQuadric();
    glTranslatef(-5.5,0,0);
    glRotatef(90,0,1,0);
    materialProperty(0.408,0.725,0.851);
    gluCylinder(quad,0.25,0.25,6,50,100);
    glPopMatrix();
    ///rings
    glPushMatrix();
        glTranslatef(0.5,0,0);
        glRotatef(90,0,1,0);
        glScalef(1.2,1,1);
        materialProperty(0.184,0.541,0.678);
        glutSolidTorus(0.15,0.15,50,100);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-5.5,0,0);
        glRotatef(90,0,1,0);
        glScalef(1.2,1,1);
        materialProperty(0.184,0.541,0.678);
        glutSolidTorus(0.15,0.15,50,100);
    glPopMatrix();
    for(int i=1;i<5;i++){
        glPushMatrix();
        glTranslatef(-i,0,0);
        glRotatef(90,0,1,0);
        glScalef(0.7,0.9,1);
        materialProperty(0.184,0.541,0.678);
        glutSolidTorus(0.15,0.4,50,100);
        glPopMatrix();
    }
    ///seats
    glPushMatrix();
    dolna_seat();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2,0,0);
    dolna_seat();
    glPopMatrix();
}
void vending_machine()
{
    glPushMatrix();
    glScalef(1,4,0.5);
    drawcube(0.129,0.478,0.749);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,24);
    glPushMatrix();
    glTranslatef(0,0,-0.51);
    glScalef(1,4,0.01);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(0.1,0.78,-0.52);
    glScalef(0.7,0.27,0.01);
    drawcube(0,0,0);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,25);
    glPushMatrix();
    glTranslatef(0.1,0.78,-0.53);
    glRotatef(vm_door,1,0,0);
    glScalef(0.7,0.27,0.1);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void bird_eye_view()
{
    swap(Eyval,Ezval);
}
void bench()
{
    glPushMatrix();
    glTranslatef(0,-4.8,-17.2);
    glScalef(0.1,1.8,0.1);
    drawcube(0.929,0.694,0.251);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.5,-4.8,-17.2);
    glScalef(0.1,1.8,0.1);
    drawcube(0.929,0.694,0.251);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-4.8,-17.7);
    glScalef(0.1,0.7,0.1);
    drawcube(0.929,0.694,0.251);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.5,-4.8,-17.7);
    glScalef(0.1,0.7,0.1);
    drawcube(0.929,0.694,0.251);
    glPopMatrix();
    ///seat
    glPushMatrix();
    glTranslatef(-1.7,-4.1,-17.2);
    glScalef(2,0.1,0.3);
    drawcube(0.8,0.145,0.208);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.7,-4.1,-17.5);
    glScalef(2,0.1,0.3);
    drawcube(0.82,0.353,0.039);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,14.1,-21.4);
    glRotatef(-90,1,0,0);
    glPushMatrix();
    glTranslatef(-1.7,-4.1,-17.2);
    glScalef(2,0.1,0.3);
    drawcube(0.8,0.145,0.208);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.7,-4.1,-17.5);
    glScalef(2,0.1,0.3);
    drawcube(0.82,0.353,0.039);
    glPopMatrix();
    glPopMatrix();
}
void ticket_counter()
{
    glPushMatrix();
    glTranslatef(-4.6,-3,-26.6);
//    glScalef(1,2,0.5);
//    drawcube(1,1,1);
 ///body
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 26);
    glPushMatrix();
    glTranslatef(0.6,-1.9,-0.8);
    glScalef(1,0.7,0.5);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 27);

    glPushMatrix();
    glTranslatef(0.6,-1.2,-0.8);
    glScalef(1,1,0.01);
    drawcube(1,1,1);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(0.6,-1.9,-0.7);
    glScalef(1,1.7,0.1);
    drawcube(0.2,0.2,0.2);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 28);

    glPushMatrix();
    glTranslatef(0.6,-0.2,-0.8);
    glScalef(1,0.4,0.01);
    drawcube(1,1,1);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(0.6,-0.2,-0.7);
    glScalef(1,0.4,0.1);
    drawcube(0,0,0.5);
    glPopMatrix();
}
void draw_sphere(int scalex, int scaley, GLfloat r)
{


    int i, j;
    GLfloat v[scalex*scaley][3];

    for (i=0; i<scalex; ++i)
    {
        for (j=0; j<scaley; ++j)
        {
            v[i*scaley+j][0]=r*cos(j*1.5*M_PI/scaley)*cos(i*M_PI/(1.5*scalex));
            v[i*scaley+j][1]=r*sin(i*M_PI/(1.5*scalex));
            v[i*scaley+j][2]=r*sin(j*1.5*M_PI/scaley)*cos(i*M_PI/(1.5*scalex));
        }
    }

    glBegin(GL_QUADS);
    for (i=0; i<scalex-1; ++i)
    {
        for (j=0; j<scaley; ++j)
        {
            glTexCoord2f(0,0);
            glVertex3fv(v[i*scaley+j]);
            glTexCoord2f(1,0);
            glVertex3fv(v[i*scaley+(j+1)%scaley]);
            glTexCoord2f(1,1);
            glVertex3fv(v[(i+1)*scaley+(j+1)%scaley]);
            glTexCoord2f(0,1);
            glVertex3fv(v[(i+1)*scaley+j]);
        }
    }
    glEnd();
}
void draw_tree()
{
    glTranslatef(0,6,0);
    glScalef(2,2,2);
    quad = gluNewQuadric();
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glBindTexture(GL_TEXTURE_2D, 29);
        //glTranslatef(0,4,0);
        glRotatef(90,1,0,0);
        materialProperty(1,1,1);
        gluCylinder(quad,0.4f,0.4f,6.2f,32,32);
        //draw_cylinder(.5,4,100);
        glDisable(GL_TEXTURE_GEN_T);
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,-2,0);
        glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glEnable(GL_TEXTURE_GEN_S);
            glEnable(GL_TEXTURE_GEN_T);
            glBindTexture(GL_TEXTURE_2D, 30);
            glTranslatef(0,4-.6,0);
            glScalef(.2,.3,.3);
            draw_sphere(15,15,6.5);
            glDisable(GL_TEXTURE_GEN_T);
            glDisable(GL_TEXTURE_GEN_S);
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();

        glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glEnable(GL_TEXTURE_GEN_S);
            glEnable(GL_TEXTURE_GEN_T);
            glBindTexture(GL_TEXTURE_2D, 31);
            glTranslatef(0,2,0);
            glScalef(.3,.4,.3);
            //glRotatef(90,0,1,0);
            //glRotatef(180,1,0,0);
            draw_sphere(15,15,6.5);
            glDisable(GL_TEXTURE_GEN_T);
            glDisable(GL_TEXTURE_GEN_S);
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    glPopMatrix();
}

void wall()
{
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_BINDING_2D,33);
    glPushMatrix();
    glTranslatef(19.2,-5,1.8);
    glScalef(1,5,30);
    drawcube(0.922,0.255,0.231);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);
}
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum(-5+l, 5+r, -5+b, 5+t, 4+n, 150);
    //glFrustum(-3, 3, -3, 3, 5, 20);
    //gluPerspective(60,1,5,100);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    gluLookAt(Exval,Eyval,Ezval, xref+dx,yref+dy,zref, xdir,ydir,zdir);
    glViewport(0, 0, windowHeight, windowWidth);

    glScalef(scaleX,scaleY,scaleZ);

    glRotatef( theta, axis_x, axis_y, 0.0 );
    glRotatef( alpha,axis_x, axis_y, 0.0 );

    glPushMatrix();
        glPushMatrix();
        ground();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,-5.4,-30.4);
        glScalef(20,0.01,5);
        ground2();
        glPopMatrix();
        //gate();
        glPushMatrix();
        glPushMatrix();
        glTranslatef(-10.2,-2.6,-21.2);
        ride1();
        glPopMatrix();
        glPopMatrix();

        glPushMatrix();
        glPushMatrix();
        glTranslatef(-.6+4.2,-2.6,-20.8);
        //glScalef(.5,.5,.5);
        ride1();
        glPopMatrix();
        glPopMatrix();

        glPushMatrix();
        glPushMatrix();
            glTranslatef(-10,-4.8+2.4,-16.2-1.2);
            glRotatef(180,0,0,1);
            glRotatef(180,1,0,0);
            glScalef(0.1,0.1,0.1);
            skyDrop();
        glPopMatrix();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(7.6,0,-16.2-100);
            //glScalef(0.5,1,1);
            ferris_wheel();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(7.8,-2.6,-10.2);
            //glScalef(0.5,1,1);
            ferris_wheel();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(7.8,-2.6,-10.2-8);
            //glScalef(0.5,1,1);
            ferris_wheel();
        glPopMatrix();
    //    glPushMatrix();
    //    glTranslatef(30,0,6.2);
    //    glScalef(0.5,1,1);
    //    ferris_wheel();
    //    glPopMatrix();

    //    glPushMatrix();
    //    glTranslatef(-7,-3,2.5);
    //    veggieshop();
    //    glPopMatrix();

        glPushMatrix();
        glTranslatef(-1.4,-2,-11.8);
        glScalef(1.2,1.2,1.2);
        hotdogvan();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-6.8,-2,-11.8);
        glScalef(1.2,1.2,1.2);
        popcorn_corner();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-3.6,-2,-5.6);
        glScalef(1.2,1.2,1.2);
        coffeestall();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-1.8,-2,-7);
        glScalef(1.2,1.2,1.2);
        pizzeria();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-5.4,-2.2,-8.6);
        glScalef(1.2,1.2,1.2);
        icecreambar();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(6.6,-1.8,-9.6);
        glScalef(0.7,0.7,0.7);
        dolnaaa();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-7.6,-5,-14.2);
        //glRotatef(-30,0,1,0);
        vending_machine();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-2.8,-4.8,-18.4);
        glScalef(3.5,0.01,2);
        ground2();
        glPopMatrix();

        for(int i=0;i<6;i+=2){
        glPushMatrix();
        glTranslatef(-1.4,0,-0.2);
        glPushMatrix();
        //glTranslatef(-i,-1.2,-3.6);
        glTranslatef(-i,-1,-31.6);
        glRotatef(180,0,1,0);
        glScalef(0.8,0.8,0.8);
        bench();
        glPopMatrix();
        glPopMatrix();
        }
        for(int i=0;i<6;i+=2){
        glPushMatrix();
        glTranslatef(-1.4,0,-2);
        glPushMatrix();
        //glTranslatef(-i,-1.2,-3.6);
        glTranslatef(-i,-1,-31.6);
        glRotatef(180,0,1,0);
        glScalef(0.8,0.8,0.8);
        bench();
        glPopMatrix();
        glPopMatrix();
        }

        glPushMatrix();
        ticket_counter();
        glPopMatrix();

        for(int i=0;i<12;i+=2){
        glPushMatrix();
        glTranslatef(13.2-i,-3.6,0);
        glScalef(0.2,0.2,0.2);
        draw_tree();
        glPopMatrix();
        }

        for(int i=0;i<12;i+=2){
        glPushMatrix();
        glTranslatef(-13.2+i,-3.6,0);
        glScalef(0.2,0.2,0.2);
        draw_tree();
        glPopMatrix();
        }

        glPushMatrix();
            glPushMatrix();
            wall();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-39,0,0);
            wall();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(17.6,0,67.6);
            glRotatef(90,0,1,0);
            glScalef(3.3,1,1.3);
            wall();
            glPopMatrix();
        glPopMatrix();
//
//        glPushMatrix();
//        glTranslatef(12.8,-4,-20.2);
//        glRotatef(90,0,0,1);
//        glScalef(1.5,1.5,1.5);
//        wheelseat();
//        glPopMatrix();

    glPopMatrix();

    light(-22,-10,-20, GL_LIGHT0, light_0_on, false);
    light(-2.1,5.6,-5, GL_LIGHT1, light_1_on, false);
    light(-1.0,5.6,-5, GL_LIGHT1, light_1_on, false);
    light(-0.5,5.6,-5, GL_LIGHT1, light_1_on, false);

    glFlush();
    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    ///rotation with respect to y axis
    case 's':
    case 'S':
        bRotate = !bRotate;
        uRotate = false;
        axis_x=0.0;
        axis_y=1.0;
        break;
    ///rotation with respect to x axis
    case 'r':
    case 'R':
        uRotate = !uRotate;
        bRotate = false;
        axis_x=1.0;
        axis_y=0.0;
        break;
    case 'e':///zoom in-out using nearplane
        n+=.2;
        glutPostRedisplay();
        break;
    case 'E':
        n-=.2;
        glutPostRedisplay();
        break;
    ///yaw
    case '1':
        yaw+=1;
        if( yaw==90 || yaw ==0)
        {
            yaw=0;
            dx=0;
            break;
        }
        dx =  abs(Ezval-zref)*tan(yaw*3.1415/180);

        yref=yref;
        break;

    case '2':
        yaw-=1;
        if(yaw==-90 || yaw==0)
        {
            yaw = 0;
            dx=0;
            break;
        }

        dx = abs(Ezval-zref)*tan(yaw*3.1415/180);

        yref=yref;
        break;

    ///pitch
    case '3':
        pitch+=1;
        if( pitch==90 || pitch ==0)
        {
            pitch=0;
            dy=0;
            break;
        }
        dy =  abs(Ezval-zref)*tan(pitch*3.1415/180);

        xref=xref;
        break;
    case '4':
        pitch-=1;
        if(pitch==-90 || pitch==0)
        {
            pitch = 0;
            dy=0;
            break;
        }
        dy = abs(Ezval-zref)*tan(pitch*3.1415/180);
        xref=xref;
        break;

    ///roll
    case '5':
        roll+=0.2;
        xdir = cos(roll);
        ydir = sin(roll);
        break;
    case '6':
        roll-=0.2;
        xdir = cos(roll);
        ydir = sin(roll);
        break;
    ///panning
    case 'p':
    case 'P':
        l-=0.1;
        r-=0.1;
        break;
    case 'l':
    case 'L':
        l+=0.1;
        r+=0.1;
        break;
    case 'b':
    case 'B':
        b-=0.1;
        t-=0.1;
        break;
    case 't':
    case 'T':
        b+=0.1;
        t+=0.1;
        break;
    ///zoom in-out in z axis
    case '+':
        Ezval++;
        zref++;
        break;
    case '-':
        Ezval--;
        zref--;
        break;
    ///zoom in-out in x axis
    case 'x':
        Exval++;
        xref++;
        break;
    case 'X':
        Exval--;
        xref--;
        break;
    ///zoom in-out in y axis
    case 'y':
        Eyval++;
        yref++;
        break;
    case 'Y':
        Eyval--;
        yref--;
        break;
    ///zooming using scaling
    case 'f':
    case 'F':
        scaleX += 0.2;
        scaleY += 0.2;
        scaleZ += 0.2;
        break;
    case 'c':
    case 'C':
        scaleX -= 0.2;
        scaleY -= 0.2;
        scaleZ -= 0.2;
        break;
    case '0':///bird eye view
        bird_eye_view();
        break;
    case 'd':///ride1
    case 'D':
        chk = !chk;
        break;
    case 'v': ///skydrop
        skyDropFlag = !skyDropFlag;
        break;
    case 'w':///ferris wheel
        chkw = !chkw;
        chkww = !chkww;
        break;
    case 'n':///swing
        swing_rotate = !swing_rotate;
        break;
    case 'm':///vending machine
        vm = !vm;
        if(vm)
            vm_door = -90;
        else
            vm_door = 0;
        break;

        case 'g':
        light_0_on = !light_0_on;
        break;
    //light 1 toggle
    case 'q':
        light_1_on = !light_1_on;
        break;
    //light 2 toggle(spot Light)
    //case 't':
        //light_2_on = !light_2_on;
        //break;
    //ambient light toggle
    case 'a':
        amb_light = !amb_light;
        break;
    //diffusion light toggle
    case '7':
        dif_light = !dif_light;
        break;
    //specular light toggle
    case '8':
        spec_light = !spec_light;
        break;
    case 27 :
        exit(1);
    }
    glutPostRedisplay();
}
int ii=1;
void animate()
{
    if (bRotate == true)
    {
        theta += 0.2;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }

    if (uRotate == true)
    {
        alpha += 0.2;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }

    if (chk == true)
    {
        spin += 3.0;
        if(spin > 360.0)
            spin -= 360.0*floor(spin/360.0);
    }

    if(chkw == true)
    {
        spinw += 1.0;
        if(spinw > 360.0)
            spinw -= 360.0*floor(spinw/360.0);
    }
    if(chkww)
    {
        spins -=1.0;
        if(spins > 180.0)
            spins += 1.0;//360.0*floor(spins/360.0);
    }

    if (swing_rotate == true)
    {
        spind += 3.0*ii;
        if(spind > 60.0){
            ii =-1;
        }
        if(spind < -60.0){
            ii=1;
        }
    }

    if(skyDropFlag == true)
    {
        if(upFlag == true)
        {
            skyDropPos += 0.5;
            if(skyDropPos >= 80)
            {
                upFlag = false;
            }
        }
        else
        {
            if(downFlag1 == true && downFlag2 == false && downFlag3 == false)
            {
                skyDropPos -= 2;
                if(skyDropPos <= 5)
                {
                    upFlag = true;
                    downFlag1 = false;
                    downFlag2 = true;
                    downFlag3 = false;
                }
            }
            else if(downFlag1 == false && downFlag2 == true && downFlag3 == false)
            {
                skyDropPos -= 3;
                if(skyDropPos <= 45)
                {
                    upFlag = true;
                    downFlag1 = false;
                    downFlag2 = false;
                    downFlag3 = true;
                }
            }
            else if(downFlag1 == false && downFlag2 == false && downFlag3 == true)
            {
                skyDropPos -= 4;
                if(skyDropPos <= 15)
                {
                    upFlag = true;
                    downFlag1 = true;
                    downFlag2 = false;
                    downFlag3 = false;
                }
            }

        }

    }
    else
    {
        skyDropPos -= 2;
        if(skyDropPos <= 2 )
        {
            skyDropPos = 2;
        }
    }
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */
void SpecialInput(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_UP:
        ttz -= 0.2;
        break;
    case GLUT_KEY_DOWN:
//do something here
        ttz += 0.2;
        break;
    case GLUT_KEY_LEFT:
//do something here
        ttx -= 0.2;
        break;
    case GLUT_KEY_RIGHT:
//do something here
        ttx += 0.2;
        break;
    }
    std:: cout<<"Starting Point "<<ttx<<","<<tty<<","<<ttz<<" \n";

    glutPostRedisplay();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(windowHeight,windowWidth);
    glutCreateWindow("FunFair");
    glShadeModel( GL_SMOOTH );

    //glClearColor(1,1,1,1);
    glShadeModel( GL_SMOOTH );
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    //glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    LoadBMP("D:\\Study\\4-2\\CSE 4208 Graphics Lab\\skydrop1_1.bmp",1);
    LoadBMP("D:\\Study\\4-2\\CSE 4208 Graphics Lab\\pinkblue.bmp",2);
    LoadBMP("D:\\Study\\4-2\\CSE 4208 Graphics Lab\\wall1.bmp",3);
    LoadBMP("D:\\Study\\4-2\\CSE 4208 Graphics Lab\\hotdog1.bmp",4);
    LoadBMP("D:\\Study\\4-2\\CSE 4208 Graphics Lab\\popcorn3.bmp",5);
    LoadBMP("D:\\Study\\4-2\\CSE 4208 Graphics Lab\\popcorn4.bmp",6);
    LoadBMP("D:\\Study\\4-2\\CSE 4208 Graphics Lab\\popcorn4_ulta.bmp",7);
    LoadBMP("D:\\Study\\4-2\\CSE 4208 Graphics Lab\\popcorn6.bmp",8);
    LoadBMP("D:\\Study\\4-2\\CSE 4208 Graphics Lab\\popcorn6_ulta.bmp",9);
    LoadBMP("D:\\Study\\4-2\\CSE 4208 Graphics Lab\\coffee.bmp",10);
    LoadBMP("D:\\Study\\4-2\\CSE 4208 Graphics Lab\\coffee_ulta.bmp",11);
    LoadBMP("D:\\Study\\4-2\\CSE 4208 Graphics Lab\\coffee1.bmp",12);
    LoadBMP("D:\\Study\\4-2\\CSE 4208 Graphics Lab\\coffee1_ulta.bmp",13);
    LoadBMP("D:\\Study\\4-2\\CSE 4208 Graphics Lab\\coffee8.bmp",14);
    LoadBMP("D:\\Study\\4-2\\CSE 4208 Graphics Lab\\coffee8_ulta.bmp",15);
    LoadBMP("D:\\Study\\4-2\\CSE 4208 Graphics Lab\\pizza1.bmp",16);
    LoadBMP("D:\\Study\\4-2\\CSE 4208 Graphics Lab\\pizza.bmp",17);
    LoadBMP("D:\\Study\\4-2\\CSE 4208 Graphics Lab\\pizza3_1.bmp",18);
    LoadBMP("D:\\Study\\4-2\\CSE 4208 Graphics Lab\\icecream2_1.bmp",19);
    LoadBMP("D:\\Study\\4-2\\CSE 4208 Graphics Lab\\icecream1_1.bmp",20);
    LoadBMP("D:\\Study\\4-2\\CSE 4208 Graphics Lab\\icecream4.bmp",21);
    LoadBMP("D:\\Study\\4-2\\CSE 4208 Graphics Lab\\icecream4_ulta.bmp",22);
    LoadBMP("D:\\Study\\4-2\\CSE 4208 Graphics Lab\\icecream5.bmp",23);
    LoadBMP("D:\\Study\\4-2\\CSE 4208 Graphics Lab\\vm_rsz3.bmp",24);
    LoadBMP("D:\\Study\\4-2\\CSE 4208 Graphics Lab\\vm_rsz4.bmp",25);
    LoadBMP("D:\\Study\\4-2\\CSE 4208 Graphics Lab\\redwhite.bmp",26);
    LoadBMP("D:\\Study\\4-2\\CSE 4208 Graphics Lab\\ticket1_1.bmp",27);
    LoadBMP("D:\\Study\\4-2\\CSE 4208 Graphics Lab\\ticket4.bmp",28);
    LoadBMP("D:\\Study\\4-2\\CSE 4208 Graphics Lab\\wood.bmp",29);
    LoadBMP("D:\\Study\\4-2\\CSE 4208 Graphics Lab\\tree1.bmp",30);
    LoadBMP("D:\\Study\\4-2\\CSE 4208 Graphics Lab\\tree1.bmp",31);
    LoadBMP("D:\\Study\\4-2\\CSE 4208 Graphics Lab\\ground.bmp",32);
    LoadBMP("D:\\Study\\4-2\\CSE 4208 Graphics Lab\\brick.bmp",33);

    glutKeyboardFunc(key);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutSpecialFunc(SpecialInput);
    glutMainLoop();
    return EXIT_SUCCESS;
}
