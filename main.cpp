#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Conexion.h"
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <unistd.h>
#include <string>
#include <list>
#include <stdio.h>
#include <string.h>


#define ALTURA 640
#define ANCHO 480
using namespace std;


//control de FPS
GLint gFramesPerSecond = 0;

void FPS(void) {
	static GLint Frames = 0;         // frames averaged over 1000mS
	static GLuint Clock;             // [milliSeconds]
	static GLuint PreviousClock = 0; // [milliSeconds]
	static GLuint NextClock = 0;     // [milliSeconds]
	
	++Frames;
	Clock = glutGet(GLUT_ELAPSED_TIME); //has limited resolution, so average over 1000mS
	if ( Clock < NextClock ) return;
	
	gFramesPerSecond = Frames/1.0; // store the averaged number of frames per second
	
	PreviousClock = Clock;
	NextClock = Clock+1000; // 1000mS=1S in the future
	Frames=0;
}




//variables globales
const GLfloat light_ambient[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

struct nodo{
	int n1;
	int n2;
	int op;
};
nodo operaciones[100];
int posNodo=0;

int ubiresp=1;
int resTemp=0;
int opciones[8] = {999,999,999,999,999,999,999,999};
int ubiOpciones=0;
int cor=0;//num correctos
int inc=0;//contador ins

//funcionesGlobales
string randomOperation();//revuelve una operacoin al azar
string dibujarTexto();//dibuja texto en la pantalla (numeros y letras)


//funciones glut
static void resize(int w, int h);//configuracion de tamaño de pantalla
static void display(void);//contenido de lo q se muestra en pantalla
static void key(unsigned char key, int x, int y);//escucha de una tecla
static void idle(void);//hilo recursivo
static void MouseMove(int x,int y);
static void mouse(int button,int state,int x,int y);
//Clases

//Class Circulo
class Circulo{	

	private:
		int ubicacion;
		float ini_x;		//posicion x desde la q  se mueve o inicial
		float ini_y;		//posicion y desde la q  se mueve o inicial
		float ini_z;
		float pos_x;		//posicion x actual
		float pos_y;		//posicion y actual
		float pos_z;		//posicion z actual
		float color_R;		//nivel de rojo actual [0.0,1.0]
		float color_G;		//nivel de verde actual [0.0,1.0]
		float color_B;		//nivel de azul actual [0.0,1.0]
		float color_A;		//nivel de opacidad actual [0.0,1.0]
		int radio;			//radio del cirulo
		bool clicleable;	//indica  si es clicleable
		double tEntrada;	//tiempo en q  el objeto se hizo presente o empezo a  moverce
		bool focus;			//si esta siendo seleccionado
		string cadena;		//la  cadena q contiene el circulo
		float angulo;		//el angulo en q el texto se pone
		string operation;	//operacion q contiene
		int num1;
		int num2;
		int respuesta;
	
	public:
		//constructor
		
		void setTEntrada(double t){
			this->tEntrada=t;
		}
		
		
		Circulo(int ubi,float x=0,float y=0,float z=0, float colR=0,float colG=0,float colB=0,float colA=1,int r=5,double tInicio = glutGet(GLUT_ELAPSED_TIME)/1000 ){
			this->ubicacion= ubi;
			this->ini_x = x;
			this->ini_y = y;
			
			this->pos_x = x;
			this->pos_y = y;
			this->pos_z = z;
			this->color_R = colR;
			this->color_G = colB;
			this->color_B = colG;
			this->color_A = colA;
			this->radio = r;
			this->clicleable=false;
			this->tEntrada = tInicio;
			this->focus=false;
			this->angulo=(ubi+1)*45.0;
			
			
			inicilializarCirculo();
			
			
			
			
		}
		
		bool getFocus(){
			return this->focus;
		}
		
		void setFocus(bool f){
			this->focus=f;
		}
		
		int getPoX(){
			return this->pos_x;
		}
		
		int getPosY(){
			return this->pos_y;
		}
		
		int getRadio(){
			return this->radio;
		}
		
		void inicilializarCirculo(){
			if(this->ubicacion==0){
				srand(time(0));
				
			}
			this->operation=randomOperation();	
			
			declarar();
			
			if(this->ubicacion==0){
				
				ubiresp = (rand()%8)+1;
			}
		}
		
		
		void declarar(){
			
			if(this->ubicacion==0){//si es el central
				this->num1=randomNumero();
				this->num2=randomNumero();
				if(!verificarRespuesta(this->num1 , this->operation , this->num2)){
					declarar();//volvemos a resear el numero si ya esta repetida la operacion
				}else{
					this->respuesta= (int)operar(this->num1 , this->operation , this->num2);
					resTemp=this->respuesta;
				}
			}else{// si son los laterales
				if(ubiresp == this->ubicacion){
					this->num1=resTemp;
					opciones[ubiresp-1]=resTemp;
					if(ubiOpciones<7){
						ubiOpciones++;
					}else{
						ubiOpciones=0;
					}
				}else{
					this->num1=randomNumero();
					if(!verificarOpciones(this->num1) || resTemp == this->num1){
						declarar();
					}
					
				}
		
			}
			
		}
		
		bool verificarOpciones(int n){
			bool resp = true;
			for(int i=0;i<ubiOpciones;i++){
				if(n == opciones[i]){
					resp= false;//recorrer par a saber si esta repetido
					break;
				}
			}
			if(resp){//si no esta repetido
				opciones[ubiOpciones]=n;
				if(ubiOpciones<7){
					ubiOpciones++;
				}else{
					ubiOpciones=0;
				}
			}
			
		}
		
		
		bool verificarRespuesta(int n1 , string op , int n2){
			bool resp = false;
			
			switch(op.at(0)){
			case '*':
				if(operar(n1,op,n2)<100){
					resp = true;
				}
				break;
			case '/':
				if( operar(n1,op,n2) - (int)operar(n1,op,n2) == 0 && n2!=0){
					resp =  true;
				}
				break;
			case '+':
				if(operar(n1,op,n2)<100){
					resp = true;
				}
				break;
			case '-':
				if(operar(n1,op,n2)>=0){
					resp = true;
				}
				
				break;
			}
			
			for(int i=0;i<posNodo;i++){
				if(operaciones[i].n1 == n1  && operaciones[i].n2 == n2  ){
					resp = false;
					break;
				}
			}
			if(resp && this->ubicacion==0){
				operaciones[posNodo].n1=n1;
				operaciones[posNodo].n2=n2;
				operaciones[posNodo].op;
				posNodo++;
			}
			
			return resp;
		}
		
		float operar(int n1 , string op , int n2){
			float resp = 999;
			switch(op.at(0)){
			case '*':
				resp = n1*n2;
				break;
			case '/':
				resp = 1.0*n1/n2;
				break;
			case '+':
				resp = n1+n2;
				break;
			case '-':
				resp = n1-n2;
				break;
			}
			return resp;
		}
		
	
		void rotarTexto(float rot){
			this->angulo=rot;
		}
	
		void dibujar(){
			
			if(this->ubicacion == 0){
				
				glColor4f(this->color_R,this->color_G,this->color_B,this->color_A);
				glTranslated(this->pos_x,this->pos_y,this->pos_z);
				//glutSolidSphere(radio,50,50);//dibuja un circulo
				//glutWireSphere(radio,50,50);
				//glutSolidTorus(radio-60,radio-20,50,50);
				glRotated(this->angulo,1,1,1);
				glutSolidTorus(radio-60,radio-20,50,50);
				glRotated(this->angulo,-1,-1,-1);
				string num1=to_string(this->num1);//contenido
				string num2=to_string(this->num2);
				string op = this->operation;
				string contenido = num1+op+num2;
				glColor4f(1-this->color_R,1-this->color_G,this->color_B,this->color_A);
				glTranslatef(0,0,-radio+1);
				
				dibujarTexto( contenido, this->radio*cos(20)/contenido.size()*2);
				
			}else{
				glColor4f(this->color_R,this->color_G,this->color_B,this->color_A);
				glTranslated(this->pos_x,this->pos_y,this->pos_z);
				
				if(this->focus){//si esta el muse  ensima del circulo
					glScalef(1.1,1.1,1);//agrandar  10% en x e y
				}
				
				glutSolidSphere(radio,50,50);
				
				
				if(ubiresp != ubicacion){
					
					string num1=to_string(this->num1);
					string op = this->operation;
					string contenido = num1;
					glColor4f(1-this->color_R,1-this->color_G,this->color_B,this->color_A);
					glTranslatef(0,0,radio+1-50);
					
					dibujarTexto( contenido, this->radio*cos(20)/contenido.size()*2);
					
				}else{
					
					string contenido = to_string(resTemp);
					glColor4f(1-this->color_R,1-this->color_G,this->color_B,this->color_A);
					glTranslatef(0,0,radio+1-50);
					
					dibujarTexto( contenido, this->radio*cos(20)/contenido.size()*2);
					
				};
				
			};
			
		}


	static void dibujarTexto(string txt,int tam){
		float x = tam;
		if(txt.size()==1){
			x=tam/1.5;
		}
		float y = x*1.5;
		float esp =0.80;
		
		string temp ;
		glPushMatrix();
		glTranslatef(-x*2.0*((txt.length()/2.0)-0.5),0,0);
		
		for(int i=0 ; i<txt.length() ; i++){
			
			temp = txt.substr(i,1);
			
			switch(temp.at(0)){
				
			case 'C':
			case 'c':
				//a
				glBegin(GL_QUADS);
				glVertex2f(x*esp,y*esp);
				glVertex2f(-x*esp,y*esp);
				glVertex2f(-x*esp,y*esp*0.7);
				glVertex2f(x*esp,y*esp*0.7);
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
			case 'o':
			case 'O':
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
			case 'r':
			case 'R':
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
				//patita de la r
				glBegin(GL_QUADS);
				glVertex2f(0, 0);
				glVertex2f((x*esp*0.5)-x, 0);
				glVertex2f(x*esp*0.5, -y*esp);
				glVertex2f(x*esp, -y*esp);
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
			case 'e':
			case 'E':
				//a
				glBegin(GL_QUADS);
				glVertex2f(x*esp,y*esp);
				glVertex2f(-x*esp,y*esp);
				glVertex2f(-x*esp,y*esp*0.7);
				glVertex2f(x*esp,y*esp*0.7);
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
			case 't':
			case 'T':
				
				glTranslatef(-x/2,0,0);
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
				glTranslatef(x/2,0,0);
				
				//a
				glBegin(GL_QUADS);
				glVertex2f(x*esp,y*esp);
				glVertex2f(-x*esp,y*esp);
				glVertex2f(-x*esp,y*esp*0.7);
				glVertex2f(x*esp,y*esp*0.7);
				glEnd();
				
				break;
			case 's':
			case 'S':
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
			case 'p':
			case 'P':
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
			case 'n':
			case 'N':
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
				//linea media n
				glBegin(GL_QUADS);
				glVertex2f(-x*esp*0.5,y*esp);
				glVertex2f(-x*esp,y*esp);
				glVertex2f(x*esp*0.5,-y*esp);
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
			case 'i':
			case 'I':
				glTranslatef(-x/2,0,0);
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
				glTranslatef(x/2,0,0);
				break;
			case '1' :
				glBegin(GL_QUADS);
					glVertex2f(x*esp,y*esp);
					glVertex2f(x*esp*0.5,y*esp);
					
					glVertex2f(x*esp*0.5,-y*esp);
					glVertex2f(x*esp,-y*esp);
				glEnd();
				glBegin(GL_QUADS);
					glVertex2f(x*esp,y*esp);
					glVertex2f(x*esp*0.5,y*esp);
					glVertex2f(-x*esp,0);
					glVertex2f(-x*esp*0.5,0);
				glEnd();		
				break;
			case '2' :
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
			case '+' :
				//g
				glBegin(GL_QUADS);
					glVertex2f(x*esp,y*0.15);
					glVertex2f(-x*esp,y*0.15);
					glVertex2f(-x*esp,-y*0.15);
					glVertex2f(x*esp,-y*0.15);
				glEnd();			
				glRotatef(90,0,0,1);
				//g
				glBegin(GL_QUADS);
					glVertex2f(x*esp,y*0.15);
					glVertex2f(-x*esp,y*0.15);
					glVertex2f(-x*esp,-y*0.15);
					glVertex2f(x*esp,-y*0.15);
				glEnd();			
				glRotatef(-90,0,0,1);
				break;
			case '*' :
				glRotatef(45,0,0,1);//roto 45°
				//coloco el mismo codigo de mas pero antes lo rote 45°
				//g
				glBegin(GL_QUADS);
					glVertex2f(x*esp,y*0.15);
					glVertex2f(-x*esp,y*0.15);
					glVertex2f(-x*esp,-y*0.15);
					glVertex2f(x*esp,-y*0.15);
				glEnd();			
				glRotatef(90,0,0,1);
				//g
				glBegin(GL_QUADS);
					glVertex2f(x*esp,y*0.15);
					glVertex2f(-x*esp,y*0.15);
					glVertex2f(-x*esp,-y*0.15);
					glVertex2f(x*esp,-y*0.15);
				glEnd();			
				glRotatef(-90,0,0,1);
				glRotatef(-45,0,0,1);//una vez que acabo la  ejecuion de codigo del "+" q volteado 45° es ahora "x" volvemos a girarlo -45° 
				break;
			case '-' :
				//g
				glBegin(GL_QUADS);
					glVertex2f(x*esp,y*0.15);
					glVertex2f(-x*esp,y*0.15);
					glVertex2f(-x*esp,-y*0.15);
					glVertex2f(x*esp,-y*0.15);
				glEnd();
				break;
			case '/' :	
				glBegin(GL_QUADS);//dibujando linea central
					glVertex2f(x*esp,y*0.15);
					glVertex2f(-x*esp,y*0.15);
					glVertex2f(-x*esp,-y*0.15);
					glVertex2f(x*esp,-y*0.15);
				glEnd();			
				glTranslatef(0,y/2.0,0);//trasladas  arriba de la  linea
				glBegin(GL_POLYGON);//dibujando cirulo arriba
					float rad = x/3.0;
					for(float  i=0; i< 3.1416*2;i=i+0.01){
						glVertex2f(rad*cos(i),rad*sin(i));
					}
				glEnd();
				glTranslatef(0,-y,0);//dibujando circulo abajo
				glBegin(GL_POLYGON);
					for(float  i=0; i< 3.1416*2;i=i+0.01){
						glVertex2f(rad*cos(i),rad*sin(i));
					}
				glEnd();			
				glTranslatef(0,y/2.0,0);
				break;			
			}
			glTranslatef(x*2.0,0,0);
		}
		glPopMatrix();
	}
	
	int randomNumero(){
		
		 return rand() % 100;
		
	}
	
	
	
	
	
	
	
	string randomOperation(){
		
		int op=rand()%2;
		
		string temp="";
		
		switch(op){
		case 0:
			temp="+";
			break;
		case 1:
			temp="-";
			break;
		case 2:
			temp="*";
			
			break;
		case 3:
			temp="/";
			break;
		default:
			temp="+";
			break;
		}
		return temp;
	}
	
	
	
	void animarLateralesEntrada(){
		
		const double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
		
		GLdouble tiempo = (t-this->tEntrada); //tiempo q  esta siendo mostrado 
		
		if(tiempo<=2){
			//this->pos_x = this->ini_x + 150*tiempo - 30*tiempo*tiempo;
			//float temp = 0.0; //radio temporal
			
			
			//movimiento cirlar animacion
			this->pos_x = this->ini_x + tiempo*70 * cos(tiempo*(5.1416-tiempo));
			this->pos_y = this->ini_y + tiempo*70 * sin(tiempo*(5.1416-tiempo));
			
		
			//applciacion de la matris de rotacion par a obtener la posicion cuando gira
			int temp_x =  this->pos_x * cos((3.14159/180)*this->angulo)  -  (this->pos_y*sin((3.14159/180)*this->angulo));
			int temp_y  =  this->pos_x * sin((3.14159/180)*this->angulo)    +  (this->pos_y*cos((3.14159/180)*this->angulo));
			this->pos_x = temp_x;
			this->pos_y = temp_y;
			
			this->color_A =0.0;
			this->color_A =tiempo/2.0;
						
			
			//cout<<color_A<<endl;
		}else{
		
			this->pos_y=this->pos_y+sin(t)*0.2;
			
		}
	}
	void animarCentralEntrada(){
		
		const double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
		GLdouble tiempo = (t-this->tEntrada); //tiempo q  esta siendo mostrado 
		
		if(tiempo<=2){
			//this->pos_x = this->ini_x + 150*tiempo - 30*tiempo*tiempo;
			//float temp = 0.0; //radio temporal
			this->angulo=tiempo*90;
			this->color_A =0.0;
			this->color_A =tiempo;
			//cout<<color_A<<endl;
		}else{//animacion despues de la  entrada
			this->pos_y=this->ini_y+sin(t)*10;
			this->angulo=tiempo*90;
			//cout<<this->pos_y;
		}
	}
	
	float getX(){
		return this->pos_x;
	}
	float getY(){
		return this->pos_y;
	}
	
};


Circulo cCentral = Circulo(0,0,0,-200,	1,NULL,NULL,1,	80, NULL);//circulo q va en el centro
//Variable glovales a partir de class Circulo

Circulo listaCirculos[8] = {
	Circulo(1,NULL,NULL,-200	,0.2	,0.2	,0		,1,45,NULL),//0
	Circulo(2,NULL,NULL,-200	,0.1	,0.1	,1		,1,45,NULL),//1
	Circulo(3,NULL,NULL,-200	,0.6	,0		,0.5	,1,45,NULL),//2
	Circulo(4,NULL,NULL,-200	,0.5	,0.2	,0.1	,1,45,NULL),//3
	Circulo(5,NULL,NULL,-200	,0.2	,0		,0.2	,1,45,NULL),//4
	Circulo(6,NULL,NULL,-200	,0.2	,0.1	,0		,1,45,NULL),//5
	Circulo(7,NULL,NULL,-200	,0.2	,0.5	,0.0	,1,45,NULL),//6
	Circulo(8,NULL,NULL,-200	,1		,NULL	,NULL	,1,45,NULL) //7
};

//funcion principal
int main(int argc, char *argv[])
{	//inicializacion
	
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
	glutPassiveMotionFunc(MouseMove); 
	glutMouseFunc(mouse);
	
	glClearColor(0.5,0.5,0.5,0.8);
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
	Conexion *c = new Conexion();
	glutMainLoop();
	
	return EXIT_SUCCESS;
}

//Implementacion de funciones Globales

static void resize(int w, int h)
{
	glEnable(GL_DEPTH_TEST);
	
	/* Setup the view of the cube. */
	glMatrixMode(GL_PROJECTION);
	gluPerspective( /* field of view in degree */ 330.0,
				   /* aspect ratio */ 1.0,
				   /* Z near */ 1.0, /* Z far */ 20.0);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0.0, 0.0, 5.0,  /* eye is at (0,0,5) */
			  0.0, 0.0, -50,      /* center is at (0,0,0) */
			  0.0, -1.0, -1.0);      /* up is in positive Y direction */
	glOrtho(-w/2,w/2,-h/2,h/2,-15,200);
	
	/*
	if (w==0||h==0) return;
	glViewport(0,0,w,h);
	glMatrixMode (GL_PROJECTION);
	//glLoadIdentity ();
	
	glOrtho(-w/2,w/2,-h/2,h/2,-15,200);
	
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();*/
}

static void display(void)
{	
	const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	const double a = t*90.0;
			

	//printf("FPS %d\n",gFramesPerSecond);
	
	//limiado de  bufer

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	glPushMatrix();
		cCentral.dibujar();
	glPopMatrix();

	
	glPushMatrix();
		listaCirculos[0].dibujar();
		
	glPopMatrix();
	
	glPushMatrix();
	
		listaCirculos[1].dibujar();
	glPopMatrix();
	
	glPushMatrix();		
		listaCirculos[2].dibujar();
	glPopMatrix();
	
	glPushMatrix();
		listaCirculos[3].dibujar();
	glPopMatrix();
	
	glPushMatrix();
		listaCirculos[4].dibujar();
	glPopMatrix();
	
	glPushMatrix();
		listaCirculos[5].dibujar();
	glPopMatrix();
	
	glPushMatrix();
		listaCirculos[6].dibujar();
	glPopMatrix();
	
	glPushMatrix();
		listaCirculos[7].dibujar();
	glPopMatrix();
	
	glPushMatrix();
		
		glColor4f(0,0,0.5,1);
		glTranslated(-400,300,0);
	
		if((int)(60-t)%10 == 0){//cada 10 s  pinta rojo el puntaje
			glColor4f(0.5,0,0,1);
			glScaled(1.2,1.1,1);
			Circulo::dibujarTexto(to_string((int)(60-t)),20);//pintado rojo
			
		}else{
			if((int)(60-t) <= 5 && 0<=(int)(60-t)){//si faltan entre 5 y 0s
				glColor4f(1,0,0,1);
				glScaled(1.2,1.1,1);
				Circulo::dibujarTexto(to_string((int)(60-t)),20);
			}else{
				if(0<=(int)(60-t)){ //cuando ya paso el tiempo
					Circulo::dibujarTexto(to_string((int)(60-t)),20);
					glTranslated(700,-600,0);
					string showpoints = "points ";
						showpoints += to_string( cor*5 - inc );
					Circulo::dibujarTexto(showpoints,20);
					glTranslated(-270,0,0);
				}
				
			}
		}
		glPopMatrix();
		if(0>(int)(60-t)){
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glPushMatrix();
			glTranslated(0,200,0);
			Circulo::dibujarTexto("points "+to_string( cor*5 - inc ),30);
			glTranslated(0,-200,0);
			Circulo::dibujarTexto("correctos "+to_string( cor ),30);
			glTranslated(0,-200,0);
			Circulo::dibujarTexto("incorrectos "+to_string( inc ),30);
			glPopMatrix();
		}
	glutSwapBuffers();
}


static void mouse(int button,int state,int x,int y){
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		
		
		bool band=false;//bandera  q indica si se presino algun circulo
		
		for(int i=0;i<8;i++){
			if(listaCirculos[i].getFocus()){
				band=true;
				break;
			}
		}
		
		if(band){
			
			if(listaCirculos[ubiresp-1].getFocus()){
				//cout<<endl<<"correctosssssssssssssssss"<<ubiresp;
				cor++;
			}else{
				//cout<<endl<<"incorrecto"<<ubiresp;
				inc++;
			}
			
			cCentral.setTEntrada(glutGet(GLUT_ELAPSED_TIME)/1000.0);
			cCentral.inicilializarCirculo();
			for(int i=0;i<8;i++){
				listaCirculos[i].setTEntrada(glutGet(GLUT_ELAPSED_TIME)/1000.0);
				listaCirculos[i].inicilializarCirculo();
			}
			
			
			
			
		}
		
		
	}
	/**cout<<endl<<" "<<cor<<" "<<inc;
	**/
}

 static void MouseMove(int x, int y)
{
	int _X = x-(640/2);
	int _Y =-y+(480/2);
	//cout<<endl<<_X<<"  "<<_Y<<endl;
	for(int i=0; i<8;i++){
		if( ( abs (listaCirculos[i].getPoX() - _X ) <= listaCirculos[i].getRadio() ) && (abs (listaCirculos[i].getPosY() - _Y ) <= listaCirculos[i].getRadio()) ){
			listaCirculos[i].setFocus(true);
			//cout<<endl<<"colision "<<i+1<<"    <"<<_X<<","<<_Y<<">";
			if(i+1==ubiresp){
		//		cout<<"correcto";
			}
		}else{
			listaCirculos[i].setFocus(false);
		}
	}
}

static void key(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27 :
	case 'q':
	case 'Q':
		
		
		//presinar "q para  salir"
		exit(0);
		break;
		
	case 'p'://presiona p para pausar
	case 'P':
		
		cCentral.setTEntrada(glutGet(GLUT_ELAPSED_TIME)/1000.0);
		cCentral.inicilializarCirculo();
		
		for(int i=0;i<8;i++){
			listaCirculos[i].setTEntrada(glutGet(GLUT_ELAPSED_TIME)/1000.0);
			listaCirculos[i].inicilializarCirculo();
		}
		break;
		
	}
	
	glutPostRedisplay();
}

//hilo de ejecucion continua
static void idle(void)
{	
	#define REGULATE_FPS
	#ifdef REGULATE_FPS
		static GLuint PreviousClock=glutGet(GLUT_ELAPSED_TIME);
		static GLuint Clock=glutGet(GLUT_ELAPSED_TIME);
		static GLfloat deltaT;
		
		Clock = glutGet(GLUT_ELAPSED_TIME);
		deltaT=Clock-PreviousClock;
		if (deltaT < 35) {return;} else {PreviousClock=Clock;}
	#endif
		
	

	cCentral.animarCentralEntrada();
		
	listaCirculos[0].animarLateralesEntrada();
	listaCirculos[1].animarLateralesEntrada();
	listaCirculos[2].animarLateralesEntrada();
	listaCirculos[3].animarLateralesEntrada();
	listaCirculos[4].animarLateralesEntrada();
	listaCirculos[5].animarLateralesEntrada();
	listaCirculos[6].animarLateralesEntrada();
	listaCirculos[7].animarLateralesEntrada();
	
	FPS(); //only call once per frame loop 
	
	glutPostRedisplay();

}
