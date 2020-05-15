#ifndef SORTITEM_H
#define SORTITEM_H

class SortItem
{
public:
    char* word;
    int count;
    SortItem(char* word,int count)
    {
        this->word = word;
        this->count = count;
    }
    SortItem()
    {

    }

    bool operator<(const SortItem a) const
    {
        if(count >= a.count)
            return true;
        else
            return false;
    }
};

#endif // SORTITEM_H
