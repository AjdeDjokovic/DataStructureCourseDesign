#ifndef THREADCOLORMAP_H
#define THREADCOLORMAP_H

#include "chessboard.h"
#include <QThread>

class threadColorMap : public QThread
{
    Q_OBJECT
public:
    threadColorMap();
    void set(Chessboard *,int,int,int);
protected:
    void run() Q_DECL_OVERRIDE;
private:
    Chessboard * chessboard;
    int k;
    int row;
    int col;
signals:
    void result();
};

#endif // THREADCOLORMAP_H
