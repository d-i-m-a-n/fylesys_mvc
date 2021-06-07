#ifndef ENTRY_H
#define ENTRY_H

#include <QString>

class Entry
{
public:
    Entry(QString name, double sizePercent, double size);

    QString m_name;

    double m_sizePercent;
    double m_size;
};

#endif // ENTRY_H
