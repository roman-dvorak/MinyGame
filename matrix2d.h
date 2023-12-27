#ifndef MATRIX2D_H
#define MATRIX2D_H

#include "qpushbutton.h"
#include <cstddef>
#include <vector>
#include <math.h>
#include <QWidget>
#include <QPushButton>
#include <iostream>

class Matrix2D {
private:
    std::vector<std::vector<int>> data;
    std::vector<std::vector<QPushButton*>> buttons;
    int rows, cols;


public:
    Matrix2D(int rows, int cols) : rows(rows), cols(cols), data(rows, std::vector<int>(cols)) {}
    Matrix2D(int size) :
        rows(sqrt(size)), cols(sqrt(size)), data(sqrt(size), std::vector<int>(sqrt(size))) {}


    void set(int row, int col, int value) {
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            data[row][col] = value;
        }
    }

    void setButton(int row, int col, QPushButton* button) {
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            std::cout << "Prirazovani do pole" << std::endl;
            std::cout << "ROW " << row << std::endl;
            std::cout << "COL " << col << std::endl;
            std::cout << "BTN " << button << std::endl;

            std::cout << "myPointer is a pointer: " << std::is_pointer<decltype(button)>::value << std::endl;
            std::cout << "myFunction is a function: " << std::is_function<decltype(button)>::value << std::endl;

            buttons[row][col] = button;
        }
    }

    int get(int row, int col) {
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            return data[row][col];
        } else {
            return 0;
        }
    }

    QPushButton* getButton(int row, int col){
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            return buttons[row][col];
        } else {
            return nullptr;
        }

    }

    std::vector<int> getNeighbors(int row, int col) {
        std::vector<int> neighbors;
        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                if (dr == 0 && dc == 0) continue; // Skip the element itself
                neighbors.push_back(get(row + dr, col + dc));
            }
        }
        return neighbors;
    }
};


#endif // MATRIX2D_H
