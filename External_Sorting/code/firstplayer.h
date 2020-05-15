#ifndef FIRSTPLAYER_H
#define FIRSTPLAYER_H
#include <qglobal.h>
struct firstPlayer
{
   int queue;
   qint64 key;

//   operator int () const {return key;}
   bool operator<=(const firstPlayer b) const
   {
       if(queue < b.queue)
           return true;
       if(queue > b.queue)
           return false;
       if(key > b.key)
           return false;
       else
           return true;
   }
   bool operator<(const firstPlayer b) const
   {
       if(key > b.key)
           return false;
       else
           return true;
   }
};


#endif // FIRSTPLAYER_H
