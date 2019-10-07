#ifndef JOB_H
#define JOB_H

#include <iostream>
#include <QDate>

using namespace std;

class Job {
public:
    string nome;
    int tempo;
    QDate deadline;
    QDate inicio;
    QDate termino;
    Job(const string& n, const int& t, const QDate& d) : nome(n), tempo(t), deadline(d) {}

    bool operator<(const Job& x) const {
        return deadline < x.deadline;
    }
};

#endif // JOB_H
