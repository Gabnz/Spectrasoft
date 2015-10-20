#include "msv.h"

using namespace std;

#define Malloc(type,n) (type *)malloc((n)*sizeof(type))
svm_problem prob;
svm_parameter parametro;
svm_model *model;
svm_node *x_space;
int nr_fold= 98;//Numero de fold para Cross-Validation
static int max_line_len;
static char *line = NULL;
char model_file_name[1024];
svm_node *x;
int max_nr_attr = 64;
int predict_probability=0;
double dataD[colum+1][fil];
int nColum=0;
int nFilas=0;


msv::msv()
{
    QDir dir;
    dir.setPath(QDir::homePath() + "/" + QStandardPaths::displayName( QStandardPaths::DesktopLocation ) + "/" + "prueba");

    if(!dir.exists())
        dir.mkdir(QDir::homePath() + "/" + QStandardPaths::displayName( QStandardPaths::DesktopLocation ) + "/" + "prueba");
}

static char* readline(QFile *input)
{
    int len;
    if((input->readLine(line,max_line_len)) == NULL)
        return NULL;
    while(strrchr(line,'\n') == NULL)
    {
        max_line_len *= 2;
        line = (char *) realloc(line,max_line_len);
        len = (int) strlen(line);
        if(input->readLine(line+len,max_line_len)==NULL){break;}
    }
    return line;
}

void exit_input_error(int line_num)
{
    qDebug()<<"Wrong input format at line "<<line_num<<"\n";
    exit(1);
}

void msv::DefParametros(){

    /*Parametros Kernel RBF*/
    parametro.svm_type = C_SVC;
    parametro.kernel_type = RBF;
    parametro.degree = 3;//3;
    parametro.gamma = pow(2,-11);
    parametro.coef0 = 1;
    parametro.nu = 0.5;
    parametro.cache_size = 100.0;
    parametro.C = pow(2,-1);
    parametro.eps = 0.001;
    parametro.p = 0.1;
    parametro.shrinking = 0;
    parametro.probability = 1;
    parametro.nr_weight = 0;
    parametro.weight_label = NULL;
    parametro.weight = NULL;

}

void msv::msv_train(QFile *Datos){

    if(!Datos->open(QIODevice::ReadOnly | QIODevice::Text))
        exit(1);

    const char *error_msg;
    string str = "out.model";
    strcpy(model_file_name,str.c_str());

    //DefParametros();

    read_problem(Datos);
    /*
    error_msg = svm_check_parameter(&prob,&parametro);
    if(error_msg){
       qDebug()<<"Error";
       return;
    }*/
    OptimizacionParametros();
    //do_cross_validation();

    model = svm_train(&prob,&parametro);
    svm_save_model(model_file_name,model);

    if(svm_save_model(model_file_name,model))
        exit(1);

    svm_free_and_destroy_model(&model);
        svm_destroy_param(&parametro);
        free(prob.y);
        free(prob.x);
        free(x_space);
        free(line);

    Datos->close();

}

void msv::msv_predict(QFile *Datos){

    QDir::setCurrent("C:/Users/Paola/Documents/prueba");
    QFile output("output_file");

    string str = "out.model";
    strcpy(model_file_name,str.c_str());

    predict_probability = 1;

    if(!Datos->open(QIODevice::ReadOnly | QIODevice::Text)){
        exit(1);
    }

    if(!output.open(QIODevice::WriteOnly | QIODevice::Text)){
        exit(1);
    }

    if((model=svm_load_model(model_file_name))==0)
    {
        qDebug()<<"can't open model file\n";
        exit(1);
    }

    x = (struct svm_node *) malloc(max_nr_attr*sizeof(struct svm_node));
    if(predict_probability==1)
    {

        if(svm_check_probability_model(model)==0)
        {
            qDebug()<<"Model does not support probabiliy estimates\n";
            exit(1);
        }
    }
    else
    {
        if(svm_check_probability_model(model)!=0)
            qDebug()<<"Model supports probability estimates, but disabled in prediction.\n";
    }

    predict(Datos,&output);
    svm_free_and_destroy_model(&model);
    free(x);
    free(line);
    Datos->close();
    output.close();

}

void msv::predict(QFile *input, QFile *output){

    /*Para medidas de Evaluacion*/
    int matrixConf[7][7]; //Matriz de Confusion
    QVector<int> Inst_Correct; //Vector de instancias Correctas
    Inst_Correct<<0<<0<<0<<0<<0<<0;
    int *data = Inst_Correct.data();
    QVector<int> Inst_incorrc;
    Inst_incorrc<<0<<0<<0<<0<<0<<0;//Vector de instancias Incorrectas
    int *inst_inc = Inst_incorrc.data();

    int correct = 0;
    int total = 0;
    double error = 0;
    double sump = 0, sumt = 0, sumpp = 0, sumtt = 0, sumpt = 0;

    int svm_type=svm_get_svm_type(model);
    int nr_class=svm_get_nr_class(model);
    double *prob_estimates=NULL;
    int j;

    QTextStream out(output);

    for (int j=1; j<=6; j++){
      for (int i=1; i<=6; i++)
        matrixConf[i][j]=0;
    }

    if(predict_probability)
    {
            int *labels=(int *) malloc(nr_class*sizeof(int));
            svm_get_labels(model,labels);
            prob_estimates = (double *) malloc(nr_class*sizeof(double));
            out<<"labels ";
            for(j=0;j<nr_class;j++)
                out<<labels[j];
            out<<"\n";
            free(labels);
    }
    max_line_len = 1024;
    line = (char *)malloc(max_line_len*sizeof(char));

    while(readline(input) != NULL && !input->atEnd())
    {
        int i = 0;
        double target_label, predict_label;
        char *idx, *val, *label, *endptr;
        int inst_max_index = -1;
        label = strtok(line," \t\n");

        if(label == NULL)
            exit_input_error(total+1);

        target_label = strtod(label,&endptr);
        if(endptr == label || *endptr != '\0')
            exit_input_error(total+1);

        while(1)
        {
            if(i>=max_nr_attr-1)
            {
                max_nr_attr *= 2;
                x = (struct svm_node *) realloc(x,max_nr_attr*sizeof(struct svm_node));
            }

            idx = strtok(NULL,":");
            val = strtok(NULL," \t");


            if(val == NULL)
                break;
            errno = 0;
            x[i].index = (int) strtol(idx,&endptr,10);
            if(endptr == idx || errno != 0 || *endptr != '\0' || x[i].index <= inst_max_index)
                exit_input_error(total+1);
            else
                inst_max_index = x[i].index;

            errno = 0;
            x[i].value = strtod(val,&endptr);
            if(endptr == val || errno != 0 || (*endptr != '\0' && !isspace(*endptr)))
                exit_input_error(total+1);

            ++i;
        }

        x[i].index = -1;


        if (predict_probability && (svm_type==C_SVC || svm_type==NU_SVC))
        {
            int Clases = atoi(label);

            predict_label = svm_predict_probability(model,x,prob_estimates);
            out<<predict_label;
            if(predict_label==1){

                if(1 == Clases)
                {
                    matrixConf[Clases][1] = matrixConf[Clases][1]+1;
                    data[0]=data[0]+1;

                }
                else{
                    matrixConf[Clases][1] = matrixConf[Clases][1] +1;
                    inst_inc[0]=inst_inc[0]+1;
                }
            }
                if(predict_label==2)
                {
                    if(2 == Clases){
                        matrixConf[Clases][2] = matrixConf[Clases][2]+1;
                        data[1]=data[1]+1;
                    }
                    else{
                        matrixConf[Clases][2] = matrixConf[Clases][2] +1;
                        inst_inc[1]=inst_inc[1]+1;
                    }
                }

            if(predict_label==3)
            {
                if(3 == Clases)
                {
                    matrixConf[Clases][3] = matrixConf[Clases][3]+1;
                    data[2]=data[2]+1;
                }
                else{
                    matrixConf[Clases][3] = matrixConf[Clases][3] +1;
                    inst_inc[2]=inst_inc[2]+1;
                }

            }
            if(predict_label==4)
            {
                if(4 == Clases)
                {
                    matrixConf[Clases][4] = matrixConf[Clases][4]+1;
                    data[3]=data[3]+1;
                }
                else{
                    matrixConf[Clases][4] = matrixConf[Clases][4] +1;
                    inst_inc[3]=inst_inc[3]+1;
                }
            }
            if(predict_label==5)
            {
                if(5 == Clases)
                {
                    matrixConf[Clases][5] = matrixConf[Clases][5]+1;
                    data[4]=data[4]+1;
                }
                else{
                    matrixConf[Clases][5] = matrixConf[Clases][5] +1;
                    inst_inc[4]=inst_inc[4]+1;
                }
            }
            if(predict_label==6)
            {
                if(6 == Clases)
                {
                    matrixConf[Clases][6] = matrixConf[Clases][6]+1;
                    data[5]=data[5]+1;
                }
                else{
                    matrixConf[Clases][6] = matrixConf[Clases][6] +1;
                    inst_inc[5]=inst_inc[5]+1;
                }
            }

            for(j=0;j<nr_class;j++)
                out<<" "<<prob_estimates[j];
            out<<"\n";

        }
        else
        {
            out<<predict_label<<"\n";

        }

        if(predict_label == target_label)
            ++correct;
        error += (predict_label-target_label)*(predict_label-target_label);
        sump += predict_label;
        sumt += target_label;
        sumpp += predict_label*predict_label;
        sumtt += target_label*target_label;
        sumpt += predict_label*target_label;
        ++total;

    }

    Print_Medidas(matrixConf,Inst_Correct,Inst_incorrc,correct,total,0);

    if(predict_probability)
        free(prob_estimates);
}

void msv::Print_Medidas(int matrixConf[7][7], QVector<int> Inst_Correct, QVector<int> Inst_incorrc, int correct, int total,int a){

    QDir::setCurrent("C:/Users/Paola/Documents/prueba");
    QString name;
    if(a==0){
        name = "resultados.txt";
    }else{
        if(a==1){
            name = "CrossValidation.txt";
        }
    }

    QFile result(name);
    if(!result.open(QIODevice::WriteOnly | QIODevice::Text))
        exit(1);

    QTextStream res(&result);

    int *data = Inst_Correct.data();
    int *inst_inc = Inst_incorrc.data();

    res<<"\n";
    res <<"===Información del Kernel utilizado===\n\n";
    if(parametro.kernel_type == 2){
        res<<"Kernel RBF (Función Base Radial)" << "\n";
        res <<"Parámetros: \t" << "C=" << parametro.C << "\tgamma="<< parametro.gamma<<"\n\n";
    }

    res <<"===Resumen===\n\n";

    res<<"Fototipos Clasificados Correctamente:     "<<correct<<"    "<<(double)correct/total*100<<"%"<<"\n";
    res<<"Fototipos Clasificados Incorrectamente:     "<<total-correct<<"    "<<100.0*(total-correct)/total<<"%"<<"\n";
    res<<"Numero Total de Fototipos:     "<<total<<"\n";
    float media = total/6;
    double desvEst = ( ( pow((data[0]-media),2) + pow((data[1]-media),2) + pow((data[2]-media),2) + pow((data[3]-media),2) + pow((data[4]-media),2) + pow((data[5]-media),2) ) / (correct-1) );
    desvEst = sqrt(desvEst);
    double cv = (desvEst/media)*100;
    res<<"Coeficiente de Variación:     "<< (double)cv<<"%"<<"\n\n";

    res<<"==Presicion Detallada por cada Fototipo==\n\n";

    res<<"Fototipos\tSensibilidad"<<"\tEspecificidad\t Precisión\n";
    res<<"\n";
    res<<"\t1:\t"<<(double)data[0]/7 <<"\t\t" <<(double)(7-data[0])/7<< "\t\t" << ((double)data[0]/(data[0]+inst_inc[0])) <<"\n";
    res<<"\t2:\t"<<(double)data[1]/53<<"\t\t" <<(double)(53-data[1])/53<< "\t\t" << ((double)data[1]/(data[1]+inst_inc[1])) <<"\n";
    res<<"\t3:\t"<<(double)data[2]/182<<"\t\t" <<(double)(182-data[2])/182<< "\t\t" << ((double)data[2]/(data[2]+inst_inc[2])) <<"\n";
    res<<"\t4:\t"<<(double)data[3]/254<<"\t\t" <<(double)(254-data[3])/254<< "\t\t" << ((double)data[3]/(data[3]+inst_inc[3])) <<"\n";
    res<<"\t5:\t"<<(double)data[4]/68<<"\t\t" <<(double)(68-data[4])/68<< "\t\t" << ((double)data[4]/(data[4]+inst_inc[4])) <<"\n";
    res<<"\t6:\t"<<(double)data[5]/23<<"\t\t" <<(double)(23-data[5])/23<< "\t\t" << ((double)data[5]/(data[5]+inst_inc[5])) <<"\n";

    res<<"\n \n";
    res<<"===Matriz de Confusión===";
    res<<"\n \n";

    res<<"1   "<<"2   "<<"3   "<<"4   "<<"5   "<<"6   "<<"<--- Clasificados";
    res<<"\n";
    for (int j=1; j<=6; j++){
      for (int i=1; i<=6; i++){
        if(matrixConf[j][i]<10){
              res<<matrixConf[j][i]<<"   ";
        }else{
            if(matrixConf[j][i]<100){
                res<<matrixConf[j][i]<<"  ";
            }else{
                if(matrixConf[j][i]>100){
                    res<<matrixConf[j][i]<<" ";
                }
            }
        }
      }
      res<<"| "<<  j <<" = Fototipo "<<j;
      res<<" \n";
    }
    res<<"\n";


}

/*Extre los 587 datos del Archivo .xlsx y los alamcena en una matriz
Para posteriormente ser procesador para la discretizacion*/
void msv::ExtraccionDatos(){

    //QDir::setCurrent("C:/Users/Paola/Documents/prueba");
    //QDir::currentPath();
    int row=1, col=1;

    //QXlsx::Document *docIN= new QXlsx::Document("DatosPrueba.xlsx");
    QXlsx::Document *docIN= new QXlsx::Document(":/clasificador/DatosPrueba.xlsx");
    nColum=docIN->dimension().lastColumn();
    nFilas=docIN->dimension().lastRow();
    double matrix[nFilas+1][nColum];

    for(col=0;col<nColum+1;col++){
        dataD[col][0]=col+1;
    }

    for(col=1;col<=nColum;col++){
        for(row=1;row<=nFilas;row++){
            QVariant v;
            v.setValue(docIN->read(row,col));
            double val = v.toFloat();
            matrix[row][col] = val;
            dataD[col-1][row]=matrix[row][col];
        }
    }
}

void msv::Discretizacion(double dataD[colum+1][fil]){

    double globalcaim,caim,v;
    double candidatecutpoint[N],cutpoint[N],temp,tempdataD[N][A+2];
    int i,j,l,n,ll,x,y,k,b,c,w;
    int cai[N];
    double caivalue[N];

    for(i=0;i<N;i++)
    {
        for(j=0;j<A+2;j++)
            tempdataD[i][j]=dataD[i][j];
    }

    for(k=1;k<N;k++)
    {
        cai[k]=0;
        caivalue[k]=0;
    }
    candidatecutpoint[0]=-100000;
    cutpoint[0]=-100000;
    cutpoint[1]=100000;

    for(i=1;i<=A;i++)
    {
      w=1;
      globalcaim=0.0;
      caim=0.0;
      sort(i);
      cutpoint[0]=-100000;
      cutpoint[1]=100000;
      temp=dataD[0][i];
      j=1;
      l=1;
      while(j<N)
      {
         if(temp==dataD[j][i])
             j++;
         else
         {
             candidatecutpoint[l]=(double)((temp+dataD[j][i])/2);
             temp=dataD[j][i];
             l++;
         }
      }
      candidatecutpoint[l]=100000;
      ll=1;
      for(n=2;n<=l;n++)
      {
            x=0;
            for(j=1;j<l;j++)
            {
                caim=CAIM(i,n,candidatecutpoint[j],cutpoint,candidatecutpoint,l);
                findsort(cai,caivalue,j,caim);
                 if((caim>globalcaim))
                {
                     globalcaim=caim;
                     y=j;
                     x=1;
                }
            }
            if((x==0)&&(n<=S))
            {
                globalcaim=caivalue[1];
                y=cai[1];
                x=1;

            }
            cutpoint[ll]=candidatecutpoint[y];
            cutpoint[ll+1]=100000;
            ll++;
            if(x==0)
            {
               cutpoint[ll-1]=100000;
               ll--;
               break;
            }
            for(b=1;b<ll-1;b++)
            {
                for(c=b+1;c<ll;c++)
                {
                    if(cutpoint[b]>cutpoint[c])
                    {
                        v=cutpoint[b];
                        cutpoint[b]=cutpoint[c];
                        cutpoint[c]=v;
                    }
                }
            }
      }
      replace(i,cutpoint,ll);
      if(inconsistency()>0)
      {

          do{
              sort(0);
              for(k=0;k<N;k++)
                  dataD[k][i]=tempdataD[k][i];
              sort(i);

              {
                  cutpoint[ll]=candidatecutpoint[cai[w]];
                  cutpoint[ll+1]=100000;
              }
              ll++;
              w++;

              replace(i,cutpoint,ll);
          }while(inconsistency()>0);
      }

   }
    sort(0);
    out();
}

void msv::sort(int n){

    int i=0,j=0,k=0;
    double a;


    k=0;
    for(i=0;i<A+2;i++)
    {
        if(n!=i) k++;
        else break;
    }
    if(k==(A+2))
    {
      exit(0);
    }

    for(i=0;i<N;i++)
    {
        j=i;
        k=i;
        while(j<N)
        {
            if(dataD[j][n]<dataD[k][n])
            {
                k=j;
            }
            j++;
        }
        for(j=0;j<A+2;j++)
        {
            a=dataD[i][j];
            dataD[i][j]=dataD[k][j];
            dataD[k][j]=a;
        }

    }

}

void msv::out(){

    QDir::setCurrent(QDir::homePath() + "/" + QStandardPaths::displayName( QStandardPaths::DesktopLocation ) + "/" + "prueba");
    QDir::currentPath();

    QFile file("DatosEspectrales");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        exit(1);
    QTextStream salida(&file);

    /***/
    QFile inp("muestra");
    if (!inp.open(QIODevice::WriteOnly | QIODevice::Text))
        exit(1);
    QTextStream valores(&inp);
    /***/

    int i,j;
    for(i=0;i<N;i++)
    {
        for(j=0;j<A+2;j++)
        {

            if(j==0){
                salida<<dataD[i][A+1]<<" ";
                if(i==N-1){
                    valores<<dataD[i][A+1]<<" ";
                }

            }else{
                if(j==A+1){
                    salida<<"";
                }else{
                salida<<j<<":"<<dataD[i][j]<<" ";
                if(i==N-1){
                    valores<<j<<":"<<dataD[i][j]<<" ";
                    }
                }

            }
        }

        salida<<"\n";

    }
    file.close();
    valores<<"\n";
    for(i=0;i<N;i++)
    {
        for(j=0;j<A+2;j++)
        {
            if(j==0){
                if(i==N-1){
                    valores<<dataD[i][A+1]<<" ";
                }
            }else{
                if(j==A+1){
                    /**/
                }else{
                    /**/
                if(i==N-1){
                    valores<<j<<":"<<dataD[i][j]<<" ";
                }
                }
            }
        }
     }
    valores<<"\n";
    inp.close();
}

double msv::inconsistency(){

    int a[N];
    int i=0,j=0,n=0,k=0,num=0;
    for(i=0;i<N;i++)
        a[i]=0;
    for(i=0;i<(N-1);i++)
    {
        j=i+1;
        while(j<N)
        {
            n=0;
            for(k=1;k<=A;k++)
            {
                if(dataD[i][k]==dataD[j][k]) n++;
                else break;
            }
            if((n==A)&&(dataD[i][A+1]!=dataD[j][A+1]))
            {
                a[i]=1;
                a[j]=1;
            }
            j++;
        }
    }
    num=0;
    for(i=0;i<N;i++)
    {
        if(a[i]==1) num++;
    }
    return((double)num/N);
}

/* Funcion CAIM, arma la "Quanda Matrix" y retorna el Valor CAIM*/
double msv::CAIM(int i,int n,double selectvalue,double point[N],double canpoint[N],int l){

    int r,m,cc,j,M[N+1],q[N+1][S+1],C[S+1],upper[S+1],a[N+1],qq[N+1],aa;
      double t=0.0,caim=0.0;
      int flag=0;
      a[0]=0;

      sort(i);
      for(r=1;r<=n;r++)
      { M[r]=0;
        qq[r]=0;
        a[r]=0;
      }
      for(cc=1;cc<=S;cc++)
      { upper[cc]=0;
        C[cc]=0;
      }
      for(r=1;r<=n;r++)
      {for(cc=1;cc<=S;cc++)
       q[r][cc]=0;}

        for(j=1;j<n;j++)
        if(selectvalue==point[j])
          flag=1;
        if(flag==0)
        {
            for(j=1;j<n;j++)
            {
                aa=n-1;
                if(selectvalue>point[j-1]&&selectvalue<point[j])
                {
                    aa=j; break;
                }
            }

      if(aa==1)
      { r=1; m=0;
        while((m<N)&&dataD[m][i]>point[r-1]&&dataD[m][i]<selectvalue)
        { M[r]++;
            for(cc=1;cc<=S;cc++)
            {

              if(dataD[m][A+1]==cc)
              q[r][cc]++;
            }
          m++;
        }

        a[r]=m;
        r++;
        while((m<N)&&dataD[m][i]>selectvalue&&dataD[m][i]<point[r-1])
        { M[r]++;
          for(cc=1;cc<=S;cc++)
              if(dataD[m][A+1]==cc)
                  q[r][cc]++;
          m++;
        }
        a[r]=m;

        for(r=aa+2;r<=n;r++)
        { while((m<N)&&dataD[m][i]>point[r-2]&&dataD[m][i]<point[r-1])
          { M[r]++;
            for(cc=1;cc<=S;cc++)
              if(dataD[m][A+1]==cc)
                  q[r][cc]++;
            m++;
          }
          a[r]=m;
        }
      }
      if(aa!=1&&aa!=n-1)
      { m=0;
        for(r=1;r<aa;r++)
        { while(dataD[m][i]>point[r-1]&&dataD[m][i]<point[r])
          { M[r]++;
            for(cc=1;cc<=S;cc++)
              if(dataD[m][A+1]==cc)
                  q[r][cc]++;
            m++;
          }
          a[r]=m;
        }
        while(dataD[m][i]>point[r-1]&&dataD[m][i]<selectvalue)
        { M[r]++;
          for(cc=1;cc<=S;cc++)
            if(dataD[m][A+1]==cc)
                q[r][cc]++;
          m++;
        }
        a[r]=m;
        r++;
        while(dataD[m][i]>selectvalue&&dataD[m][i]<point[r-1])
        { M[r]++;
          for(cc=1;cc<=S;cc++)
            if(dataD[m][A+1]==cc)
                q[r][cc]++;
          m++;
        }
        a[r]=m;
        for(r=aa+2;r<=n;r++)
        { while((m<N)&&(dataD[m][i]>point[r-2])&&(dataD[m][i]<point[r-1]))
          { M[r]++;
            for(cc=1;cc<=S;cc++)
              if(dataD[m][A+1]==cc)
                  q[r][cc]++;
            m++;
          }
          a[r]=m;
        }
      }
      if(aa==n-1&&n>2)
      { m=0;
        for(r=1;r<aa;r++)
        { while(dataD[m][i]>point[r-1]&&dataD[m][i]<point[r])
          { M[r]++;
            for(cc=1;cc<=S;cc++)
              if(dataD[m][A+1]==cc)
                  q[r][cc]++;
            m++;
          }
          a[r]=m;
        }
        while(dataD[m][i]>point[r-1]&&dataD[m][i]<selectvalue)
        { M[r]++;
          for(cc=1;cc<=S;cc++)
            if(dataD[m][A+1]==cc)
                q[r][cc]++;
          m++;
        }
        a[r]=m;
        r++;
        while((m<N)&&dataD[m][i]>selectvalue&&dataD[m][i]<point[r-1])
        { M[r]++;
          for(cc=1;cc<=S;cc++)
            if(dataD[m][A+1]==cc)
                q[r][cc]++;
          m++;
        }
        a[r]=m;
      }

      for(m=0;m<N;m++)
      { for(j=1;j<=S;j++)
          if(dataD[m][A+1]==j)
              C[j]++;}

      for(r=1;r<=n;r++)
      {
          for(j=1;j<=S;j++)
          {
              for(m=a[r-1];m<a[r];m++)
                  if(dataD[m][A+1]==j)
                  {
                      upper[j]+=M[r];
                      break;
                  }
          }
      }

      for(r=1;r<=n;r++)
      {
          for(j=1;j<=S;j++)
          {
              if(q[r][j]>qq[r])
                  qq[r]=q[r][j];
          }
      }
      for(r=1;r<=n;r++)
          t+=(((double)qq[r])*((double)qq[r]))/M[r];
      caim=(double)t/(double)n;
      }
      else
      {caim=-100;}
      return(caim);
}


void msv::findsort(int cai[N],double caivalue[N],int j,double caim){

    int m,k;
    for(m=j-1;m>0;m--)
    {
        if((caim<caivalue[m])||(caim==caivalue[m]))
            break;
    }
    for(k=j;k>m+1;k--)
    {
        cai[k]=cai[k-1];
        caivalue[k]=caivalue[k-1];
    }
    cai[m+1]=j;
    caivalue[m+1]=caim;
}

void msv::replace(int i,double cutpoint[N],int ll){

    sort(i);
    int j,m,p,q;
    double z,plus=1.0;
    for(p=1;p<ll-1;p++)
    {    for(q=p+1;q<ll;q++)
        {
            if(cutpoint[p]>cutpoint[q])
            {
                z=cutpoint[p];
                cutpoint[p]=cutpoint[q];
                cutpoint[q]=z;
            }
        }
    }

    m=0;
    for(j=1;j<=ll;j++)
    {  while((m<N)&&dataD[m][i]>cutpoint[j-1]&&dataD[m][i]<cutpoint[j])
    {
       dataD[m][i]=plus;
       m++;
       }
       plus++;
    }


}

void msv::read_problem(QFile *Datos){

    int max_index, inst_max_index, i;
    size_t elements, j;
    char *endptr;
    char *idx, *val, *label;

    if (Datos->open(QIODevice::ReadOnly | QIODevice::Text)){
        exit(1);
    }

    prob.l = 0;
    elements = 0;

    max_line_len = 1024;
    line = Malloc(char,max_line_len);

    while (readline(Datos)!=NULL && !Datos->atEnd()) {

       char *p = strtok(line," \t"); // label
       while (1) {
           p = strtok(NULL," \t");
           if(p == NULL || *p == '\n'){break;}
           ++elements;
       }
       ++elements;
       ++prob.l;
    }

    Datos->close();
    Datos->open(QIODevice::ReadOnly | QIODevice::Text);

    prob.y = Malloc(double,prob.l);
    prob.x = Malloc(struct svm_node *,prob.l);
    x_space = Malloc(struct svm_node,elements);

    max_index = 0;
    j=0;

    for(i=0;i<prob.l;i++)
    {
        inst_max_index = -1; // strtol gives 0 if wrong format, and precomputed kernel has <index> start from 0
        readline(Datos);
        prob.x[i] = &x_space[j];
        label = strtok(line," \t\n");
        if(label == NULL) // empty line
            exit_input_error(i+1);

        prob.y[i] = strtod(label,&endptr);
        if(endptr == label || *endptr != '\0')
            exit_input_error(i+1);

        while(1)
        {
            idx = strtok(NULL,":");
            val = strtok(NULL," \t");

            if(val == NULL)
                break;

            errno = 0;
            x_space[j].index = (int) strtol(idx,&endptr,10);
            if(endptr == idx || errno != 0 || *endptr != '\0' || x_space[j].index <= inst_max_index)
                exit_input_error(i+1);
            else
                inst_max_index = x_space[j].index;

            errno = 0;
            x_space[j].value = strtod(val,&endptr);
            if(endptr == val || errno != 0 || (*endptr != '\0' && !isspace(*endptr)))
                exit_input_error(i+1);

            ++j;
        }

        if(inst_max_index > max_index)
            max_index = inst_max_index;
        x_space[j++].index = -1;
    }
    Datos->close();

}

float msv::do_cross_validation(){

    /*Para medidas de Evaluacion*/
    int matrixConf[7][7]; //Matriz de Confusion
    QVector<int> Inst_Correct; //Vector de instancias Correctas
    Inst_Correct<<0<<0<<0<<0<<0<<0;
    int *data = Inst_Correct.data();
    QVector<int> Inst_incorrc;
    Inst_incorrc<<0<<0<<0<<0<<0<<0;//Vector de instancias Incorrectas
    int *inst_inc = Inst_incorrc.data();

    int i;
    int total_correct=0;
    double *target = Malloc(double, prob.l);
    float acc;

    svm_cross_validation(&prob,&parametro,nr_fold,target);

    for (int j=1; j<=6; j++){
      for (int i=1; i<=6; i++)
        matrixConf[i][j]=0;
    }

        for(i=0;i<prob.l;i++){
            if(target[i] == prob.y[i])
                ++total_correct;
            qDebug()<<target[i]<<" "<<prob.y[i];

                if(target[i] == 1)
                {
                    int Clases = prob.y[i];
                    if(1 == prob.y[i])
                    {
                        matrixConf[Clases][1] = matrixConf[Clases][1]+1;
                        data[0]=data[0]+1;
                    }
                    else{
                        matrixConf[Clases][1] = matrixConf[Clases][1] +1;
                        inst_inc[0]=inst_inc[0]+1;
                    }
                }

                if(target[i] == 2)
                {
                    int Clases = prob.y[i];
                    if(2 == prob.y[i]){
                        matrixConf[Clases][2] = matrixConf[Clases][2]+1;
                        data[1]=data[1]+1;
                    }
                    else{
                        matrixConf[Clases][2] = matrixConf[Clases][2] +1;
                        inst_inc[1]=inst_inc[1]+1;
                    }
                }

                if(target[i] == 3)
                {
                    int Clases = prob.y[i];
                    if(3 == prob.y[i])
                    {
                        matrixConf[Clases][3] = matrixConf[Clases][3]+1;
                        data[2]=data[2]+1;
                     }
                else{
                        matrixConf[Clases][3] = matrixConf[Clases][3] +1;
                        inst_inc[2]=inst_inc[2]+1;
                    }

                }
                if(target[i]==4)
                {
                    int Clases = prob.y[i];
                    if(4 == prob.y[i])
                    {
                        matrixConf[Clases][4] = matrixConf[Clases][4]+1;
                        data[3]=data[3]+1;
                    }
                    else{
                        matrixConf[Clases][4] = matrixConf[Clases][4] +1;
                        inst_inc[3]=inst_inc[3]+1;
                    }
                }
                if(target[i] == 5)
                {
                    int Clases = prob.y[i];
                    if(5 == prob.y[i])
                    {
                        matrixConf[Clases][5] = matrixConf[Clases][5]+1;
                        data[4]=data[4]+1;
                    }
                    else{
                        matrixConf[Clases][5] = matrixConf[Clases][5] +1;
                        inst_inc[4]=inst_inc[4]+1;
                    }
                }
                if(target[i] == 6)
                {
                    int Clases = prob.y[i]; //svm_predict(model,x);
                    if(6 == prob.y[i])
                    {
                        matrixConf[Clases][6] = matrixConf[Clases][6]+1;
                        data[5]=data[5]+1;
                    }
                    else{
                        matrixConf[Clases][6] = matrixConf[Clases][6] +1;
                        inst_inc[5]=inst_inc[5]+1;
                    }
                }

        }

        acc = 100.0*total_correct/prob.l;

        Print_Medidas(matrixConf,Inst_Correct,Inst_incorrc,total_correct,prob.l,1);

        return acc;
        free(target);
}

void msv::OptimizacionParametros(){

    QDir::setCurrent("C:/Users/Paola/Documents/prueba");
    QDir::currentPath();

    int cont=1;
    float i=0.0,j=0.0, accurracy1=0.0,accurracy=0.1, gammaOpt=0.0,cOpt=0.0,gamma,c;
    i=-5; // 2^-5 Parametro C
    j=-15;  // 2^-15 Parametro gamma
    const char *error_msg;

    while(1){

        gamma = pow(2,j);
        c = pow(2,i);

        parametro.svm_type = C_SVC;
        parametro.kernel_type = RBF;
        parametro.degree = 0;
        parametro.gamma = pow(2,-15);
        parametro.coef0 = 0;
        parametro.nu = 0.5;
        parametro.cache_size = 100.0;
        parametro.C = pow(2,-5);
        parametro.eps = 1.0e-12;
        parametro.p = 0.1;
        parametro.shrinking = 1;
        parametro.probability = 1;
        parametro.nr_weight = 0;
        parametro.weight_label = NULL;
        parametro.weight = NULL;

        error_msg = svm_check_parameter(&prob,&parametro);
        if(error_msg){
           qDebug()<<"Error";
           return;
        }

        accurracy = do_cross_validation();

        if(accurracy > accurracy1){
            accurracy1 = accurracy;
            gammaOpt = pow(2,j);
            cOpt = pow(2,i);
        }else{
            if (cont<1){
                qDebug()<<"Continua";
            }else{break;}
        }
        i=i+2;//i*0.25;
        j=j+2;//j*0.25;
        cont++;

    }

    parametro.gamma = gammaOpt;
    parametro.C = cOpt;

}

/*Procedimiento Entrada recibe un vector con los nuevos valores
 * *L, *a, *b, dichos valores son incluidos en la matriz dataD
 * para posteriormente aplicar la discretizacion.
*/
void msv::Entrada(QVector<float> Datos){

    Datos.push_back(1);
    float *data = Datos.data();
    for(int i=1;i<=nFilas;i++){
        dataD[colum][i] = data[i-1];
    }

    Discretizacion(dataD);
}

/*Procedimiento Administrados Ejecuta el entrenamiento del
 * con los datos discretizados.
*/
void msv::Administrador(){

    QDir::setCurrent("C:/Users/Paola/Documents/prueba");
    QDir::currentPath();
    QFile archivo("DatosEspectrales");

    msv_train(&archivo);
    msv_predict(&archivo);

    archivo.close();

}

/*Funcion Usuario Medico retorna el fototipo
de una muestra dada*/
int msv::UsuarioMedico(){

    qDebug() << "entra en usuariomedico";

    QDir::currentPath();
    QFile archivo(QDir::homePath() + "/" + QStandardPaths::displayName( QStandardPaths::DesktopLocation ) + "/prueba/" + "muestra");
    QFile output(QDir::homePath() + "/" + QStandardPaths::displayName( QStandardPaths::DesktopLocation ) + "/prueba/" + "output_file");
    QFile::copy(":/clasificador/out.model", QDir::homePath() + "/" + QStandardPaths::displayName( QStandardPaths::DesktopLocation ) + "/prueba/" + "out.model");
    QString modelo(QDir::homePath() + "/" + QStandardPaths::displayName( QStandardPaths::DesktopLocation ) + "/prueba/" + "out.model");

    string str = modelo.toStdString();
    strcpy(model_file_name,str.c_str());

    if(!archivo.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "se sale en 1";
        exit(1);
    }

    if(!output.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "se sale en 2";
        exit(1);
    }

    predict_probability = 1;

    if((model=svm_load_model(model_file_name))==0){
        qDebug() << "se sale en 2.5";
        exit(1);
    }

    x = (struct svm_node *) malloc(max_nr_attr*sizeof(struct svm_node));
    if(predict_probability==1)
    {

        if(svm_check_probability_model(model)==0){
            qDebug() << "se sale en 3";
            exit(1);
        }
    }
    else
    {
        if(svm_check_probability_model(model)!=0)
            qDebug()<<"Model supports probability estimates, but disabled in prediction.\n";
    }

    int fototipo = Clasificacion(&archivo);
    svm_free_and_destroy_model(&model);
    free(x);
    free(line);

    archivo.close();
    output.close();

    qDebug() << "sale de usuariomedico";

    return fototipo;
}


/*Funcion Clasificacion recibe los valores *L, *a, *b del fototipo
 * y retorna el fototipo clasificado*/
int msv::Clasificacion(QFile *input){

    int total = 0;
    int fototipo;
    int svm_type=svm_get_svm_type(model);//Obtiene el Modelo
    int nr_class=svm_get_nr_class(model);//Obtiene el numero de Clases (6 Fototipos)
    double *prob_estimates=NULL;

    if(predict_probability)
    {
            int *labels=(int *) malloc(nr_class*sizeof(int));
            svm_get_labels(model,labels);
            prob_estimates = (double *) malloc(nr_class*sizeof(double));
            free(labels);
    }
    max_line_len = 1024;
    line = (char *)malloc(max_line_len*sizeof(char));

    while(readline(input) != NULL && !input->atEnd())
    {
        int i = 0;
        double target_label, predict_label;
        char *idx, *val, *label, *endptr;
        int inst_max_index = -1; // strtol gives 0 if wrong format, and precomputed kernel has <index> start from 0

        label = strtok(line," \t\n");

        if(label == NULL) // empty line
            exit_input_error(total+1);

        target_label = strtod(label,&endptr);
        if(endptr == label || *endptr != '\0')
            exit_input_error(total+1);

        while(1)
        {
            if(i>=max_nr_attr-1)	// need one more for index = -1
            {
                max_nr_attr *= 2;
                x = (struct svm_node *) realloc(x,max_nr_attr*sizeof(struct svm_node));
            }

            idx = strtok(NULL,":");
            val = strtok(NULL," \t");


            if(val == NULL)
                break;
            errno = 0;
            x[i].index = (int) strtol(idx,&endptr,10);
            if(endptr == idx || errno != 0 || *endptr != '\0' || x[i].index <= inst_max_index)
                exit_input_error(total+1);
            else
                inst_max_index = x[i].index;

            errno = 0;
            x[i].value = strtod(val,&endptr);
            if(endptr == val || errno != 0 || (*endptr != '\0' && !isspace(*endptr)))
                exit_input_error(total+1);

            ++i;
        }

        x[i].index = -1;

        if (predict_probability && (svm_type==C_SVC || svm_type==NU_SVC))
        {
            predict_label = svm_predict_probability(model,x,prob_estimates);
            fototipo = predict_label;
        }


    }

    return fototipo;

    if(predict_probability)
        free(prob_estimates);
}

msv::~msv()
{
    free(x);
    free(line);
}

