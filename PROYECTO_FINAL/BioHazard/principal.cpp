#include "principal.h"
#include "ui_principal.h"

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
}

void principal::LeerRegistroDeUsuarios()
{
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
    int acum=0;
     for(int i=0;i<Usuario.size();i++){
         acum+= Usuario[i] - (i+1);
     }

     return acum;
}

int principal::BusquedaBinaria(string Usuario, int EquivalenteUsuario, int maximo)
{
    int minimo=0,resultado;
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
    InterfazIniciarSesion->show();
}

void principal::on_pushButton_2_clicked()
{
    InterfazRegistrar->show();
}

void principal::VerificarNoEstaRegistar()
{
    int indicador;
    AuxUsuario=InterfazRegistrar->GetNombreUsuario();
    AuxPaswoord1=InterfazRegistrar->GetPaswoord();
    if(!UsuariosRegistrados.empty()){
        indicador=BusquedaBinaria(AuxUsuario,StringNumeroCodigo(AuxUsuario),UsuariosRegistrados.size());
        if(indicador == -1){
            LlenarConUsuariosRegistrados(AuxUsuario+","+AuxPaswoord1);
            Ordenamiento_por_Insercion(UsuariosRegistrados.size());
            Registrar();
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
    int encontrar;
    AuxUsuario=InterfazIniciarSesion->GetUserName();
    AuxPaswoord1=InterfazIniciarSesion->GerPaswoord();
    if(!UsuariosRegistrados.empty())
        encontrar=BusquedaBinaria(AuxUsuario,StringNumeroCodigo(AuxUsuario),UsuariosRegistrados.size());
    else
        encontrar=-1;
    if(encontrar != -1 and UsuariosRegistrados[encontrar].begin()->first==AuxUsuario and UsuariosRegistrados[encontrar].begin()->second.begin()->first==AuxPaswoord1){
        InterfazIniciarSesion->close();
        InterfazRegistrar->~Registro();
        InterfazIniciarSesion->~InicarSesion2();
        QMessageBox::information(this,"Sesion iniciada","Bienvenido usuario.");
        this->close();
    }else {
        QMessageBox::warning(this,"ERROR","El usuario o contrasena es incorrecto. ");
        InterfazIniciarSesion->SetUserNameReiniciar("");
        InterfazIniciarSesion->SetPaswoordReiniciar("");
        InterfazIniciarSesion->close();
    }
}
