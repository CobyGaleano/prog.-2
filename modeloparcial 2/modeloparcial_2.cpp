//NOMBRE: Brian Galeano
//TP N°:
//EJ N°:

using namespace std;

#include <iostream>
#include <cstring>
#include "parcial2.h"

///CLASES

class AvionPropio{

private:
    int _codigo;
    char _marca[30];
    char _nombre[30];

public:
    void setCodigo(int codigo){_codigo=codigo;}
    void setMarca(const char *marca){strcpy(_marca,marca);}
    void setNombre(const char *nombre){strcpy(_nombre,nombre);}

    int getCodigo(){return _codigo;}
    const char *getMarca(){return _marca;}
    const char *getNombre(){return _nombre;}

    void mostrar()
    {
        cout<<"Codigo: "<<getCodigo()<<endl;
        cout<<"Marca: "<<getMarca()<<endl;
        cout<<"Nombre: "<<getNombre()<<endl;
    }

    void operator=(Avion &obj)
    {
        setCodigo(obj.getCodigoAvion());
        setMarca(obj.getMarca());
        setNombre(obj.getNombre());
    }

};

class VueloPorAvion
{
private:
    int _codigoAvion;
    char _nombre[30];
    int _vuelos;


public:
    void setNombre(const char *nombre){strcpy(_nombre,nombre);}
    void setCodigo(int codigo){_codigoAvion=codigo;}
    void setVuelos(int cant){_vuelos=cant;}

    int grabarEnDisco()
    {
        FILE *p;
        p=fopen("VuelosPorAvion.dat", "ab");
        if(p==NULL) return -1;
        int grabo=fwrite(this, sizeof *this,1, p);
        fclose(p);
        return grabo;
    }




};

///DECLARACIONES

bool NoPasajes(int pasajero);
void modificarRegistro(Avion a, int pos);

int contarPropio();
void copiarAvionesPropios(AvionPropio *Ap);
void mostrarAvionesPropios(AvionPropio *Ap,int cant);

bool PasajerosAnioActual(Pasajero pas);
void archivoAnioActual(bool actual, Pasajero pas);

int cantVuelos(Avion a);


///MAIN
int main (){
    int opcion;
    do{
        system("cls");
        cout<<"Modelo parcial 2"<<endl;
        cout<<"================="<<endl;
        cout<<"1) PUNTO 1"<<endl;
        cout<<"2) PUNTO 2"<<endl;
        cout<<"3) PUNTO 3"<<endl;
        cout<<"4) PUNTO 4"<<endl;
        cout<<"5) PUNTO 5"<<endl;
        cout<<"6) PUNTO 6"<<endl;
        cout<<"7) PUNTO 7"<<endl;
        cout<<"================="<<endl;
        cout<<"0) SALIR"<<endl;
        cout<<"================="<<endl;
        cout<<"Ingrese una opcion: ";
        cin>>opcion;

        switch (opcion)
        {
        case 1:
            {
        //Generar un archivo con los pasajeros que no hayan comprado pasajes en el presente año.
        //El formato del archivo debe ser igual que el del archivo de pasajeros.
                system("cls");
                Pasajero pas;
                int pos=0;
                while(pas.leerDeDisco(pos++)==1)
                {
                    if(NoPasajes(pas.getNumeroPasajero())==true)
                    {
                        FILE *p;
                        p=fopen("NoPasajes.dat", "ab");
                        if(p==NULL){"NO SE PUDO ABRIR EL ARCHIVO";}
                        fwrite(&pas, sizeof (Pasajero),1, p);
                        fclose(p);
                    }
                }
                system("pause");
            }
            break;
        case 2:
            {
        //Por razones de seguridad la cantidad de asientos en los aviones con la marca Boeing,
        // debe reducirse un 5%. Modificar el archivo de aviones para reflejar los cambios solicitados.
                system("cls");
                Avion a;
                int pos=0;
                while(a.leerDeDisco(pos)==1)
                {
                    if(stricmp(a.getMarca(),"Boeing")==0&& a.getActivo()==true)
                    {
                    int cant=(a.getCantidadAsientos()*5)/100;
                    a.setCantidadAsientos(cant);
                    modificarRegistro(a,pos);
                    }
                    pos++;
                }


                system("pause");

            }
            break;
        case 3:
            {
        //Generar un vector dinámico con los aviones de tipo propio y mostrarlo por pantalla.
        //El vector debe contener el código de avión, el nombre y la marca.
                system("cls");
                AvionPropio *Ap;
                int cant=contarPropio();
                Ap=new AvionPropio[cant];
                copiarAvionesPropios(Ap);
                cout<<"AVIONES PROPIOS";
                cout<<endl<<"====================="<<endl;
                mostrarAvionesPropios(Ap, cant);
                system("pause");
            }
            break;
        case 4:
            {
        //Sobrecargar algún operador en alguna de las clases que sea de utilidad para el
        //desarrollo de los puntos anteriores.

                system("cls");
                //resuelto en punto 3
                system("pause");
            }
            break;
        case 5:
            {
        //Generar un archivo con los pasajeros que hayan comprado pasajes en el presente año.
        // El formato del archivo debe ser igual que el del archivo de pasajeros.
                system("cls");
                Pasajero pas;
                Pasaje reg;
                int pos=0;
                while(pas.leerDeDisco(pos++)==1)
                {
                bool actual=PasajerosAnioActual(pas);
                archivoAnioActual(actual,pas);

                }
                system("pause");
            }
            break;
        case 6:
            {
       // Generar un archivo con la cantidad de vuelos realizados por los aviones.
       //Cada registro debe tener el código de avión, el nombre y la cantidad de vuelos.
                system("cls");
                VueloPorAvion va;
                Avion a;
                int pos=0,cant=0;
                while(a.leerDeDisco(pos++)==1)
                {
                    va.setVuelos(cantVuelos(a));
                    va.setCodigo(a.getCodigoAvion());
                    va.setNombre(a.getNombre());

                    va.grabarEnDisco();
                }

                system("pause");
            }
            break;
        case 7:
            {
       // Generar un vector dinámico para copiar y luego mostrar el archivo del punto anterior.
                system("cls");

                system("pause");
            }
            break;
        case 0:
            {
                cout<<"GRACIAS POR USAR EL PROGRAMA"<<endl;
            }
            break;
        default:
        cout<<"OPCION INCORRECTA"<<endl;

        }

   }while(opcion!=0);


        return 0;
}


////////////////////////////////////
//FUNCIONES////////////////////////

bool NoPasajes(int pasajero){
    Pasaje pas;
    int pos=0;
    while(pas.leerDeDisco(pos++)==1)
    {
        if(pasajero==pas.getNumeroPasajero())
        {
            return false;
        }
    }
    return true;
}

void modificarRegistro(Avion a, int pos)
{
    FILE *p;
    p=fopen("aviones.dat", "rb+");
    if(p==NULL){"NO SE PUDO ABRIR EL ARCHIVO";}
    fseek(p,sizeof(Avion)*pos,0);
    fwrite(&a, sizeof (Avion),1, p);
    fclose(p);
}

////////////////////////////////
int contarPropio()
{
    Avion a;
    int pos=0,cant=0;
    while(a.leerDeDisco(pos++)==1)
    {
        if(a.getTipo()==1)cant++;
    }
    return cant;
}


void copiarAvionesPropios(AvionPropio *Ap)
{
    Avion a;
    int pos=0,i=0;
    while(a.leerDeDisco(pos++)==1)
    {
        if(a.getTipo()==1)
        {
            Ap[i++]=a;
        }
    }

}

void mostrarAvionesPropios(AvionPropio *Ap,int cant)
{
    for(int i=0;i<cant;i++)
    {
        Ap[i].mostrar();
        cout<<endl;
    }
}

/////////////////////////////////////

bool PasajerosAnioActual(Pasajero pas)
{
    Pasaje reg;
    int  pos=0;
    while(reg.leerDeDisco(pos++)==1)
    {
        if(reg.getNumeroPasajero()==pas.getNumeroPasajero()&&reg.getActivo()==
           true&&reg.getFechaCompra().getAnio()==2022){return true;}

    }
    return false;
}

void archivoAnioActual(bool actual, Pasajero pas)
{
    if(actual==true)
    {
        FILE *p;
        p=fopen("AñoActual.dat", "ab");
        if(p==NULL){"NO SE PUDO ABRIR EL ARCHIVO";}
        fwrite(&pas, sizeof (Pasajero),1, p);
        fclose(p);

    }
}

int cantVuelos(Avion a)
{

}
