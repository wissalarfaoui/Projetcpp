#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include"Medicament.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool controlesaisi();
    bool controlesaisi1();



private slots:
    void on_ajouter_clicked();

    void on_supprimer_clicked();

    void on_modifier_clicked();

    void on_tabmedi_activated(const QModelIndex &index);

    void on_add_clicked();
 /*   void on_tabmedi_clicked(const QModelIndex &index);

    void on_tabmedi_doubleClicked(const QModelIndex &index);*/

    void on_trier_clicked();

    void on_trier_2_clicked();

private:
    Ui::MainWindow *ui;
    Medicament M;

};

#endif // MAINWINDOW_H
