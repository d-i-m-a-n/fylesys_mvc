#ifndef COMPUTEFILESSIZEFUNCTIONS_H
#define COMPUTEFILESSIZEFUNCTIONS_H

#include <QList>
#include <QString>

#include "entry.h"

QList<Entry> computeFilesSize(const QString &path);

QList<Entry> computeExtensionsSize(const QString &path);

double computeDirFilesSize(const QString &path);

double computeDirectorySize(const QString &path);

#endif // COMPUTEFILESSIZEFUNCTIONS_H
