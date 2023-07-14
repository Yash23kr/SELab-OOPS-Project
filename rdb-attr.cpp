#include "rdb.h"

bool IntAttr::operator==(const Attr &right) { return value == static_cast<const IntAttr &>(right).value; }
bool IntAttr::operator!=(const Attr &right) { return value != static_cast<const IntAttr &>(right).value; }
bool IntAttr::operator<=(const Attr &right) { return value <= static_cast<const IntAttr &>(right).value; }
bool IntAttr::operator>=(const Attr &right) { return value >= static_cast<const IntAttr &>(right).value; }
bool IntAttr::operator<(const Attr &right) { return value < static_cast<const IntAttr &>(right).value; }
bool IntAttr::operator>(const Attr &right) { return value > static_cast<const IntAttr &>(right).value; }

bool StringAttr::operator==(const Attr &right) { return value == static_cast<const StringAttr &>(right).value; }
bool StringAttr::operator!=(const Attr &right) { return value != static_cast<const StringAttr &>(right).value; }
bool StringAttr::operator<=(const Attr &right) { return value <= static_cast<const StringAttr &>(right).value; }
bool StringAttr::operator>=(const Attr &right) { return value >= static_cast<const StringAttr &>(right).value; }
bool StringAttr::operator<(const Attr &right) { return value < static_cast<const StringAttr &>(right).value; }
bool StringAttr::operator>(const Attr &right) { return value > static_cast<const StringAttr &>(right).value; }

bool floatAttr::operator==(const Attr &right) { return value == static_cast<const floatAttr &>(right).value; }
bool floatAttr::operator!=(const Attr &right) { return value != static_cast<const floatAttr &>(right).value; }
bool floatAttr::operator<=(const Attr &right) { return value <= static_cast<const floatAttr &>(right).value; }
bool floatAttr::operator>=(const Attr &right) { return value >= static_cast<const floatAttr &>(right).value; }
bool floatAttr::operator<(const Attr &right) { return value < static_cast<const floatAttr &>(right).value; }
bool floatAttr::operator>(const Attr &right) { return value > static_cast<const floatAttr &>(right).value; }

Record::Record(vector<Attr *> attrptr) : attrptr(attrptr) {}
void Record::addAttr(Attr *attr)
{
    attrptr.push_back(attr);
}
void Relation::print()      // print the relation
{
    cout << "\n";
    for (int i = 0; i < nattr; i++)     
        cout << "\t";
    cout << "Relation\n"
         << endl;
    cout << "|\t";
    for (auto attr : attrnames)     // print the attribute names
        cout << attr << "\t|\t";
    cout << endl;
    cout << endl;
    for (auto rec : recs)       // print the records
    {
        cout << "|\t";
        for (auto attr : rec->attrptr)
        {
            if (typeid(*attr) == typeid(IntAttr))
                cout << static_cast<IntAttr *>(attr)->value << "\t|\t";
            else if (typeid(*attr) == typeid(StringAttr))
                cout << static_cast<StringAttr *>(attr)->value << "\t|\t";
            else if (typeid(*attr) == typeid(floatAttr))
                cout << static_cast<floatAttr *>(attr)->value << "\t|\t";
        }
        cout << endl;
    }
}
void Relation::push_record(Record *rec)
{
    recs.push_back(rec);        // add the record to the relation
    nrecs++;
}
