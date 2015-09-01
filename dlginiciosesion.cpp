#include "dlginiciosesion.h"
#include "ui_dlginiciosesion.h"

dlgInicioSesion::dlgInicioSesion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgInicioSesion)
{
    ui->setupUi(this);

    infoUsuario.clear();
    ui->btnIngresar->setEnabled(false);
    usuario = clave = false;
    usuarioValido.setPattern("^[V|E]\\d{1,10}$");
    claveValida.setPattern("^((?=.*\\d)(?=.*[a-z])(?=.*[A-Z]).{8,16})$");

    this->setWindowFlags(Qt::WindowCloseButtonHint);
    this->setFixedSize(this->size());
}

dlgInicioSesion::~dlgInicioSesion()
{
    delete ui;
}

void dlgInicioSesion::on_lineaUsuario_textChanged(const QString &arg1)
{
    if(!arg1.isEmpty()){
        usuario = true;
    }else{
        usuario = false;
    }

    if(usuario && clave){
        ui->btnIngresar->setEnabled(true);
    }else{
        ui->btnIngresar->setEnabled(false);
    }
}

void dlgInicioSesion::on_lineaClave_textChanged(const QString &arg1)
{
    if(!arg1.isEmpty()){
        clave = true;
    }else{
        clave = false;
    }

    if(clave && usuario){
        ui->btnIngresar->setEnabled(true);
    }else{
        ui->btnIngresar->setEnabled(false);
    }
}

void dlgInicioSesion::on_btnIngresar_clicked()
{
    bool listo = false;
    QSqlQuery query;
    QRegularExpressionMatch usuarioMatch = usuarioValido.match(ui->lineaUsuario->text());
    QRegularExpressionMatch claveMatch = claveValida.match(ui->lineaClave->text());
    QDate fechaAux;

    if(usuarioMatch.hasMatch() && claveMatch.hasMatch()){
        query.exec("SELECT * FROM spectradb.usuario WHERE cedula = '" + ui->lineaUsuario->text() + "' AND clave = '" + ui->lineaClave->text() + "'");

        if(query.next()){
            listo = true;
        }
    }

    if(listo){
        int indice = query.record().indexOf("cedula");
        QString aux = (query.value(indice)).toString();
        infoUsuario["cedula"] = aux;

        indice = query.record().indexOf("nombre");
        aux = (query.value(indice)).toString();
        infoUsuario["nombre"] = aux;

        indice = query.record().indexOf("apellido");
        aux = (query.value(indice)).toString();
        infoUsuario["apellido"] = aux;

        indice = query.record().indexOf("fecha_nac");
        fechaAux = fechaAux.fromString(query.value((indice)).toString(), "yyyy-MM-dd");
        aux = fechaAux.toString("dd-MM-yyyy");
        infoUsuario["fecha_nac"] = aux;

        indice = query.record().indexOf("sexo");
        aux = (query.value(indice)).toString();

        if(aux == "F")
            aux = "Femenino";
        else
            aux = "Masculino";

        infoUsuario["sexo"] = aux;

        indice = query.record().indexOf("clave");
        aux = (query.value(indice)).toString();
        infoUsuario["clave"] = aux;

        indice = query.record().indexOf("rol");
        aux = (query.value(indice)).toString();
        infoUsuario["rol"] = aux;

        QMessageBox::information(this, "Sesión iniciada", "Se ha iniciado la sesión correctamente.");
        close();
    }else{
        infoUsuario.clear();
        QMessageBox::critical(this, "Datos incorrectos", "La cédula de identidad o la contraseña que introdujo es incorrecta.");
        ui->lineaUsuario->clear();
        ui->lineaClave->clear();
    }
}

QHash<QString, QString> dlgInicioSesion::getUsuario()
{
    return infoUsuario;
}
