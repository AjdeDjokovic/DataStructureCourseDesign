#include "threadcolormap.h"

threadColorMap::threadColorMap()
{

}

void threadColorMap::set(Chessboard * chessboard,int k,int row,int col)
{
    this->chessboard = chessboard;
    this->k = k;
    this->row = row;
    this->col = col;
}

void threadColorMap::run()
{
    chessboard->getColorMap();
    while(chessboard->colorMax > 4)
    {
        delete chessboard;
        chessboard = new Chessboard(k,row,col);
        chessboard->getColorMap();
    }

    emit result();
    quit();
}
