#ifndef TRIE_H
#define TRIE_H

#include <trienode.h>
#include <assert.h>
#include "sortitem.h"

class Trie
{
public:
    Trie();
    ~Trie();
    void Insert(const char* str,int row);//插入字符串str
    TrieNode* Search(const char* str);
    TrieNode* SearchNode(const char* str);//查找字符串str，并返回出现的次数
    bool Remove(const char* str);//删除字符串str
    void PrintALL();//打印trie树中所有的结点
    void PrintPre(const char* str);//打印以str为前缀的单词
    void sortPre(TrieNode* pRoot,std::vector<SortItem>&);
    TrieNode* pRoot;
    void Destory(TrieNode* pRoot);
};

//class Trie
//{
//public:
//    TrieNode* pRoot;                                      //根节点
//    Trie();
//    ~Trie();
//    void Insert(const char* str,int row);                 //插入字符串str节点
//    TrieNode* Search(const char* str);                    //查找并返回字符串str节点
//    bool Remove(const char* str);                         //删除字符串str节点
//    void sortPre(TrieNode* pRoot,std::vector<SortItem>&); //先序遍历
//    void Destory(TrieNode* pRoot);
//};

#endif // TRIE_H
