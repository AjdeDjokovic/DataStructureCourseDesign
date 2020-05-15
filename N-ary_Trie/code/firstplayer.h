#ifndef FIRSTPLAYER_H
#define FIRSTPLAYER_H
#include <qglobal.h>
#include <QString>
struct firstPlayer
{
    QString word;
    int count;

//   operator int () const {return key;}
   bool operator<=(const firstPlayer a) const
   {
       if(count >= a.count)
           return true;
       else
           return false;
   }
   bool operator<(const firstPlayer a) const
   {
       if(count >= a.count)
           return true;
       else
           return false;
   }
};


#endif // FIRSTPLAYER_H
