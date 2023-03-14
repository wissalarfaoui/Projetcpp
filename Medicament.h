#ifndef MEDICAMENT_H
#define MEDICAMENT_H
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QListWidget>

class Medicament
{
private:
 QString nom;
  int id,quantite;
float prix;
public:
  //constructeurs
   Medicament(){};
  Medicament(int,QString,int, float);
  //getters
  QString getNom(){return nom;}
  int getQuantite(){return quantite;}
   float getPrix(){return prix;}
  int getID (){return id;}
  //setters
  void setNom(QString n){nom=n;}
   void setQuantite(int q){this ->quantite=q;}
   void setID(int id){this ->id=id;}
    void setPrix(float prix){this ->prix=prix;}
//fonctionnalités de base relatives a l entite medicaments
   bool ajouter();
   QSqlQueryModel * afficher ();
   bool supprimer (int);
   bool modifier(int );

   bool verification_id(int);

   void toDoList(QListWidget* toDoListWidget);
   QSqlQueryModel* trie_prix();
     QSqlQueryModel* trie_ID();

 void send_sms(const QString& api_key, const QString& api_secret, const QString& from_number, const QString& to_number, const QString& message);

};
#endif // MEDICAMENT_H
