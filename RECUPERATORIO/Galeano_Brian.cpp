//NOMBRE: Brian Galeano
//TP N°:
//EJ N°:

using namespace std;
#include <iostream>
#include <cstring>
#include "clases.h"

///CLASES/////////////////////
/////////////////////////////
class ReservasCat2{
private:
    int _cod;
    char _nombre[30];
    int _reservas;

public:

    ReservasCat2 ()///CONTRUCTOR PARA EL PUNTO 4
    {
        _cod=0;
        strcpy(_nombre,"SIN NOMBRE");
        _reservas=0;
    }

    void setCod(int codigo){_cod=codigo;}
    void setNombre(const char *n){strcpy(_nombre,n);}
    void setReservas(int cant){_reservas=cant;}

    int getCod(){return _cod;}
    const char *getNombre(){return _nombre;}
    int getReservas(){return _reservas;}

    void mostar()
    {
        cout<<"Codigo: "<<_cod<<endl;
        cout<<"Nombre: "<<_nombre<<endl;
        cout<<"Cantidad de reservas: "<<_reservas<<endl;
    }

    bool grabarEnDisco(){
    FILE *p;
    p=fopen("ReservasCat2.dat","ab");
    if(p==NULL) return false;
    bool escribio=fwrite(this, sizeof *this, 1, p);
    fclose(p);
    return escribio;
    }

    bool leerDeDisco(int pos){
    FILE *p;
    p=fopen("ReservasCat2.dat","rb");
    if(p==NULL) return false;
    fseek(p,pos*sizeof *this, 0);
    bool leyo=fread(this, sizeof *this, 1, p);
    fclose(p);
    return leyo;
    }



};


////DECLARACIONES//////////////
//////////////////////////////

int CantReservasCat2(Restaurante& resto);
void ListarResCat2();

///////////////////////////

void bajaLogica();
int cantidadReservas();
void grabarEnVector(Reserva *res);
void listarVector(Reserva *res,int cant);

//////////////////////////////

void grabarEnVector2(Reserva *res);


/////////////////////////////////////
////////////////////////////////////
int main (){
    int opcion;
    do{
        system("cls");
        cout<<"RECUPERATORIO"<<endl;
        cout<<"================="<<endl;
        cout<<"1) PUNTO 1"<<endl;
        cout<<"2) PUNTO 2"<<endl;
        cout<<"3) PUNTO 5"<<endl;
        cout<<"================="<<endl;
        cout<<"0) SALIR"<<endl;
        cout<<"================="<<endl;
        cout<<"Ingrese una opcion: ";
        cin>>opcion;

        switch (opcion)
        {
        case 1:
            {
                /*Generar un archivo con la cantidad de reservas que cada restaurante
                de la categoría 2 tuvo el año pasado.
                Cada registro debe tener el siguiente formato:
                Código de restaurante, nombre de restaurante, y cantidad de reservas del año pasado.
                Listar el archivo generado.*/
                system("cls");
                Restaurante resto;
                ReservasCat2 res;
                int pos=0;
                while(resto.leerDeDisco(pos++))
                {
                    int cant=0;
                    if(resto.getCategoriaRestaurante()==2){
                    cant=CantReservasCat2(resto);
                    if(cant!=0)
                    {
                    res.setCod(resto.getCodigoRestaurante());
                    res.setNombre(resto.getNombre());
                    res.setReservas(cant);
                    res.grabarEnDisco();
                    }
                    }
                }

                ListarResCat2();

                system("pause");
            }
            break;
        case 2:
            {
                //Dar la baja lógica a las reservas del cliente 987.
                //Listar el archivo sin los registros borrados.
                system("cls");
                bajaLogica();
                Reserva *res;
                int cant=cantidadReservas();
                res=new Reserva[cant];
                grabarEnVector(res);

                cout<<"====================="<<endl;
                cout<<"LISTADO DE RESERVAS MODIFICADO"<<endl;

                listarVector(res, cant);
                delete res;

                system("pause");

            }
            break;
        case 5:
            {
                ///Generar un vector dinámico para copiar y mostrar los registros de las reservas
                ///que no sean de del presente año.
                system("cls");

                Reserva *res;
                int cant=cantidadReservas();
                res=new Reserva[cant];
                grabarEnVector2(res);

                cout<<"====================="<<endl;
                cout<<"LISTADO DE RESERVAS DE AÑOS ANTERIORES"<<endl;

                listarVector(res, cant);
                delete res;


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


///FUNCIONES//////////////////
//////////////////////////////

int CantReservasCat2(Restaurante& resto)
{
    ReservasCat2 res;
    Reserva obj;
    int pos=0,cReservas=0;
    while(obj.leerDeDisco(pos++))
    {
       if(obj.getCodigoRestaurante()==resto.getCodigoRestaurante() &&
          obj.getEstado()==true && obj.getFechaReserva().getAnio()==2021&&
          resto.getEstado()==true)
       {
            cReservas++;
       }
    }
    return cReservas;
}

void ListarResCat2()
{
    ReservasCat2 obj;
    int pos=0;
    cout<<"Reservas 2021: RESTO CAT 2"<<endl<<endl;
    while(obj.leerDeDisco(pos++))
    {
        obj.mostar();
        cout<<"================="<<endl;
    }

}

/////////////////

void bajaLogica()
{
    Reserva obj;
    int pos=0;
    while(obj.leerDeDisco(pos++))
    {
        if(obj.getDNI()==987){obj.setEstado(false);}
    }
}

int cantidadReservas()
{
 int cant;
 FILE *p;
 p=fopen("reservas.dat","rb");
 if(p==nullptr) return 0;
 fseek(p,0,2);
 cant=ftell(p)/sizeof(Reserva);
 fclose(p);
 return cant;
}

void grabarEnVector(Reserva *res)
{
    Reserva aux;
    int pos=0,i=0;
    while(aux.leerDeDisco(pos++))
    {
        if(aux.getDNI()!=987){res[i++]=aux;}
    }
}

void listarVector(Reserva *res,int cant)
{
     for(int i=0;i<cant;i++)
     {
         res[i].Mostrar();
         cout<<endl;
     }
}

/////////////////////////////


void grabarEnVector2 (Reserva *res)
{
    Reserva aux;
    int pos=0,i=0;
    while(aux.leerDeDisco(pos++))
    {
        if(aux.getEstado()==true && aux.getFechaReserva().getAnio()<2022){res[i++]=aux;}
    }
}


///PUNTO 4//////////////////////////////////
///////////////////////////////////////////


       /* bool operator <(int h)
        {
            if(hora<h) return true;
            return false;
        }*/






