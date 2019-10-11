#include "window.h"
#include <QFont>
#include <QFormLayout>
#include <QPushButton>
#include <QEventLoop>
#include <QMessageBox>
#include <random>

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
    lista->setFont(QFont("Times", 16, QFont::Bold));
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

    QPushButton *complete_job = new QPushButton("Completar Tarefa", this);
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

    QPushButton *other = new QPushButton("Calendário Aleatório", this);
    other->setFixedWidth(button_width);
    other->setFixedHeight(button_height);
    other->setFont(buttonFont);
    connect(other, &QPushButton::clicked, this, &window::tela_aleatorio);
    detalhes_layout->addWidget(other, 4, 0);

    /**************** Finalizações ****************/

    tela->addItem(lista_layout);
    tela->addItem(tarefas_layout);
    tela->addItem(detalhes_layout);
    setLayout(tela);
}

void window::tela_adicionar_tarefa() {
    new_window = new QWidget(nullptr);
    new_window->setFixedSize(600, 400);
    new_window->setWindowTitle("Adicionar Tarefa");

    QFont buttonFont("Times", 20);
    int button_size = 470;
    QFont labelFont("Times", 20, QFont::Bold);
    QFont campoFont("Times", 20);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);

    QLabel *main_label = new QLabel("Insira os dados da Tarefa");
    main_label->setFont(labelFont);
    main_label->setAlignment(Qt::AlignCenter);
    QLabel *label_nome = new QLabel("Nome:");
    label_nome->setFont(labelFont);
    QLabel *label_tempo = new QLabel("Tempo:");
    label_tempo->setFont(labelFont);
    QLabel *label_deadline = new QLabel("Entrega:");
    label_deadline->setFont(labelFont);

    campo_texto1 = new QLineEdit();
    campo_texto1->setFont(campoFont);
    campo_texto1->setMaxLength(50);

    campo_texto2 = new QLineEdit();
    campo_texto2->setFont(campoFont);
    campo_texto2->setValidator(new QIntValidator());

    calendar = new QCalendarWidget();
    calendar->setMinimumDate(QDate::currentDate());
    calendar->setGridVisible(true);

    formLayout->addWidget(main_label);
    formLayout->addRow(label_nome, campo_texto1);
    formLayout->addRow(label_tempo, campo_texto2);
    formLayout->addRow(label_deadline, calendar);

    QPushButton *button = new QPushButton("Adicionar");
    button->setMinimumWidth(button_size);
    button->setFont(buttonFont);
    connect(button, &QPushButton::clicked, this, &window::adicionar_tarefa);

    alert = new QLabel(" ");
    alert->setAlignment(Qt::AlignCenter);
    alert->setMaximumHeight(20);

    formLayout->addWidget(button);
    formLayout->addWidget(alert);

    new_window->setLayout(formLayout);
    new_window->show();

    QEventLoop loop;
    connect(this, SIGNAL(destroyed()), & loop, SLOT(quit()));
    loop.exec();
}

void window::adicionar_tarefa() {
    QString nome = campo_texto1->text();
    if(nome == "") {
        alert->setText("Nome não pode ser em branco");
        return;
    }

    int tempo = campo_texto2->text().toInt();
    if(tempo < 1) {
        alert->setText("Tempo deve ser 1 ou maior");
        return;
    }

    for(const auto& j : jobs) {
        if(QString::fromStdString(j.nome) == nome) {
            alert->setText("Já existe uma tarefa com esse nome");
            return;
        }
    }

    jobs.emplace_back(nome.toStdString(), tempo, calendar->selectedDate());
    atualizar_lista(data_inicio);

    new_window->close();
}

void window::tela_editar_tarefa() {
    new_window = new QWidget(nullptr);

    if(!jobs.size()) {
        QMessageBox::information(new_window, tr("Aviso"), tr("Não há nenhuma tarefa cadastrada"));
        return;
    }

    new_window->setFixedSize(500, 300);
    new_window->setWindowTitle("Editar Tarefa");

    QFont buttonFont("Times", 20);
    QFont labelFont("Times", 20, QFont::Bold);
    QFont campoFont("Times", 20);
    int button_size = 480;
    int maximum_label_height = 30;

    campo_texto1 = new QLineEdit();
    campo_texto1->setFont(campoFont);

    QVBoxLayout *tela = new QVBoxLayout();

    QLabel *label = new QLabel("Insira o nome da Tarefa");
    label->setAlignment(Qt::AlignCenter);
    label->setMaximumHeight(maximum_label_height);
    label->setFont(labelFont);

    QPushButton *button = new QPushButton("Enviar");
    button->setFixedWidth(button_size);
    button->setFont(buttonFont);
    connect(button, &QPushButton::clicked, this, &window::coletar_dados);

    alert = new QLabel("");
    alert->setAlignment(Qt::AlignCenter);
    alert->setMaximumHeight(15);

    tela->addWidget(label);
    tela->addWidget(campo_texto1);
    tela->addWidget(button);
    tela->addWidget(alert);
    new_window->setLayout(tela);
    new_window->show();

    QEventLoop loop;
    connect(this, SIGNAL(destroyed()), & loop, SLOT(quit()));
    loop.exec();
}

void window::coletar_dados() {
    this->validar_busca_tarefa();
    if(this->achado == -1)
        return;

    new_window->close();

    new_window = new QWidget(nullptr);
    new_window->setFixedSize(600, 400);
    new_window->setWindowTitle("Editar Tarefa");

    QFont buttonFont("Times", 20);
    int button_size = 470;
    QFont labelFont("Times", 20, QFont::Bold);
    QFont campoFont("Times", 20);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);

    QLabel *main_label = new QLabel("Insira os dados da Tarefa");
    main_label->setFont(labelFont);
    main_label->setAlignment(Qt::AlignCenter);
    QLabel *label_nome = new QLabel("Nome:");
    label_nome->setFont(labelFont);
    QLabel *label_tempo = new QLabel("Tempo:");
    label_tempo->setFont(labelFont);
    QLabel *label_deadline = new QLabel("Entrega:");
    label_deadline->setFont(labelFont);

    campo_texto1 = new QLineEdit();
    campo_texto1->setFont(campoFont);
    campo_texto1->setMaxLength(50);

    campo_texto2 = new QLineEdit();
    campo_texto2->setFont(campoFont);
    campo_texto2->setValidator(new QIntValidator());

    calendar = new QCalendarWidget();
    calendar->setMinimumDate(QDate::currentDate());
    calendar->setGridVisible(true);

    formLayout->addWidget(main_label);
    formLayout->addRow(label_nome, campo_texto1);
    formLayout->addRow(label_tempo, campo_texto2);
    formLayout->addRow(label_deadline, calendar);

    QPushButton *button = new QPushButton("Editar");
    button->setMinimumWidth(button_size);
    button->setFont(buttonFont);
    connect(button, &QPushButton::clicked, this, &window::editar_tarefa);

    alert = new QLabel(" ");
    alert->setAlignment(Qt::AlignCenter);
    alert->setMaximumHeight(20);

    formLayout->addWidget(button);
    formLayout->addWidget(alert);

    new_window->setLayout(formLayout);
    new_window->show();

    QEventLoop loop;
    connect(this, SIGNAL(destroyed()), & loop, SLOT(quit()));
    loop.exec();
}

void window::editar_tarefa() {
    QString nome = campo_texto1->text();
    if(nome == "") {
        alert->setText("Nome não pode ser em branco");
        return;
    }

    int tempo = campo_texto2->text().toInt();
    if(tempo < 1) {
        alert->setText("Tempo deve ser 1 ou maior");
        return;
    }

    jobs[achado] = Job(nome.toStdString(), tempo, calendar->selectedDate());
    atualizar_lista(data_inicio);
    new_window->close();
}

void window::tela_remover_tarefa() {
    new_window = new QWidget(nullptr);

    if(!jobs.size()) {
        QMessageBox::information(new_window, tr("Aviso"), tr("Não há nenhuma tarefa cadastrada"));
        return;
    }

    QFont buttonFont("Times", 20);
    QFont labelFont("Times", 20, QFont::Bold);
    QFont campoFont("Times", 20);
    int button_size = 480;
    int maximum_label_height = 30;

    campo_texto1 = new QLineEdit();
    campo_texto1->setFont(campoFont);

    new_window->setFixedSize(500, 300);
    new_window->setWindowTitle("Remover Tarefa");

    QVBoxLayout *tela = new QVBoxLayout();

    QLabel *label = new QLabel("Insira o nome da Tarefa");
    label->setAlignment(Qt::AlignCenter);
    label->setMaximumHeight(maximum_label_height);
    label->setFont(labelFont);

    QPushButton *button = new QPushButton("Enviar");
    button->setFixedWidth(button_size);
    button->setFont(buttonFont);
    connect(button, &QPushButton::clicked, this, &window::remover_tarefa);

    alert = new QLabel("");
    alert->setAlignment(Qt::AlignCenter);
    alert->setMaximumHeight(15);

    tela->addWidget(label);
    tela->addWidget(campo_texto1);
    tela->addWidget(button);
    tela->addWidget(alert);
    new_window->setLayout(tela);
    new_window->show();

    QEventLoop loop;
    connect(this, SIGNAL(destroyed()), & loop, SLOT(quit()));
    loop.exec();
}

void window::remover_tarefa() {
    this->validar_busca_tarefa();
    if(this->achado == -1)
        return;

    int i = 0;

    for(auto it = jobs.begin(); it != jobs.end(); ++it, ++i) {
        if(i == achado)
            jobs.erase(it);
    }

    atualizar_lista(data_inicio);
    new_window->close();
}

void window::tela_completar_tarefa() {
    new_window = new QWidget(nullptr);

    if(!jobs.size()) {
        QMessageBox::information(new_window, tr("Aviso"), tr("Não há nenhuma tarefa"));
        return;
    }

    QFont buttonFont("Times", 20);
    QFont labelFont("Times", 20, QFont::Bold);
    QFont campoFont("Times", 20);
    int button_size = 480;
    int maximum_label_height = 30;

    new_window->setFixedSize(500, 250);
    new_window->setWindowTitle("Completar Tarefa");

    QVBoxLayout *tela = new QVBoxLayout();

    QLabel *label = new QLabel("Você completou a seguinte tarefa?");
    label->setAlignment(Qt::AlignCenter);
    label->setMaximumHeight(maximum_label_height);
    label->setFont(labelFont);

    QLabel *tarefa_completada = new QLabel(QString::fromStdString(jobs[0].nome));
    tarefa_completada->setAlignment(Qt::AlignCenter);
    tarefa_completada->setMaximumHeight(maximum_label_height);
    tarefa_completada->setFont(labelFont);

    QPushButton *yes_button = new QPushButton("Sim");
    yes_button->setFixedWidth(button_size);
    yes_button->setFont(buttonFont);
    connect(yes_button, &QPushButton::clicked, this, &window::completar_tarefa);

    QPushButton *no_button = new QPushButton("Não");
    no_button->setFixedWidth(button_size);
    no_button->setFont(buttonFont);
    //connect(no_button, &QPushButton::clicked, this, close());

    alert = new QLabel("");
    alert->setAlignment(Qt::AlignCenter);
    alert->setMaximumHeight(15);

    tela->addWidget(label);
    tela->addWidget(tarefa_completada);
    tela->addWidget(yes_button);
    tela->addWidget(no_button);
    tela->addWidget(alert);
    new_window->setLayout(tela);
    new_window->show();

    QEventLoop loop;
    connect(this, SIGNAL(destroyed()), & loop, SLOT(quit()));
    loop.exec();
}

void window::completar_tarefa() {
    jobs.erase(jobs.begin());

    if(jobs.size())
        atualizar_lista(jobs[0].inicio);
    else
        atualizar_lista(data_inicio);

    new_window->close();
}

void window::tela_mostrar_detalhes_tarefa() {
    new_window = new QWidget(nullptr);

    if(!jobs.size()) {
        QMessageBox::information(new_window, tr("Aviso"), tr("Não há nenhuma tarefa cadastrada"));
        return;
    }

    new_window->setFixedSize(500, 300);
    new_window->setWindowTitle("Editar Tarefa");

    QFont buttonFont("Times", 20);
    QFont labelFont("Times", 20, QFont::Bold);
    QFont campoFont("Times", 20);
    int button_size = 480;
    int maximum_label_height = 30;

    campo_texto1 = new QLineEdit();
    campo_texto1->setFont(campoFont);

    QVBoxLayout *tela = new QVBoxLayout();

    QLabel *label = new QLabel("Insira o nome da Tarefa");
    label->setAlignment(Qt::AlignCenter);
    label->setMaximumHeight(maximum_label_height);
    label->setFont(labelFont);

    QPushButton *button = new QPushButton("Enviar");
    button->setFixedWidth(button_size);
    button->setFont(buttonFont);
    connect(button, &QPushButton::clicked, this, &window::mostrar_detalhes_tarefa);

    alert = new QLabel("");
    alert->setAlignment(Qt::AlignCenter);
    alert->setMaximumHeight(15);

    tela->addWidget(label);
    tela->addWidget(campo_texto1);
    tela->addWidget(button);
    tela->addWidget(alert);
    new_window->setLayout(tela);
    new_window->show();

    QEventLoop loop;
    connect(this, SIGNAL(destroyed()), & loop, SLOT(quit()));
    loop.exec();
}

void window::mostrar_detalhes_tarefa() {
    this->validar_busca_tarefa();
    if(this->achado == -1)
        return;

    size_t i = achado;

    new_window->close();
    new_window = new QWidget(nullptr);

    QFont labelFont("Times", 20, QFont::Bold);
    int maximum_label_height = 30;

    QGridLayout *layout = new QGridLayout();

    QLabel *label_nome = new QLabel("Nome: ");
    QLabel *label_ordem = new QLabel("Ordem da Tarefa: ");
    QLabel *label_inicio = new QLabel("Data de início: ");
    QLabel *label_termino = new QLabel("Data de término: ");
    QLabel *label_entrega = new QLabel("Data de entrega: ");
    QLabel *label_atraso = new QLabel("Entrega com atraso? ");

    QLabel *j_nome = new QLabel(QString::fromStdString(jobs[i].nome));
    QLabel *j_ordem = new QLabel(QString::number(i+1));
    QLabel *j_inicio = new QLabel(jobs[i].inicio.toString(Qt::SystemLocaleDate));
    QLabel *j_termino = new QLabel(jobs[i].termino.toString(Qt::SystemLocaleDate));
    QLabel *j_entrega = new QLabel(jobs[i].deadline.toString(Qt::SystemLocaleDate));
    QLabel *j_atraso = new QLabel(jobs[i].deadline < jobs[i].termino ? QString::number(int(jobs[i].deadline.daysTo(jobs[i].termino))) + " dias" : "Não");

    label_nome->setMaximumHeight(maximum_label_height);
    label_nome->setFont(labelFont);
    label_ordem->setMaximumHeight(maximum_label_height);
    label_ordem->setFont(labelFont);
    label_inicio->setMaximumHeight(maximum_label_height);
    label_inicio->setFont(labelFont);
    label_termino->setMaximumHeight(maximum_label_height);
    label_termino->setFont(labelFont);
    label_entrega->setMaximumHeight(maximum_label_height);
    label_entrega->setFont(labelFont);
    label_atraso->setMaximumHeight(maximum_label_height);
    label_atraso->setFont(labelFont);

    j_nome->setMaximumHeight(maximum_label_height);
    j_nome->setFont(labelFont);
    j_ordem->setMaximumHeight(maximum_label_height);
    j_ordem->setFont(labelFont);
    j_inicio->setMaximumHeight(maximum_label_height);
    j_inicio->setFont(labelFont);
    j_termino->setMaximumHeight(maximum_label_height);
    j_termino->setFont(labelFont);
    j_entrega->setMaximumHeight(maximum_label_height);
    j_entrega->setFont(labelFont);
    j_atraso->setMaximumHeight(maximum_label_height);
    j_atraso->setFont(labelFont);

    label_nome->setAlignment(Qt::AlignRight);
    label_ordem->setAlignment(Qt::AlignRight);
    label_inicio->setAlignment(Qt::AlignRight);
    label_termino->setAlignment(Qt::AlignRight);
    label_entrega->setAlignment(Qt::AlignRight);
    label_atraso->setAlignment(Qt::AlignRight);

    layout->addWidget(label_nome, 0, 0);
    layout->addWidget(label_ordem, 1, 0);
    layout->addWidget(label_inicio, 2, 0);
    layout->addWidget(label_termino, 3, 0);
    layout->addWidget(label_entrega, 4, 0);
    layout->addWidget(label_atraso, 5, 0);

    j_nome->setAlignment(Qt::AlignLeft);
    j_ordem->setAlignment(Qt::AlignLeft);
    j_inicio->setAlignment(Qt::AlignLeft);
    j_termino->setAlignment(Qt::AlignLeft);
    j_entrega->setAlignment(Qt::AlignLeft);
    j_atraso->setAlignment(Qt::AlignLeft);

    layout->addWidget(j_nome, 0, 1);
    layout->addWidget(j_ordem, 1, 1);
    layout->addWidget(j_inicio, 2, 1);
    layout->addWidget(j_termino, 3, 1);
    layout->addWidget(j_entrega, 4, 1);
    layout->addWidget(j_atraso, 5, 1);

    new_window->setWindowTitle("Detalhes da Tarefa");
    new_window->setLayout(layout);
    new_window->setFixedSize(550, 400);
    new_window->show();

    QEventLoop loop;
    connect(this, SIGNAL(destroyed()), & loop, SLOT(quit()));
    loop.exec();
}

void window::mostrar_detalhes_calendario() {
    new_window = new QWidget(nullptr);

    QFont labelFont("Times", 20, QFont::Bold);
    int maximum_label_height = 30;

    QGridLayout *layout = new QGridLayout();

    QLabel *label_tarefas = new QLabel("Quantidade de Tarefas: ");
    QLabel *label_atrasos = new QLabel("Quantidade de atrasos: ");
    QLabel *label_max = new QLabel("Maior atraso: ");

    QLabel *s_tarefas = new QLabel(QString::number(jobs.size()));
    QLabel *s_atrasos = new QLabel(QString::number(qtd_atrasos));
    QLabel *s_max = new QLabel(QString::number(atraso_maximo));

    label_tarefas->setMaximumHeight(maximum_label_height);
    label_tarefas->setFont(labelFont);
    label_atrasos->setMaximumHeight(maximum_label_height);
    label_atrasos->setFont(labelFont);
    label_max->setMaximumHeight(maximum_label_height);
    label_max->setFont(labelFont);

    s_tarefas->setMaximumHeight(maximum_label_height);
    s_tarefas->setFont(labelFont);
    s_atrasos->setMaximumHeight(maximum_label_height);
    s_atrasos->setFont(labelFont);
    s_max->setMaximumHeight(maximum_label_height);
    s_max->setFont(labelFont);

    label_tarefas->setAlignment(Qt::AlignRight);
    label_atrasos->setAlignment(Qt::AlignRight);
    label_max->setAlignment(Qt::AlignRight);

    layout->addWidget(label_tarefas, 0, 0);
    layout->addWidget(label_atrasos, 1, 0);
    layout->addWidget(label_max, 2, 0);

    s_tarefas->setAlignment(Qt::AlignLeft);
    s_atrasos->setAlignment(Qt::AlignLeft);
    s_max->setAlignment(Qt::AlignLeft);

    layout->addWidget(s_tarefas, 0, 1);
    layout->addWidget(s_atrasos, 1, 1);
    layout->addWidget(s_max, 2, 1);

    new_window->setWindowTitle("Detalhes do Calendário");
    new_window->setLayout(layout);
    new_window->setFixedSize(400, 250);
    new_window->show();

    QEventLoop loop;
    connect(this, SIGNAL(destroyed()), & loop, SLOT(quit()));
    loop.exec();
}

void window::tela_atualizar_data_inicio() {
    new_window = new QWidget(nullptr);
    new_window->setFixedSize(600, 400);
    new_window->setWindowTitle("Adicionar Tarefa");

    QFont buttonFont("Times", 20);
    QFont labelFont("Times", 20, QFont::Bold);
    QFont campoFont("Times", 20);
    int button_size = 580;
    int maximum_label_height = 30;

    calendar = new QCalendarWidget();
    calendar->setMinimumDate(QDate::currentDate());
    calendar->setGridVisible(true);

    QVBoxLayout *tela = new QVBoxLayout();

    QLabel *label = new QLabel("Insira a nova data");
    label->setAlignment(Qt::AlignCenter);
    label->setMaximumHeight(maximum_label_height);
    label->setFont(labelFont);

    QPushButton *button = new QPushButton("Enviar");
    button->setFixedWidth(button_size);
    button->setFont(buttonFont);
    connect(button, &QPushButton::clicked, this, &window::atualizar_data_inicio);

    alert = new QLabel("");
    alert->setAlignment(Qt::AlignCenter);
    alert->setMaximumHeight(15);

    tela->addWidget(label);
    tela->addWidget(calendar);
    tela->addWidget(button);
    new_window->setLayout(tela);
    new_window->show();

    QEventLoop loop;
    connect(this, SIGNAL(destroyed()), & loop, SLOT(quit()));
    loop.exec();
}

void window::atualizar_data_inicio() {
    data_inicio = calendar->selectedDate();
    data_label->setText("INÍCIO : " + this->data_inicio.toString(Qt::SystemLocaleDate));
    atualizar_lista(data_inicio);
    new_window->close();
}

void window::atualizar_lista(QDate inicio) {
    QDate last_finished = inicio;
    int lateness=0;
    this->qtd_atrasos = 0;

    sort(jobs.begin(), jobs.end());
    lista->clear();

    for(auto& j : jobs) {
        QDate temp = last_finished.addDays(j.tempo);

        j.inicio = last_finished;
        j.termino = temp;

        lista->addItem(QString::fromStdString(j.nome) + "\n" +
                       "Início: " +last_finished.toString(Qt::SystemLocaleDate) + "\n" +
                       "Término: " + temp.toString(Qt::SystemLocaleDate) + "\n" +
                       "Entrega: " + j.deadline.toString(Qt::SystemLocaleDate) + "\n");

        last_finished = temp;

        int dif = max(int(j.deadline.daysTo(last_finished)), 0);

        if (lateness < dif)
            lateness = dif;

        if(j.deadline < j.termino)
            this->qtd_atrasos++;
    }

    tarefa_label->setText("TAREFAS : " + QString::number(this->jobs.size()));

    this->atraso_maximo = lateness;
}

void window::validar_busca_tarefa() {
    QString nome = campo_texto1->text();
    if(nome == "") {
        alert->setText("Nome não pode ser em branco");
        return;
    }

    this->achado = -1;

    for(size_t i = jobs.size(); i--; ) {
        if(QString::fromStdString(jobs[i].nome) == nome) {
            this->achado = i;
            break;
        }
    }

    if(this->achado == -1) {
        alert->setText("Tarefa não encontrada");
        return;
    }
}

void window::tela_aleatorio() {
    new_window = new QWidget(nullptr);
    new_window->setFixedSize(500, 300);
    new_window->setWindowTitle("Calendário Aleatório");

    QFont buttonFont("Times", 20);
    QFont labelFont("Times", 20, QFont::Bold);
    QFont campoFont("Times", 20);
    int button_size = 480;
    int maximum_label_height = 30;

    campo_texto1 = new QLineEdit();
    campo_texto1->setFont(campoFont);
    campo_texto1->setValidator(new QIntValidator());

    QVBoxLayout *tela = new QVBoxLayout();

    QLabel *label = new QLabel("Insira a quantidade de Tarefas");
    label->setAlignment(Qt::AlignCenter);
    label->setMaximumHeight(maximum_label_height);
    label->setFont(labelFont);

    QPushButton *button = new QPushButton("Enviar");
    button->setFixedWidth(button_size);
    button->setFont(buttonFont);
    connect(button, &QPushButton::clicked, this, &window::calendario_aleatorio);

    alert = new QLabel("");
    alert->setAlignment(Qt::AlignCenter);
    alert->setMaximumHeight(15);

    progressBar = new QProgressBar();
    progressBar->setFixedHeight(40);

    tela->addWidget(label);
    tela->addWidget(campo_texto1);
    tela->addWidget(button);
    tela->addWidget(progressBar);
    tela->addWidget(alert);
    new_window->setLayout(tela);
    new_window->show();

    QEventLoop loop;
    connect(this, SIGNAL(destroyed()), & loop, SLOT(quit()));
    loop.exec();
}

void window::calendario_aleatorio() {
    int qtd = campo_texto1->text().toInt();
    if(qtd < 1) {
        alert->setText("Numero deve ser 1 ou maior");
        return;
    }

    random_device rd;
    mt19937_64 mt(rd());

    uniform_int_distribution<int> dist_verbos(0, N_VERBOS-1);
    uniform_int_distribution<int> dist_nomes(0, N_NOMES-1);
    uniform_int_distribution<int> dist_locais(0, N_LOCAIS-1);
    uniform_int_distribution<int> dist_tempos(1, 5);

    jobs.clear();
    jobs.reserve(qtd);

    progressBar->setMinimum(0);
    progressBar->setMaximum(qtd);
    progressBar->setValue(0);

    int um_perc = qtd/100 ? qtd/100 : 1;

    alert->setText("Criando Tarefas");
    QDate temp = data_inicio;

    for(int i = qtd; i--; ) {
        temp = temp.addDays(dist_tempos(mt));
        jobs.emplace_back(verbos[dist_verbos(mt)] + " " + nomes[dist_nomes(mt)] + " " + locais[dist_locais(mt)],
                          dist_tempos(mt),
                          temp);
        if(!((qtd-i)%um_perc)) progressBar->setValue(qtd-i);
    }

    this->atualizar_lista(data_inicio);

    new_window->close();
}
