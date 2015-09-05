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
    //fototipo = 0;
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

    version = "20150828";

    //abriendo la conexion con la base de datos
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("CIMBUC");
    db.setUserName("CIMBUC");
    db.setPassword("CIMBUC");
    db.open();
    //
    revisionBtns();
    this->setFixedSize(this->size());
}

void MainWindow::borrarResultados()
{
    datosEspectrales.clear();
    //fototipo = 0;

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

//    QSize tam;

//    tam.setWidth(125);
//    tam.setHeight(125);

//    QPixmap imgFototipo(":/img/fototipo_0.png");

//    imgFototipo.scaled(tam);
//    ui->etqNumeroFototipo->setText("-");
//    ui->etqFototipo->setPixmap(imgFototipo);
}

void MainWindow::revisionBtns()
{
    bool btnConectar, btnDesconectar, btnEstandarizar, btnMedir, btnGuardar, btnEliminar, btnRef, btnAbs, btnDatosAdicionales,
    iniciarSesion, verUsuario, masOpcionesU, registrarU, eliminarU, cerrarSesion,
    registrarHistoria, buscarHistoria, verHistoria, cerrarHistoria, modificarHistoria, eliminarHistoria, masOpcionesH;

    if(conectado){
        btnConectar = false;
        btnDesconectar = true;
        btnEstandarizar = btnMedir = true;
    }else{
        btnConectar = true;
        btnDesconectar = false;
         btnEstandarizar = btnMedir = false;
    }

    if(!infoUsuario.isEmpty()){
        iniciarSesion = false;
        verUsuario = true;

        if(infoUsuario["rol"] == "administrador")
            masOpcionesU = registrarU = eliminarU = true;
        else
            masOpcionesU = registrarU = eliminarU = false;

        cerrarSesion = true;

        if(!infoHistoria.isEmpty()){
            registrarHistoria = buscarHistoria = false;
            verHistoria = cerrarHistoria = modificarHistoria = eliminarHistoria = masOpcionesH = true;
        }else{
            registrarHistoria = buscarHistoria = true;
            verHistoria = cerrarHistoria = modificarHistoria = eliminarHistoria = masOpcionesH = false;
        }

    }else{
        iniciarSesion = true;
        verUsuario = masOpcionesU = registrarU = eliminarU = cerrarSesion = false;
        registrarHistoria = buscarHistoria = verHistoria = cerrarHistoria = modificarHistoria = eliminarHistoria = masOpcionesH = false;
    }

    if(!datosEspectrales.isEmpty()){
        btnGuardar = btnEliminar = btnRef = btnAbs = btnDatosAdicionales = true;

    }else{
        btnGuardar = btnEliminar = btnRef = btnAbs = btnDatosAdicionales = false;
    }

    ui->actionConectar->setEnabled(btnConectar);
    ui->actionDesconectar->setEnabled(btnDesconectar);
    ui->actionEstandarizar->setEnabled(btnEstandarizar);
    ui->btnMedir->setEnabled(btnMedir);
    ui->btnGuardar->setEnabled(btnGuardar);
    ui->btnEliminar->setEnabled(btnEliminar);
    ui->btnReflectancia->setEnabled(btnRef);
    ui->btnAbsorbancia->setEnabled(btnAbs);
    ui->btnDatosAdicionales->setEnabled(btnDatosAdicionales);
    ui->actionIniciar_sesion->setEnabled(iniciarSesion);
    ui->actionVer_usuario->setEnabled(verUsuario);
    ui->menuMas_opciones_u->setEnabled(masOpcionesU);
    ui->actionRegistrar_usuario->setEnabled(registrarU);
    ui->actionEliminar_usuario->setEnabled(eliminarU);
    ui->actionCerrar_sesion->setEnabled(cerrarSesion);
    ui->actionRegistrar_historia->setEnabled(registrarHistoria);
    ui->actionBuscar_historia->setEnabled(buscarHistoria);
    ui->actionVer_historia->setEnabled(verHistoria);
    ui->actionCerrar_historia->setEnabled(cerrarHistoria);
    ui->actionModificar_historia->setEnabled(modificarHistoria);
    ui->actionEliminar_historia->setEnabled(eliminarHistoria);
    ui->menuMas_opciones_h->setEnabled(masOpcionesH);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionConectar_triggered()
{
    conectado = true;
    //conectado = miniscan.conectar();
    QMessageBox msg;

    if(conectado){
        QMessageBox::information(this, "Conectado", "El MiniScan se ha conectado correctamente.");
    }else{
        QMessageBox::critical(this, "Error al conectar", "El MiniScan no se pudo conectar.");
    }

    revisionBtns();
}

void MainWindow::on_actionDesconectar_triggered()
{
    conectado = false;
    //conectado = miniscan.desconectar();

    if(!conectado){
        QMessageBox::information(this, "Desconectado", "El MiniScan se ha desconectado correctamente.");
    }else{
        QMessageBox::critical(this, "Error al desconectar", "El MiniScan no se pudo desconectar.");
    }

    borrarResultados();
    revisionBtns();
}

void MainWindow::on_actionSalir_triggered()
{
    close();
}

void MainWindow::on_btnMedir_clicked()
{
    borrarResultados();

    QList<QVariant> medicion;

    medicion = miniscan.medir();

    QList<QVariant>::const_iterator iter = qFind(medicion.begin(), medicion.end(), 0);

    if(iter == medicion.end()){
        //si no se consigue ningun cero exacto (0), es porque la lista fue llenada correctamente y por lo tanto la medicion ocurrio

    }else{
        medicion.clear();

        QMessageBox::critical(this, "Error al medir la muestra", "La medición no se pudo realizar.");

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

    numCurvas += 1;
    revisionBtns();
}

void MainWindow::on_actionAcerca_de_triggered()
{
    QImage logo(":/img/logo_pequeno.png");
    QMessageBox msgBox;
    msgBox.setIconPixmap(QPixmap::fromImage(logo));
    QString titulo("<html><head><head/><body><p><span style=' font-size:14pt; font-weight:600; color:#4b4b4b;'>Spectrasoft</span>&nbsp; &nbsp;<span style=' font-size:8pt; font-weight:450; color:#4b4b4b;'>versión " + version + "</span></p>");
    QString resumen("<p>Software para el manejo del MiniScan XE Plus.</p>");
    QString desarrollador("<p>Diseñado, desarrollado e implementado por Gabriel Núñez.\nContacto: gabriel.nzn@gmail.com</p></body></html>");
    msgBox.setText(titulo + resumen + desarrollador);
    msgBox.exec();
}

//void MainWindow::on_btnFototipo_clicked()
//{
//    dlgFototipo dlg(ops.fototipo());
//    dlg.exec();

//    int aux;
//    aux = dlg.fototipoSeleccionado();

//    if(aux != 0){
//        fototipo = aux;
//        QSize tam;

//        tam.setWidth(125);
//        tam.setHeight(125);

//        QPixmap imgFototipo(":/img/fototipo_" + QString().setNum(fototipo) + ".png");
//        imgFototipo.scaled(tam);

//        ui->etqNumeroFototipo->setText(QString().setNum(fototipo));

//        ui->etqFototipo->setPixmap(imgFototipo);
//    }

    //revisionBtns();
//}

void MainWindow::on_btnReflectancia_clicked()
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

void MainWindow::on_btnAbsorbancia_clicked()
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

void MainWindow::on_btnDatosAdicionales_clicked()
{
    if(dts != NULL && !dts->isMinimized() && !dts->isActiveWindow()){
        delete dts;
        dts = NULL;
    }

    if(dts == NULL){

        QVector<float> aux(31);

        for(int i = 0; i < 31; ++i){
            aux[i] = datosEspectrales[i]/100.0;
        }

        dts = new dlgDatosAdicionales(aux);
        dts->show();
    }else{
        dts->showMaximized();
    }
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

void MainWindow::on_btnEliminar_clicked()
{
    borrarResultados();
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
    dlgVerUsuario verUsuario(infoUsuario);

    verUsuario.exec();
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

    elimH.exec();

    if(elimH.getHistoriaEliminada()){
        infoHistoria.clear();
    }
    revisionBtns();
}

void MainWindow::on_actionModificar_historia_triggered()
{
    dlgModificarHistoria modH(infoUsuario["clave"], infoHistoria);

    modH.exec();

    if(modH.historiaModificada()){
        infoHistoria = modH.getInfoHistoria();
    }
}
