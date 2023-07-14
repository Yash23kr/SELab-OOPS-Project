#include "rdb-attr.cpp"
using namespace std;
Relation *Relation::difference(Relation *R1, Relation *R2)      // Operation to perform difference
{
    Relation *newrel = new Relation();
    newrel->nattr = R1->nattr;
    newrel->attrnames = R1->attrnames;
    newrel->attrinds = R1->attrinds;
    for (auto rec : R1->recs)       // Iterating through the records of the first relation
    {
        bool found = true;
        for (auto origrec : R2->recs)       // Iterating through the records of the second relation
        {
            bool match = true;
            for (int i = 0; i < R1->nattr; i++)
            {
                Attr *origattr = origrec->attrptr[R2->attrinds[i]];
                Attr *newattr = rec->attrptr[R1->attrinds[i]];

                if (!(*origattr == *newattr))
                {
                    match = false;
                    break;
                }
            }
            if (match)
            {
                found = false;
                break;
            }
        }
        if (found)
        {
            newrel->push_record(rec);
        }
    }
    return newrel;
}
Relation *Relation::projection(Relation *R1, list<string> projectattrs)     // Operation to perform projection
{
    // create new relation with a subset of columns
    Relation *newrel = new Relation();
    newrel->nattr = projectattrs.size();
    for (auto it = projectattrs.begin(); it != projectattrs.end(); it++)
    {
        newrel->attrnames.push_back(*it);
        auto attridx = find(R1->attrnames.begin(), R1->attrnames.end(), *it) - R1->attrnames.begin();
        newrel->attrinds.push_back(R1->attrinds[attridx]);
    }

    for (auto rec : R1->recs)       
    {
        Record *newrec = new Record(vector<Attr *>());
        for (auto idx : newrel->attrinds)
        {
            newrec->attrptr.push_back(rec->attrptr[idx]);
        }
        newrel->recs.push_back(newrec);
        newrel->nrecs++;
    }

    return newrel;
}
Relation *Relation::cartesianproduct(Relation *R1, Relation *R2)        // Operation to perform cartesian product
{
    Relation *result = new Relation();      // Creating a new relation to store the result
    result->nattr = R1->nattr + R2->nattr;
    for (int i = 0; i < R1->nattr; i++)     // Adding the attributes of the two relations to the result relation
    {
        result->attrnames.push_back(R1->attrnames[i]);
        result->attrinds.push_back(i);
    }   
    for (int i = 0; i < R2->nattr; i++)     
    {
        result->attrnames.push_back(R2->attrnames[i]);
        result->attrinds.push_back(R1->nattr + i);
    }
    for (auto rec1 : R1->recs)        // Adding the records of the two relations to the result relation
    {
        for (auto rec2 : R2->recs)      
        {
            Record *newrec = new Record(vector<Attr *>());
            for (int i = 0; i < R1->nattr; i++)
            {

                newrec->addAttr(rec1->attrptr[i]);
            }
            for (int i = 0; i < R2->nattr; i++)
            {
                newrec->addAttr(rec2->attrptr[i]);
            }
            result->push_record(newrec);
        }
    }
    return result;
}
Relation *Relation::difference(Relation *R1, string s1, string s2) // Operation to rename an attribute in schema
{
    auto it = R1->attrnames.begin();
    while (it != R1->attrnames.end())       // Finding the attribute to be renamed
    {
        if (*it == s1)
        {
            *it = s2;
            break;
        }
        it++;
    }
    return R1;
}
Relation *Relation::union_op(Relation *R1, Relation *R2)        // Operation to perform union of two relations
{
    if (R1->nattr != R2->nattr)                            // Checking if the number of attributes are same
        return nullptr;
    for (int i = 0; i < R1->nattr; i++)               // Checking if the attributes are same
    {
        if (R1->attrnames[i] == R2->attrnames[i])
            continue;
        else
            return nullptr;
    }
    Relation *result = new Relation();
    result->nattr = R1->nattr;
    result->attrnames = R1->attrnames;
    result->attrinds = R1->attrinds;
    for (auto rec : R1->recs)                // Adding the records of R1 to the result relation
    {
        Record *newrec = new Record(vector<Attr *>());
        for (auto attr : rec->attrptr)
        {
            if (typeid(*attr) == typeid(IntAttr))
            {
                newrec->attrptr.push_back(new IntAttr(static_cast<IntAttr *>(attr)->value));
            }
            else if (typeid(*attr) == typeid(StringAttr))
            {
                newrec->attrptr.push_back(new StringAttr(static_cast<StringAttr *>(attr)->value));
            }
            else if (typeid(*attr) == typeid(floatAttr))
            {
                newrec->attrptr.push_back(new floatAttr(static_cast<floatAttr *>(attr)->value));
            }
        }
        result->recs.push_back(newrec);
    }
    for (auto rec : R2->recs)
    {
        bool found = false;
        for (auto origrec : R1->recs)
        {   // Checking if the record already exists in the relation
            bool match = true;
            for (int i = 0; i < R1->nattr; i++)
            {
                Attr *origattr = origrec->attrptr[R1->attrinds[i]];
                Attr *newattr = rec->attrptr[R2->attrinds[i]];
                if (!(*origattr == *newattr))
                {
                    match = false;
                    break;
                }
            }
            if (match)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            Record *newrec = new Record(vector<Attr *>());
            for (auto attr : rec->attrptr)      // Copying the attributes of the record
            {
                if (typeid(*attr) == typeid(IntAttr))
                {
                    newrec->attrptr.push_back(new IntAttr(static_cast<IntAttr *>(attr)->value));
                }
                else if (typeid(*attr) == typeid(StringAttr))
                {
                    newrec->attrptr.push_back(new StringAttr(static_cast<StringAttr *>(attr)->value));
                }
                else if (typeid(*attr) == typeid(floatAttr))
                {
                    newrec->attrptr.push_back(new floatAttr(static_cast<floatAttr *>(attr)->value));
                }
            }
            result->recs.push_back(newrec);
        }
    }
    return result;
}
Relation *Relation::Selection(Relation *R1, DNFformula *f)      // Selection operation
{
    Relation *result = new Relation();
    result->nattr = R1->nattr;
    result->attrnames = R1->attrnames;
    result->attrinds = R1->attrinds;
    for (auto rec : R1->recs)       // For each record in the relation
    {
        bool match = false;
        for (auto disj : f->ops)        //For each disjunction in the formula
        {
            bool disjmatch = true;
            for (auto conj : disj)      // For each conjunction in the disjunction
            {
                string attrname = get<0>(conj);
                char op = get<1>(conj);
                Attr *attr = get<2>(conj);
                int attridx = find(R1->attrnames.begin(), R1->attrnames.end(), attrname) - R1->attrnames.begin();
                if (typeid(*attr) == typeid(IntAttr))       // For integer attributes
                {
                    IntAttr *intattr = static_cast<IntAttr *>(attr);
                    IntAttr *recattr = static_cast<IntAttr *>(rec->attrptr[attridx]);
                    if (op == '=')
                    {
                        if (intattr->value != recattr->value)
                        {
                            disjmatch = false;
                            break;
                        }
                    }
                    else if (op == '>')
                    {
                        if (intattr->value >= recattr->value)
                        {
                            disjmatch = false;
                            break;
                        }
                    }
                    else if (op == '<')
                    {
                        if (intattr->value <= recattr->value)
                        {
                            disjmatch = false;
                            break;
                        }
                    }
                    else if (op == '!')
                    {
                        if (intattr->value == recattr->value)
                        {
                            disjmatch = false;
                            break;
                        }
                    }
                }
                else if (typeid(*attr) == typeid(StringAttr))       // For string attributes
                {
                    StringAttr *strattr = static_cast<StringAttr *>(attr);
                    StringAttr *recattr = static_cast<StringAttr *>(rec->attrptr[attridx]);
                    if (op == '=')
                    {
                        if (strattr->value != recattr->value)
                        {
                            disjmatch = false;
                            break;
                        }
                    }
                    else if (op == '>')
                    {
                        if (strattr->value >= recattr->value)
                        {
                            disjmatch = false;
                            break;
                        }
                    }
                    else if (op == '<')
                    {
                        if (strattr->value <= recattr->value)
                        {
                            disjmatch = false;
                            break;
                        }
                    }
                    else if (op == '!')
                    {
                        if (strattr->value == recattr->value)
                        {
                            disjmatch = false;
                            break;
                        }
                    }
                }
                else if (typeid(*attr) == typeid(floatAttr))        // For float attributes
                {
                    floatAttr *floatattr = static_cast<floatAttr *>(attr);
                    floatAttr *recattr = static_cast<floatAttr *>(rec->attrptr[attridx]);
                    if (op == '=')
                    {
                        if (floatattr->value != recattr->value)
                        {
                            disjmatch = false;
                            break;
                        }
                    }
                    else if (op == '>')
                    {
                        if (floatattr->value >= recattr->value)
                        {
                            disjmatch = false;
                            break;
                        }
                    }
                    else if (op == '<')
                    {
                        if (floatattr->value <= recattr->value)
                        {
                            disjmatch = false;
                            break;
                        }
                    }
                    else if (op == '!')
                    {
                        if (floatattr->value == recattr->value)
                        {
                            disjmatch = false;
                            break;
                        }
                    }
                }
                if (disjmatch == false)
                {
                    break;
                }
            }
            if (disjmatch)
            {
                match = true;
                break;
            }
        }
        if (match)
        {
            Record *newrec = new Record(vector<Attr *>());
            for (auto attr : rec->attrptr)
            {
                if (typeid(*attr) == typeid(IntAttr))
                {
                    newrec->attrptr.push_back(new IntAttr(static_cast<IntAttr *>(attr)->value));
                }
                else if (typeid(*attr) == typeid(StringAttr))
                {
                    newrec->attrptr.push_back(new StringAttr(static_cast<StringAttr *>(attr)->value));
                }
            }
            result->recs.push_back(newrec);
        }
    }
    return result;
}

// int main(){
//     Relation *obj2 = new Relation();
//     obj2->nattr = 3;
//     obj2->attrnames.push_back("id");
//     obj2->attrnames.push_back("name");
//     obj2->attrnames.push_back("age");
//     obj2->attrinds.push_back(0);
//     obj2->attrinds.push_back(1);
//     obj2->attrinds.push_back(2);
//     obj2->nrecs = 0;
//     obj2->push_record(new Record({new IntAttr(1), new StringAttr("Harsh"), new IntAttr(20)}));
//     obj2->push_record(new Record({new IntAttr(2), new StringAttr("Jane"), new IntAttr(30)}));
//     obj2->push_record(new Record({new IntAttr(4), new StringAttr("Jim"), new IntAttr(62)}));
//     obj2->print();
//     Relation *obj3 = new Relation();
//     obj3=obj2->difference(obj2, "id", "id2");
//     obj3->print();
// }