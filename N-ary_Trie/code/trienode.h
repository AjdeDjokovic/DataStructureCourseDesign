#ifndef TRIENODE_H
#define TRIENODE_H

#include <iostream>
#include <cstring>
#include <vector>
const int MaxBranchNum = 26;

class TrieNode
{
public:
    char* word; //节点表示的单词
    int count;  //单词出现的次数
    TrieNode* nextBranch[MaxBranchNum];//指向26个字符节点的指针
    std::vector<int> v;
    int height;
    char c;

    TrieNode() : word(NULL),count(0),v(),height(0)
    {
        memset(nextBranch,NULL,sizeof(TrieNode*) * MaxBranchNum);
    }
};

//class TrieNode
//{
//public:
//    char* word;                         //节点表示的单词
//    int count;                          //单词出现的次数
//    TrieNode* nextBranch[MaxBranchNum]; //指向26个字符节点的指针
//    std::vector<int> v;                 //单词出现行号
//    int height;
//    char c;
//};

#endif // TRIENODE_H
