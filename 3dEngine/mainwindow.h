#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Light.h"

#include <QtWidgets>

#include <QtCore>
#include <QtGui>

#include "Render.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    explicit MainWindow(vector <Light*>* lights, Render *r, QWidget *parent = 0);
    
    ~MainWindow();
    
    private slots:
    void on_btnAddLight_clicked();
    
    void on_btnDeleteLight_clicked();
    
    void on_chooseLight_objectNameChanged(const QString &objectName);
    void rowChangedSlot( const QItemSelection& selected, const QItemSelection& deselect);
    
    void on_btnOpenDiffColor_clicked();
    
    void on_btnOpenSpecColor_clicked();
    
    void on_btnOpenAmbColor_clicked();
    
    void on_comboBox_currentIndexChanged(int index);
        
    void diffColorChoosen (const QColor & color);
    void specColorChoosen (const QColor & color);
    void ambColorChoosen (const QColor & color);
    void confirm ();
private:
     QColor diffColor;
     QColor specColor;
     QColor ambColor;
    Ui::MainWindow *ui;
    QStringListModel *model;
    vector <Light*>* lights;
    Render *r;
    QItemSelectionModel *selectionModel;
    QColorDialog * qCDialogDiff;
    QColorDialog * qCDialogSpec;
    QColorDialog * qCDialogAmb;
};

#endif // MAINWINDOW_H
