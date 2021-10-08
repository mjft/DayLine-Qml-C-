#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "QObject"
#include "Windows.h"

class Functions:public QObject
{
    Q_OBJECT
public:
    Functions(QObject *parent = nullptr);

public slots:
    bool isFileExplorer(int x,int y);
    std::string getPath(int x,int y,QString fileName);
    void saveFile(std::string path,QString text);
};

#endif // FUNCTIONS_H
