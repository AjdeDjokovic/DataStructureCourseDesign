#include "chessboard.h"

Chessboard::Chessboard(int k,int defectRow,int defectColumn)
{
    this->size = pow(2,k);
    this->defectRow = defectRow;
    this->defectColumn = defectColumn;
    title = 1;
    colorMax = 4;

    board = new int*[size];
    for(int i = 0;i < size;i++)
    {
        board[i] = new int[size];
        memset(board[i],0,sizeof (board[i][0]) * size);
    }
}

Chessboard::~Chessboard()
{
    for(int i = 0;i < size;i++)
        delete[] board[i];
    delete[] board;

    for(int i = 0;i <= title;i++)
        delete[] connectMap[i];
    delete[] connectMap;

    delete[] color;

    delete[] colorLess;
}


void Chessboard::titleBoard(int topRow, int topColumn, int defectRow, int defectColumn, int size){
   //topRow       表示棋盘左上角方格的行号
   //topColumn  表示棋盘左上角方格的列号
   //defectRow  表示残缺方格的行号
   //defectColumn 表示残缺方格的列号
   //size  表示棋盘一个边的长度
   if(size == 1) return;
   int titleToUse = title++;
   int quadrantSize = size/2;
   
    //覆盖左上角象限
    if(defectRow < topRow + quadrantSize && defectColumn < topColumn + quadrantSize){
           //残缺方格属于这个象限
            titleBoard(topRow, topColumn, defectRow,defectColumn ,  quadrantSize );
    }else{
        //这个象限无残缺方格
        //在右下角放置一个三格板
        board[topRow + quadrantSize - 1][topColumn + quadrantSize - 1] = titleToUse;
         //覆盖其余的方格
         titleBoard(topRow, topColumn, topRow + quadrantSize - 1, topColumn + quadrantSize - 1, quadrantSize);
    }

//剩余三个象限的覆盖代码类似
    //覆盖右上角象限
    if(defectRow < topRow + quadrantSize && defectColumn >= topColumn + quadrantSize){
           //残缺方格属于这个象限
            titleBoard(topRow, topColumn + quadrantSize, defectRow,defectColumn ,  quadrantSize );
    }else{
        //这个象限无残缺方格
        //在右下角放置一个三格板
        board[topRow + quadrantSize - 1][topColumn + quadrantSize] = titleToUse;
         //覆盖其余的方格
         titleBoard(topRow, topColumn + quadrantSize, topRow + quadrantSize - 1, topColumn + quadrantSize, quadrantSize);
    }

    //覆盖左下角象限

    if(defectRow >= topRow + quadrantSize && defectColumn < topColumn + quadrantSize)
            titleBoard(topRow + quadrantSize, topColumn, defectRow, defectColumn, quadrantSize);
    else
    {
        board[topRow + quadrantSize][topColumn + quadrantSize - 1] = titleToUse;
        titleBoard(topRow + quadrantSize, topColumn, topRow + quadrantSize, topColumn + quadrantSize - 1, quadrantSize);
    }

    //4右下角区域，类上
        if(defectRow >= topRow + quadrantSize && defectColumn >= topColumn + quadrantSize)
            titleBoard(topRow + quadrantSize, topColumn + quadrantSize, defectRow, defectColumn, quadrantSize);
        else
        {
            board[topRow + quadrantSize][topColumn + quadrantSize] = titleToUse;
            titleBoard(topRow + quadrantSize, topColumn + quadrantSize, topRow + quadrantSize, topColumn + quadrantSize, quadrantSize);
        }
}

void Chessboard::getColorMap()
{
    titleBoard(0,0,defectRow,defectColumn,size);
    title--;

    connectMap = new int*[title + 1];
    for(int i = 0;i <= title;i++)
    {
        connectMap[i] = new int[title + 1];
        memset(connectMap[i],0,sizeof (connectMap[i][0]) * (title + 1));
    }

    getConnectMap();

    color = new int[title + 1];
    memset(color,0,sizeof (color[0]) * (title + 1));

    colorLess = new int[title + 1];
    memset(colorLess,0,sizeof (colorLess[0]) * (title + 1));

//    inputColor(0,color,0,0,0);
    inputColor(1,color,0);
}

void Chessboard::getConnectMap()
{
    for(int i = 0;i < size;i++)
        for(int j = 0;j < size;j++)
        {
            for(int p = 0;p < 4;p++)
            {
                if(i + position[p][0] >= 0 && i + position[p][0] < size && j + position[p][1] >= 0 && j + position[p][1] < size && board[i][j] != board[i + position[p][0]][j + position[p][1]])
                {
                    connectMap[board[i][j]][board[i + position[p][0]][j + position[p][1]]] = 1;
                    connectMap[board[i + position[p][0]][j + position[p][1]]][board[i][j]] = 1;
                }
            }
        }
}

//void Chessboard::inputColor(int n,int *color,int col,int sign,int count)
//{
//    if(col == 0)
//    {//未着色 ，则着色
//        for(int i=1;i<=4;i++)
//        {//颜色1-4
//            if(i >= colorMax)
//                return;
//            color[n] = i;
//            if(i > count)
//                inputColor(n,color,1,0,i);//验证着此色是否可行
//            else
//                inputColor(n,color,1,0,count);//验证着此色是否可行
//        }
//    }
//    else if(col==1 && sign==0){//已着色但未验证 ，则验证此位
//        for(int i=0;i<=title;i++)
//            if(connectMap[n][i]==1 && color[n]==color[i])
//                return;
//        inputColor(n,color,1,1,count);//此色可用，sign置为1
//    }
//    else if(col==1 && sign==1){//着色且此色可用
//        if(n<title)//进行下一位
//            inputColor(n+1,color,0,0,count);
//        else if(n==title && count < colorMax){//若此位是最后一位，则打印输出
//            for(int i=0;i<=title;i++)
//                colorLess[i] = color[i];
//            colorMax = count;
//        }
//    }
//}

void Chessboard::inputColor(int n,int *color,int count)
{
    if(n == title + 1)
    {//若此位是最后一位，则打印输出
        if(count < colorMax)
        {
            for(int i=0;i<=title;i++)
                colorLess[i] = color[i];
            colorMax = count;
        }
        return;
    }
    for(int i=1;i<=4;i++)
    {//颜色1-4
        if(i >= colorMax)
            return;
        bool flag = true;
        for(int j=1;j<=title;j++)
            if(connectMap[n][j] == 1 && i == color[j])
                flag = false;
        if(flag)
        {
            color[n] = i;
            if(i > count)
                inputColor(n + 1,color,i);//验证着此色是否可行
            else
                inputColor(n + 1,color,count);//验证着此色是否可行
        }
    }
}


