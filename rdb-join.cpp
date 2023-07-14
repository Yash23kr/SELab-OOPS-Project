#include "rdb-basics.cpp"
using namespace std;

Relation *Relation::naturaljoin(Relation *R1, Relation *R2, list<string> joinattr)
{
    Relation *result = new Relation();
    result->nattr = R1->nattr + R2->nattr - joinattr.size();        // number of attributes in the result relation
    for( auto attr : joinattr)                                // attributes in the join condition
        {
            result->attrnames.push_back(attr);
            result->attrinds.push_back(R1->attrinds[find(R1->attrnames.begin(), R1->attrnames.end(), attr) - R1->attrnames.begin()]);
        }
    for (auto attr : R1->attrnames)     //attributes in R1 but not in join condition
    {
        if (find(joinattr.begin(), joinattr.end(), attr) == joinattr.end())
        {
            result->attrnames.push_back(attr);
            result->attrinds.push_back(R1->attrinds[find(R1->attrnames.begin(), R1->attrnames.end(), attr) - R1->attrnames.begin()]);
        }
    }
    for (auto attr : R2->attrnames)     //attributes in R2 but not in join condition
    {
        if (find(joinattr.begin(), joinattr.end(), attr) == joinattr.end())
        {
            result->attrnames.push_back(attr);
            result->attrinds.push_back(R1->nattr + R2->attrinds[find(R2->attrnames.begin(), R2->attrnames.end(), attr) - R2->attrnames.begin()]);
        }
    }
    for (auto rec1 : R1->recs)
    {
        for (auto rec2 : R2->recs)
        {
            bool match = true;
            for (auto attr : joinattr)      //check if the join condition is satisfied
            {
                int ind1 = R1->attrinds[find(R1->attrnames.begin(), R1->attrnames.end(), attr) - R1->attrnames.begin()];
                int ind2 = R2->attrinds[find(R2->attrnames.begin(), R2->attrnames.end(), attr) - R2->attrnames.begin()];
                if (!(*rec1->attrptr[ind1] == *rec2->attrptr[ind2]))
                {
                    match = false;
                    break;
                }
            }
            if (match)      //if the join condition is satisfied, create a new record
            {
                Record *newrec = new Record(vector<Attr *>());
                for (int i = 0; i < R1->nattr; i++)     //add attributes from R1
                {
                    if (typeid(*rec1->attrptr[i]) == typeid(IntAttr))
                    {
                        newrec->attrptr.push_back(new IntAttr(static_cast<IntAttr *>(rec1->attrptr[i])->value));
                    }
                    else if (typeid(*rec1->attrptr[i]) == typeid(StringAttr))
                    {
                        newrec->attrptr.push_back(new StringAttr(static_cast<StringAttr *>(rec1->attrptr[i])->value));
                    }
                    else if (typeid(*rec1->attrptr[i]) == typeid(floatAttr))
                    {
                        newrec->attrptr.push_back(new floatAttr(static_cast<floatAttr *>(rec1->attrptr[i])->value));
                    }
                }
                for (int i = 0; i < R2->nattr; i++)     //add attributes from R2
                {
                    if (find(joinattr.begin(), joinattr.end(), R2->attrnames[i]) == joinattr.end())
                    {
                        if (typeid(*rec2->attrptr[i]) == typeid(IntAttr))
                        {
                            newrec->attrptr.push_back(new IntAttr(static_cast<IntAttr *>(rec2->attrptr[i])->value));
                        }
                        else if (typeid(*rec2->attrptr[i]) == typeid(StringAttr))
                        {
                            newrec->attrptr.push_back(new StringAttr(static_cast<StringAttr *>(rec2->attrptr[i])->value));
                        }
                        else if (typeid(*rec2->attrptr[i]) == typeid(floatAttr))
                        {
                            newrec->attrptr.push_back(new floatAttr(static_cast<floatAttr *>(rec2->attrptr[i])->value));
                        }
                    }
                }

                result->recs.push_back(newrec);     //add the new record to the result relation
            }
        }
    }
    return result;
}
// int main()
// {
//     cout<<"hi";
// }