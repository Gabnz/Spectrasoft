#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    conectado = false;
    numCurvas = 0;
    ref = abs = NULL;
    dts = NULL;
    infoUsuario.clear();
    infoHistoria.clear();
    infoMuestra.clear();
    modeloDatos = new QStandardItemModel(2, 31, this);

    QStringList cabeceras;

    cabeceras.push_back("Valor");
    cabeceras.push_back("Longitud");
    modeloDatos->setVerticalHeaderLabels(cabeceras);
    ui->tablaDatosEspectrales->setModel(modeloDatos);
    ui->tablaDatosEspectrales->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tablaDatosEspectrales->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    int alto, ancho, rango;

    alto = 50;
    ancho = 55;
    rango = 400;
    ui->tablaDatosEspectrales->setRowHeight(0, alto);
    ui->tablaDatosEspectrales->setRowHeight(1, alto);

    QModelIndex indice;

    for(int i = 0; i < 31; ++i){

        ui->tablaDatosEspectrales->setColumnWidth(i, ancho);
        indice = modeloDatos->index(1, i, QModelIndex());
        modeloDatos->setData(indice, rango);
        rango+=10;
    }
    //abriendo la conexion con la base de datos
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("CIMBUC");
    db.setUserName("CIMBUC");
    db.setPassword("CIMBUC");
    db.open();
    //
    this->setFixedSize(this->size());
    revisionBtns();
}

void MainWindow::on_actionConectar_triggered()
{
    if(!conectado){
        conectado = true;
        ui->actionConectar->setText("Desconectar");
        //conectado = miniscan.conectar();

        if(conectado){
            QMessageBox::information(this, "Conectado", "El MiniScan se ha conectado correctamente.");
        }else{
            QMessageBox::critical(this, "Error al conectar", "El MiniScan no se pudo conectar.");
        }
        ui->actionConectar->setIcon(QIcon(":img/off.png"));
    }else{
        conectado = false;
        ui->actionConectar->setText("Conectar");
        //conectado = miniscan.desconectar();

        if(!conectado){
            QMessageBox::information(this, "Desconectado", "El MiniScan se ha desconectado correctamente.");
        }else{
            QMessageBox::critical(this, "Error al desconectar", "El MiniScan no se pudo desconectar.");
        }
         ui->actionConectar->setIcon(QIcon(":img/on.png"));
    }

    revisionBtns();
}

void MainWindow::on_actionSalir_triggered()
{
    close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::borrarResultados()
{
    datosEspectrales.clear();
    XYZ.clear();
    LAB.clear();
    absorcion = esparcimiento = eritema = 0.0;

    QModelIndex indice;

    for(int i = 0; i < 31; ++i){
        indice = modeloDatos->index(0, i, QModelIndex());
        modeloDatos->setData(indice, "");
    }

    if(ref != NULL){
        delete ref;
        ref = NULL;
    }

    if(abs != NULL){
        delete abs;
        abs = NULL;
    }

    if(dts != NULL){
        delete dts;
        dts = NULL;
    }
}

void MainWindow::revisionBtns()
{
    bool estandarizar, medirM, borrarResultadosM, registrarM, buscarM, verM, verRefM, verAbsM, datosAdicionalesM, masOpcionesM, modificarM, eliminarM, cerrarM,
    sesionU, verU, masOpcionesU, registrarU, eliminarU, cerrarU,
    registrarH, buscarH, verH, cerrarH, modificarH, eliminarH, masOpcionesH;

    if(conectado){
        estandarizar = true;

        if(infoMuestra.isEmpty())
            medirM = true;
        else
            medirM = false;
    }else{
         estandarizar = medirM = false;
    }

    if(!datosEspectrales.isEmpty()){
        verRefM = verAbsM = datosAdicionalesM = true;

        if(infoMuestra.isEmpty())
            borrarResultadosM = true;
        else
            borrarResultadosM = false;
    }else{
        verRefM = verAbsM = datosAdicionalesM = borrarResultadosM = false;
    }

    if(!infoUsuario.isEmpty()){
        sesionU = false;
        verU = cerrarU = true;

        if(infoUsuario["rol"] == "administrador")
            masOpcionesU = registrarU = eliminarU = true;
        else
            masOpcionesU = registrarU = eliminarU = false;

        if(!infoHistoria.isEmpty()){
            registrarH = buscarH = false;
            verH = masOpcionesH = modificarH = eliminarH = cerrarH = true;

            if(!infoMuestra.isEmpty()){
                registrarM = buscarM = false;
                verM = cerrarM = masOpcionesM = modificarM = eliminarM = true;
            }else{

                buscarM = true;
                verM = cerrarM = masOpcionesM = modificarM = eliminarM = false;

                if(!datosEspectrales.isEmpty()){
                    registrarM = true;
                }else{
                    registrarM = false;
                }
            }

        }else{
            registrarH = buscarH = true;
            verH = masOpcionesH = modificarH = eliminarH = cerrarH = false;
            registrarM = buscarM = verM = masOpcionesM = modificarM = eliminarM = cerrarM = false;
        }

    }else{
        sesionU = true;
        verU = masOpcionesU = registrarU = eliminarU = cerrarU = false;
        registrarH = buscarH = verH = masOpcionesH = modificarH = eliminarH = cerrarH = false;
        registrarM = buscarM = verM = masOpcionesM = modificarM = eliminarM = cerrarM = false;
    }

    ui->actionEstandarizar->setEnabled(estandarizar);

    ui->actionIniciar_sesion->setEnabled(sesionU);
    ui->actionVer_usuario->setEnabled(verU);
    ui->menuMas_opciones_u->setEnabled(masOpcionesU);
    ui->actionRegistrar_usuario->setEnabled(registrarU);
    ui->actionEliminar_usuario->setEnabled(eliminarU);
    ui->actionCerrar_sesion->setEnabled(cerrarU);

    ui->actionRegistrar_historia->setEnabled(registrarH);
    ui->actionBuscar_historia->setEnabled(buscarH);
    ui->actionVer_historia->setEnabled(verH);
    ui->menuMas_opciones_h->setEnabled(masOpcionesH);
    ui->actionModificar_historia->setEnabled(modificarH);
    ui->actionEliminar_historia->setEnabled(eliminarH);
    ui->actionCerrar_historia->setEnabled(cerrarH);

    ui->actionMedir_muestra->setEnabled(medirM);
    ui->actionBorrar_resultados->setEnabled(borrarResultadosM);
    ui->actionRegistrar_muestra->setEnabled(registrarM);
    ui->actionBuscar_muestra->setEnabled(buscarM);
    ui->actionVer_muestra->setEnabled(verM);
    ui->actionVer_reflectancia->setEnabled(verRefM);
    ui->actionVer_absorbancia->setEnabled(verAbsM);
    ui->actionDatos_adicionales->setEnabled(datosAdicionalesM);
    ui->menuMas_opciones_m->setEnabled(masOpcionesM);
    ui->actionModificar_muestra->setEnabled(modificarM);
    ui->actionEliminar_muestra->setEnabled(eliminarM);
    ui->actionCerrar_muestra->setEnabled(cerrarM);
}

void MainWindow::on_actionAcerca_de_triggered()
{
    dlgAcercaDe acercaDe;

    acercaDe.exec();
}

void MainWindow::on_actionEstandarizar_triggered()
{
    bool negroListo, blancoListo;
    negroListo = blancoListo = false;
    dlgEstandarizar est;
    est.exec();
    negroListo = miniscan.estNegro();

    if(negroListo){

        est.estBlanco();
        est.exec();
        blancoListo = miniscan.estBlanco();
    }

    if(negroListo && blancoListo){
        QMessageBox::information(this, "Estandarizado", "El MiniScan se ha estandarizado correctamente.");
    }else{
        QMessageBox::critical(this, "Error al estandarizar", "No se pudo estandarizar el MiniScan.");
    }

    revisionBtns();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(db.isOpen()){
        db.close();
    }

    if(conectado){
        //miniscan.desconectar();
    }

    borrarResultados();
    event->accept();
}

void MainWindow::on_actionIniciar_sesion_triggered()
{
    dlgInicioSesion sesion;

    sesion.exec();

    infoUsuario = sesion.getUsuario();
    revisionBtns();
}

void MainWindow::on_actionCerrar_sesion_triggered()
{
    infoHistoria.clear();
    infoUsuario.clear();
    QMessageBox::information(this, "Sesión cerrada", "Se ha cerrado la sesión correctamente.");
    revisionBtns();
}

void MainWindow::on_actionVer_usuario_triggered()
{
    dlgVerUsuario verU(infoUsuario);

    verU.exec();
}

void MainWindow::on_actionCerrar_historia_triggered()
{
    infoHistoria.clear();
    QMessageBox::information(this, "Historia cerrada", "Se ha cerrado la historia correctamente.");
    revisionBtns();
}

void MainWindow::on_actionRegistrar_historia_triggered()
{
    dlgRegHistoria regH;

    regH.exec();

    infoHistoria = regH.getHistoria();
    revisionBtns();
}

void MainWindow::on_actionRegistrar_usuario_triggered()
{
    dlgRegUsuario regU;

    regU.exec();
}

void MainWindow::on_actionEliminar_usuario_triggered()
{
    dlgEliminarUsuario elimU;

    elimU.exec();
}

void MainWindow::on_actionVer_historia_triggered()
{
    dlgVerHistoria verH(infoHistoria);

    verH.exec();
}

void MainWindow::on_actionBuscar_historia_triggered()
{
    dlgBuscarHistoria buscarH;

    buscarH.exec();

    infoHistoria = buscarH.getHistoria();
    revisionBtns();
}

void MainWindow::on_actionEliminar_historia_triggered()
{
    dlgEliminarHistoria elimH(infoHistoria["id_historia"], infoUsuario["clave"]);

    connect(&elimH, &dlgEliminarHistoria::historiaEliminada, this, &MainWindow::on_historiaEliminada);

    elimH.exec();
}

void MainWindow::on_historiaEliminada()
{
    infoHistoria.clear();

    if(!infoMuestra.isEmpty()){
        infoMuestra.clear();
        borrarResultados();
    }
    revisionBtns();
}

void MainWindow::on_actionModificar_historia_triggered()
{
    dlgModificarHistoria modH(infoUsuario["clave"], infoHistoria);

    connect(&modH, &dlgModificarHistoria::historiaModificada, this, &MainWindow::on_historiaModificada);

    modH.exec();
}

void MainWindow::on_historiaModificada(QHash<QString, QString> infoModificada)
{
    infoHistoria = infoModificada;
}



void MainWindow::on_actionMedir_muestra_triggered()
{
    borrarResultados();

    QList<QVariant> medicion;

    medicion = miniscan.medir();

    QList<QVariant>::const_iterator iter = qFind(medicion.begin(), medicion.end(), 0);

    if(iter == medicion.end()){
        //si no se consigue ningun cero exacto (0), es porque la lista fue llenada correctamente y por lo tanto la medicion ocurrio

    }else{
        medicion.clear();

        QMessageBox::critical(this, "Error al medirM la muestra", "La medición no se pudo realizar.");

        medicion.push_back(float(17.2101 + numCurvas));
        medicion.push_back(float(15.2329 + numCurvas));
        medicion.push_back(float(15.13 + numCurvas));
        medicion.push_back(float(14.2457 + numCurvas));
        medicion.push_back(float(16.0641 + numCurvas));
        medicion.push_back(float(18.2752 + numCurvas));
        medicion.push_back(float(19.687 + numCurvas));
        medicion.push_back(float(21.0481 + numCurvas));
        medicion.push_back(float(21.9136 + numCurvas));
        medicion.push_back(float(23.1382 + numCurvas));
        medicion.push_back(float(23.9694 + numCurvas));
        medicion.push_back(float(25.4163 + numCurvas));
        medicion.push_back(float(25.2229 + numCurvas));
        medicion.push_back(float(24.8392 + numCurvas));
        medicion.push_back(float(24.9241 + numCurvas));
        medicion.push_back(float(25.2234 + numCurvas));
        medicion.push_back(float(26.2638 + numCurvas));
        medicion.push_back(float(26.5036 + numCurvas));
        medicion.push_back(float(27.8098 + numCurvas));
        medicion.push_back(float(31.5459 + numCurvas));
        medicion.push_back(float(36.2515 + numCurvas));
        medicion.push_back(float(39.0012 + numCurvas));
        medicion.push_back(float(40.6161 + numCurvas));
        medicion.push_back(float(42.1796 + numCurvas));
        medicion.push_back(float(43.205 + numCurvas));
        medicion.push_back(float(44.057 + numCurvas));
        medicion.push_back(float(45.0165 + numCurvas));
        medicion.push_back(float(45.779 + numCurvas));
        medicion.push_back(float(46.4996 + numCurvas));
        medicion.push_back(float(47.3194 + numCurvas));
        medicion.push_back(float(47.8099 + numCurvas));
    }

    QModelIndex indice;

    for(int i = 0; i < 31; ++i){

        datosEspectrales.push_back(medicion.at(i).toFloat());
        indice = modeloDatos->index(0, i, QModelIndex());
        modeloDatos->setData(indice, datosEspectrales.at(i));
    }

    QVector<float> aux(31);

    for(int i = 0; i < 31; ++i){
        aux[i] = datosEspectrales[i]/100.0;
    }

    XYZ = ops.CIExyz(aux);
    LAB = ops.CIELAB(aux);
    absorcion = ops.absorcion(aux);
    esparcimiento = ops.esparcimiento(aux);
    eritema = ops.eritema(aux);

    numCurvas += 1;
    revisionBtns();
}

void MainWindow::on_actionVer_reflectancia_triggered()
{
    if(ref != NULL && !ref->isMinimized() && !ref->isActiveWindow()){
        delete ref;
        ref = NULL;
    }

    if(ref == NULL){

        QVector<double> aux(31);

        for(int i = 0; i < 31; ++i){
            aux[i] = double(datosEspectrales[i]);
        }

        ref = new dlgGrafica("reflectancia", "Longitud de onda (nm)", "Reflectancia (%)");
        ref->agregarCurva(aux);
        ref->show();
    }else{
        ref->showMaximized();
    }
}

void MainWindow::on_actionVer_absorbancia_triggered()
{
    if(abs != NULL && !abs->isMinimized() && !abs->isActiveWindow()){
        delete abs;
        abs = NULL;
    }

    if(abs == NULL){

        QVector<double> aux(31);

        for(int i = 0; i < 31; ++i){
            aux[i] = double(100.0 - datosEspectrales[i]);
        }

        abs = new dlgGrafica("absorbancia", "Longitud de onda (nm)", "Absorbancia (%)");
        abs->agregarCurva(aux);
        abs->show();
    }else{
        abs->showMaximized();
    }
}

void MainWindow::on_actionDatos_adicionales_triggered()
{
    if(dts != NULL && !dts->isMinimized() && !dts->isActiveWindow()){
        delete dts;
        dts = NULL;
    }

    if(dts == NULL){

        dts = new dlgDatosAdicionales(XYZ, LAB, absorcion, esparcimiento, eritema);
        dts->show();
    }else{
        dts->showMaximized();
    }
}

void MainWindow::on_actionBorrar_resultados_triggered()
{
    borrarResultados();
    revisionBtns();
}

void MainWindow::on_actionRegistrar_muestra_triggered()
{
    dlgTipoMuestra tipoM;

    connect(&tipoM, &dlgTipoMuestra::tipo_muestra, this, &MainWindow::on_tipoMuestra);

    tipoM.exec();
}

void MainWindow::on_tipoMuestra(const QString tipo)
{
    if(tipo == "lesion"){
        dlgRegLesion regL(infoUsuario["cedula"], infoHistoria["id_historia"], datosEspectrales, XYZ, LAB, absorcion, esparcimiento, eritema);

        connect(&regL, &dlgRegLesion::lesion_registrada, this, &MainWindow::on_muestraRegistrada);

        regL.exec();
    }else{
        dlgRegFototipo regF;

        regF.exec();
    }
}

void MainWindow::on_muestraRegistrada(const QHash<QString, QString> info)
{
    infoMuestra = info;
    revisionBtns();
}

void MainWindow::on_actionVer_muestra_triggered()
{
    if(infoMuestra["tipo_muestra"] == "lesion"){
        dlgVerLesion verL(infoMuestra);

        verL.exec();
    }else{

    }
}

void MainWindow::on_actionCerrar_muestra_triggered()
{
    infoMuestra.clear();
    borrarResultados();
    QMessageBox::information(this, "Muestra cerrada", "Se ha cerrado la muestra correctamente.");
    revisionBtns();
}

void MainWindow::on_actionEliminar_muestra_triggered()
{
    dlgEliminarMuestra eliminarM(infoMuestra["id_muestra"], infoUsuario["clave"]);

    connect(&eliminarM, &dlgEliminarMuestra::muestraEliminada, this, &MainWindow::on_muestraEliminada);

    eliminarM.exec();
}

void MainWindow::on_muestraEliminada()
{
    infoMuestra.clear();
    borrarResultados();
    revisionBtns();
}

void MainWindow::on_actionModificar_muestra_triggered()
{
    if(infoMuestra["tipo_muestra"] == "lesion"){
        dlgModificarLesion modL(infoUsuario["clave"], infoMuestra);

        connect(&modL, &dlgModificarLesion::lesionModificada, this, &MainWindow::on_muestraModificada);

        modL.exec();
    }else{

    }
}

void MainWindow::on_muestraModificada(QHash<QString, QString> infoModificada)
{
    infoMuestra = infoModificada;
}
