#include "window.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    window tela;
    tela.resize(1500, 800);
    tela.setWindowTitle("Organizador de Tarefas");
    tela.show();
    return app.exec();
}
