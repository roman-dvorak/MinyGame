#include "minywindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include <iostream>

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QIntValidator>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

class IntInputDialog : public QDialog {
public:
    IntInputDialog(QWidget *parent = nullptr) : QDialog(parent) {
        // Vytvoření a nastavení line editů
        lineEdit1 = new QSpinBox(this);
        lineEdit2 = new QSpinBox(this);

        lineEdit1->setValue(20);
        lineEdit1->setMinimum(0);
        lineEdit1->setMaximum(50);

        lineEdit2->setValue(5);
        lineEdit2->setMinimum(0);
        lineEdit2->setMaximum(10);

        QPushButton *okButton = new QPushButton("OK", this);
        QPushButton *cancelButton = new QPushButton("Cancel", this);

        // Layout
        QVBoxLayout *vLayout = new QVBoxLayout(this);
        QHBoxLayout *hLayout1 = new QHBoxLayout();
        QHBoxLayout *hLayout2 = new QHBoxLayout();
        QHBoxLayout *hLayout3 = new QHBoxLayout();

        // Přidání widgetů do layoutů
        hLayout1->addWidget(new QLabel("šířka pole:"));
        hLayout1->addWidget(lineEdit1);

        hLayout2->addWidget(new QLabel("Složitost:"));
        hLayout2->addWidget(lineEdit2);

        hLayout3->addWidget(okButton);
        hLayout3->addWidget(cancelButton);

        vLayout->addLayout(hLayout1);
        vLayout->addLayout(hLayout2);
        vLayout->addLayout(hLayout3);

        // Připojení signálů a slotů
        connect(okButton, &QPushButton::clicked, this, &IntInputDialog::accept);
        connect(cancelButton, &QPushButton::clicked, this, &IntInputDialog::reject);
    }

    int getSize(){
        return lineEdit1->value();
    }

    int getDifficulty(){
        return lineEdit2->value();
    }
private:
    QSpinBox *lineEdit1;
    QSpinBox *lineEdit2;
};




int main(int argc, char *argv[])
{

    QApplication a(argc, argv);


    int GameSize, GameDifficulty;

    IntInputDialog dialog(NULL);

    if (dialog.exec() == QDialog::Accepted) {
        GameSize = dialog.getSize();
        GameDifficulty = dialog.getDifficulty();
    }

    std::cout << "Dialog prijat; rozmery " << GameSize << std::endl;

    MinyWindow w(nullptr, GameSize, GameDifficulty);
    w.show();
    return a.exec();
}
