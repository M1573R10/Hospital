#include "iostream"
#include "conio.h"
#include "ctype.h"
#include "stdio.h"
#include "string.h"
#include <cstdlib>
#include <windows.h>
#include <fstream>

/** Agregar control de historias clinicas 
	Agregar en el menu de agregar su historia clinica 
	archivo por cada cliente con sus historias o en un solo archivo **/

using namespace std;


struct paciente {
	char nombre[30];
	char apellido[30];
	int edad;
	char dni[9];
	char direccion[60];
	char telefono[20];
	char codigo[3];
	char departamento[20];
	char historiaclinica[500];
};


FILE *fp;
paciente x;

// sizeof : Function que devuelve la cantidad de bytes de la variable
// o el tipo de dato
#define tam sizeof(paciente)
char continuar(const char msg[])
{
	char resp;
	do{
		cout<<msg;
		cin>>resp;
		//toupper: Si está entre s y n lo convierte a su equivalente en el rango S y N
		resp=toupper(resp);
	}while(resp!='S' && resp!='N');
	return resp;
}
void IngresoDatos()
{
	char resp;
	fp=fopen("pacientes.dat","ab");
	
	do{
		system("cls");
		cin.get();
		cout<<"\t\t\t\t\t=======================";
		cout<<"\n\t\t\t\t\t REGISTRO DE PACIENTES"<<endl;
		cout<<"\t\t\t\t\t=======================";
		cout<<"\n\n\t\t\tNombre : ";
		cin.getline(x.nombre,30);
		cout<<"\n\t\t\tApellido :";
		cin.getline(x.apellido,30);
		cout<<"\n\t\t\tEdad : ";
		cin>>x.edad;
		cin.get();
		cout<<"\n\t\t\tDNI : ";
		cin.getline(x.dni,9);
		cout<<"\n\t\t\tDireccion : ";
		cin.getline(x.direccion,60);
		cout<<"\n\t\t\tTelefono : ";
		cin.getline(x.telefono,20);
		fwrite(&x,tam,1,fp);
		resp=continuar("\n\t\t\tDeseas ingresar otro registro(S/N)");
	}while(resp=='S');
	fclose(fp);
}
void Reporte()
{
	fp=fopen("pacientes.dat","rb");
	system("cls");
	cout<<"\t\t\t\t\t====================";
	cout<<"\n\t\t\t\t\t LISTA DE PACIENTES"<<endl;
	cout<<"\t\t\t\t\t====================";
	fread(&x,tam,1,fp);
	while(!feof(fp))
	{
		cout<<"\n\t"<<x.nombre<<"\t\t"<<x.apellido<<"\t"<<x.edad<<"\t"<<x.dni<<"\t"<<x.direccion<<"\t"<<x.telefono<<endl;
		fread(&x,tam,1,fp);
	}
	fclose(fp);
}

void ConsultadeUnPaciente()
{
	char resp;
	char dni[9];
	int enc;
	fp=fopen("pacientes.dat","rb");
	
	do{
		system("cls");
		cout<<"\t\t\t\t\t=====================";
		cout<<"\n\t\t\t\t\tCONSULTA DE PACIENTES"<<endl;
		cout<<"\t\t\t\t\t=====================";
		cin.get();	   
		cout<<"\n\n\t\t\tDNI : ";
		cin.getline(dni,9);
		//fseek cuenta los caracteres
		fseek(fp,0,0);
		fread(&x,tam,1,fp);
		enc=0;
		while(!feof(fp) && enc==0)
		{
			if(strcmp(dni,x.dni)==0)
			{
				cout<<"\n\n\t\t\t\t\tDATOS DEL PACIENTE"<<endl;
				cout<<"\n\t\t\tNOMBRE : "<<x.nombre<<endl;
				cout<<"\n\t\t\tAPELLIDO : "<<x.apellido<<endl;
				cout<<"\n\t\t\tEDAD : "<<x.edad<<endl;
				cout<<"\n\t\t\tDNI : "<<x.dni<<endl;
				cout<<"\n\t\t\tDIRECCION : "<<x.direccion<<endl;
				cout<<"\n\t\t\tTELEFONO : "<<x.telefono<<endl;
				enc=1;
			}
			else
			   fread(&x,tam,1,fp);
		}
		if(enc==0)
			  cout<<"-El paciente no se encuentra..."<<endl;
		resp=continuar("\n\t\t\tDeseas consultar otro paciente (S/N)");
	}while(resp=='S');
	fclose(fp);
}
void ModificaDatosdeUnPaciente()
{
	char resp;
	char dni[9];
	int enc;
	fp=fopen("pacientes.dat","rb+");
	do{
		system("cls");
		cout<<"\t\t\t\t\t========================";
		cout<<"\n\t\t\t\t\t ACTUALIZACION DE DATOS"<<endl; 
		cout<<"\t\t\t\t\t========================";
		cin.get();
		cout<<"\n\n\n\t\t\t Ingrese DNI :";
		cin.getline(dni,9);
		//fseek cuenta los caracteres
		fseek(fp,0,0);
		fread(&x,tam,1,fp);
		enc=0;
		//feof retorna un valor distinto de cero
		while(!feof(fp) && enc==0)
		{
			//retorna un número entero mayor, igual, o menor que cero
			if(strcmp(dni,x.dni)==0)
			{
				cout<<"\n\t\t\t\tDATOS DEL PACIENTE"<<endl;
				cout<<"\n\t\t\t\tNOMBRE : "<<x.nombre<<endl;
				cout<<"\n\t\t\t\tAPELLIDO :"<<x.apellido<<endl;
				cout<<"\n\t\t\t\tEDAD :"<<x.edad<<endl;
				cout<<"\n\t\t\t\tDNI :"<<x.dni<<endl;
				cout<<"\n\t\t\t\tDIRECCION :"<<x.direccion<<endl;
				cout<<"\n\t\t\t\tTELEFONO :"<<x.telefono<<endl;
				cout<<"\n\t\t\t\tINGRESO DE NUEVOS DATOS"<<endl;
				cout<<"\n\t\t\t\tDIRECCION :";
				cin.getline(x.direccion,60);
				cout<<"\n\t\t\t\tTELEFONO :";
				cin.getline(x.telefono,20);
				//fseek retorna un valor distinto de 0
				fseek(fp,ftell(fp)-tam,0);
				fwrite(&x,tam,1,fp);
				enc=1;
			}
			else
			   fread(&x,tam,1,fp);
		}
		if(enc==0)
			  cout<<"-El paciente no se encuentra..."<<endl;
		resp=continuar("\n\t\t\tDeseas modificar otro paciente (S/N)");
	}while(resp=='S');
	fclose(fp);
}

void HistorialClinico ()
{
	char resp;
	char dni[9];
	int enc;
	fp=fopen("pacientes.dat","rb+");
	do{
		system("cls");
		cout<<"\t\t\t\t\t==================";
		cout<<"\n\t\t\t\t\t Historia Clinica"<<endl; 
		cout<<"\t\t\t\t\t==================";
		cin.get();
		cout<<"\n\n\n\t\t\tIngrese DNI : ";
		cin.getline(dni,9);
		//fseek cuenta los caracteres
		fseek(fp,0,0);
		fread(&x,tam,1,fp);
		enc=0;
		//feof retorna un valor distinto de cero
		while(!feof(fp) && enc==0)
		{
			//retorna un número entero mayor, igual, o menor que cero
			if(strcmp(dni,x.dni)==0)
			{
				cout<<"\n\n\n\t\t\tDATOS DEL PACIENTE"<<endl;
				cout<<"\n\t\t\tNOMBRE : "<<x.nombre<<endl;
				cout<<"\n\t\t\tAPELLIDO :"<<x.apellido<<endl;
				cout<<"\n\t\t\tEDAD :"<<x.edad<<endl;
				cout<<"\n\t\t\tDETALLE DE HISTORIAL CLINICA"<<endl;
				cout<<"\n\t\t\tCODIGO : ";
				cin.getline(x.codigo,3);
				cout<<"\n\t\t\tDEPARTAMENTO : ";
				cin.getline(x.departamento,20);
				cout<<"\n\t\t\tDETALLE DE HISTORIA CLINICA : "<<endl;
				cin.getline(x.historiaclinica,500);
				//fseek retorna un valor distinto de 0
				fseek(fp,ftell(fp)-tam,0);
				fwrite(&x,tam,1,fp);
				enc=1;
				
			}
			else
				fread(&x,tam,1,fp);
		}
		if(enc==0)
			cout<<"\n\t\t\tEl paciente no se encuentra..."<<endl;
		resp=continuar("\n\t\t\t¿Deseas registrar la historia de otro paciente?(S/N)");
	}while(resp=='S');
	fclose(fp);
}

void ReporteHistorialClinico ()
{
	char resp;
	char dni[9];
	int enc;
	int i;
	fp=fopen("pacientes.dat","rb");
	do{
		system("cls");
		cout<<"\t\t\t\t\t=============================";
		cout<<"\n\t\t\t\t\t Reporte de Historia Clinica"<<endl; 
		cout<<"\t\t\t\t\t=============================";
		cin.get();
		cout<<"\n\n\t\t\t\tIngrese DNI : ";
		cin.getline(dni,9);
		//fseek cuenta los caracteres
		fseek(fp,0,0);
		fread(&x,tam,1,fp);
		enc=0;
		//feof retorna un valor distinto de cero
		while(!feof(fp) && enc==0)
		{
			//retorna un número entero mayor, igual, o menor que cero
			if(strcmp(dni,x.dni)==0)
			{
				cout<<"\n\n\n\t\t\t\tDATOS DEL PACIENTE"<<endl;
				cout<<"\n\t\t\t\tNOMBRE : "<<x.nombre<<endl;
				cout<<"\n\t\t\t\tAPELLIDO : "<<x.apellido<<endl;
				cout<<"\n\t\t\t\tEDAD : "<<x.edad<<endl;
				cout<<"\n\t\t\t\tCODIGO : "<<x.codigo<<endl;
				cout<<"\n\t\t\t\tDEPARTAMENTO : "<<x.departamento<<endl;
				cout<<"\n\t\t\t\tHISTORIA : "<<x.historiaclinica<<endl;
				//fseek retorna un valor distinto de 0
				//ftell retorna el valor del indicador de posición de fichero
				fseek(fp,ftell(fp)-tam,0);
				fwrite(&x,tam,1,fp);
				enc=1;
			}
			else
			   fread(&x,tam,1,fp);
		}
		if(enc==0)
			  cout<<"-El paciente no se encuentra..."<<endl;
		resp=continuar("\n\t\t\t¿Deseas consulta la historia de otro paciente?(S/N)");
	}while(resp=='S');
	fclose(fp);
}

/**
void ReporteHistorialClinicoCodigo ()
{
	char resp;
	char dni[9];
	int enc;
	char codigo[3];
	int i;
	fp=fopen("pacientes.dat","rb");
	do{
		system("cls");
		cout<<"\t\t\t\t\t=============================";
		cout<<"\n\t\t\t\t\t Reporte de Historia Clinica"<<endl; 
		cout<<"\t\t\t\t\t=============================";
		cin.get();
		/**cout<<"\n\n\t\t\t\tIngrese DNI : ";
		cin.getline(dni,9);
		//fseek cuenta los caracteres
		fseek(fp,0,0)
		
		cout<<"\n\n\t\t\t\tIngrese Codigo : ";
		cin.getline(codigo,3);
		//fseek cuenta los caracteres
		fseek(fp,0,0);
		fread(&x,tam,1,fp);
		enc=0;
		//feof retorna un valor distinto de cero
		while(!feof(fp) && enc==0)
		{
			//retorna un número entero mayor, igual, o menor que cero
			if(strcmp(codigo,x.codigo)==0)
			{
				cout<<"\n\n\n\t\t\t\tDATOS DEL PACIENTE"<<endl;
				cout<<"\n\t\t\t\tNOMBRE : "<<x.nombre<<endl;
				cout<<"\n\t\t\t\tAPELLIDO : "<<x.apellido<<endl;
				cout<<"\n\t\t\t\tEDAD : "<<x.edad<<endl;
				cout<<"\n\t\t\t\tDEPARTAMENTO : "<<x.departamento<<endl;
				cout<<"\n\t\t\t\tHISTORIA : "<<x.historiaclinica<<endl;
				//fseek retorna un valor distinto de 0
				//ftell retorna el valor del indicador de posición de fichero
				fseek(fp,ftell(fp)-tam,0);
				fwrite(&x,tam,1,fp);
				enc=1;
			}
			else
			   fread(&x,tam,1,fp);
		}
		if(enc==0)
			  cout<<"-El paciente no se encuentra..."<<endl;
		resp=continuar("\n\t\t\t¿Deseas consulta la historia de otro paciente?(S/N)");
	}while(resp=='S');
	fclose(fp);
}
**/

int main()
{
	system("Color 1B");
	int op;
	do{
		system("cls");
		cout<<"\t\t\t\t=================="<<endl;
		cout<<"\t\t\t\t MENU DE ARCHIVOS"<<endl;
		cout<<"\t\t\t\t=================="<<endl;
		cout<<"\n\t\t\t[1] Ingreso "<<endl;
		cout<<"\t\t\t[2] Reporte "<<endl;
		cout<<"\t\t\t[3] Consulta "<<endl;
		cout<<"\t\t\t[4] Modifica "<<endl;
		cout<<"\t\t\t[5] Historial Clínico "<<endl;
		cout<<"\t\t\t[6] Reporte de Historia Clinica "<<endl;
		//cout<<"\t\t\t\t[7] Reporte de Historia Clinica "<<endl;
		cout<<"\t\t\t[7] Salir "<<endl;
		do{
			cout<<"\n\t\t\t\tIngrese un opcion :";
			cin>>op;
		}while(op<1 || op>7);
		switch(op)
		{
		case 1:
			IngresoDatos();
			getch(); break;
		case 2:
			Reporte();
			getch(); break;
		case 3:
			ConsultadeUnPaciente();
			getch();
			break;
		case 4:
			ModificaDatosdeUnPaciente();
			getch();
			break;
		case 5:
			HistorialClinico();
			getch();
			break;
		case 6:
			ReporteHistorialClinico();
			getch();
			break;
		//case 7:
			//ReporteHistorialClinicoCodigo ();
			//getch();
			//break;
		}
	}while(op!=8);
	return 0;
}
