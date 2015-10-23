#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    conectado = bdConectada = false;
    ref = abs = absorcion = NULL;
    dts = NULL;
    infoUsuario.clear();
    infoHistoria.clear();
    infoMuestra.clear();
    modeloDatos = new QStandardItemModel(2, 31, this);

    QStringList cabeceras;
    //dando formato a la tabla de datos espectrales de la vista principal
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
    bdConectada = db.open();

    if(!bdConectada){
        QMessageBox::critical(this, "Error de conexión", "No se pudo establecer una conexión con la base de datos, muchas operaciones no estarán disponibles.");
    }

    this->setFixedSize(this->size());
    revisionBtns();
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::revisionBtns()
{
    bool estandarizar, medirM, borrarResultadosM, registrarM, buscarM, verM, exportarM, verRef, verAbs, verAbsorcion, datosA, masOpcionesM, modificarM, eliminarM, cerrarM,
    sesionU, verU, modificarU, cambiarC, masOpcionesU, registrarU, administrarU, cerrarU,
    registrarH, buscarH, verH, cerrarH, modificarH, eliminarH, masOpcionesH;

    //revisa los botones relacionados con las funciones del MiniScan,
    //y los habilita/deshabilita dependiendo de si el MiniScan esta conectado o no
    if(conectado){
        estandarizar = true;

        if(infoMuestra.isEmpty())
            medirM = true;
        else
            medirM = false;
    }else{
         estandarizar = medirM = false;
    }

    //revisa los botones relacionados con los resultados de una medicion,
    //y los habilita/deshabilita dependiendo de si hay una medicion cargada o no
    if(!datosEspectrales.isEmpty()){
        verRef = verAbs = verAbsorcion = datosA = true;

        if(infoMuestra.isEmpty())
            borrarResultadosM = true;
        else
            borrarResultadosM = false;
    }else{
        verRef = verAbs = verAbsorcion = datosA = borrarResultadosM = false;
    }

    //revisa todos los botones que realicen operaciones relacionadas con la base de datos
    if(bdConectada){

        //revisa los botones relacionados con las funciones del usuario,
        //y los habilita/deshabilita dependiendo de cual sea el caso
        if(!infoUsuario.isEmpty()){
            sesionU = false;
            verU = modificarU = cambiarC = cerrarU = true;

            if(infoUsuario["rol"] == "administrador"){
                masOpcionesU = registrarU = administrarU = true;
            }else{
                masOpcionesU = registrarU = administrarU = false;
            }

            //revisa los botones relacionados con las funciones de la historia,
            //y los habilita/deshabilita dependiendo de cual sea el caso
            if(!infoHistoria.isEmpty()){

                registrarH = buscarH = false;
                verH = cerrarH = true;

                if(infoUsuario["rol"] == "dermatologo"){
                    masOpcionesH = modificarH = eliminarH = true;
                }else{
                    masOpcionesH = modificarH = eliminarH = false;
                }

                //revisa los botones relacionados con las funciones de la muestra,
                //y los habilita/deshabilita dependiendo de cual sea el caso
                if(!infoMuestra.isEmpty()){
                    registrarM = buscarM = false;
                    verM = exportarM = cerrarM = true;

                    if(infoUsuario["rol"] == "dermatologo"){
                        masOpcionesM = modificarM = eliminarM = true;
                    }else{
                        masOpcionesM = modificarM = eliminarM = false;
                    }
                }else{

                    buscarM = true;
                    verM = exportarM = cerrarM = masOpcionesM = modificarM = eliminarM = false;

                    if(!datosEspectrales.isEmpty() && infoUsuario["rol"] == "dermatologo"){
                        registrarM = true;
                    }else{
                        registrarM = false;
                    }
                }

            }else{

                buscarH = true;
                verH = masOpcionesH = modificarH = eliminarH = cerrarH = false;
                registrarM = buscarM = verM = exportarM = masOpcionesM = modificarM = eliminarM = cerrarM = false;

                if(infoUsuario["rol"] == "dermatologo"){
                    registrarH = true;
                }else{
                    registrarH = false;
                }
            }

        //si no hay un usuario cargado, deshabilita todos los botones de las funciones de usuario,
        //y los botones de las funciones dependiente del mismo
        }else{
            sesionU = true;
            verU =  modificarU = cambiarC = masOpcionesU = registrarU = administrarU = cerrarU = false;
            registrarH = buscarH = verH = masOpcionesH = modificarH = eliminarH = cerrarH = false;
            registrarM = buscarM = verM = exportarM = masOpcionesM = modificarM = eliminarM = cerrarM = false;
        }

    //si la base de datos esta desconectada de software,
    //deshabilita todos los botones que realicen operaciones con la misma
    }else{
        sesionU = verU =  modificarU = cambiarC = masOpcionesU = registrarU = administrarU = cerrarU = false;
        registrarH = buscarH = verH = masOpcionesH = modificarH = eliminarH = cerrarH = false;
        registrarM = buscarM = verM = exportarM = masOpcionesM = modificarM = eliminarM = cerrarM = false;
    }

    //habilita/deshabilita el boton para estandarizar
    ui->actionEstandarizar->setEnabled(estandarizar);

    //habilita/deshabilita los botones de las funciones de los resultados
    ui->actionVer_reflectancia->setEnabled(verRef);
    ui->actionVer_absorbancia->setEnabled(verAbs);
    ui->actionVer_absorcion->setEnabled(verAbsorcion);
    ui->actionDatos_adicionales->setEnabled(datosA);

    //habilita/deshabilita los botones de las funciones del usuario
    ui->actionIniciar_sesion->setEnabled(sesionU);
    ui->actionVer_usuario->setEnabled(verU);
    ui->actionModificar_usuario->setEnabled(modificarU);
    ui->actionCambiar_clave->setEnabled(cambiarC);
    ui->menuMas_opciones_u->setEnabled(masOpcionesU);
    ui->actionRegistrar_usuario->setEnabled(registrarU);
    ui->actionAdministrar_usuarios->setEnabled(administrarU);
    ui->actionCerrar_sesion->setEnabled(cerrarU);

    //habilita/deshabilita los botones de las funciones de la historia
    ui->actionRegistrar_historia->setEnabled(registrarH);
    ui->actionBuscar_historia->setEnabled(buscarH);
    ui->actionVer_historia->setEnabled(verH);
    ui->menuMas_opciones_h->setEnabled(masOpcionesH);
    ui->actionModificar_historia->setEnabled(modificarH);
    ui->actionEliminar_historia->setEnabled(eliminarH);
    ui->actionCerrar_historia->setEnabled(cerrarH);

    //habilita/deshabilita los botones de las funciones de la muestra
    ui->actionRealizar_medicion->setEnabled(medirM);
    ui->actionBorrar_resultados->setEnabled(borrarResultadosM);
    ui->actionRegistrar_muestra->setEnabled(registrarM);
    ui->actionBuscar_muestra->setEnabled(buscarM);
    ui->actionVer_muestra->setEnabled(verM);
    ui->actionExportar_muestra->setEnabled(exportarM);
    ui->menuMas_opciones_m->setEnabled(masOpcionesM);
    ui->actionModificar_muestra->setEnabled(modificarM);
    ui->actionEliminar_muestra->setEnabled(eliminarM);
    ui->actionCerrar_muestra->setEnabled(cerrarM);
}

void MainWindow::borrarResultados()
{
    //Limpia las variables y libera la memoria asignada dinamicamente
    //relacionada con los resultados de una medicion
    datosEspectrales.clear();
    datosAbsorbancia.clear();
    XYZ.clear();
    LAB.clear();
    datosAbsorcion.clear();
    eritema = 0.0;

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

    if(absorcion != NULL){
        delete absorcion;
        absorcion = NULL;
    }

    if(dts != NULL){
        delete dts;
        dts = NULL;
    }
}

void MainWindow::on_actionConectar_triggered()
{
    if(!conectado){
        //conectado = true;
        ui->actionConectar->setText("Desconectar");
        conectado = miniscan.conectar();

        if(conectado){
            QMessageBox::information(this, "Conectado", "El MiniScan se ha conectado correctamente.");
        }else{
            QMessageBox::critical(this, "Error al conectar", "El MiniScan no se pudo conectar, verifique el cable de comunicación.");
        }
        ui->actionConectar->setIcon(QIcon(":img/off.png"));
    }else{
        //conectado = false;
        ui->actionConectar->setText("Conectar");
        conectado = miniscan.desconectar();

        if(!conectado){
            QMessageBox::information(this, "Desconectado", "El MiniScan se ha desconectado correctamente.");
        }else{
            QMessageBox::critical(this, "Error al desconectar", "El MiniScan no se pudo desconectar, verifique el cable de comunicación.");
        }
         ui->actionConectar->setIcon(QIcon(":img/on.png"));
    }

    if(conectado){
        ui->etqLogotipo->setPixmap(QPixmap::fromImage(QImage(":/img/logo_nuevo.png")));
    }else{
        ui->etqLogotipo->setPixmap(QPixmap::fromImage(QImage(":/img/logo_gris.png")));
    }

    revisionBtns();
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
        QMessageBox::critical(this, "Error al estandarizar", "El MiniScan no se pudo estandarizar, verifique el cable de comunicación.");
    }

    revisionBtns();
}

void MainWindow::on_actionSalir_triggered()
{
    close();
}

void MainWindow::on_actionAcerca_de_triggered()
{
    dlgAcercaDe acercaDe;
    acercaDe.exec();
}

void MainWindow::on_actionIniciar_sesion_triggered()
{
    dlgInicioSesion sesion;

    connect(&sesion, &dlgInicioSesion::sesion_iniciada, this, &MainWindow::on_sesionIniciada);
    sesion.exec();
}

void MainWindow::on_sesionIniciada(QHash<QString, QString> info)
{
    infoUsuario = info;
    revisionBtns();
}

void MainWindow::on_actionVer_usuario_triggered()
{
    dlgVerUsuario verU(infoUsuario);
    verU.exec();
}

void MainWindow::on_actionModificar_usuario_triggered()
{
    dlgModificarUsuario modU(infoUsuario);

    connect(&modU, &dlgModificarUsuario::usuarioModificado, this, &MainWindow::on_usuarioModificado);
    modU.exec();
}

void MainWindow::on_usuarioModificado(QHash<QString, QString> infoModificada)
{
    infoUsuario = infoModificada;
}

void MainWindow::on_actionCambiar_clave_triggered()
{
    dlgCambiarClave cambiarC(infoUsuario["cedula"], infoUsuario["clave"]);

    connect(&cambiarC, &dlgCambiarClave::claveCambiada, this, &MainWindow::on_claveCambiada);
    cambiarC.exec();
}

void MainWindow::on_claveCambiada(QString info)
{
    infoUsuario["clave"] = info;
}

void MainWindow::on_actionAdministrar_usuarios_triggered()
{
    dlgAdministrarUsuarios administrarU(infoUsuario["cedula"], infoUsuario["clave"]);
    administrarU.exec();
}

void MainWindow::on_actionCerrar_sesion_triggered()
{
    infoHistoria.clear();
    infoUsuario.clear();

    if(!infoMuestra.isEmpty()){
        infoMuestra.clear();
        borrarResultados();
    }

    QMessageBox::information(this, "Sesión cerrada", "Se ha cerrado la sesión correctamente.");
    revisionBtns();
}

void MainWindow::on_actionRegistrar_usuario_triggered()
{
    dlgRegUsuario regU(infoUsuario["clave"]);
    regU.exec();
}

void MainWindow::on_actionRegistrar_historia_triggered()
{
    dlgRegHistoria regH(infoUsuario["clave"]);

    connect(&regH, &dlgRegHistoria::historia_registrada, this, &MainWindow::on_historiaRegistrada);
    regH.exec();
}

void MainWindow::on_historiaRegistrada(QHash<QString, QString> info)
{
    infoHistoria = info;
    revisionBtns();
}

void MainWindow::on_actionBuscar_historia_triggered()
{
    dlgBuscarHistoria buscarH;

    connect(&buscarH, &dlgBuscarHistoria::historiaAbierta, this, &MainWindow::on_historiaAbierta);
    buscarH.exec();
}

void MainWindow::on_historiaAbierta(QHash<QString, QString> info)
{
    infoHistoria = info;
    revisionBtns();
}

void MainWindow::on_actionVer_historia_triggered()
{
    dlgVerHistoria verH(infoHistoria);
    verH.exec();
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

void MainWindow::on_actionCerrar_historia_triggered()
{
    infoHistoria.clear();

    if(!infoMuestra.isEmpty()){
        infoMuestra.clear();
        borrarResultados();
    }

    QMessageBox::information(this, "Historia cerrada", "Se ha cerrado la historia correctamente.");
    revisionBtns();
}

void MainWindow::on_actionRealizar_medicion_triggered()
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
        //medida de piel de Gabriel Nunez
        medicion.push_back(float(17.2101));
        medicion.push_back(float(15.2329));
        medicion.push_back(float(15.13));
        medicion.push_back(float(14.2457));
        medicion.push_back(float(16.0641));
        medicion.push_back(float(18.2752));
        medicion.push_back(float(19.687));
        medicion.push_back(float(21.0481));
        medicion.push_back(float(21.9136));
        medicion.push_back(float(23.1382));
        medicion.push_back(float(23.9694));
        medicion.push_back(float(25.4163));
        medicion.push_back(float(25.2229));
        medicion.push_back(float(24.8392));
        medicion.push_back(float(24.9241));
        medicion.push_back(float(25.2234));
        medicion.push_back(float(26.2638));
        medicion.push_back(float(26.5036));
        medicion.push_back(float(27.8098));
        medicion.push_back(float(31.5459));
        medicion.push_back(float(36.2515));
        medicion.push_back(float(39.0012));
        medicion.push_back(float(40.6161));
        medicion.push_back(float(42.1796));
        medicion.push_back(float(43.205));
        medicion.push_back(float(44.057));
        medicion.push_back(float(45.0165));
        medicion.push_back(float(45.779));
        medicion.push_back(float(46.4996));
        medicion.push_back(float(47.3194));
        medicion.push_back(float(47.8099));

//        //medida de piel oscura
//        medicion.push_back(float(3.95));
//        medicion.push_back(float(3.78));
//        medicion.push_back(float(6.24));
//        medicion.push_back(float(5.68));
//        medicion.push_back(float(6.34));
//        medicion.push_back(float(6.66));
//        medicion.push_back(float(7.38));
//        medicion.push_back(float(7.62));
//        medicion.push_back(float(8.19));
//        medicion.push_back(float(8.84));
//        medicion.push_back(float(8.86));
//        medicion.push_back(float(9.62));
//        medicion.push_back(float(9.88));
//        medicion.push_back(float(9.78));
//        medicion.push_back(float(10.02));
//        medicion.push_back(float(10.23));
//        medicion.push_back(float(10.73));
//        medicion.push_back(float(11.29));
//        medicion.push_back(float(12.14));
//        medicion.push_back(float(13.83));
//        medicion.push_back(float(16.54));
//        medicion.push_back(float(18.89));
//        medicion.push_back(float(20.28));
//        medicion.push_back(float(22.06));
//        medicion.push_back(float(22.81));
//        medicion.push_back(float(24.6));
//        medicion.push_back(float(25.2));
//        medicion.push_back(float(26.36));
//        medicion.push_back(float(27.9));
//        medicion.push_back(float(29.17));
//        medicion.push_back(float(30.11));
    }

    QModelIndex indice;

    for(int i = 0; i < 31; ++i){

        datosEspectrales.push_back(medicion.at(i).toFloat());
        indice = modeloDatos->index(0, i, QModelIndex());
        modeloDatos->setData(indice, datosEspectrales.at(i));
    }

    QVector<float> aux(31);

    //divide los datos entre 100 para quitarles el factor por el que son multiplicados por el MiniScan,
    //y los almacena en aux
    for(int i = 0; i < 31; ++i){
        aux[i] = datosEspectrales[i]/100.0;
    }

    //invoca a las funciones que realizan los calculos relacionados con los resultados de una medicion
    datosAbsorbancia = ops.absorbancia(datosEspectrales);
    XYZ = ops.CIExyz(aux);
    LAB = ops.CIELAB(aux);
    datosAbsorcion = ops.absorcion(aux);
    eritema = ops.eritema(aux);

    revisionBtns();
}

void MainWindow::on_actionVer_reflectancia_triggered()
{
    if(ref != NULL && !ref->isMinimized() && !ref->isActiveWindow()){
        delete ref;
        ref = NULL;
    }

    //crea la ventana para visualizar la reflectancia
    QVector<double> aux(31);

    for(int i = 0; i < 31; ++i){
        aux[i] = double(datosEspectrales[i]);
    }

    ref = new dlgGrafica("Curva de reflectancia difusa", "Longitud de onda (nm)", "Reflectancia (%)", 100);
    ref->agregarCurva(aux);
    ref->show();
}

void MainWindow::on_actionVer_absorbancia_triggered()
{
    if(abs != NULL && !abs->isMinimized() && !abs->isActiveWindow()){
        delete abs;
        abs = NULL;
    }

    //crea la ventana para visualizar la absorbancia
    QVector<double> aux(31);

    for(int i = 0; i < 31; ++i){
        aux[i] = double(datosAbsorbancia[i]);
    }

    abs = new dlgGrafica("Curva de absorbancia aparente", "Longitud de onda (nm)", "Absorbancia (%)", 100);
    abs->agregarCurva(aux);
    abs->show();
}

void MainWindow::on_actionVer_absorcion_triggered()
{
    if(absorcion != NULL && !absorcion->isMinimized() && !absorcion->isActiveWindow()){
        delete absorcion;
        absorcion = NULL;
    }

    //crea la ventana para visualizar la absorcion
    QVector<double> aux(31);
    double yMax = 0.0;

    for(int i = 0; i < 31; ++i){
        aux[i] = double(datosAbsorcion[i]);

        if(yMax < aux[i]){
            yMax = aux[i];
        }
    }

    absorcion = new dlgGrafica("Coeficiente de absorción", "Longitud de onda (nm)", "Valor de absorción", yMax + 50);
    absorcion->agregarCurva(aux);
    absorcion->show();
}

void MainWindow::on_actionDatos_adicionales_triggered()
{
    if(dts != NULL && !dts->isMinimized() && !dts->isActiveWindow()){
        delete dts;
        dts = NULL;
    }

    //crea la ventana para visualizar los datos adicionales
    dts = new dlgDatosAdicionales(XYZ, LAB, eritema);
    dts->show();
}

void MainWindow::on_actionBorrar_resultados_triggered()
{
    borrarResultados();
    QMessageBox::information(this, "Resultados borrados", "Los resultados se han borrado correctamente.");
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
    //dependiendo de si la muestra que se va a registrar es un fototipo o una lesion,
    //crea la ventana correspondiente
    if(tipo == "lesion"){
        dlgRegLesion regL(infoUsuario["clave"], infoUsuario["cedula"], infoHistoria["id_historia"], datosEspectrales, XYZ, LAB, datosAbsorcion, eritema);

        connect(&regL, &dlgRegLesion::lesion_registrada, this, &MainWindow::on_muestraRegistrada);
        regL.exec();
    }else{
        dlgRegFototipo regF(infoUsuario["clave"], infoUsuario["cedula"], infoHistoria["id_historia"], datosEspectrales, XYZ, LAB, datosAbsorcion, eritema);

        connect(&regF, &dlgRegFototipo::fototipo_registrado, this, &MainWindow::on_muestraRegistrada);
        connect(&regF, &dlgRegFototipo::actualizar_fototipo, this, &MainWindow::on_actualizarFototipo);
        regF.exec();
    }
}

void MainWindow::on_muestraRegistrada(const QHash<QString, QString> info)
{
    infoMuestra = info;
    revisionBtns();
}

void MainWindow::on_actualizarFototipo(int infoF)
{
    infoHistoria["fototipo"] = QString().setNum(infoF);
}

void MainWindow::on_actionVer_muestra_triggered()
{
    dlgVerMuestra verM(infoMuestra);
    verM.exec();
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
    if(infoMuestra["tipo_muestra"] == "fototipo"){
        infoHistoria.remove("fototipo");
    }

    infoMuestra.clear();
    borrarResultados();
    revisionBtns();
}

void MainWindow::on_actionModificar_muestra_triggered()
{
    dlgModificarMuestra modM(infoUsuario["clave"], infoMuestra);

    connect(&modM, &dlgModificarMuestra::muestraModificada, this, &MainWindow::on_muestraModificada);
    modM.exec();
}

void MainWindow::on_muestraModificada(QHash<QString, QString> infoModificada)
{
    infoMuestra = infoModificada;
}

void MainWindow::on_actionBuscar_muestra_triggered()
{
    dlgBuscarMuestra buscarM(infoHistoria["id_historia"]);

    connect(&buscarM, &dlgBuscarMuestra::muestraAbierta, this, &MainWindow::on_muestraAbierta);
    buscarM.exec();
}

void MainWindow::on_muestraAbierta(QHash<QString, QString> infoM, float infoDatos[2][31], float infoCoordenadas[2][3], float infoEritema)
{
    borrarResultados();

    infoMuestra = infoM;
    QModelIndex indice;

    for(int i = 0; i < 31; ++i){
        datosEspectrales.push_back(infoDatos[0][i]);
        datosAbsorcion.push_back(infoDatos[1][i]);
        indice = modeloDatos->index(0, i, QModelIndex());
        modeloDatos->setData(indice, infoDatos[0][i]);
    }

    for(int i = 0; i < 3; ++i){
        XYZ.push_back(infoCoordenadas[0][i]);
        LAB.push_back(infoCoordenadas[1][i]);
    }

    eritema = infoEritema;

    revisionBtns();
}

void MainWindow::on_actionExportar_muestra_triggered()
{
    int fila = 1;

    //crea un archivo xlsx y escribe la informacion de la muestra cargada actualmente
    QXlsx::Document xlsx;
    xlsx.write("A" + QString().setNum(fila), "Información de la historia:");
    fila+=2;
    xlsx.write("A" + QString().setNum(fila), "Nombre(s): " + infoHistoria["nombre"]);
    ++fila;
    xlsx.write("A" + QString().setNum(fila), "Apellido(s): " + infoHistoria["apellido"]);
    ++fila;
    xlsx.write("A" + QString().setNum(fila), "Fecha de nacimiento: " + QDate().fromString(infoHistoria["fecha_nac"], "yyyy-MM-dd").toString("dd-MM-yyyy"));
    ++fila;

    if(infoMuestra["sexo"] == "F"){
        xlsx.write("A" + QString().setNum(fila), "Sexo: Femenino");
    }else{
        xlsx.write("A" + QString().setNum(fila), "Sexo: Masculino");
    }

    ++fila;

    if(infoHistoria.contains("fototipo")){

        int numFototipo = infoHistoria["fototipo"].toInt();
        QString aux;

        switch (numFototipo) {
        case 1:
            aux = "I";
            break;
        case 2:
            aux = "II";
            break;
        case 3:
            aux = "III";
            break;
        case 4:
            aux = "IV";
            break;
        case 5:
            aux = "V";
            break;
        case 6:
            aux = "VI";
            break;
        }

        xlsx.write("A" + QString().setNum(fila), "Fototipo: " + aux);
    }

    fila+=2;

    xlsx.write("A" + QString().setNum(fila), "Información de la muestra:");
    fila+=2;
    xlsx.write("A" + QString().setNum(fila), "Tipo: " + infoMuestra["tipo_muestra"]);
    ++fila;
    xlsx.write("A" + QString().setNum(fila), "Nombre: " + infoMuestra["nombre_muestra"]);
    ++fila;
    xlsx.write("A" + QString().setNum(fila), "Área: " + infoMuestra["area_muestra"]);
    fila+=2;
    xlsx.write("A" + QString().setNum(fila), "Coordenadas de cromaticidad CIE xyz");
    ++fila;
    xlsx.write("A" + QString().setNum(fila), "x:");
    xlsx.write("B" + QString().setNum(fila), XYZ[0]);
    ++fila;
    xlsx.write("A" + QString().setNum(fila), "y:");
    xlsx.write("B" + QString().setNum(fila), XYZ[1]);
    ++fila;
    xlsx.write("A" + QString().setNum(fila), "z:");
    xlsx.write("B" + QString().setNum(fila), XYZ[2]);
    fila+=2;
    xlsx.write("A" + QString().setNum(fila), "Coordenadas del espacio CIELAB");
    ++fila;
    xlsx.write("A" + QString().setNum(fila), "L:");
    xlsx.write("B" + QString().setNum(fila), LAB[0]);
    ++fila;
    xlsx.write("A" + QString().setNum(fila), "a:");
    xlsx.write("B" + QString().setNum(fila), LAB[1]);
    ++fila;
    xlsx.write("A" + QString().setNum(fila), "b:");
    xlsx.write("B" + QString().setNum(fila), LAB[2]);
    fila+=2;
    xlsx.write("A" + QString().setNum(fila), "Datos espectrales de la muestra:");
    fila+=2;

    int rango = 400;
    QString auxS;
    char letra = 'A';
    bool bandera = false;

    for(int i = 0; i < 31; ++i){

        if(!bandera){
            auxS = QString(letra);
        }else{
            auxS = "A" + QString(letra);
        }

        xlsx.write(auxS + QString().setNum(fila), rango);
        xlsx.write(auxS + QString().setNum(fila + 1), datosEspectrales.at(i));

        if(letra == 'Z'){
            letra = 'A';
            letra-=1;
            bandera = true;
        }
        rango+=10;
        letra+=1;
    }
    fila+=3;
    xlsx.write("A" + QString().setNum(fila), "Datos de absorción de la muestra:");
    fila+=2;

    rango = 400;
    auxS.clear();
    letra = 'A';
    bandera = false;

    for(int i = 0; i < 31; ++i){

        if(!bandera){
            auxS = QString(letra);
        }else{
            auxS = "A" + QString(letra);
        }

        xlsx.write(auxS + QString().setNum(fila), rango);
        xlsx.write(auxS + QString().setNum(fila + 1), datosAbsorcion.at(i));

        if(letra == 'Z'){
            letra = 'A';
            letra-=1;
            bandera = true;
        }
        rango+=10;
        letra+=1;
    }
    fila+=3;
    xlsx.write("A" + QString().setNum(fila), "Índice de eritema:");
    ++fila;
    xlsx.write("A" + QString().setNum(fila), eritema);

    xlsx.saveAs(QDir::homePath() + "/" + QStandardPaths::displayName( QStandardPaths::DesktopLocation ) + "/" + "muestra-" + infoMuestra["id_muestra"] + "-fecha-" + QDate::currentDate().toString("dd-MM-yyyy") + ".xlsx");
    QMessageBox::information(this, "Muestra exportada", "Se ha exportado la muestra correctamente a su escritorio.");
}
