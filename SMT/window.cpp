#include "window.h"
#include <QFont>
#include <QFormLayout>
#include <QPushButton>

window::window(QWidget *parent) : QWidget(parent) {
    int button_width = 420, button_height = 80;
    int maximum_label_height = 30;
    QFont buttonFont("Times", 25);
    QFont labelFont("Times", 20, QFont::Bold);

    QHBoxLayout *tela = new QHBoxLayout(this);
    QGridLayout *lista_layout = new QGridLayout();
    QGridLayout *tarefas_layout = new QGridLayout();
    QGridLayout *detalhes_layout = new QGridLayout();

    /**************** Lista ****************/

    QLabel *indiv_label = new QLabel("Ordem das tarefas", this);
    lista_layout->addWidget(indiv_label, 0, 0);
    indiv_label->setAlignment(Qt::AlignCenter);
    indiv_label->setMaximumHeight(maximum_label_height);
    indiv_label->setFont(labelFont);

    lista = new QListWidget(this);
    lista->setMaximumWidth(500);
    lista->setMinimumWidth(100);
    lista_layout->addWidget(lista, 1, 0);

    /**************** Tarefas ****************/

    tarefa_label = new QLabel("TAREFAS : " + QString::number(this->jobs.size()), this);
    tarefas_layout->addWidget(tarefa_label, 0, 0);
    tarefa_label->setAlignment(Qt::AlignCenter);
    tarefa_label->setMaximumHeight(maximum_label_height);
    tarefa_label->setFont(labelFont);

    QPushButton *add_job = new QPushButton("Adicionar Tarefa", this);
    add_job->setFixedWidth(button_width);
    add_job->setFixedHeight(button_height);
    add_job->setFont(buttonFont);
    connect(add_job, &QPushButton::clicked, this, &window::tela_adicionar_tarefa);
    tarefas_layout->addWidget(add_job, 1, 0);

    QPushButton *edit_job = new QPushButton("Editar Tarefa", this);
    edit_job->setFixedWidth(button_width);
    edit_job->setFixedHeight(button_height);
    edit_job->setFont(buttonFont);
    connect(edit_job, &QPushButton::clicked, this, &window::tela_editar_tarefa);
    tarefas_layout->addWidget(edit_job, 2, 0);

    QPushButton *remove_job = new QPushButton("Remover Tarefa", this);
    remove_job->setFixedWidth(button_width);
    remove_job->setFixedHeight(button_height);
    remove_job->setFont(buttonFont);
    connect(remove_job, &QPushButton::clicked, this, &window::tela_remover_tarefa);
    tarefas_layout->addWidget(remove_job, 3, 0);

    QPushButton *complete_job = new QPushButton("Adicionar Tarefa", this);
    complete_job->setFixedWidth(button_width);
    complete_job->setFixedHeight(button_height);
    complete_job->setFont(buttonFont);
    connect(complete_job, &QPushButton::clicked, this, &window::tela_completar_tarefa);
    tarefas_layout->addWidget(complete_job, 4, 0);

    /**************** Detalhes ****************/

    data_label = new QLabel("INÍCIO : " + this->data_inicio.toString(Qt::SystemLocaleDate), this);
    detalhes_layout->addWidget(data_label, 0, 0);
    data_label->setAlignment(Qt::AlignCenter);
    data_label->setMaximumHeight(maximum_label_height);
    data_label->setFont(labelFont);

    QPushButton *details_job = new QPushButton("Detalhes de uma Tarefa", this);
    details_job->setFixedWidth(button_width);
    details_job->setFixedHeight(button_height);
    details_job->setFont(buttonFont);
    connect(details_job, &QPushButton::clicked, this, &window::tela_mostrar_detalhes_tarefa);
    detalhes_layout->addWidget(details_job, 1, 0);

    QPushButton *details_schedule = new QPushButton("Detalhes do Calendário", this);
    details_schedule->setFixedWidth(button_width);
    details_schedule->setFixedHeight(button_height);
    details_schedule->setFont(buttonFont);
    connect(details_schedule, &QPushButton::clicked, this, &window::mostrar_detalhes_calendario);
    detalhes_layout->addWidget(details_schedule, 2, 0);

    QPushButton *update_date = new QPushButton("Atualizar Data de Início", this);
    update_date->setFixedWidth(button_width);
    update_date->setFixedHeight(button_height);
    update_date->setFont(buttonFont);
    connect(update_date, &QPushButton::clicked, this, &window::tela_atualizar_data_inicio);
    detalhes_layout->addWidget(update_date, 3, 0);

    QPushButton *other = new QPushButton("Outras Informações", this);
    other->setFixedWidth(button_width);
    other->setFixedHeight(button_height);
    other->setFont(buttonFont);
    //connect(add_indiv, &QPushButton::clicked, this, &window::tela_add_pes);
    detalhes_layout->addWidget(other, 4, 0);

    /**************** Finalizações ****************/

    tela->addItem(lista_layout);
    tela->addItem(tarefas_layout);
    tela->addItem(detalhes_layout);
    setLayout(tela);
}

void window::tela_adicionar_tarefa() {

}

void window::adicionar_tarefa() {

}

void window::tela_editar_tarefa() {

}

void window::editar_tarefa() {

}

void window::tela_remover_tarefa() {

}

void window::remover_tarefa() {

}

void window::tela_completar_tarefa() {

}

void window::completar_tarefa() {

}

void window::tela_mostrar_detalhes_tarefa() {

}

void window::mostrar_detalhes_tarefa() {

}

void window::mostrar_detalhes_calendario() {

}

void window::tela_atualizar_data_inicio() {

}

void window::atualizar_data_inicio() {

}
