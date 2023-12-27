#ifndef MINYWINDOW_H
#define MINYWINDOW_H

#include <QMainWindow>
#include "matrix2d.h"
#include <QGridLayout>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MinyWindow;
}
QT_END_NAMESPACE

class MinyWindow : public QMainWindow
{
    Q_OBJECT

public:
    MinyWindow(QWidget *parent = nullptr, int Size = 5, int Difficulty = 3);
    ~MinyWindow();


public slots:
    void buttonClicked();

private:
    int MatrixSize;
    int scanAround(int row, int col, int onlyCount);
    Ui::MinyWindow *ui;
    Matrix2D *matrix;
    QGridLayout *gridLayout; // Matice, ve ktere jsou ulozena metadata

    void updateStatusLabel();
    QLabel *StatusLabel;

    // Promene pro ukladani herniho statusu 
    int GameStatus_clicks = 0;
    int GameStatus_ends = 0;
    int GameStatus_opened = 0;
    int GameStatus_marked = 0;
};
#endif // MINYWINDOW_H
