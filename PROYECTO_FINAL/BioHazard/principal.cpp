#include "principal.h"
#include "ui_principal.h"
#include <math.h>

principal::principal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::principal)
{
    ui->setupUi(this);
    InterfazRegistrar=new Registro ();
    InterfazIniciarSesion=new InicarSesion2 ();
    LeerRegistroDeUsuarios();
    connect(InterfazRegistrar,SIGNAL(buttonPressed()),this,SLOT(VerificarNoEstaRegistar()));
    connect(InterfazIniciarSesion,SIGNAL(buttonPressed()),this,SLOT(VerificarSiEstaInicioSesion()));
    //connect(InterFazParaUsuario,SIGNAL(buttonClicked()),this,SLOT(Aparecer()));
    //connect(InterFazParaUsuario,&VentanaPrincipalUsuario::buttonClicked,this,&principal::Aparecer);
}

void principal::LeerRegistroDeUsuarios()
{
    // Lee del archivo UsuariosRegistrados los usuarios.
    ifstream archivoUsuarios("UsuariosRegistrados.txt");

    if(archivoUsuarios.fail())
        QMessageBox::warning(this,"ERROR","No se pudo abrir el archivo.");
    else {
        while (!archivoUsuarios.eof()) {
            string renglon="";
            getline(archivoUsuarios,renglon);
            if(renglon!="")
                LlenarConUsuariosRegistrados(renglon);
        }
    }

    archivoUsuarios.close();
}

void principal::LlenarConUsuariosRegistrados(string UsuarioContrasena)
{
    // Lo que hace esta funcion es tomar el Usuario y Contrasena del archivo y lo añade al vector usuarios registrados.

    map<string,map<string,int>> Temporal;
    map<string,int> auxMayor;
    int aux;
    string Usuario;
    string Paswoord;
    aux=UsuarioContrasena.find(",");
    Usuario=UsuarioContrasena.substr(0,aux);
    Paswoord=UsuarioContrasena.substr(aux+1,UsuarioContrasena.size()-aux);
    aux=StringNumeroCodigo(Usuario);
    auxMayor.insert(pair<string,int>(Paswoord,aux));
    Temporal.insert(pair<string,map<string,int>>(Usuario,auxMayor));
    UsuariosRegistrados.push_back(Temporal);
}

int principal::StringNumeroCodigo(string Usuario)
{
    /* Esta funcion coge el nombre de usuario y bajo ciertas reglas le asigna una equvalencia en un numero entero.
     * Metodo de equivalencia: Se toma cada letra del nombre de usuario, se extrae su valor ascii, a dicho valor se le resta el subindice mas 1 y se lo suma
     * a una variable acumulador.
     * Esto se hace con el fin de hacer eficiente el proceso de busqueda.
     */
    int acum=0;
     for(int i=0;i<Usuario.size();i++){
         acum+= Usuario[i] - (i+1);
     }

     return acum;
}

int principal::BusquedaBinaria(string Usuario, int EquivalenteUsuario, int maximo)
{
    // Metodo clasico de busqueda binario sobre el vector de usuarios registrados.
    int minimo=0,resultado;
    if(UsuariosRegistrados.size()==0)
        return -1;
    if(UsuariosRegistrados.size()==1){
        if(Usuario==UsuariosRegistrados[0].begin()->first)
            return 0;
        else
            return -1;
    }
    while(minimo<=maximo){
        resultado=(minimo+maximo)/2;
        if(EquivalenteUsuario > UsuariosRegistrados[resultado].begin()->second.begin()->second)
            minimo=resultado+1;
        else if (EquivalenteUsuario < UsuariosRegistrados[resultado].begin()->second.begin()->second)
            maximo=resultado-1;
        else{
            if(UsuariosRegistrados[resultado].begin()->first==Usuario)
                return resultado;
            else
                return -2;
        }

    }
    return -1;
}

void principal::Ordenamiento_por_Insercion(int tamanio)
{
    // Metodo clasico de ordenamiento por insercion sobre el vector de usuarios registrados. Tomando como referencia
    // la equivalencia del nombre de usuario. Explicado anteriormente.
    int pos;
    map<string,map<string,int>> aux;
    for (int i = 0;i<tamanio;i++) {
        pos=i;
        aux=UsuariosRegistrados[i];
        while ((pos>0) and UsuariosRegistrados[pos-1].begin()->second.begin()->second > aux.begin()->second.begin()->second) {
            UsuariosRegistrados[pos]=UsuariosRegistrados[pos-1];
            pos--;
        }
        UsuariosRegistrados[pos]=aux;
    }
}

void principal::Registrar()
{
    // Escribe los nombres de ususarios y contraseñas en el archivo UsuariosRegistrados, bajo cierta configuracion.
    // NombreDeUsuarios,Contraseña
    ofstream ArchivoUsuarios("UsuariosRegistrados.txt");
    for (int i=0;i<UsuariosRegistrados.size();i++) {
        ArchivoUsuarios<<UsuariosRegistrados[i].begin()->first<<","<<UsuariosRegistrados[i].begin()->second.begin()->first<<endl;
    }

    ArchivoUsuarios.close();
}

principal::~principal()
{
    delete ui;
}

void principal::on_sesion_clicked()
{
    this->close();
    InterfazIniciarSesion->show();
}

void principal::on_pushButton_2_clicked()
{
    this->close();
    InterfazRegistrar->show();
}

void principal::VerificarNoEstaRegistar()
{
    // Esta funcion lo que hace es verificar que el nombre de usuario ingresado no se encuentre en uso.
    // Si es así, se registrará, de lo contrario invalidara el registro.
    int indicador;
    AuxUsuario=InterfazRegistrar->GetNombreUsuario();
    AuxPaswoord1=InterfazRegistrar->GetPaswoord();
    if(!UsuariosRegistrados.empty()){
        indicador=BusquedaBinaria(AuxUsuario,StringNumeroCodigo(AuxUsuario),UsuariosRegistrados.size());
        if(indicador == -1){
            LlenarConUsuariosRegistrados(AuxUsuario+","+AuxPaswoord1);
            Ordenamiento_por_Insercion(UsuariosRegistrados.size());
            Registrar();
            AuxUsuario+=".txt";
            ofstream ArchivoUsuarioNuevo(AuxUsuario);
            ArchivoUsuarioNuevo<<"1,0"<<endl;
            ArchivoUsuarioNuevo.close();
            QMessageBox::information(this,"GUARDADO","El susario se ha creado exitosamente.");
        }
        else {
            QMessageBox::warning(this,"INVALIDO","El nombre de usuario ya se encuentra en uso. ");
        }
        InterfazRegistrar->SetPaswoordReiniciar("");
        InterfazRegistrar->SetUsuarioNameReiniciar("");
        InterfazRegistrar->close();

    }
    else {
        LlenarConUsuariosRegistrados(AuxUsuario+","+AuxPaswoord1);
        Registrar();
        QMessageBox::information(this,"GUARDADO","El susario se ha creado exitosamente.");
        InterfazRegistrar->SetPaswoordReiniciar("");
        InterfazRegistrar->SetUsuarioNameReiniciar("");
        InterfazRegistrar->close();
    }
}

void principal::VerificarSiEstaInicioSesion()
{
    //Esta funcion lo que hace es verificar, a la hora de iniciar sesion, si el nombre de usuario y contraseña son correctos.
    int encontrar;
    AuxUsuario=InterfazIniciarSesion->GetUserName();
    AuxPaswoord1=InterfazIniciarSesion->GerPaswoord();
    if(!UsuariosRegistrados.empty())
        encontrar=BusquedaBinaria(AuxUsuario,StringNumeroCodigo(AuxUsuario),UsuariosRegistrados.size());
    else
        encontrar=-1;
    if(encontrar != -1 and UsuariosRegistrados[encontrar].begin()->first==AuxUsuario and UsuariosRegistrados[encontrar].begin()->second.begin()->first==AuxPaswoord1){
        InterfazIniciarSesion->close();
        InterfazRegistrar->close();
        InterfazIniciarSesion->close();
        InterfazIniciarSesion->SetUserNameReiniciar("");
        InterfazIniciarSesion->SetPaswoordReiniciar("");
        QMessageBox::information(this,"Sesion iniciada","Bienvenido usuario.");
        this->close();
        ifstream ArchivoUsuario(AuxUsuario+".txt");
        string renglon;
        getline(ArchivoUsuario,renglon);
        int nivel=renglon[0]-48;
        int encontrar=renglon.find(",");
        renglon=renglon.substr(encontrar+1,renglon.size()-encontrar);
        int puntos= StringANumero(renglon);
        VentanaPrincipalUsuario *InterFazParaUsuario= new VentanaPrincipalUsuario(nivel,puntos,AuxUsuario);
        connect(InterFazParaUsuario,&VentanaPrincipalUsuario::buttonClicked,this,&principal::Aparecer);
        InterFazParaUsuario->show();

    }else {
        QMessageBox::warning(this,"ERROR","El usuario o contrasena es incorrecto. ");
        InterfazIniciarSesion->SetUserNameReiniciar("");
        InterfazIniciarSesion->SetPaswoordReiniciar("");
        InterfazIniciarSesion->close();
    }
}

void principal::Aparecer()
{
    this->show();
}

void principal::on_Cerrar_clicked()
{
    this->~principal();
}

int principal:: StringANumero(string cadena){
    int acum=0;
    for(int i=0; i<cadena.size();i++){
        acum+=cadena[i]-48;
    }
    return acum;
}
