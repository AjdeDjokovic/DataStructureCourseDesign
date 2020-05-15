#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <math.h>
#include <cstring>
#include <set>
#define MAX 32

class Chessboard
{
    int title;
    int defectRow;
    int defectColumn;
    int position[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
    int **connectMap;
    int *color;
public:
    int size;
    int **board;
    int *colorLess;
    int colorMax;
    Chessboard(int k,int defectRow,int defectColumn);
    ~Chessboard();
    void titleBoard(int topRow, int topColumn, int defectRow, int defectColumn, int size);
    void getColorMap();
    void getConnectMap();
//    void inputColor(int n,int *color,int col,int sign,int count);
    void inputColor(int n,int *color,int count);
};

#endif // CHESSBOARD_H
