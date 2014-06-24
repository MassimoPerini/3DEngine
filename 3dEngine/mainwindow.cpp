#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <iostream>

#include "Render.h"

#include <QtWidgets/QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    model=new QStringListModel (this);
    
    QStringList list;
    
 //   list<<"a"<<"b"<<"c";
    
    model->setStringList(list);
    
    ui->listView->setModel(model);
    
    ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked);
    
}

MainWindow::MainWindow(vector <Light*>* lights, Render *r, QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow)
{
    this->r=r;
    
    ui->setupUi(this);
    
    model=new QStringListModel (this);
    
    QStringList list;
    this->lights=lights;
    
    for (unsigned int i=0;i<this->lights->size();i++)
    {
        QString name=QString::fromStdString(((*this->lights)[i]->getName()));
        list<<name;
    }
    
    model->setStringList(list);
    
    ui->listView->setModel(model);
    
    ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked);
    
    selectionModel = ui->listView->selectionModel();
    
    connect(selectionModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(rowChangedSlot(QItemSelection, QItemSelection)));
    
    
    
    qCDialogDiff=new QColorDialog(this);
    qCDialogSpec=new QColorDialog(this);
    qCDialogAmb=new QColorDialog(this);
    
    qCDialogDiff->setWindowTitle("Diffuse color");
    qCDialogSpec->setWindowTitle("Specular color");
    qCDialogAmb->setWindowTitle("Ambient color");
    
    
    
    connect(qCDialogDiff, SIGNAL(colorSelected(QColor)), this, SLOT (diffColorChoosen(QColor)));
    connect(qCDialogSpec, SIGNAL(colorSelected(QColor)), this, SLOT (specColorChoosen(QColor)));
    connect(qCDialogAmb, SIGNAL(colorSelected(QColor)), this, SLOT (ambColorChoosen(QColor)));


}

void MainWindow::diffColorChoosen (const QColor & color)
{
    if (qCDialogDiff->isHidden())       //Fix OSX problem (qt bug? colorSelected == currentColorChanged ?)
    {
        QString str="";
        diffColor=color;
        str.append(QString("%1,").arg(color.red()));
        str.append(QString("%1,").arg(color.green()));
        str.append(QString("%1").arg(color.blue()));

        ui->pushButton_4->setText(str);
    }
}

void MainWindow::specColorChoosen (const QColor & color)
{
    if (qCDialogSpec->isHidden())       //Fix OSX problem (qt bug? colorSelected == currentColorChanged ?)
    {
        QString str="";
        specColor=color;
        str.append(QString("%1,").arg(color.red()));
        str.append(QString("%1,").arg(color.green()));
        str.append(QString("%1").arg(color.blue()));
        
        ui->pushButton_5->setText(str);
    }
}

void MainWindow::ambColorChoosen (const QColor & color)
{
    if (qCDialogAmb->isHidden())       //Fix OSX problem (qt bug? colorSelected == currentColorChanged ?)
    {
        QString str="";
        ambColor=color;
        str.append(QString("%1,").arg(color.red()));
        str.append(QString("%1,").arg(color.green()));
        str.append(QString("%1").arg(color.blue()));
        
        ui->pushButton_6->setText(str);
    }
}
            
void MainWindow::rowChangedSlot( const QItemSelection& selected, const QItemSelection& deselect ) {
    cout<<"cambiato";
    QLocale italy(QLocale::Italian, QLocale::Italy);

    //save old values (if exists!)
    if (deselect.indexes().length()>=1){
        int oldRowIndex=deselect.indexes()[0].row();
        Light *oldL=(*lights)[oldRowIndex];
        oldL->setPosition(italy.toFloat(ui->lineEdit->text()),  italy.toFloat(ui->lineEdit_2->text()),  italy.toFloat(ui->lineEdit_3->text()), 1);
        oldL->setDiffuse(((GLfloat)diffColor.red()/(GLfloat)255), ((GLfloat)diffColor.green()/(GLfloat)255), ((GLfloat)diffColor.blue()/(GLfloat)255), 0);
        oldL->setSpecular(((GLfloat)specColor.red()/(GLfloat)255), ((GLfloat)specColor.green()/(GLfloat)255), ((GLfloat)specColor.blue()/(GLfloat)255), 0);
        oldL->setAmbient(((GLfloat)ambColor.red()/(GLfloat)255), ((GLfloat)ambColor.green()/(GLfloat)255), ((GLfloat)ambColor.blue()/(GLfloat)255), 0);
    }
    
    //load new values
    
    if (selected.indexes().length()>=1){
    int newRowIndex=selected.indexes()[0].row();
    Light *l=(*lights)[newRowIndex];
    
    float *pos=l->getPosition();
    
    QString posX = italy.toString(pos[0], 'f');
    QString posY = italy.toString(pos[1], 'f');
    QString posZ = italy.toString(pos[2], 'f');

    ui->lineEdit->setText(posX);
    ui->lineEdit_2->setText(posY);
    ui->lineEdit_3->setText(posZ);
    
        //Carica colori
    float *cDiffuse=l->getDiffuse();
    float *cSpec=l->getSpecular();
    float *cAmb=l->getAmbient();
    
    QColor diffColor ((int)((cDiffuse[0])*255), (int)((cDiffuse[1])*255), (int)((cDiffuse[2])*255),0);
    QColor specColor ((int)((cSpec[0])*255), (int)((cSpec[1])*255), (int)((cSpec[2])*255),0);
    QColor ambColor ((int)((cAmb[0])*255), (int)((cAmb[1])*255), (int)((cAmb[2])*255),0);
    
        this->diffColor=diffColor;
        this->specColor=specColor;
        this->ambColor=ambColor;
        
        
    qCDialogAmb->setCurrentColor(ambColor);
    qCDialogSpec->setCurrentColor(specColor);
    qCDialogDiff->setCurrentColor(diffColor);
    
    
 //   ui->doubleSpinBox->setValue(cDiffuse[3]*100);
 //   ui->doubleSpinBox_2->setValue(cSpec[3]*100);
 //   ui->doubleSpinBox_3->setValue(cAmb[3]*100);
    }
#pragma mark delete after debug
    r->render();
    cout<<"rowChangedSlot";
}

/*void MainWindow::on_chooseLight_objectNameChanged(const QString &objectName=NULL)
{
    cout<<"b";
}*/

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnAddLight_clicked()
{
    Light *l=new Light("");
    
    int row=model->rowCount();
    
    this->lights->insert(lights->begin()+row, l);

    model->insertRows(row, 1);              //where, how much
    
    QModelIndex index = model->index(row);
    
    ui->listView->setCurrentIndex(index);
    ui->listView->edit(index);
    
    r->render();
}



void MainWindow::on_btnDeleteLight_clicked()
{
    int row=ui->listView->currentIndex().row();
    
    delete (*lights)[row];
    
    this->lights->erase(this->lights->begin()+row);
    
    model->removeRows(row, 1);
    r->render();
}

void MainWindow::on_btnOpenDiffColor_clicked()
{
    qCDialogDiff->show();
}

void MainWindow::on_btnOpenSpecColor_clicked()
{
    qCDialogSpec->show();

}

void MainWindow::on_btnOpenAmbColor_clicked()
{
    qCDialogAmb->show();
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    std::cout<<"z";
}

void MainWindow::confirm()
{
    QLocale italy(QLocale::Italian, QLocale::Italy);
    //save old values (if exists!)
    int rowIndex=selectionModel->currentIndex().row();
    cout<<rowIndex;
    if (rowIndex>=0)
    {
        Light *oldL=(*lights)[rowIndex];
        oldL->setPosition(italy.toFloat(ui->lineEdit->text()),  italy.toFloat(ui->lineEdit_2->text()),  italy.toFloat(ui->lineEdit_3->text()), 1);
        oldL->setDiffuse(((GLfloat)diffColor.red()/(GLfloat)255), ((GLfloat)diffColor.green()/(GLfloat)255), ((GLfloat)diffColor.blue()/(GLfloat)255), 0);
        oldL->setSpecular(((GLfloat)specColor.red()/(GLfloat)255), ((GLfloat)specColor.green()/(GLfloat)255), ((GLfloat)specColor.blue()/(GLfloat)255), 0);
        oldL->setAmbient(((GLfloat)ambColor.red()/(GLfloat)255), ((GLfloat)ambColor.green()/(GLfloat)255), ((GLfloat)ambColor.blue()/(GLfloat)255), 0);
        r->render();
    }
    
    
    
}

