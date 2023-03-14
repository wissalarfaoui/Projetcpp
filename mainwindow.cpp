#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include "Medicament.h"
#include <QMessageBox>
#include <QApplication>
#include <QListWidget>
 #include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->tabmedi->setModel(M.afficher());


    QListWidget* toDoListWidget = ui->list;//new QListWidget(this);
   // toDoListWidget->setGeometry(10, 10, 200, 150);


       // Créer un objet Medicament
       Medicament* medicament = new Medicament();

       // Appeler la fonction toDoList de Medicament en passant le QListWidget comme argument
       medicament->toDoList(toDoListWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
bool MainWindow::controlesaisi1()
{

    if(
            !(ui->le_nom->text().contains(QRegExp("^[A-Za-z]+$"))) ||
             ui->la_quantite->text().isEmpty()||
             ui->le_prix->text().isEmpty()||
            ui->le_ID->text().isEmpty()||
            ui->le_ID->text().toInt()==0)
        return 0;
    else return 1;
}

void MainWindow::on_ajouter_clicked()
{

    int id=ui->le_ID->text().toInt();
    QString nom=ui->le_nom->text();
    int quantite=ui->la_quantite->text().toInt();
   float prix=ui->le_prix->text().toFloat();
    Medicament M(id,nom,quantite,prix);
    bool test=controlesaisi1();
    if(test)
            test=M.ajouter();
    if (test){
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("ajout effectué \n"
                                             "click cancel to exit."), QMessageBox:: Cancel);
         ui->tabmedi->setModel(M.afficher());

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                              QObject::tr("ajout non effectué .\n"
                                         "click cancel to exit."),QMessageBox::Cancel);

}

void MainWindow::on_supprimer_clicked()
{
    Medicament M1; M1.setID(ui->le_ID_sup->text().toInt());
    bool test=M1.supprimer(M1.getID());
    QMessageBox msgBox;
    if (test)
    {

    msgBox.setText("supprimé avec succes");
      ui->tabmedi->setModel(M.afficher());
    }
    else
        msgBox.setText("Echec de suppression");
    msgBox.exec();

}

bool MainWindow::controlesaisi()
{

    if(
            !(ui->le_nom_2->text().contains(QRegExp("^[A-Za-z]+$"))) ||
             ui->la_quantite_2->text().isEmpty()||
             ui->le_prix_2->text().isEmpty()||
            ui->le_ID_2->text().isEmpty()||
            ui->le_ID_2->text().toInt()==0)
        return 0;
    else return 1;
}

void MainWindow::on_modifier_clicked()
{

    bool test;bool trouver;

        int id=ui->le_ID_2->text().toInt();
        QString nom=ui->le_nom_2->text();
        int quantite=ui->la_quantite_2->text().toInt();
 float prix=ui->le_prix_2->text().toFloat();


        Medicament M(id,nom,quantite,prix);
        QMessageBox msg;
       test=controlesaisi();
        if(test)
        test=M.modifier(id);

        trouver=M.verification_id(id);
        if(!trouver)
        {
            test=false;
            msg.setText("id n'existe pas");
            msg.exec();
         }

        if(test)
        {
          msg.setText("modification avec succes!!");

          ui->tabmedi->setModel(M.afficher());

  ui->le_ID_2->clear();
          ui->le_nom_2->clear();
                  ui->la_quantite_2->clear();
ui->le_prix_2->clear();
         }
        else

        msg.setText("echec de modification");
         msg.exec();


}

void MainWindow::on_tabmedi_activated(const QModelIndex &index)
{

    QString val=ui->tabmedi->model()->data(index).toString();
        QSqlQuery qry;
        qry.prepare("select * from MEDICAMENT where ID='"+val+"'");
        //qry.prepare("select * from MEDICAMENT where NOM='"+val+"'");
       if (qry.exec())
       {
           while(qry.next())
           {
              ui->le_ID_2->setText(qry.value(0).toString());
              if (ui->tabWidget->count() > 1) {
                            ui->tabWidget->setCurrentIndex( (ui->tabWidget->currentIndex()+1) % ui->tabWidget->count() );

}

ui->le_ID_sup->setText(qry.value(0).toString());


           }
       }
       else
       {
           QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                   QObject::tr("Echec"),
                   QMessageBox::Cancel);
       }
}






/*void MainWindow::on_selectMedicament_clicked()
{

    if (ui->tabWidget->count() > 1) {
              ui->tabWidget->setCurrentIndex( (ui->tabWidget->currentIndex()+2) % ui->tabWidget->count() );
           }
}*/





void MainWindow::on_add_clicked()
{
    Medicament med;
    QListWidget* toDoListWidget = new QListWidget(this);
    toDoListWidget->setGeometry(10, 10, 200, 150);
    med.toDoList(toDoListWidget); // pass the toDoListWidget object to the function
}



void MainWindow::on_trier_clicked()
{

    //Medicament M;
   // ui->tabmedi->setModel(M.trie_prix());

    QSqlQueryModel *sortedModel = M.trie_prix();
      ui->tabmedi->setModel(nullptr);
    ui->tabmedi->setModel(sortedModel);
    ui->tabmedi->resizeColumnsToContents();
}

void MainWindow::on_trier_2_clicked()
{
    QSqlQueryModel *sortedModel = M.trie_ID();
      ui->tabmedi->setModel(nullptr);
    ui->tabmedi->setModel(sortedModel);
    ui->tabmedi->resizeColumnsToContents();
}
