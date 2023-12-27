#include "minywindow.h"
#include "./ui_minywindow.h"
#include "matrix2d.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <QGuiApplication>

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QIntValidator>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include "minywindow.h"
#include "GameEnd.h"


MinyWindow::MinyWindow(QWidget *parent, int Size, int Difficulty)
    : QMainWindow(parent)
    , ui(new Ui::MinyWindow)
{
    ui->setupUi(this);
    srand (time(NULL));
    MatrixSize = Size;

    // Vytvoření widgetu, který bude obsahovat layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *VBox = new QVBoxLayout();

    this->setCentralWidget(centralWidget);

    // Vytvoření layoutu
    gridLayout = new QGridLayout();
    gridLayout->setSpacing(0);

    Matrix2D *matrix = new Matrix2D(Size);

    QPushButton { "padding: 10px; margin: 10px; width: 20px; height: 20px;" };
    for (int row = 0; row < Size; ++row) {
        for (int column = 0; column < Size; ++column) {
            int randval = rand() % 10 + 1;
            randval = (randval <= (Difficulty));
            QPushButton *button = new QPushButton(" ", centralWidget);
            button->setFixedSize(25, 25);
            connect(button, &QPushButton::clicked, this, &MinyWindow::buttonClicked);

            matrix->set(row, column, randval);
            //matrix->setButton(row, column, button);

            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            button->setProperty("row", row);
            button->setProperty("column", column);
            button->setProperty("val", randval);
            button->setProperty("open", 0);
            gridLayout->addWidget(button, row, column);
        }
    }

    // Nastavení layoutu pro centralWidget
    VBox->addLayout(gridLayout);



    //QHBoxLayout *Status1 = new QHBoxLayout();
    StatusLabel = new QLabel(" ");
    //Status1->addWidget( StatusLabel );


    VBox->addWidget(StatusLabel);
    centralWidget->setLayout(VBox);
}


void MinyWindow::updateStatusLabel(){


    std::string status = "Už jsi provedl "+ std::to_string(GameStatus_clicks) +" tahů \n" +
                         "Zatím jste stoupl na minu " + std::to_string(GameStatus_ends) + " x;\n Již máte otevřeno " +
                         std::to_string(GameStatus_opened) + " polí.\n Potenciální bomba je pod " +
                         std::to_string(GameStatus_marked) + " poli.";
    StatusLabel->setText( QString::fromStdString(status) );

    return;
};

int MinyWindow::scanAround(int row, int col, int onlyCount){
    std::cout << "ScanAround z [" << row << ", " << col << "] " << onlyCount << std::endl;

    QPushButton *button = qobject_cast<QPushButton*>(gridLayout->itemAtPosition(row, col)->widget());

    if(button->isCheckable()){
        std::cout << "Vychozi tlacitko uz bylo prohlizeno " << std::endl;
        return 0;
    }

    button->setCheckable(true);
    button->toggle();
    button->setDisabled(true);
    button->setText("");
    GameStatus_opened ++;

    int result = 0;
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) continue; // Skip the element itself
            if (row+dr < 0 || row+dr+1 > MatrixSize) continue;
            if (col+dc < 0 || col+dc+1 > MatrixSize) continue;


            QPushButton *btn = qobject_cast<QPushButton*>(gridLayout->itemAtPosition(row + dr, col + dc)->widget());
            if(!btn){
                std::cout << "Tohle neni button..." << std::endl;
                continue;
            }

            // co, kdyz je tu bomba?
            if(btn->property("val").toInt()){
                std::cout << "Bomba na [" << row+dr << ", " << col+dc << "]" << std::endl;
                result ++;
            } else {
                int oc = (dc==0 || dr==0);
                if(oc) scanAround(row+dr, col+dc, oc);
            }
        }
    }

    if(result){
        button->setText( QString::number(result) );

    }

    return result;
}


void MinyWindow::buttonClicked() {
    qDebug() << "Tlačítko bylo stisknuto";
    GameStatus_clicks ++;
    QPushButton *button = qobject_cast<QPushButton *>(sender());

    int col = button->property("column").toInt();
    int row = button->property("row").toInt();
    int val = button->property("val").toInt();


    if (QGuiApplication::keyboardModifiers() & Qt::ControlModifier) {
        qDebug() << "Ctrl klávesa je stisknuta při aktivaci slotu";

        button->setProperty("marked", true);
        button->setStyleSheet("QPushButton { background-color: oragne; }");
        //button->setCheckable(true);
        //button->toggle();
        //button->setDisabled(true);
        GameStatus_marked ++;

    } else {


        if(val){
            button->setStyleSheet("QPushButton { background-color: red; }");
            GameStatus_ends ++;
            GameEnd dialog;
            dialog.exec();

        }else{
            //button->setStyleSheet("QPushButton { background-color: green; }");
            scanAround(row, col, 1);
        }
        // button->setCheckable(true);
        // button->toggle();
        // button->setDisabled(true);

    }

    updateStatusLabel();
}


MinyWindow::~MinyWindow()
{
    delete ui;
}
