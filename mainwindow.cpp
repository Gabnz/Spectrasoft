#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    conectado = bdConectada = false;
    ref = abs = absorcion = esparcimiento = NULL;
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
    bdConectada = db.open();

    if(!bdConectada){
        QMessageBox::critical(this, "Error de conexión", "No se pudo establecer una conexión con la base de datos, muchas operaciones no estarán disponibles.");
    }

    //
    this->setFixedSize(this->size());
    revisionBtns();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::revisionBtns()
{
    bool estandarizar, medirM, borrarResultadosM, registrarM, buscarM, verM, exportarM, verRef, verAbs, verAbsorcion, verEsparcimiento, datosA, masOpcionesM, modificarM, eliminarM, cerrarM,
    sesionU, verU, modificarU, cambiarC, masOpcionesU, registrarU, administrarU, cerrarU,
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
        verRef = verAbs = verAbsorcion = verEsparcimiento = datosA = true;

        if(infoMuestra.isEmpty())
            borrarResultadosM = true;
        else
            borrarResultadosM = false;
    }else{
        verRef = verAbs = verAbsorcion = verEsparcimiento = datosA = borrarResultadosM = false;
    }

    if(bdConectada){

        if(!infoUsuario.isEmpty()){
            sesionU = false;
            verU = modificarU = cambiarC = cerrarU = true;

            if(infoUsuario["rol"] == "administrador"){
                masOpcionesU = registrarU = administrarU = true;
            }else{
                masOpcionesU = registrarU = administrarU = false;
            }

            if(!infoHistoria.isEmpty()){

                registrarH = buscarH = false;
                verH = cerrarH = true;

                if(infoUsuario["rol"] == "dermatologo"){
                    masOpcionesH = modificarH = eliminarH = true;
                }else{
                    masOpcionesH = modificarH = eliminarH = false;
                }

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

        }else{
            sesionU = true;
            verU =  modificarU = cambiarC = masOpcionesU = registrarU = administrarU = cerrarU = false;
            registrarH = buscarH = verH = masOpcionesH = modificarH = eliminarH = cerrarH = false;
            registrarM = buscarM = verM = exportarM = masOpcionesM = modificarM = eliminarM = cerrarM = false;
        }

    }else{
        sesionU = verU =  modificarU = cambiarC = masOpcionesU = registrarU = administrarU = cerrarU = false;
        registrarH = buscarH = verH = masOpcionesH = modificarH = eliminarH = cerrarH = false;
        registrarM = buscarM = verM = exportarM = masOpcionesM = modificarM = eliminarM = cerrarM = false;
    }

    ui->actionEstandarizar->setEnabled(estandarizar);

    ui->actionVer_reflectancia->setEnabled(verRef);
    ui->actionVer_absorbancia->setEnabled(verAbs);
    ui->actionVer_absorcion->setEnabled(verAbsorcion);
    ui->actionVer_esparcimiento->setEnabled(verEsparcimiento);
    ui->actionDatos_adicionales->setEnabled(datosA);

    ui->actionIniciar_sesion->setEnabled(sesionU);
    ui->actionVer_usuario->setEnabled(verU);
    ui->actionModificar_usuario->setEnabled(modificarU);
    ui->actionCambiar_clave->setEnabled(cambiarC);
    ui->menuMas_opciones_u->setEnabled(masOpcionesU);
    ui->actionRegistrar_usuario->setEnabled(registrarU);
    ui->actionAdministrar_usuarios->setEnabled(administrarU);
    ui->actionCerrar_sesion->setEnabled(cerrarU);

    ui->actionRegistrar_historia->setEnabled(registrarH);
    ui->actionBuscar_historia->setEnabled(buscarH);
    ui->actionVer_historia->setEnabled(verH);
    ui->menuMas_opciones_h->setEnabled(masOpcionesH);
    ui->actionModificar_historia->setEnabled(modificarH);
    ui->actionEliminar_historia->setEnabled(eliminarH);
    ui->actionCerrar_historia->setEnabled(cerrarH);

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
    datosEspectrales.clear();
    datosAbsorbancia.clear();
    XYZ.clear();
    LAB.clear();
    datosAbsorcion.clear();
    datosEsparcimiento.clear();
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

    if(esparcimiento != NULL){
        delete esparcimiento;
        esparcimiento = NULL;
    }

    if(dts != NULL){
        delete dts;
        dts = NULL;
    }
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

        QMessageBox::critical(this, "Error al medirM la muestra", "La medición no se pudo realizar.");

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

    datosAbsorbancia = ops.absorbancia(datosEspectrales);
    XYZ = ops.CIExyz(aux);
    LAB = ops.CIELAB(aux);
    datosAbsorcion = ops.absorcion(aux);
    datosEsparcimiento = ops.esparcimiento(aux);
    eritema = ops.eritema(aux);

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

        ref = new dlgGrafica("Curva de reflectancia difusa", "Longitud de onda (nm)", "Reflectancia (%)", 100);
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
            aux[i] = double(datosAbsorbancia[i]);
        }

        abs = new dlgGrafica("Curva de absorbancia aparente", "Longitud de onda (nm)", "Absorbancia (%)", 100);
        abs->agregarCurva(aux);
        abs->show();
    }else{
        abs->showMaximized();
    }
}

void MainWindow::on_actionVer_absorcion_triggered()
{
    if(absorcion != NULL && !absorcion->isMinimized() && !absorcion->isActiveWindow()){
        delete absorcion;
        absorcion = NULL;
    }

    if(absorcion == NULL){

        QVector<double> aux(31);

        for(int i = 0; i < 31; ++i){
            aux[i] = double(datosAbsorcion[i]);
        }

        absorcion = new dlgGrafica("Coeficiente de absorción", "Longitud de onda (nm)", "Absorción (%)", 200);
        absorcion->agregarCurva(aux);
        absorcion->show();
    }else{
        absorcion->showMaximized();
    }
}

void MainWindow::on_actionVer_esparcimiento_triggered()
{
    if(esparcimiento != NULL && !esparcimiento->isMinimized() && !esparcimiento->isActiveWindow()){
        delete esparcimiento;
        esparcimiento = NULL;
    }

    if(esparcimiento == NULL){

        QVector<double> aux(31);

        for(int i = 0; i < 31; ++i){
            aux[i] = double(datosEsparcimiento[i]);
        }

        esparcimiento = new dlgGrafica("Coeficiente de esparcimiento", "Longitud de onda (nm)", "Esparcimiento (%)", 200);
        esparcimiento->agregarCurva(aux);
        esparcimiento->show();
    }else{
        esparcimiento->showMaximized();
    }
}

void MainWindow::on_actionDatos_adicionales_triggered()
{
    if(dts != NULL && !dts->isMinimized() && !dts->isActiveWindow()){
        delete dts;
        dts = NULL;
    }

    if(dts == NULL){

        dts = new dlgDatosAdicionales(XYZ, LAB, eritema);
        dts->show();
    }else{
        dts->showMaximized();
    }
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
    if(tipo == "lesion"){
        dlgRegLesion regL(infoUsuario["clave"], infoUsuario["cedula"], infoHistoria["id_historia"], datosEspectrales, XYZ, LAB, datosAbsorcion, datosEsparcimiento, eritema);

        connect(&regL, &dlgRegLesion::lesion_registrada, this, &MainWindow::on_muestraRegistrada);
        regL.exec();
    }else{
        dlgRegFototipo regF(infoUsuario["clave"], infoUsuario["cedula"], infoHistoria["id_historia"], datosEspectrales, XYZ, LAB, datosAbsorcion, datosEsparcimiento, eritema);

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

void MainWindow::on_muestraAbierta(QHash<QString, QString> infoM, float infoDatos[3][31], float infoCoordenadas[2][3], float infoEritema)
{
    borrarResultados();

    infoMuestra = infoM;
    QModelIndex indice;

    for(int i = 0; i < 31; ++i){
        datosEspectrales.push_back(infoDatos[0][i]);
        datosAbsorcion.push_back(infoDatos[1][i]);
        datosEsparcimiento.push_back(infoDatos[2][i]);
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
    xlsx.write("A" + QString().setNum(fila), "Datos de esparcimiento de la muestra:");
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
        xlsx.write(auxS + QString().setNum(fila + 1), datosEsparcimiento.at(i));

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
