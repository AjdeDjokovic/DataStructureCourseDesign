#include "trie.h"

Trie::Trie()
{
    pRoot = new TrieNode();//注意字典树的根不存放字符
}

Trie::~Trie()
{
    Destory(pRoot);
    pRoot = NULL;
}

/*插入一个单词*/
void Trie::Insert(const char* str,int row)
{
    assert(NULL != str);
    int index;
    TrieNode* pLoc = pRoot;
    for (int i = 0;str[i];i++)
    {
        index = str[i] - 'a';//如果区分大小写，可以扩展

        if(index < 0 || index > MaxBranchNum)//不执行插入
        {
            return;
        }

        if(pLoc->height + i < strlen(str))
            pLoc->height = strlen(str) - i;

        if (NULL == pLoc->nextBranch[index])//该单词的前缀不存在，要生成该结点
        {
            pLoc->nextBranch[index] = new TrieNode();
            pLoc->nextBranch[index]->c = str[i];
        }
        pLoc = pLoc->nextBranch[index];
    }
    if (NULL != pLoc->word)//单词已经出现过
    {
        pLoc->v.push_back(row);
        pLoc->count++;
        return;
    }
    else    //单词没有出现过，应该插入单词
    {
        pLoc->count++;
        pLoc->word = new char[strlen(str) + 1];
        assert(NULL != pLoc->word);
        strcpy(pLoc->word,str);
        pLoc->v.push_back(row);
    }
}



//void Trie::Insert(const char* str,int row)
//{
//    assert(NULL != str);
//    int index;                                       //数组
//    TrieNode* pLoc = pRoot;
//    for (int i = 0;str[i];i++)
//    {
//        index = str[i] - 'a';                        //如果区分大小写，可以扩展
//        if(index < 0 || index > MaxBranchNum) return;//不执行插入
//        if (NULL == pLoc->nextBranch[index])         //该单词的前缀不存在，要生成该结点
//        {
//            pLoc->nextBranch[index] = new TrieNode();
//            pLoc->nextBranch[index]->c = str[i];
//        }
//        pLoc = pLoc->nextBranch[index];
//    }
//    if (NULL != pLoc->word)                          //节点已经存在
//    {
//        pLoc->v.push_back(row);
//        pLoc->count++;
//        return;
//    } else                                           //节点未建立，初始化节点
//    {
//        pLoc->count++;
//        pLoc->word = new char[strlen(str) + 1];
//        assert(NULL != pLoc->word);
//        strcpy(pLoc->word,str);
//        pLoc->v.push_back(row);
//    }
//}




/*查找一个单词，如果存在该单词，则返回其出现次数*/
//TrieNode* Trie::Search(const char* str)
//{
//    assert(str != NULL);
//    int index = -1;;
//    TrieNode* pLoc = pRoot;
//    while(pLoc && *str)
//    {
//        index = *str - 'a';//如果区分大小写，可以扩展

//        if(index < 0 || index > MaxBranchNum)//不是一个单词，不执行插入
//        {
//            return NULL;
//        }

//        pLoc = pLoc->nextBranch[index];
//        str++;
//    }
//    if (pLoc && pLoc->word)//条件成立，找到该单词
//        return pLoc;
//    return NULL;
//}

/*查找一个单词，如果存在该单词，则返回其出现次数*/
TrieNode* Trie::Search(const char* str)
{
    assert(str != NULL);
    int index = -1;
    TrieNode* pLoc = pRoot;
    while(pLoc && *str)
    {
        if(index < 0 || index > MaxBranchNum) //不是一个单词，不执行插入
        {
            return NULL;
        }
        pLoc = pLoc->nextBranch[index];      //转换当前节点
        str++;
    }
    if (pLoc && pLoc->word)                  //条件成立，找到该单词
        return pLoc;
    return NULL;                             //没有找到
}

TrieNode* Trie::SearchNode(const char* str)
{
    assert(str != NULL);
    int index = -1;;
    TrieNode* pLoc = pRoot;
    while(pLoc && *str)
    {
        index = *str - 'a';//如果区分大小写，可以扩展

        if(index < 0 || index > MaxBranchNum)//不是一个单词，不执行插入
        {
            return NULL;
        }

        pLoc = pLoc->nextBranch[index];
        str++;
    }
    if (pLoc)//条件成立，找到该单词
        return pLoc;
    return NULL;
}

//bool Trie::Remove(const char* str)
//{
//    assert(NULL != str);
//    int index = -1;;
//    TrieNode* pLoc = pRoot;
//    while(pLoc && *str)
//    {
//        index = *str - 'a';//如果区分大小写，可以扩展

//        if(index < 0 || index > MaxBranchNum)//不是一个单词，不执行插入
//        {
//            return false;
//        }

//        pLoc = pLoc->nextBranch[index];
//        str++;
//    }
//    if (pLoc && pLoc-> word)//条件成立，找到该单词
//    {
//        Destory(pLoc);
//        return true;
//    }
//    return false;
//}

bool Trie::Remove(const char* str)
{
    assert(NULL != str);
    int index = -1;;
    TrieNode* pLoc = pRoot;
    TrieNode* parent = NULL;
    while(pLoc && *str)
    {
        index = *str - 'a';//如果区分大小写，可以扩展

        if(index < 0 || index > MaxBranchNum)//不是一个单词，不执行插入
        {
            return false;
        }
        parent = pLoc;
        pLoc = pLoc->nextBranch[index];
        str++;
    }
    if (pLoc && pLoc-> word)//条件成立，找到该单词
    {
        Destory(parent->nextBranch[*(str - 1) - 'a']);
        parent->nextBranch[*(str - 1) - 'a'] = NULL;
        return true;
    }
    return false;
}

//bool Trie::Remove(const char* str)
//{
//    assert(NULL != str);
//    int index = -1;
//    TrieNode* pLoc = pRoot;
//    TrieNode* parent = NULL;
//    while(pLoc && *str)                      //依次遍历str
//    {
//        if(index < 0 || index > MaxBranchNum)//不是一个字母
//            return false;
//        parent = pLoc;
//        pLoc = pLoc->nextBranch[index];      //转换当前节点
//        str++;
//    }
//    if (pLoc && pLoc-> word)                 //条件成立，删除该单词
//    {
//        Destory(parent->nextBranch[*(str - 1) - 'a']);
//        parent->nextBranch[*(str - 1) - 'a'] = NULL;
//        return true;
//    }
//    return false;
//}


//void Trie::PrintALL()
//{
//    Print(pRoot);
//}

//void Trie::PrintPre(const char* str)
//{
//    assert(str != NULL);
//    int i = 0;
//    int index = -1;;
//    TrieNode* pLoc = pRoot;
//    while(pLoc && *str)
//    {
//        index = *str - 'a';//如果区分大小写，可以扩展

//        if(index < 0 || index > MaxBranchNum)//不是一个单词，不执行插入
//        {
//            return;
//        }

//        pLoc = pLoc->nextBranch[index];
//        str++;
//    }
//    if (pLoc)//条件成立，找到该单词
//    {
//        Print(pLoc);
//    }
//}

///*按照字典顺序输出以pRoot为根的所有的单词*/
void Trie::sortPre(TrieNode* pRoot,std::vector<SortItem>& v)
{
    //输出单词
    if (NULL != pRoot->word)
    {
        v.push_back(SortItem(pRoot->word,pRoot->count));
    }
    //递归处理分支
    for (int i = 0;i < MaxBranchNum;i++)
        if(pRoot->nextBranch[i] != NULL)
            sortPre(pRoot->nextBranch[i],v);
}

/*销毁trie树*/
void Trie::Destory(TrieNode * pRoot)
{
    if (NULL == pRoot)
    {
        return;
    }
    for (int i = 0;i < MaxBranchNum;i++)
    {
        Destory(pRoot->nextBranch[i]);
    }
    //销毁单词占得空间
    if (NULL != pRoot->word)
    {
        delete []pRoot->word;
        pRoot->word = NULL;
    }
    delete pRoot;//销毁结点
    pRoot = NULL;
}

//int main()
//{
//    Trie t;
//    string str;
//    int count = -1;
//    ifstream in("word.txt");
//    //把单词输入字典树
//    while(in >> str)
//    {
//        transform(str.begin(),str.end(),str.begin(),tolower);//大写变小写
//        t.Insert(str.c_str());
//    }
//    //查找
//    bool isFind = t.Search("the",count);
//    if (isFind)
//    {
//        cout<<"存在the,出现次数："<<count<<endl;
//    }
//    else
//    {
//        cout<<"不存在the!"<<endl;
//    }
//    //输出
//    t.PrintALL();
//    //删除
//    bool isDel = t.Remove("the");
//    if (isDel)
//    {
//        cout<<"删除成功!"<<endl;
//    }
//    else
//    {
//        cout<<"删除失败!"<<endl;
//    }
//    //输出以w开头的单词
//    t.PrintPre("w");
//    cout<<endl;
//    system("pause");
//}
