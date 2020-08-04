#include "ventanaprincipalusuario.h"
#include "ui_ventanaprincipalusuario.h"
#include "game.h"
#include "game2.h"

game2 extern *Game2;
game extern *Game;

VentanaPrincipalUsuario::VentanaPrincipalUsuario(int nivel, int puntos, string NombreUsuario,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VentanaPrincipalUsuario)
{
    LeerRankingDeJugadores();
    PuntosActuales=puntos;
    NivelActual=nivel;
    ui->setupUi(this);
    NickName = QString::fromStdString(NombreUsuario);
    ui->NombreUsuario->setText(NickName);
    Ordenamiento_por_Insercion(RankingDeUsuarios.size());
}

VentanaPrincipalUsuario::~VentanaPrincipalUsuario()
{
    delete ui;
}

void VentanaPrincipalUsuario::LeerRankingDeJugadores()
{
   ifstream ArchivoRanking("RankingDeUsuarios.txt");
   if(ArchivoRanking.fail())
       QMessageBox::warning(this,"ERROR","No se pudo abrir el archivo. ");
   else {
       while (!ArchivoRanking.eof()) {
           string renglon="";
           getline(ArchivoRanking,renglon);
           if(renglon!=""){
                PonerEnElvector(renglon);
           }

       }
   }
   ArchivoRanking.close();
}

void VentanaPrincipalUsuario::PonerEnElvector(string lineaActual)
{
    map<string,int> Auxiliar;
    int encontrar=lineaActual.find(",");
    int Puntaje=StringANumero(lineaActual.substr(encontrar+1,lineaActual.size()-encontrar));
    Auxiliar[lineaActual.substr(0,encontrar)]=Puntaje;
    RankingDeUsuarios.push_back(Auxiliar);
}

void VentanaPrincipalUsuario::on_Campana_clicked()
{
    ModoDeJuego=1;
    this->close();
    SeleccionarNivelUsuario = new SeleccionarNivel(NivelActual,NickName.toStdString());
    connect(SeleccionarNivelUsuario,&SeleccionarNivel::buttonClicked,this,&VentanaPrincipalUsuario::Aparecer);
    connect(SeleccionarNivelUsuario,&SeleccionarNivel::buttonClicked2,this,&VentanaPrincipalUsuario::IniciarNivelSeleccionado);
    SeleccionarNivelUsuario->show();
}

void VentanaPrincipalUsuario::on_Cooperativo_clicked()
{
    this->close();
    ModoDeJuego=2;
    nivelSeleccionado=3;
    Game = new game(&contadorPuntos,&nivelSeleccionado,ModoDeJuego,"Jugadores");
    connect(Game->InterfazPausa,&pausar::buttonClicked2,this,&VentanaPrincipalUsuario::InterrumpidoRegresarMenuPrincipal);
    connect(Game->InterfazPerder,&perder::buttonClicked2,this,&VentanaPrincipalUsuario::InterrumpidoRegresarMenuPrincipal);
    connect(Game->InterfazPerder,&perder::buttonClicked,this,&VentanaPrincipalUsuario::LlamarIniciarJuego);
}

void VentanaPrincipalUsuario::on_Ranking_clicked()
{
    InterfazMostarRanking= new mostrarranking(RankingDeUsuarios);
    InterfazMostarRanking->show();
    connect(InterfazMostarRanking,&mostrarranking::buttonClicked,this,&VentanaPrincipalUsuario::eliminarInterfazMostarRankingUsuarios);
}

void VentanaPrincipalUsuario::on_CerrarSesion_clicked()
{
    emit buttonClicked();
    this->close();
}

void VentanaPrincipalUsuario::Aparecer()
{
    this->show();
}

void VentanaPrincipalUsuario::on_comojugar_clicked()
{
    this->close();
    InterfazControles= new controles();
    InterfazControles->show();
    connect(InterfazControles,&controles::buttonClicked,this,&VentanaPrincipalUsuario::Destruircontroles);

}

void VentanaPrincipalUsuario::IniciarNivelSeleccionado()
{
    nivelSeleccionado=SeleccionarNivelUsuario->GetNivelSeleccionado();
    delete SeleccionarNivelUsuario;
    IniciarNivel();
}

void VentanaPrincipalUsuario::InterrumpidoRegresarMenuPrincipal()
{
    if(nivelSeleccionado==1 or nivelSeleccionado==3){
        if(ModoDeJuego==2)
        {
            if(contadorPuntos>PuntosActuales){
                PuntosActuales=contadorPuntos;
                RegistrarEnElArchivo();
                for(int i=0;i<RankingDeUsuarios.size();i++){
                    if(RankingDeUsuarios[i].begin()->first==NickName.toStdString()){
                        RankingDeUsuarios[i].begin()->second=PuntosActuales;
                        Ordenamiento_por_Insercion(RankingDeUsuarios.size());
                        RegistarCambiosEnElRanking();
                        break;
                    }
                }
            }
            contadorPuntos=0;
        }
        if(ModoDeJuego==1)
            Game->InterfazGanar->close();
        Game->InterfazPerder->close();
        Game->InterfazPausa->close();
        if(ModoDeJuego==1)
            Game->InterfazPasarNivel->close();
        delete Game;
    }
    else{
        Game2->InterfazPerder->close();
        Game2->InterfazPausar->close();
        Game2->InterfazPasarNivel->close();
        delete Game2;
    }
    this->show();

}

void VentanaPrincipalUsuario::LlamarIniciarJuego()
{
    if(nivelSeleccionado==1 or nivelSeleccionado==3){
        if(ModoDeJuego==2)
        {
            if(contadorPuntos>PuntosActuales)
            {
                PuntosActuales=contadorPuntos;
                RegistrarEnElArchivo();
                for(int i=0;i<RankingDeUsuarios.size();i++){
                    if(RankingDeUsuarios[i].begin()->first==NickName.toStdString()){
                        RankingDeUsuarios[i].begin()->second=PuntosActuales;
                        Ordenamiento_por_Insercion(RankingDeUsuarios.size());
                        RegistarCambiosEnElRanking();
                        break;
                    }
                }
            }
            contadorPuntos=0;
        }
        Game->InterfazPausa->close();
        Game->InterfazPerder->close();
       delete Game;
    }
    else{
        Game2->InterfazPausar->close();
        Game2->InterfazPerder->close();
        delete Game2;
    }
    IniciarNivel();
}

void VentanaPrincipalUsuario::CompararPasarNivelInmediatamente()
{
    if(nivelSeleccionado>NivelActual){
        NivelActual=nivelSeleccionado;
        RegistrarEnElArchivo();
    }
    if(nivelSeleccionado-1==1){
        Game->InterfazPasarNivel->close();
        delete Game;
    }
    else {
        Game2->InterfazPasarNivel->close();
        delete Game2;
    }
    IniciarNivel();
}

void VentanaPrincipalUsuario::SubirNivelSinEjecutar()
{
    if(nivelSeleccionado>NivelActual){
        NivelActual=nivelSeleccionado;
        RegistrarEnElArchivo();
    }
    if(nivelSeleccionado-1==1){
        Game->InterfazPasarNivel->close();
        delete Game;
    }
    else {
        Game2->InterfazPasarNivel->close();
        delete Game2;
    }
    this->show();
}

void VentanaPrincipalUsuario::Ordenamiento_por_Insercion(int tamanio)
{
    // Metodo clasico de ordenamiento por insercion sobre el vector de UsuariosRanking. Tomando como eje de comparacion
    // los puntos de cada uno de los usarios.
    int pos;
    map<string,int> aux;
    for (int i = 0;i<tamanio;i++) {
        pos=i;
        aux=RankingDeUsuarios[i];
        while ((pos>0) and RankingDeUsuarios[pos-1].begin()->second > aux.begin()->second) {
            RankingDeUsuarios[pos]=RankingDeUsuarios[pos-1];
            pos--;
        }
       RankingDeUsuarios[pos]=aux;
    }
}

void VentanaPrincipalUsuario::RegistarCambiosEnElRanking()
{
    ofstream EscribirArchivoRanking("RankingDeUsuarios.txt");
    if(EscribirArchivoRanking.fail())
        QMessageBox::warning(this,"ERROR","No se pudo abrir el archivo. ");
    else {
        for(int i=0;i<RankingDeUsuarios.size();i++){
            EscribirArchivoRanking<<RankingDeUsuarios[i].begin()->first<<","<<RankingDeUsuarios[i].begin()->second<<endl;
        }
    }
    EscribirArchivoRanking.close();
}

void VentanaPrincipalUsuario::eliminarInterfazMostarRankingUsuarios()
{
    InterfazMostarRanking->close();
    delete InterfazMostarRanking;
}

void VentanaPrincipalUsuario::Destruircontroles()
{
    this->show();
    delete InterfazControles;
}

void VentanaPrincipalUsuario::RegistrarEnElArchivo()
{
    ofstream archivo(NickName.toStdString()+".txt");
    if(archivo.fail())
        QMessageBox::warning(this, "ERROR","No se pudo abrir el archivo. ");
    else {
        archivo<<NivelActual<<","<<PuntosActuales<<endl;
    }
    archivo.close();
}

void VentanaPrincipalUsuario::IniciarNivel()
{
    this->close();
    if(nivelSeleccionado==3 && ModoDeJuego==2)
    {
        Game = new game(&contadorPuntos,&nivelSeleccionado,ModoDeJuego,"Jugadores");
        connect(Game->InterfazPausa,&pausar::buttonClicked2,this,&VentanaPrincipalUsuario::InterrumpidoRegresarMenuPrincipal);
        connect(Game->InterfazPerder,&perder::buttonClicked2,this,&VentanaPrincipalUsuario::InterrumpidoRegresarMenuPrincipal);
        connect(Game->InterfazPerder,&perder::buttonClicked,this,&VentanaPrincipalUsuario::LlamarIniciarJuego);
    }
    else if(nivelSeleccionado==1){
        Game=new game(&contadorPuntos,&nivelSeleccionado,ModoDeJuego,NickName.toStdString());
        connect(Game->InterfazPausa,&pausar::buttonClicked2,this,&VentanaPrincipalUsuario::InterrumpidoRegresarMenuPrincipal);
        connect(Game->InterfazPerder,&perder::buttonClicked2,this,&VentanaPrincipalUsuario::InterrumpidoRegresarMenuPrincipal);
        connect(Game->InterfazPerder,&perder::buttonClicked,this,&VentanaPrincipalUsuario::LlamarIniciarJuego);
        connect(Game->InterfazPasarNivel,&PasarNivel::buttonClicked,this,&VentanaPrincipalUsuario::CompararPasarNivelInmediatamente);
        connect(Game->InterfazPasarNivel,&PasarNivel::buttonClicked2,this,&VentanaPrincipalUsuario::SubirNivelSinEjecutar);
        connect(Game->InterfazGanar,&ganar::buttonClicked,this,&VentanaPrincipalUsuario::InterrumpidoRegresarMenuPrincipal);
    }
    else if (nivelSeleccionado==2) {
        Game2=new game2(&nivelSeleccionado,NickName.toStdString());
        connect(Game2->InterfazPausar,&pausar::buttonClicked2,this,&VentanaPrincipalUsuario::InterrumpidoRegresarMenuPrincipal);
        connect(Game2->InterfazPerder,&perder::buttonClicked2,this,&VentanaPrincipalUsuario::InterrumpidoRegresarMenuPrincipal);
        connect(Game2->InterfazPerder,&perder::buttonClicked,this,&VentanaPrincipalUsuario::LlamarIniciarJuego);
        connect(Game2->InterfazPasarNivel,&PasarNivel::buttonClicked,this,&VentanaPrincipalUsuario::CompararPasarNivelInmediatamente);
        connect(Game2->InterfazPasarNivel,&PasarNivel::buttonClicked2,this,&VentanaPrincipalUsuario::SubirNivelSinEjecutar);
    }
    else {
        Game=new game(&contadorPuntos,&nivelSeleccionado,ModoDeJuego,NickName.toStdString());
        connect(Game->InterfazPausa,&pausar::buttonClicked2,this,&VentanaPrincipalUsuario::InterrumpidoRegresarMenuPrincipal);
        connect(Game->InterfazPerder,&perder::buttonClicked2,this,&VentanaPrincipalUsuario::InterrumpidoRegresarMenuPrincipal);
        connect(Game->InterfazPerder,&perder::buttonClicked,this,&VentanaPrincipalUsuario::LlamarIniciarJuego);
        connect(Game->InterfazGanar,&ganar::buttonClicked,this,&VentanaPrincipalUsuario::InterrumpidoRegresarMenuPrincipal);
    }

}

int VentanaPrincipalUsuario:: StringANumero(string cadena){
    //Convierte una cadena de caracteres al numero que está representando.
    int acum=0;
    for(int i=0; i<cadena.size();i++){
        acum+=cadena[i]-48;
        acum*=10;
    }
    acum/=10;
    return acum;
}

