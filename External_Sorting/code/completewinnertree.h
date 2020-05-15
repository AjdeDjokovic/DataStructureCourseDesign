#ifndef COMPLETEWINNERTREE_H
#define COMPLETEWINNERTREE_H


#include <iostream>
#include "winnertree.h"
//#include "myExceptions.h"
#include "player.h"
#include "firstplayer.h"

template<class T>
class completeWinnerTree : public winnerTree<T>
{
   public:
      completeWinnerTree(T *thePlayer, int theNumberOfPlayers);
      ~completeWinnerTree() {delete [] tree;}
      void initialize(T*, int);
      int winner() const//返回赢者树的根节点。
         {return tree[1];}
      int winner(int i) const//返回第i个节点的胜者
         {return (i < numberOfPlayers) ? tree[i] : 0;}
         // return winner of match at node i
      void rePlay(int);
      void output() const;
      T *player;
   private:
      int lowExt;           // lowest-level external nodes
      int offset;           // 2^log(n-1) - 1
      int * tree;            // array for winner tree
      int numberOfPlayers;            // array of players
      void play(int, int, int);
};


template<class T>
completeWinnerTree<T>::completeWinnerTree(T thePlayer[], int theNumberOfPlayers)
{
    tree = NULL;
    initialize(thePlayer, theNumberOfPlayers);
}

template<class T>
void completeWinnerTree<T>::play(int p, int leftChild, int rightChild)
{// play matches beginning at tree[p]
 // leftChild is left child of p
 // rightChild is right child of p
//如果左节点的数据较小则左节点晋级。
   tree[p] = (player[leftChild] <= player[rightChild]) ?
                   leftChild : rightChild;

   // more matches possible if at right child
   while (p % 2 == 1 && p > 1)//如果当前节点是右节点，且不是根节点，那么继续进行比赛。
   {// at a right child
      tree[p / 2] = (player[tree[p - 1]] <= player[tree[p]]) ?
                       tree[p - 1] : tree[p];
      p /= 2;  // go to parent
   }
}


template<class T>
void completeWinnerTree<T>::initialize(T *thePlayer,int theNumberOfPlayers)
{// Create winner tree for thePlayer[1:numberOfPlayers].
//比赛参与者最少2个人否则报错
   int n = theNumberOfPlayers;
   if (n < 2)
       return;
//      throw illegalParameterValue("must have at least 2 players");


   player = thePlayer;//获取外节点数组。
   numberOfPlayers = n;
   delete [] tree;//初始化树节点，因为第0位置不放数据，所以实际大小为n-1.
   tree = new int[n];//

   // compute  s = 2^log (n-1)
   int i, s;//计算内部节点最左边的节点编号，下面采取寻访方式计算s，非常巧妙
   for (s = 1; 2 * s <= n - 1; s += s);

   lowExt = 2 * (n - s);//计算最低层外部节点的个数
   offset = 2 * s - 1;

   // play matches for lowest-level external nodes
   for (i = 2; i <= lowExt; i += 2)//首先进行最底层外部节点的比赛，i从2开始且每次+2是为了每次都是从右子节点开始进行比赛
      play((offset + i) / 2, i - 1, i);

   // handle remaining external nodes
   if (n % 2 == 1)//如果倒数第二层最左边的元素为某个父节点的右节点，则进行如下处理，即比赛。
   {// special case for odd n, play internal and exteral node
      play(n/2, tree[n - 1], lowExt + 1);
      i = lowExt + 3;//然后从lowExt+3即倒数第二层外部节点的右儿子开始比赛
   }
   else i = lowExt + 2;//否则右儿子为lowExt+2

   // i is left-most remaining external node
   for (; i <= n; i += 2)//然后开始处理倒数第二层其他外部节点。
      play((i - lowExt + n - 1) / 2, i - 1, i);//play每次都会处理到上层的左节点为止，然后再去处理下一个右节点。
}

template<class T>
void completeWinnerTree<T>::rePlay(int thePlayer)
{// Replay matches for player thePlayer.
   int n = numberOfPlayers;
   if (thePlayer <= 0 || thePlayer > n)//改变的选手必须要在范围内。
       return;
//      throw illegalParameterValue("Player index is illegal");

   int matchNode,       // node where next match is to be played需要重赛的父节点
       leftChild,       // left child of matchNode该父节点的左孩子
       rightChild;      // right child of matchNode右孩子

   // find first match node and its children
   if (thePlayer <= lowExt)//如果改变的参数在最低层
   {// begin at lowest level
      matchNode = (offset + thePlayer) / 2;//要求重赛的父节点
      leftChild = 2 * matchNode - offset;//及其子节点
      rightChild = leftChild + 1;
   }
   else
   {
      matchNode = (thePlayer - lowExt + n - 1) / 2;//如果要求重赛的选手在倒数第二层的外部节点。
      if (2 * matchNode == n - 1)//如果要求重赛的选手在倒数第二层与倒数第一层的交界点处
      {
         leftChild = tree[2 * matchNode];
         rightChild = thePlayer;
      }
      else//否则在倒数第二层的外部节点处。
      {
         leftChild = 2 * matchNode - n + 1 + lowExt;
         rightChild = leftChild + 1;
      }
   }

   tree[matchNode] = (player[leftChild] <= player[rightChild])//重赛
                            ? leftChild : rightChild;

   // special case for second match
   if (matchNode == n - 1 && n % 2 == 1)//比赛节点为最底层内部节点，并且倒数第二层最左边的元素为某个父节点的右节点。
   {
      matchNode /= 2;   // move to parent
      tree[matchNode] = (player[tree[n - 1]] <=
                         player[lowExt + 1]) ?
                        tree[n - 1] : lowExt + 1;
   }

   // play remaining matches
   matchNode /= 2;  // move to parent
   for (; matchNode >= 1; matchNode /= 2)//依次往上进行重赛直到主节点。
      tree[matchNode] = (player[tree[2 * matchNode]] <=
                         player[tree[2 * matchNode + 1]]) ?
                        tree[2 * matchNode] : tree[2 * matchNode + 1];
}


#endif // COMPLETEWINNERTREE_H
