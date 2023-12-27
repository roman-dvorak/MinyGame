#include "minywindow.h"
#include "ui_minywindow.h"
#include "matrix2d.h"
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
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

    // Nastavit CentralWidget do okna hry
    this->setCentralWidget(centralWidget);

    // Vytvoření layoutu pro samotnou matici s hernim polem
    gridLayout = new QGridLayout();
    gridLayout->setSpacing(0);

    // Vytvoreni nove instance vlastni tridy Matrix2D, do ktere si ukladam metadata
    Matrix2D *matrix = new Matrix2D(Size);

    // Nastaveni globalnich parametru pro tlacitka 
    QPushButton { "padding: 10px; margin: 10px; width: 20px; height: 20px;" };

    // Nyni budu iterovat pres radky a sloupce. Tak, abych naplnil vsechny bunky tlacitky
    for (int row = 0; row < Size; ++row) {
        for (int column = 0; column < Size; ++column) {

            // Vygenerovani nahodne hodnoty. Hodnota je v rozsahu 1-10
            // Na zaklade slozitosti se z toho vygeneruje seznam min
            int randval = rand() % 10 + 1;
            randval = (randval <= (Difficulty));
            
            // Vytvorime Tlacitko, nastavime mu poslouchani signalu
            QPushButton *button = new QPushButton(" ", centralWidget);
            button->setFixedSize(25, 25);
            connect(button, &QPushButton::clicked, this, &MinyWindow::buttonClicked);

            // Poznamenam si metadata
            matrix->set(row, column, randval);

            // Nastavim parametry tlacitku, se kterymi budu dale pracovat. 
            // Obsahuje napr informaci o poloze nebo informaci o tom, zdali je tam mina.
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            button->setProperty("row", row);
            button->setProperty("column", column);
            button->setProperty("val", randval);
            button->setProperty("open", 0);
            // Pridam tlacitko do gridu
            gridLayout->addWidget(button, row, column);
        }
    }

    // Nastavení layoutu pro centralWidget
    VBox->addLayout(gridLayout);

    // Vytvorim popisek, ktery bude obsahovat parametry pro zobrazení stavu hry
    StatusLabel = new QLabel(" ");

    VBox->addWidget(StatusLabel);
    centralWidget->setLayout(VBox);
}


/** Funkce pro aktualizaci popisku */
void MinyWindow::updateStatusLabel(){

    // Aktualizace popisku s aktuálními parametry
    std::string status = "Už jsi provedl "+ std::to_string(GameStatus_clicks) +" tahů \n" +
                         "Zatím jste stoupl na minu " + std::to_string(GameStatus_ends) + " x;\n Již máte otevřeno " +
                         std::to_string(GameStatus_opened) + " polí.\n Potenciální bomba je pod " +
                         std::to_string(GameStatus_marked) + " poli.";
    StatusLabel->setText( QString::fromStdString(status) );

    return;
};

/* 
** Funkce pro kontrolu min v okoli.
** Pokud tam mina neni, tak pole odkryje. 
** Pokud mina je v okoli, tak je spocita a zobrazi uvnitr bunky 
** Pokud je volne pole uhlopricne, tak ho igronuje. Otevira to volne pole,
** ktera sdili celou hranu. 
*/
int MinyWindow::scanAround(int row, int col, int onlyCount){
    //std::cout << "ScanAround z [" << row << ", " << col << "] " << onlyCount << std::endl;

    QPushButton *button = qobject_cast<QPushButton*>(gridLayout->itemAtPosition(row, col)->widget());

    // Kontrola, ze jsem se na tohle tlacitko uz dival (v predchozim kole rekurze)
    if(button->isCheckable()){
        //std::cout << "Vychozi tlacitko uz bylo prohlizeno " << std::endl;
        return 0;
    }

    // Nastavit parametry tlacitka, na zaklade kterych se pozna, ze jsem tohle uz kontroloval. 
    // Zaroven uz na nej nepujde klikat. 
    button->setCheckable(true);
    button->toggle();
    button->setDisabled(true);
    button->setText("");
    GameStatus_opened ++;

    int result = 0;
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) continue; // Preskocit prvek, ze ktereho vyhledavam
            // Kontrola, ze hledam pouze v hernim poli. Pokud ne, tak preskocit. 
            if (row+dr < 0 || row+dr+1 > MatrixSize) continue;
            if (col+dc < 0 || col+dc+1 > MatrixSize) continue;

            // Tady si ziskam objekt tlacitka z gridu na zadanych souradnicich
            QPushButton *btn = qobject_cast<QPushButton*>(gridLayout->itemAtPosition(row + dr, col + dc)->widget());
            if(!btn){
                // Kontrola, ze tady je button. Melo by to byt vzdy, ale co kdyby.. 
                // std::cout << "Tohle neni button..." << std::endl;
                continue;
            }

            // co, kdyz je tu bomba? ... no, tak ji zapocitam
            if(btn->property("val").toInt()){
                // std::cout << "Bomba na [" << row+dr << ", " << col+dc << "]" << std::endl;
                result ++;
            // Pokud tu neni mina, tak rekurzivne proscanuji i tento prostor. 
            } else {
                int oc = (dc==0 || dr==0);
                if(oc) scanAround(row+dr, col+dc, oc);
            }
        }
    }

    // Pokud je v okoli mina, tak se spocita jejich pocet a zobrazi se uvnitr bunky.
    if(result){
        button->setText( QString::number(result) );
    }

    return result;
}


/* Tohle je callback po stisku otevreneho tlacitka. */
void MinyWindow::buttonClicked() {
    GameStatus_clicks ++;
    QPushButton *button = qobject_cast<QPushButton *>(sender());

    // Zde si z tlacitek zjistim nejake parametry
    int col = button->property("column").toInt();
    int row = button->property("row").toInt();
    int val = button->property("val").toInt();

    // Kontrola, jestli je CTRL stisknuto. V takovem pripade to oznacim jako 
    // mozna mina. 
    if (QGuiApplication::keyboardModifiers() & Qt::ControlModifier) {

        button->setProperty("marked", true);
        button->setStyleSheet("QPushButton { background-color: yellow; }");
        GameStatus_marked ++;

    // Tlacitko je stisknuto bez CTRL
    } else {

        // Kontrola, jestil je tam mina nebo ne. 
        // V pripade miny zvysime hodnoty proher, otevreme dialog. 
        if(val){
            button->setStyleSheet("QPushButton { background-color: red; }");
            GameStatus_ends ++;
            GameEnd dialog;
            dialog.exec();

        // V pripade, ze je to OK, proskenuji okoli. 
        // A ty spravne bunky oznacim rekurzivnim procesem. 
        }else{
            //button->setStyleSheet("QPushButton { background-color: green; }");
            scanAround(row, col, 1);
        }

    }

    // Tak je cas na aktualizaci popisku
    updateStatusLabel();
}


MinyWindow::~MinyWindow()
{
    delete ui;
    // QT se samo postará o ukončení programu a dealokaci vsech vytvorených objektu
    // A tedy spravne uvolneni pameti. 
}
