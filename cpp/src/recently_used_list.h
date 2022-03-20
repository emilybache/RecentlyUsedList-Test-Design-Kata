#ifndef SAMPLE_H
#define SAMPLE_H

#include <vector>
#include <string>

using namespace std;

class RecentlyUsedList
{
public:
    RecentlyUsedList();

    void insert(const string& item);
    const vector<string>& getContents() const;

private:
    vector<string>* _contents;
};

#endif //SAMPLE_H
