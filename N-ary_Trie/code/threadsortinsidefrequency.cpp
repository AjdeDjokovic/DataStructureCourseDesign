#include "threadsortinsidefrequency.h"

threadSortInsideFrequency::threadSortInsideFrequency()
{

}

void threadSortInsideFrequency::set(Trie* trie,TrieNode * node)
{
    this->trie = trie;
    this->node = node;
}

void threadSortInsideFrequency::run()
{
    std::vector<SortItem> v;
    trie->sortPre(node,v);
    int numberCount = v.size();
    int now = 0;
    sort(v.begin(),v.end());
    QString str;
    for (std::vector<SortItem>::iterator i = v.begin();i != v.end();i++)
    {
        str += QString(QLatin1String(i->word)) + ":" + QString::number(i->count) + "\t";
        now++;

        double f = 0.1;
        if(now / numberCount > f || now == numberCount)
        {
            emit update((int)(now * 100/ numberCount));
            f += 0.1;
        }
    }
    emit result(str);
    quit();
}
