# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'minywindow.ui'
##
## Created by: Qt User Interface Compiler version 6.5.2
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
    QMetaObject, QObject, QPoint, QRect,
    QSize, QTime, QUrl, Qt)
from PySide6.QtGui import (QBrush, QColor, QConicalGradient, QCursor,
    QFont, QFontDatabase, QGradient, QIcon,
    QImage, QKeySequence, QLinearGradient, QPainter,
    QPalette, QPixmap, QRadialGradient, QTransform)
from PySide6.QtWidgets import (QApplication, QMainWindow, QMenuBar, QSizePolicy,
    QStatusBar, QWidget)

class Ui_MinyWindow(object):
    def setupUi(self, MinyWindow):
        if not MinyWindow.objectName():
            MinyWindow.setObjectName(u"MinyWindow")
        MinyWindow.resize(200, 200)
        self.centralwidget = QWidget(MinyWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        MinyWindow.setCentralWidget(self.centralwidget)
        self.menubar = QMenuBar(MinyWindow)
        self.menubar.setObjectName(u"menubar")
        self.menubar.setGeometry(QRect(0, 0, 200, 22))
        MinyWindow.setMenuBar(self.menubar)
        self.statusbar = QStatusBar(MinyWindow)
        self.statusbar.setObjectName(u"statusbar")
        MinyWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MinyWindow)

        QMetaObject.connectSlotsByName(MinyWindow)
    # setupUi

    def retranslateUi(self, MinyWindow):
        MinyWindow.setWindowTitle(QCoreApplication.translate("MinyWindow", u"MinyWindow", None))
    # retranslateUi

