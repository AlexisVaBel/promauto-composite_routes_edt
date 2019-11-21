#include "mainwindow.h"
#include <QApplication>

int main(int argc, char ** argv){
    QApplication app(argc, argv);


    MainWindow *wnd = new MainWindow();
    wnd->show();

    auto appResult = app.exec();
    return appResult;
}
