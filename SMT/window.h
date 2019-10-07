#ifndef WINDOW_H
#define WINDOW_H

#include "job.h"

#include <QWidget>
#include <QListWidget>
#include <vector>
#include <QLabel>
#include <QLineEdit>
#include <QCalendarWidget>

class window : public QWidget {

public:
    explicit window(QWidget *parent = nullptr);

private:
    QWidget *new_window;
    QListWidget *lista;
    vector<Job> jobs;
    QLabel *tarefa_label;
    QLabel *data_label;
    QDate data_inicio = QDate::currentDate();
    QLineEdit *campo_texto1;
    QLineEdit *campo_texto2;
    QCalendarWidget *calendar;
    QLabel *alert;
    int atraso_maximo = 0;
    int qtd_atrasos = 0;
    int achado = -1;

public slots:
    void tela_adicionar_tarefa();
    void adicionar_tarefa();
    void tela_editar_tarefa();
    void coletar_dados();
    void editar_tarefa();
    void tela_remover_tarefa();
    void remover_tarefa();
    void tela_completar_tarefa();
    void completar_tarefa();
    void tela_mostrar_detalhes_tarefa();
    void mostrar_detalhes_tarefa();
    void mostrar_detalhes_calendario();
    void tela_atualizar_data_inicio();
    void atualizar_data_inicio();
    void atualizar_lista(QDate);
    void validar_busca_tarefa();
    void tela_informacoes();
};

#endif // WINDOW_H
