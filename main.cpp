/*
* GLUT Shapes Demo
*
* Written by Nigel Stewart November 2003
*
* This program is test harness for the sphere, cone
* and torus shapes in GLUT.
*
* Spinning wireframe and smooth shaded shapes are
* displayed until the ESC or q key is pressed.  The
* number of geometry stacks and slices can be adjusted
* using the + and - keys.
*/

#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

static int slices = 16;
static int stacks = 16;



void dibujarOperacion(string txt,int tam){
	
	float x = tam;
	float y = tam*1.5;
	float esp =0.80;
	string temp ;
	glPushMatrix();
	glTranslatef(-x*2.0*((txt.length()/2.0)-0.5),0,0);
	
	for(int i=0 ; i<txt.length() ; i++){
		
		temp = txt.substr(i,1);
		
		switch(temp.at(0)){
		case '1' :
			//1	x
			
					glBegin(GL_QUADS);
						glVertex2f(x*esp,y*esp);
						glVertex2f(x*esp*0.5,y*esp);
						glVertex2f(x*esp*0.5,-y*esp);
						glVertex2f(x*esp,-y*esp);
					glEnd();
					cout<<i<<endl;
					glBegin(GL_QUADS);
						glVertex2f(x*esp,y*esp);
						glVertex2f(x*esp*0.5,y*esp);
						glVertex2f(-x*esp,0);
						glVertex2f(-x*esp*0.5,0);
					glEnd();
			
			//fin 1
			break;
		case '2' :
			//2
			
				//a
				glBegin(GL_QUADS);
					glVertex2f(x*esp,y*esp);
					glVertex2f(-x*esp,y*esp);
					glVertex2f(-x*esp,y*esp*0.7);
					glVertex2f(x*esp,y*esp*0.7);
				glEnd();
			
				//b
				glBegin(GL_QUADS);
					glVertex2f(x*esp,y*esp);
					glVertex2f(x*esp*0.5,y*esp);
					glVertex2f(x*esp*0.5,0);
					glVertex2f(x*esp,0);
				glEnd();
				

			
				//d
				glBegin(GL_QUADS);
					glVertex2f(x*esp,-y*esp*0.7);
					glVertex2f(-x*esp,-y*esp*0.7);
					glVertex2f(-x*esp,-y*esp);
					glVertex2f(x*esp,-y*esp);
				glEnd();
			
				//e
				glBegin(GL_QUADS);
					glVertex2f(-x*esp*0.5,0);
					glVertex2f(-x*esp,0);
					glVertex2f(-x*esp,-y*esp);
					glVertex2f(-x*esp*0.5,-y*esp);
				glEnd();
				
	
				
				//g
				glBegin(GL_QUADS);
				glVertex2f(x*esp,y*0.15);
				glVertex2f(-x*esp,y*0.15);
				glVertex2f(-x*esp,-y*0.15);
				glVertex2f(x*esp,-y*0.15);
				glEnd();
				
			
			//fin2
			break;
		case '3' :
			//a
			glBegin(GL_QUADS);
			glVertex2f(x*esp,y*esp);
			glVertex2f(-x*esp,y*esp);
			glVertex2f(-x*esp,y*esp*0.7);
			glVertex2f(x*esp,y*esp*0.7);
			glEnd();
			
			//b
			glBegin(GL_QUADS);
			glVertex2f(x*esp,y*esp);
			glVertex2f(x*esp*0.5,y*esp);
			glVertex2f(x*esp*0.5,0);
			glVertex2f(x*esp,0);
			glEnd();
			
			//c
			glBegin(GL_QUADS);
			glVertex2f(x*esp,0);
			glVertex2f(x*esp*0.5,0);
			glVertex2f(x*esp*0.5,-y*esp);
			glVertex2f(x*esp,-y*esp);
			glEnd();
			
			//d
			glBegin(GL_QUADS);
			glVertex2f(x*esp,-y*esp*0.7);
			glVertex2f(-x*esp,-y*esp*0.7);
			glVertex2f(-x*esp,-y*esp);
			glVertex2f(x*esp,-y*esp);
			glEnd();
	
			
			//g
			glBegin(GL_QUADS);
			glVertex2f(x*esp,y*0.15);
			glVertex2f(-x*esp,y*0.15);
			glVertex2f(-x*esp,-y*0.15);
			glVertex2f(x*esp,-y*0.15);
			glEnd();
			break;
		case '4' :
		
			
			//b
			glBegin(GL_QUADS);
			glVertex2f(x*esp,y*esp);
			glVertex2f(x*esp*0.5,y*esp);
			glVertex2f(x*esp*0.5,0);
			glVertex2f(x*esp,0);
			glEnd();
			
			//c
			glBegin(GL_QUADS);
			glVertex2f(x*esp,0);
			glVertex2f(x*esp*0.5,0);
			glVertex2f(x*esp*0.5,-y*esp);
			glVertex2f(x*esp,-y*esp);
			glEnd();
			
		
	
			
			//f
			glBegin(GL_QUADS);
			glVertex2f(-x*esp*0.5,y*esp);
			glVertex2f(-x*esp,y*esp);
			glVertex2f(-x*esp,0);
			glVertex2f(-x*esp*0.5,0);
			glEnd();
			
			//g
			glBegin(GL_QUADS);
			glVertex2f(x*esp,y*0.15);
			glVertex2f(-x*esp,y*0.15);
			glVertex2f(-x*esp,-y*0.15);
			glVertex2f(x*esp,-y*0.15);
			glEnd();
			break;
		case'5' :
			//a
			glBegin(GL_QUADS);
			glVertex2f(x*esp,y*esp);
			glVertex2f(-x*esp,y*esp);
			glVertex2f(-x*esp,y*esp*0.7);
			glVertex2f(x*esp,y*esp*0.7);
			glEnd();
			
			//c
			glBegin(GL_QUADS);
			glVertex2f(x*esp,0);
			glVertex2f(x*esp*0.5,0);
			glVertex2f(x*esp*0.5,-y*esp);
			glVertex2f(x*esp,-y*esp);
			glEnd();
			
			//d
			glBegin(GL_QUADS);
			glVertex2f(x*esp,-y*esp*0.7);
			glVertex2f(-x*esp,-y*esp*0.7);
			glVertex2f(-x*esp,-y*esp);
			glVertex2f(x*esp,-y*esp);
			glEnd();
			
	
			
			//f
			glBegin(GL_QUADS);
			glVertex2f(-x*esp*0.5,y*esp);
			glVertex2f(-x*esp,y*esp);
			glVertex2f(-x*esp,0);
			glVertex2f(-x*esp*0.5,0);
			glEnd();
			
			//g
			glBegin(GL_QUADS);
			glVertex2f(x*esp,y*0.15);
			glVertex2f(-x*esp,y*0.15);
			glVertex2f(-x*esp,-y*0.15);
			glVertex2f(x*esp,-y*0.15);
			glEnd();
			break;
		case '6' :
			//a
			glBegin(GL_QUADS);
			glVertex2f(x*esp,y*esp);
			glVertex2f(-x*esp,y*esp);
			glVertex2f(-x*esp,y*esp*0.7);
			glVertex2f(x*esp,y*esp*0.7);
			glEnd();
			
	
			
			//c
			glBegin(GL_QUADS);
			glVertex2f(x*esp,0);
			glVertex2f(x*esp*0.5,0);
			glVertex2f(x*esp*0.5,-y*esp);
			glVertex2f(x*esp,-y*esp);
			glEnd();
			
			//d
			glBegin(GL_QUADS);
			glVertex2f(x*esp,-y*esp*0.7);
			glVertex2f(-x*esp,-y*esp*0.7);
			glVertex2f(-x*esp,-y*esp);
			glVertex2f(x*esp,-y*esp);
			glEnd();
			
			//e
			glBegin(GL_QUADS);
			glVertex2f(-x*esp*0.5,0);
			glVertex2f(-x*esp,0);
			glVertex2f(-x*esp,-y*esp);
			glVertex2f(-x*esp*0.5,-y*esp);
			glEnd();
			
			//f
			glBegin(GL_QUADS);
			glVertex2f(-x*esp*0.5,y*esp);
			glVertex2f(-x*esp,y*esp);
			glVertex2f(-x*esp,0);
			glVertex2f(-x*esp*0.5,0);
			glEnd();
			
			//g
			glBegin(GL_QUADS);
			glVertex2f(x*esp,y*0.15);
			glVertex2f(-x*esp,y*0.15);
			glVertex2f(-x*esp,-y*0.15);
			glVertex2f(x*esp,-y*0.15);
			glEnd();
			break;
		case '7' :
			//a
			glBegin(GL_QUADS);
			glVertex2f(x*esp,y*esp);
			glVertex2f(-x*esp,y*esp);
			glVertex2f(-x*esp,y*esp*0.7);
			glVertex2f(x*esp,y*esp*0.7);
			glEnd();
			
			//b
			glBegin(GL_QUADS);
			glVertex2f(x*esp,y*esp);
			glVertex2f(x*esp*0.5,y*esp);
			glVertex2f(x*esp*0.5,0);
			glVertex2f(x*esp,0);
			glEnd();
			
			//c
			glBegin(GL_QUADS);
			glVertex2f(x*esp,0);
			glVertex2f(x*esp*0.5,0);
			glVertex2f(x*esp*0.5,-y*esp);
			glVertex2f(x*esp,-y*esp);
			glEnd();
			
		

			
			
			break;
		case '8' :
			//a
			glBegin(GL_QUADS);
			glVertex2f(x*esp,y*esp);
			glVertex2f(-x*esp,y*esp);
			glVertex2f(-x*esp,y*esp*0.7);
			glVertex2f(x*esp,y*esp*0.7);
			glEnd();
			
			//b
			glBegin(GL_QUADS);
			glVertex2f(x*esp,y*esp);
			glVertex2f(x*esp*0.5,y*esp);
			glVertex2f(x*esp*0.5,0);
			glVertex2f(x*esp,0);
			glEnd();
			
			//c
			glBegin(GL_QUADS);
			glVertex2f(x*esp,0);
			glVertex2f(x*esp*0.5,0);
			glVertex2f(x*esp*0.5,-y*esp);
			glVertex2f(x*esp,-y*esp);
			glEnd();
			
			//d
			glBegin(GL_QUADS);
			glVertex2f(x*esp,-y*esp*0.7);
			glVertex2f(-x*esp,-y*esp*0.7);
			glVertex2f(-x*esp,-y*esp);
			glVertex2f(x*esp,-y*esp);
			glEnd();
			
			//e
			glBegin(GL_QUADS);
			glVertex2f(-x*esp*0.5,0);
			glVertex2f(-x*esp,0);
			glVertex2f(-x*esp,-y*esp);
			glVertex2f(-x*esp*0.5,-y*esp);
			glEnd();
			
			//f
			glBegin(GL_QUADS);
			glVertex2f(-x*esp*0.5,y*esp);
			glVertex2f(-x*esp,y*esp);
			glVertex2f(-x*esp,0);
			glVertex2f(-x*esp*0.5,0);
			glEnd();
			
			//g
			glBegin(GL_QUADS);
			glVertex2f(x*esp,y*0.15);
			glVertex2f(-x*esp,y*0.15);
			glVertex2f(-x*esp,-y*0.15);
			glVertex2f(x*esp,-y*0.15);
			glEnd();
			break;
		case '9' :
			//a
			glBegin(GL_QUADS);
				glVertex2f(x*esp,y*esp);
				glVertex2f(-x*esp,y*esp);
				glVertex2f(-x*esp,y*esp*0.7);
				glVertex2f(x*esp,y*esp*0.7);
			glEnd();
			
			//b
			glBegin(GL_QUADS);
				glVertex2f(x*esp,y*esp);
				glVertex2f(x*esp*0.5,y*esp);
				glVertex2f(x*esp*0.5,0);
				glVertex2f(x*esp,0);
			glEnd();
			
			//c
			glBegin(GL_QUADS);
				glVertex2f(x*esp,0);
				glVertex2f(x*esp*0.5,0);
				glVertex2f(x*esp*0.5,-y*esp);
				glVertex2f(x*esp,-y*esp);
			glEnd();
			
			//d
			glBegin(GL_QUADS);
			glVertex2f(x*esp,-y*esp*0.7);
			glVertex2f(-x*esp,-y*esp*0.7);
			glVertex2f(-x*esp,-y*esp);
			glVertex2f(x*esp,-y*esp);
			glEnd();
			
			//e
			glBegin(GL_QUADS);
			glVertex2f(-x*esp*0.5,y*esp);
			glVertex2f(-x*esp,y*esp);
			glVertex2f(-x*esp,0);
			glVertex2f(-x*esp*0.5,0);
			glEnd();
			
			//f
			glBegin(GL_QUADS);
			glVertex2f(x*esp,y*0.15);
			glVertex2f(-x*esp,y*0.15);
			glVertex2f(-x*esp,-y*0.15);
			glVertex2f(x*esp,-y*0.15);
			glEnd();
			break;
		case '0' :
			//a
			glBegin(GL_QUADS);
			glVertex2f(x*esp,y*esp);
			glVertex2f(-x*esp,y*esp);
			glVertex2f(-x*esp,y*esp*0.7);
			glVertex2f(x*esp,y*esp*0.7);
			glEnd();
			
			//b
			glBegin(GL_QUADS);
			glVertex2f(x*esp,y*esp);
			glVertex2f(x*esp*0.5,y*esp);
			glVertex2f(x*esp*0.5,0);
			glVertex2f(x*esp,0);
			glEnd();
			
			//c
			glBegin(GL_QUADS);
			glVertex2f(x*esp,0);
			glVertex2f(x*esp*0.5,0);
			glVertex2f(x*esp*0.5,-y*esp);
			glVertex2f(x*esp,-y*esp);
			glEnd();
			
			//d
			glBegin(GL_QUADS);
			glVertex2f(x*esp,-y*esp*0.7);
			glVertex2f(-x*esp,-y*esp*0.7);
			glVertex2f(-x*esp,-y*esp);
			glVertex2f(x*esp,-y*esp);
			glEnd();
			
			//e
			glBegin(GL_QUADS);
			glVertex2f(-x*esp*0.5,0);
			glVertex2f(-x*esp,0);
			glVertex2f(-x*esp,-y*esp);
			glVertex2f(-x*esp*0.5,-y*esp);
			glEnd();
			
			//f
			glBegin(GL_QUADS);
			glVertex2f(-x*esp*0.5,y*esp);
			glVertex2f(-x*esp,y*esp);
			glVertex2f(-x*esp,0);
			glVertex2f(-x*esp*0.5,0);
			glEnd();
			
			break;
//		case '/' :
//			
//			break;
//		case 'x' :
//			
//			break;
//		case '+' :
//			
//			break;
//		case '-' :
//			
//			break;
			
			
		}
		glTranslatef(x*2.0,0,0);
		
	}
	
	glPopMatrix();
	
}



class Circulo{
	
private:
	float ini_x;
	float ini_y;
	float pos_x;
	float pos_y;
	float pos_z;
	float color_R;
	float color_G;
	float color_B;
	float color_A;
	int radio;
	bool clicleable;
	double tEntrada;
	float scale_x;
	float scale_y;
	bool focus;
	string cadena;
	
	
public:
	
	Circulo(){
		this->pos_x = 0;
		this->pos_y = 0;
		this->pos_z = 0;
		this->color_R = 1.0;
		this->color_G = 1.0;
		this->color_B = 1.0;
		this->color_A = 0.0;
		this->radio = 10;
		this->clicleable=false;
		this->tEntrada = glutGet(GLUT_ELAPSED_TIME)/1000.0;
		this->scale_x=1;
		this->scale_y=1;
		
	}
	
	Circulo(float x=0,float y=0,float colR=0,float colG=0,float colB=0,float colA=1,int r=5,double tInicio = glutGet(GLUT_ELAPSED_TIME)/1000 ){
		
		this->ini_x = x;
		this->ini_y = y;
		this->scale_x=1;
		this->scale_y=1;
		this->pos_x = x;
		this->pos_y = y;
		this->pos_z = -rand() % 100-80;
		this->color_R = colR;
		this->color_G = colB;
		this->color_B = colG;
		this->color_A = colA;
		this->radio = r;
		this->clicleable=false;
		this->tEntrada = tInicio;
		this->focus=false;
	}
	
	void dibujar(){
		
		
		glColor4f(this->color_R,this->color_G,this->color_B,this->color_A);
		
		
		glTranslated(this->pos_x,this->pos_y,this->pos_z);
		
		//glRotated(60,1,0,0);
		//glRotated(a,0,0,1);
		glutSolidSphere(radio,50,50);
		
		
		
	}
	
	
	void numero();
	
	
	void animarLateralesEntrada(){
		
		const double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
		
		GLdouble tiempo = (t-this->tEntrada); //tiempo q  esta siendo mostrado 
		//expansion hacia  afuera
		//cout<<tiempo<<endl;
		
		
//		x = r * cos(α) + x0
//			y = r * sen(α) + y0
		
		if(tiempo<=2){
			//this->pos_x = this->ini_x + 150*tiempo - 30*tiempo*tiempo;
			//float temp = 0.0; //radio temporal
			
			this->pos_x = this->ini_x + tiempo*70 * cos(tiempo*(5.1416-tiempo));
			this->pos_y = this->ini_y + tiempo*70 * sin(tiempo*(5.1416-tiempo));
			this->color_A =0.0;
			this->color_A =tiempo/2.0;
			//cout<<color_A<<endl;
		}
		
	}
	
	float getX(){
		return this->pos_x;
	}
	float getY(){
		return this->pos_y;
	}
	
};




Circulo cCentral = Circulo(0,0,	1,NULL,NULL,1,	80, NULL);

Circulo listaCirculos[8] = {
	Circulo(NULL,NULL	,0.2	,0.2	,0		,1,45,NULL),//0
	Circulo(NULL,NULL	,0.1	,0.1	,1		,1,45,NULL),//1
	Circulo(NULL,NULL	,0.6	,0		,0.5	,1,45,NULL),//2
	Circulo(NULL,NULL	,0.5	,0.2	,0.1	,1,45,NULL),//3
	Circulo(NULL,NULL	,0.5	,0		,0.2	,1,45,NULL),//4
	Circulo(NULL,NULL	,0.2	,0.1	,0		,1,45,NULL),//5
	Circulo(NULL,NULL	,0.2	,0.5	,0.0	,1,45,NULL),//6
	Circulo(NULL,NULL	,1		,NULL	,NULL	,1,45,NULL)};//7
/* GLUT callback Handlers */



static void resize(int w, int h)
{
	if (w==0||h==0) return;
	glViewport(0,0,w,h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho(-w/2,w/2,-h/2,h/2,-15,200);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
}

static void display(void)
{
	const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	const double a = t*90.0;
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
		cCentral.dibujar();
	glPopMatrix();
	
	glPushMatrix();
		listaCirculos[0].dibujar();
	glPopMatrix();
	
	glPushMatrix();
		glRotatef(45,0,0,1);
		listaCirculos[1].dibujar();
	glPopMatrix();
	
	glPushMatrix();
		glRotatef(90,0,0,1);
		listaCirculos[2].dibujar();
	glPopMatrix();
	
	glPushMatrix();
		glRotatef(135,0,0,1);
		listaCirculos[3].dibujar();
	glPopMatrix();
	
	glPushMatrix();
		glRotatef(180,0,0,1);
		listaCirculos[4].dibujar();
	glPopMatrix();
	
	glPushMatrix();
		glRotatef(225,0,0,1);
		listaCirculos[5].dibujar();
	glPopMatrix();
	
	glPushMatrix();
		glRotatef(270,0,0,1);
		listaCirculos[6].dibujar();
	glPopMatrix();
	
	
	glPushMatrix();
		glRotatef(270+45,0,0,1);
		listaCirculos[7].dibujar();
	glPopMatrix();
	
	
	
	int x=60;
	int y=50;
	
	glColor4f(0,0,1,1);
	dibujarOperacion( "01298764586", 20);
	
			
			
	//ejes
//	
//	glPushMatrix();
//		glBegin(GL_LINES);
//		glVertex2f(x/3,y);	glVertex2f(x/3,-y);
//		glVertex2f(-x/3,y);	glVertex2f(-x/3,-y);
//		glEnd();
//	glPopMatrix();
//	
//	
//	
//	glColor4f(0,0,0,1);
//	//central
//	glPushMatrix();
//	glBegin(GL_QUADS);
//	glVertex2f(x,y);
//	glVertex2f(-x,y);
//	glVertex2f(-x,-y);
//	glVertex2f(x,-y);
//	glEnd();
//	glPopMatrix();
//	
	
	
	
	
	glutSwapBuffers();

}


static void key(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27 :
	case 'q':
		exit(0);
		break;
		
	case '+':
		slices++;
		stacks++;
		break;
		
	case '-':
		if (slices>3 && stacks>3)
		{
			slices--;
			stacks--;
		}
		break;
	}
	
	glutPostRedisplay();
}





static void idle(void)
{	
	glutPostRedisplay();
	listaCirculos[0].animarLateralesEntrada();
	listaCirculos[1].animarLateralesEntrada();
	listaCirculos[2].animarLateralesEntrada();
	listaCirculos[3].animarLateralesEntrada();
	listaCirculos[4].animarLateralesEntrada();
	listaCirculos[5].animarLateralesEntrada();
	listaCirculos[6].animarLateralesEntrada();
	listaCirculos[7].animarLateralesEntrada();
	//GetCursorPos(&mousePos);
	//cout<<mousePos.x<<"  "<<mousePos.y<<endl;
}

const GLfloat light_ambient[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(10,10);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	
	glutCreateWindow("GLUT Shapes");
	glEnable (GL_BLEND); glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);
	
	glClearColor(1,1,1,1);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	
	glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	
	glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	
	glutMainLoop();
	
	return EXIT_SUCCESS;
}

