#include "Medicament.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QListWidget>
#include <QInputDialog>
 #include <QMessageBox>
//#include <Nexmo.hpp>
//#include <NexmoMessage.hpp>
Medicament::Medicament(int id,QString nom, int quantite, float prix)
{
   this->id=id;
   this->nom=nom;
   this->quantite=quantite;
    this->prix=prix;
}

bool Medicament::ajouter()
{
    QSqlQuery query;
  QString res= QString::number(id);
QString res1= QString::number(quantite);
QString res2= QString::number(prix);
      query.prepare("INSERT INTO MEDICAMENT(id, nom, quantite, prix) ""VALUES (:id, :nom, :quantite, :prix)");
             query.bindValue(":id",res);
             query.bindValue(":nom",nom);
             query.bindValue(":quantite", res1);
             query.bindValue(":prix", res2);
    return query.exec();
}
QSqlQueryModel * Medicament ::afficher()
{
   QSqlQueryModel* model=new QSqlQueryModel();
   model->setQuery("SELECT* FROM MEDICAMENT ");
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("quantite"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("prix"));

  return model;
}
bool Medicament ::supprimer(int id)
{
   QSqlQuery query;
   QString res=QString::number(id);
   query.prepare("Delete from MEDICAMENT where id= :id");
   query.bindValue(":id",res);
   return query.exec();
}


bool Medicament::verification_id(int id)
{
QSqlQuery query;
QString n;
QString numid = QString::number (id);
query.exec ("SELECT ID from MEDICAMENT");
while (query.next())
{
n=query.value ("ID").toString();
if (n==numid)
{
return true;
}
}
return false;
}

bool Medicament::modifier(int id)
 {
     QString res=QString::number(id);
QString des=QString::number(quantite);
QString aes=QString::number(prix);
     QSqlQuery query;
           query.prepare("UPDATE MEDICAMENT SET nom=:nom, quantite=:quantite, prix=:prix WHERE id=:id");
           query.bindValue(":id",res);
           query.bindValue(":nom",nom);
           query.bindValue(":quantite", des);
           query.bindValue(":prix", aes);

     if(id !=0  || nom!="" ||  quantite!=0 ||  prix!=0)
          return query.exec();
     return 0;

 }





void Medicament::toDoList(QListWidget* toDoListWidget) {
    bool ok;
    while (true) {
        QString choix = QInputDialog::getText(nullptr, ("Que voulez-vous faire ?"),
                                                ("1. Ajouter une tâche\n"
                                                   "2. Voir les tâches à faire\n"
                                                   "3. Marquer une tâche comme terminée\n"
                                                   "4. Quitter"),
                                                QLineEdit::Normal, QString(), &ok);
        if (ok && !choix.isEmpty()) {
            if (choix == "1") {
                QString nouvelleTache = QInputDialog::getText(nullptr, ("Nouvelle tâche"),
                                                               ("Entrez une nouvelle tâche : "));
                toDoListWidget->addItem(nouvelleTache);
                QMessageBox::information(nullptr, ("Tâche ajoutée avec succès !"),
                                            ("La tâche a été ajoutée avec succès."));
            } else if (choix == "2") {
                if (toDoListWidget->count() == 0) {
                    QMessageBox::information(nullptr, ("Aucune tâche à faire."),
                                                ("Il n'y a aucune tâche à faire pour le moment."));
                } else {
                    QString taches = ("Tâches à faire : \n");
                    for (int i = 0; i < toDoListWidget->count(); i++) {
                        taches += QString::number(i+1) + ". " + toDoListWidget->item(i)->text() + "\n";
                    }
                    QMessageBox::information(nullptr, ("Tâches à faire."),
                                                taches);
                }
            } else if (choix == "3") {
                if (toDoListWidget->count() == 0) {
                    QMessageBox::information(nullptr, ("Aucune tâche à faire."),
                                                ("Il n'y a aucune tâche à faire pour le moment."));
                } else {
                    QString taches = ("Tâches à faire : \n");
                    for (int i = 0; i < toDoListWidget->count(); i++) {
                        taches += QString::number(i+1) + ". " + toDoListWidget->item(i)->text() + "\n";
                    }
                    QString numTache = QInputDialog::getText(nullptr, ("Tâche terminée"),
                                                               taches + ("Entrez le numéro de la tâche terminée : "));
                    bool ok;
                    int num = numTache.toInt(&ok);
                    if (ok && num > 0 && num <= toDoListWidget->count()) {
                        delete toDoListWidget->takeItem(num - 1);
                        QMessageBox::information(nullptr, ("Tâche terminée avec succès !"),
                                                    ("La tâche a été marquée comme terminée avec succès."));
                    } else if (ok && (num <= 0 || num > toDoListWidget->count())) {
                        QMessageBox::information(nullptr, ("Numéro de tâche invalide."),
                                                    ("Le numéro de tâche entré est invalide."));
                    }
                }
            } else if (choix == "4") {
                break;
            }
        }
    }
}


QSqlQueryModel* Medicament ::trie_prix()
{
  QSqlQueryModel *model=new QSqlQueryModel();
 model->setQuery("SELECT * FROM MEDICAMENT ORDER BY PRIX " );
 model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
 model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
 model->setHeaderData(2,Qt::Horizontal,QObject::tr("quantite"));
 model->setHeaderData(3,Qt::Horizontal,QObject::tr("prix"));

  return  model;

}
QSqlQueryModel* Medicament ::trie_ID()
{
  QSqlQueryModel *model=new QSqlQueryModel();
 model->setQuery("SELECT * FROM MEDICAMENT ORDER BY ID " );
 model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
 model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
 model->setHeaderData(2,Qt::Horizontal,QObject::tr("quantite"));
 model->setHeaderData(3,Qt::Horizontal,QObject::tr("prix"));

  return  model;

}


/*void Medicament::send_sms(const QString& api_key, const QString& api_secret, const QString& from_number, const QString& to_number, const QString& message)
{
    // Convert QStrings to standard C++ strings
    std::string api_key_str = api_key.toStdString();
    std::string api_secret_str = api_secret.toStdString();
    std::string from_number_str = from_number.toStdString();
    std::string to_number_str = to_number.toStdString();
    std::string message_str = message.toStdString();

    // Create a Nexmo client object
    nexmo::client client(api_key_str, api_secret_str);

    // Create a Nexmo message object and set the properties
    nexmo::message msg;
    msg.to = to_number_str;
    msg.from = from_number_str;
    msg.text = message_str;

    // Send the message
    nexmo::response res = client.send_message(msg);

    // Check if the message was sent successfully
    if (res.status == nexmo::response::status_type::success) {
        qDebug() << "SMS sent successfully: " << res.message_id.c_str();
    } else {
        qDebug() << "Failed to send SMS: " << res.error_message.c_str();
    }
}*/
