#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;


struct alumno{
	int cod;
	alumno *sgt;
};

struct escuela{
	string nombre;
	alumno *ListAlumnos;
	escuela *sgte;
};
typedef struct escuela *E; //defines escula como puntero

E cabezaEscuelas,nodoEscuela;

void add(escuela &cabezaEscuelas){
	/*if(!cabezaEscuelas){
		nodoEscuela = new (struct escuela);
		gets(nodoEscuela->nombre);
	}*/
	nodoEscuela = new(struct escuela);
	cout<<"nombre : ";
	gets(nodoEscuela->nombre);
}


int main(){
	E lista=NULL;
}
/*
struct dato {
	int i;
	
	dato *s;
}*a, *i, *p, *e;

int da;

int buscar(int d);
void insertar(int dat);
void mostrar(void);
void borrar(void);
void menu(void);
void guardar(void);
void cargar(void);

int main()
{
	menu();
	return 0;
}

void menu(void)
{
	int opc,da;
	do
	{
		cout<<"1 - Buscar datos";
		cout<<"\t2 - Insertar datos";
		cout<<"\t3 - Mostrar todos los datos";
		cout<<"\t4 - Borrar un dato";
		cout<<"\t5 - Guardar datos a Archivo";
		cout<<"\t6 - Cargar datos de Archivo";
		cout<<"\t0 - Finalizar";
		cout<<"\nSeleccione opcion: ";
		cin>>opc;
		switch(opc)
		{
		case 0: cout<<"\n\nFinaliza el programa";
		
		//no hay que olvidarse que antes de
		//abandonar el barco ...
		//hay que hundir todos los botes
		// o sea usar delete para eliminar
		//toda la lista
		p=i;
		while(p)
		{
			a=p;
			p=p->s;
			delete(a);
		}
		exit(0);
		case 1: cout<<"\n\nIngrese dato a buscar: ";
		cin>>da;
		if(buscar(da))
			cout<<"\n\nDato existe";
		else
			cout<<"\n\nDato NO EXISTE";
		
		break;
		case 2: cout<<"Ingrese dato: ";
		cin>>da;
		insertar(da);
		break;
		case 3: mostrar();
		break;
		case 4: borrar();
		break;
		case 5: guardar();
		break;
		case 6: cargar();
		break;
		//por las dudas que el operador ingrese
		//cualquier verdura, fruta u otro tipo de hierba
		default: cout<<"\n\nOPCION NO VALIDA!!!";
		
		}
	}while(opc);
}

void mostrar(void)
{
	int cont=1;
	if(!i)
	{
		cout<<"\n\nNO HAY LISTA PARA MOSTRAR";
		
		return;
	}
	p=i;
	cout<<endl<<endl;
	while(p)
	{
		cout<<cont++<<" - Valor = "<<p->i<<endl;
		p=p->s;
	}
	cout<<"\n\nEso es todo";
	
}

int buscar(int d)
{
	if (!i)
	{
		cout<<"No hay datos en la lista!!!";
		
		return(0);
	}
	p=i;
	a=NULL;
	while(p->s && p->i<d)
	{
		a=p;
		p=p->s;
	}
	return(p->i==d?1:0);
}

void insertar(int dat)
{
	if(!i)
	{
		i=new(dato);
		i->s=NULL;
		i->i=dat;
		return;
	}
	if(buscar(dat))
	{
		cout<<"\n\nDato existente";
		
		return;
	}
	e=new(dato);
	e->i=dat;
	if(p==i && p->s)
	{
		e->s=p;
		i=e;
		return;
	}
	if(p==i && !p->s)
	{
		if(p->i < e->i)
		{
			p->s=e;
			e->s=NULL;
		}
		else
		{
			e->s=p;
			i=e;
		}
		return;
	}
	if(p->s)
	{
		a->s=e;
		e->s=p;
		return;
	}
	if(e->i > p->i)
	{
		e->s=NULL;
		p->s=e;
	}
	else
	{
		a->s=e;
		e->s=p;
	}
}

void borrar(void)
{
	cout<<"\n\nIngrese dato a eliminar: ";
	cin>>da;
	if(buscar(da))
	{
		if(a)
			a->s=p->s;
		else
			i=p->s;
		delete(p);
		cout<<"\n\nDato eliminado";
	}
	else
			  cout<<"\n\nDato no se encuentra";
	
}

void guardar(void)
{
	FILE *arch;
	arch=fopen("DATOS-A.TXT","w");
	if(!i)
	{
		cout<<"\n\nNO HAY LISTA PARA GUARDAR";
		
		return;
	}
	p=i;
	while(p)
	{
		fprintf(arch,"%i\n",p->i);
		p=p->s;
	}
	cout<<"\n\nArchivo Guardado";
	fclose(arch);
	
}

void cargar(void)
{
	int c,x;
	FILE *arch;
	arch=fopen("DATOS-A.TXT","r");
	if(!arch)
	{
		cout<<"\n\nNO EXISTE EL ARCHIVO";
		
		return;
	}
	
	do {
		c=fscanf(arch,"%i\n",&x);
		if(c!=EOF)
		{
			insertar(x);
		}
	}
	while (c!=EOF);
	cout<<"\n\nArchivo Cargado";
	fclose(arch);
	
}
