#ifndef GAMEEND_H
#define GAMEEND_H



#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class GameEnd : public QDialog {
    Q_OBJECT

public:
    GameEnd(QWidget *parent = nullptr) : QDialog(parent) {
        // Nastavení titulku dialogu
        setWindowTitle("Hra Prohrána");

        // Vytvoření a nastavení labelu s hláškou
        QLabel *label = new QLabel("Tak nic moc.. právě jsi stoupl na minu... :-( \n V naší hře ale můžeš zkusit pokračovat..", this);

        // Vytvoření tlačítka pro zavření dialogu
        QPushButton *closeButton = new QPushButton("Zavřít", this);
        connect(closeButton, &QPushButton::clicked, this, &GameEnd::accept);

        // Vytvoření layoutu a přidání widgetů
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(label);
        layout->addWidget(closeButton);
    }
};


#endif // GAMEEND_H
