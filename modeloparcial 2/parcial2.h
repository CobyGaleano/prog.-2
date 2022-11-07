///Ejercicio: Parcial 2 de Programación II
///Autor:DEK
///Fecha:13/06/2022
///Comentario:
using namespace std;

#include <iostream>
#include <cstring>

void cargarCadena(char *pal, int tam){
    int i;
    fflush(stdin);
    for(i=0; i<tam; i++)
    {
        pal[i]=cin.get();
        if(pal[i]=='\n') break;
    }
    pal[i]='\0';
    fflush(stdin);
}


class Fecha{
private:
    int dia,mes, anio;
public:
    void Cargar(){
        cin>>dia;
        cin>>mes;
        cin>>anio;
    }
    void Mostrar(){
        cout<<dia<<"/";
        cout<<mes<<"/";
        cout<<anio<<endl;
    }
    int getDia(){return dia;}
    int getMes(){return mes;}
    int getAnio(){return anio;}

    void setDia(int d){dia=d;}
    void setMes(int m){mes=m;}
    void setAnio(int a){anio=a;}

};


class Vuelo{
private:
    char codigoVuelo[5];
    char nombre[30];
    int destino;
    float tiempoViaje;
    int tipoViaje;
    bool activo;
public:
    void Cargar(){
        cargarCadena(codigoVuelo,4);
        cargarCadena(nombre,29);
        cin>>destino;
        cin>>tiempoViaje;
        cin>>tipoViaje;
        activo=true;
    }

    void Mostrar(){
        cout<<codigoVuelo<<endl;
        cout<<nombre<<endl;
        cout<<destino<<endl;
        cout<<tiempoViaje<<endl;
        cout<<tipoViaje<<endl;
    }

    const char* getCodigoVuelo(){return codigoVuelo;}
    const char* getNombre(){return nombre;}
    int getDestino(){return destino;}
    float getTiempoViaje(){return tiempoViaje;}
    int getTipoViaje(){return tipoViaje;}
    bool getActivo(){return activo;}

    void setCodigoVuelo(const char *cv){strcpy(codigoVuelo, cv);}
    void setNombre(const char *n){strcpy(nombre,n);}
    void setDestino(int d){destino=d;}
    void setTiempoViaje(float e){tiempoViaje=e;}
    void setTipoViaje(int tv){tipoViaje=tv;}
    void setActivo(bool a){activo=a;}

    int leerDeDisco(int pos){
        FILE *p;
        p=fopen("vuelos.dat", "rb");
        if(p==NULL) return -1;
        fseek(p, sizeof(Vuelo)*pos,0);
        int leyo=fread(this, sizeof *this,1, p);
        fclose(p);
        return leyo;
    }

    int grabarEnDisco(){
        FILE *p;
        p=fopen("vuelos.dat", "ab");
        if(p==NULL) return -1;
        int grabo=fwrite(this, sizeof *this,1, p);
        fclose(p);
        return grabo;
    }
};

class Avion{
private:
    int codigoAvion;
    char nombre[30];
    char marca[30];
    int tipo;
    int cantidadAsientos;
    bool activo;
public:
    void Cargar(){
        cin>>codigoAvion;
        cargarCadena(nombre,29);
        cargarCadena(marca,29);
        cin>>tipo;
        cin>>cantidadAsientos;
        activo=true;
    }
    void Mostrar(){
        cout<<codigoAvion<<endl;
        cout<<nombre<<endl;
        cout<<marca<<endl;
        cout<<tipo<<endl;
        cout<<cantidadAsientos<<endl;
    }
    int getCodigoAvion(){return codigoAvion;}
    int getTipo(){return tipo;}
    const char *getNombre(){return nombre;}
    const char *getMarca(){return marca;}
    int getCantidadAsientos(){return cantidadAsientos;}
    bool getActivo(){return activo;}

    void setCodigoAvion(int ca){codigoAvion=ca;}
    void setTipo(int t){tipo=t;}
    void setNombre(const char *m){strcpy(nombre,m);}
    void setMarca(const char *m){strcpy(marca,m);}
    void setCantidadAsientos(int ca){cantidadAsientos=ca;}
    void setActivo(bool a){activo=a;}

    int leerDeDisco(int pos){
        FILE *p;
        p=fopen("aviones.dat", "rb");
        if(p==NULL) return -1;
        fseek(p, sizeof *this*pos,0);
        int leyo=fread(this, sizeof *this,1, p);
        fclose(p);
        return leyo;
    }

    int grabarEnDisco(){
        FILE *p;
        p=fopen("aviones.dat", "ab");
        if(p==NULL) return -1;
        int grabo=fwrite(this, sizeof *this,1, p);
        fclose(p);
        return grabo;
    }
};



class Pasaje{
private:
    int numeroPasaje, numeroPasajero, codigoAvion;
    char codigoVuelo[5];
    int cantidad;
    float importe;
    Fecha fechaCompra;
    bool activo;
public:
    void Cargar(){
        cin>>numeroPasaje;
        cin>>numeroPasajero;
        cin>>codigoAvion;
        cargarCadena(codigoVuelo,4);
        cin>>cantidad;
        cin>>importe;
        fechaCompra.Cargar();
        activo=true;
    }

    void Mostrar(){
        cout<<numeroPasaje<<endl;
        cout<<numeroPasajero<<endl;
        cout<<codigoAvion<<endl;
        cout<<codigoVuelo<<endl;
        cout<<cantidad<<endl;
        cout<<importe<<endl;
        fechaCompra.Mostrar();
        cout<<endl;
    }
    int getNumeroPasaje(){return numeroPasaje;}
    int getNumeroPasajero(){return numeroPasajero;}
    int getCodigoAvion(){return codigoAvion;}
    int getCantidad(){return cantidad;}
    float getImporte(){return importe;}
    Fecha getFechaCompra(){return fechaCompra;}
    const char *getCodigoVuelo(){return codigoVuelo;}
    bool getActivo(){return activo;}

    void setNumeroPasaje(int np){numeroPasaje=np;}
    void setNumeroPasajero(int np){numeroPasajero=np;}
    void setCodigoAvion(int ca){codigoAvion=ca;}
    void setCantidad(int c){cantidad=c;}
    void setImporte(float i){importe=i;}
    void setFechaCompra(Fecha f){fechaCompra=f;}
    void setCodigoVuelo(const char *cv){strcpy(codigoVuelo,cv);}
    void setActivo(bool a){activo=a;}

    int leerDeDisco(int pos){
        FILE *p;
        p=fopen("pasajes.dat", "rb");
        if(p==NULL) return -1;
        fseek(p, sizeof *this*pos,0);
        int leyo=fread(this, sizeof *this,1, p);
        fclose(p);
        return leyo;
    }

    int grabarEnDisco(){
        FILE *p;
        p=fopen("pasajes.dat", "ab");
        if(p==NULL) return -1;
        int grabo=fwrite(this, sizeof *this,1, p);
        fclose(p);
        return grabo;
    }
};


class Pasajero{
private:
    int numeroPasajero;
    char nombre[30];
    char telefono[30];
    char direccion[30];
    int provincia;
    bool activo;
public:
    void Cargar(){
        cin>>numeroPasajero;
        cargarCadena(nombre,29);
        cargarCadena(telefono,29);
        cargarCadena(direccion,29);
        cin>>provincia;
        activo=true;
    }
    void Mostrar(){
        cout<<numeroPasajero<<endl;
        cout<<nombre<<endl;
        cout<<telefono<<endl;
        cout<<direccion<<endl;
        cout<<provincia<<endl;
    }

    int getNumeroPasajero(){return numeroPasajero;}
    int getProvincia(){return provincia;}
    const char *getNombre(){return nombre;}
    const char *getTelefono(){return telefono;}
    const char *getDireccion(){return direccion;}
    bool getActivo(){return activo;}

    void setNumeroPasajero(int np){numeroPasajero=np;}
    void setProvincia(int np){provincia=np;}
    void setNombre(const char *n){strcpy(nombre,n);}
    void setTelefono(const char *n){strcpy(telefono,n);}
    void setDireccion(const char *n){strcpy(direccion,n);}
    void setActivo(bool a){activo=a;}

    int leerDeDisco(int pos){
        FILE *p;
        p=fopen("pasajeros.dat", "rb");
        if(p==NULL) return -1;
        fseek(p, sizeof *this*pos,0);
        int leyo=fread(this, sizeof *this,1, p);
        fclose(p);
        return leyo;
    }

    int grabarEnDisco(){
        FILE *p;
        p=fopen("pasajeros.dat", "ab");
        if(p==NULL) return -1;
        int grabo=fwrite(this, sizeof *this,1, p);
        fclose(p);
        return grabo;
    }
};

