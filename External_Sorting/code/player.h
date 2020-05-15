#ifndef PLAYER_H
#define PLAYER_H
#include <qglobal.h>

struct player
{
   qint64 key;

   bool operator<=(const player b) const
   {
       if(key > b.key)
           return false;
       else
           return true;
   }
};


#endif // PLAYER_H
