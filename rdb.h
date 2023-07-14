#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <list>
#include <typeinfo>
using namespace std;

class Relation;
class Record;
class Attr;

typedef struct DNFformula{
    list<list<tuple<string, char, Attr*>>> ops;
} DNFformula;

class Attr
{
public:
    virtual bool operator==(const Attr &right) = 0;
    virtual bool operator!=(const Attr &right) = 0;
    virtual bool operator<=(const Attr &right) = 0;
    virtual bool operator>=(const Attr &right) = 0;
    virtual bool operator<(const Attr &right) = 0;
    virtual bool operator>(const Attr &right) = 0;
    virtual ~Attr() {}
};

class IntAttr : public Attr
{
public:
    int value;
    IntAttr(int v) : value(v) {}
    bool operator==(const Attr &right);
    bool operator!=(const Attr &right);
    bool operator<=(const Attr &right);
    bool operator>=(const Attr &right);
    bool operator<(const Attr &right);
    bool operator>(const Attr &right);
};

class StringAttr : public Attr
{
public:
    string value;
    StringAttr(string v) : value(v) {}
    bool operator==(const Attr &right);
    bool operator!=(const Attr &right);
    bool operator<=(const Attr &right);
    bool operator>=(const Attr &right);
    bool operator<(const Attr &right);
    bool operator>(const Attr &right);
};

class floatAttr : public Attr
{
public:
    float value;
    floatAttr(float v) : value(v) {}
    bool operator==(const Attr &right); 
    bool operator!=(const Attr &right); 
    bool operator<=(const Attr &right); 
    bool operator>=(const Attr &right);
    bool operator<(const Attr &right);
    bool operator>(const Attr &right);
};
class Record
{
public:
    vector<Attr *> attrptr;
    Record(vector<Attr *> attrptr);
    void addAttr(Attr *attr);
};
class Relation
{
    public:
    int nattr, nrecs;
    vector<string> attrnames; 
    vector<int> attrinds;     
    list<Record *> recs;
    void print();
    void push_record(Record *rec);
    Relation *difference(Relation *R1, Relation *R2);
    Relation *projection(Relation *R1, list<string> projectattrs);
    Relation *cartesianproduct(Relation *R1, Relation *R2);
    Relation *difference(Relation *R1, string s1, string s2);
    Relation *union_op(Relation *R1, Relation *R2);
    Relation *Selection(Relation *R1, DNFformula *f);
    Relation *naturaljoin(Relation *R1, Relation *R2, list<string> joinattr);
};
