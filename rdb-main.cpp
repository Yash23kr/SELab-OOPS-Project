#include "rdb-join.cpp"
using namespace std;
void print_all(vector<Relation *> &v)       //Function to print all relations
{
    for (auto i : v)
    {
        i->print();
    }
}
void menu()     //Function to print the menu to user
{
    cout<<"\n";
    cout<<"<------------------Relational Database Management System------------------->"<<endl;
    cout<<"1. Create a new relation"<<endl;
    cout<<"2. Insert a new record"<<endl;
    cout<<"3. Delete a relation"<<endl;
    cout<<"4. Display a relation"<<endl;
    cout<<"5. Display all relations"<<endl;
    cout<<"6. Print union of two relations"<<endl;
    cout<<"7. Print difference of two relations"<<endl;
    cout<<"8. Print cartesian product of two relations"<<endl;
    cout<<"9. Print natural join of two relations"<<endl;
    cout<<"10. Rename an attribute of a relation"<<endl;
    cout<<"11. Print the Selection union of a relation"<<endl;
    cout<<"12. Print the Projection of a relation"<<endl;
    cout<<"13. Exit"<<endl;
    cout<<"<-------------------------------------------------------------------------->"<<endl;

}
void choices(int choice, vector<Relation *> &relations)
{
    switch(choice){
        case 1:{        //Create a new relation
            Relation *obj = new Relation();
            relations.push_back(obj);
            cout<<"Created a new relation with index: "<<relations.size()-1<<endl;
            cout<<"Enter the number of attributes: ";
            int n;
            cin>>n;
            obj->nattr = n;
            for(int i=0; i<n; i++){
                string attr;
                cout<<"Enter the name of the attribute " << i+1 << ": ";
                cin>>attr;
                obj->attrnames.push_back(attr);
                obj->attrinds.push_back(i);
            }

            break;
        }
        case 2:{        //Insert a new record
            int idx;
            
            cout<<"Enter the index of the relation: ";
            cin>>idx;
            while(!(idx>=0 && idx<relations.size()))
            {
                cout<<"Invalid index. Enter again: ";
                cin>>idx;
            }
            Relation *obj = relations[idx];
            vector<Attr *> attrptr;
            for(int i=0; i<obj->nattr; i++){
                    cout<<obj->attrnames[i]<<": ";
                    cout<<"Enter 1 for int, 2 for string, 3 for float: ";
                    int type;
                    cin>>type;
                    if(type == 1){
                        int val;
                        cout<<"Enter the value: ";
                        cin>>val;
                        attrptr.push_back(new IntAttr(val));
                    }
                    else if(type == 2){
                        string val;
                        cout<<"Enter the value: ";
                        cin>>val;
                        attrptr.push_back(new StringAttr(val));
                    }
                    else if(type == 3){
                        float val;
                        cout<<"Enter the value: ";
                        cin>>val;
                        attrptr.push_back(new floatAttr(val));
                    }
                    else{
                        cout<<"Invalid input"<<endl;
                    }

            }
            Record *rec = new Record(attrptr);
            obj->push_record(rec);
            obj->nrecs++;
            break;
        }
        case 3:{        //Delete a relation
            int idx;
            cout<<"Enter the index of the relation: ";
            cin>>idx;
            while(!(idx>=0 && idx<relations.size()))
            {
                cout<<"Invalid index. Enter again: ";
                cin>>idx;
            }
            relations.erase(relations.begin()+idx);
            break;
        }
        case 4:{        //Display a relation
            int idx;
            cout<<"Enter the index of the relation: ";
            cin>>idx;
            while(!(idx>=0 && idx<relations.size()))
            {
                cout<<"Invalid index. Enter again: ";
                cin>>idx;
            }
            relations[idx]->print();
            break;
        }
        case 5:{
            print_all(relations);
            break;
        }
        case 6:{        //Union of two relations
            int idx1, idx2;
            cout<<"Enter the index of the first relation: ";
            cin>>idx1;
            cout<<"Enter the index of the second relation: ";
            cin>>idx2;
            Relation *obj1 = relations[idx1];
            Relation *obj2 = relations[idx2];
            Relation *obj3 = obj1->union_op(obj1, obj2);
            obj3->print();
            break;
        }
        case 7:{        //Difference
            int idx1, idx2;
            cout<<"Enter the index of the first relation: ";
            cin>>idx1;
            cout<<"Enter the index of the second relation: ";
            cin>>idx2;
            Relation *obj1 = relations[idx1];
            Relation *obj2 = relations[idx2];
            Relation *obj3 = obj1->difference(obj1, obj2);
            obj3->print();
            break;
        }
        case 8:{        //Cartesian product
            int idx1, idx2;
            cout<<"Enter the index of the first relation: ";
            cin>>idx1;
            cout<<"Enter the index of the second relation: ";
            cin>>idx2;
            Relation *obj1 = relations[idx1];
            Relation *obj2 = relations[idx2];
            Relation *obj3 = obj1->cartesianproduct(obj1, obj2);
            obj3->print();
            break;
        }
        case 9:{        //Natural join
            int idx1, idx2;
            cout<<"Enter the index of the first relation: ";
            cin>>idx1;
            cout<<"Enter the index of the second relation: ";
            cin>>idx2;
            Relation *obj1 = relations[idx1];
            Relation *obj2 = relations[idx2];
            list<string> attrnames;
            for(int i=0;i<obj1->nattr;i++){
                for(int j=0;j<obj2->nattr;j++){
                    if(obj1->attrnames[i]==obj2->attrnames[j]){
                        attrnames.push_back(obj1->attrnames[i]);
                    }
                }
            }
            Relation *obj3 = obj1->naturaljoin(obj1, obj2, attrnames);
            obj3->print();
            break;
        }
        case 10:{       //Renaming an attribute
            int idx;
            cout<<"Enter the index of the relation: ";
            cin>>idx;
            string attrname, attrname2;
            cout<<"Enter the present name of the attribute: ";
            cin>>attrname;
            cout<<"Enter the new name of the attribute: ";
            cin>>attrname2;
            Relation *obj1 = relations[idx];
            obj1=obj1->difference(obj1, attrname, attrname2);
            break;
        }
        case 11:{       //Selection union
            int idx;
            cout<<"Enter the index of the relation: ";
            cin>>idx;
            Relation *obj1 = relations[idx];
            cout<<"Enter the name of disjunctions: ";
            int dij;
            cin>>dij;
            DNFformula sdnf;
            for(int i=0;i<dij;i++)
            {
                cout<<"Enter the number of conjuction for disjunction "<<i+1<<": ";
                int conj;
                cin>>conj;
                list<tuple<string,char,Attr*>> conjlist;
                for(int j=0;j<conj;j++)
                {
                    string attrname;
                    cout<<"Enter the name of the attribute: ";
                    cin>>attrname;
                    cout<<"Enter !, =, > or <: ";
                    char ch;
                    cin>>ch;
                    cout<<"Enter the value of the attribute to be compared: ";
                    cout<<"Enter 1 for int, 2 for string, 3 for float: ";
                    int type;
                    cin>>type;
                    tuple <string, char, Attr *> tup;
                    if(type == 1){
                        int val;
                        cout<<"Enter the value: ";
                        cin>>val;
                        tup = make_tuple(attrname, ch, new IntAttr(val));
                    }
                    else if(type == 2){
                        string val;
                        cout<<"Enter the value: ";
                        cin>>val;
                        tup = make_tuple(attrname, ch, new StringAttr(val));
                    }
                    else if(type == 3){
                        float val;
                        cout<<"Enter the value: ";
                        cin>>val;
                        tup = make_tuple(attrname, ch, new floatAttr(val));
                    }
                    else{
                        cout<<"Invalid input"<<endl;
                    }
                    conjlist.push_back(tup);
                }
                sdnf.ops.push_back(conjlist);
            }
            Relation *obj2 = obj1->Selection(obj1, &sdnf);
            obj2->print();
            break;
        }
        case 12:{       //Projection
            int idx;
            cout<<"Enter the index of the relation: ";
            cin>>idx;
            Relation *obj1 = relations[idx];
            cout<<"Enter the number of attributes to be projected: ";
            int n;
            cin>>n;
            list<string> attrnames;
            for(int i=0;i<n;i++)
            {
                string attrname;
                cout<<"Enter the name of the attribute"<<i+1<<": ";
                cin>>attrname;
                attrnames.push_back(attrname);
            }
            Relation *obj2 = obj1->projection(obj1, attrnames);
            obj2->print();
            break;
        }
    }
}
int main()
{
    // Relation *obj2 = new Relation();
    // obj2->nattr = 3;
    // obj2->attrnames.push_back("id");
    // obj2->attrnames.push_back("name");
    // obj2->attrnames.push_back("age");
    // obj2->attrinds.push_back(0);
    // obj2->attrinds.push_back(1);
    // obj2->attrinds.push_back(2);
    // obj2->nrecs = 0;
    // obj2->push_record(new Record({new IntAttr(1), new StringAttr("Harsh"), new IntAttr(20)}));
    // obj2->push_record(new Record({new IntAttr(2), new StringAttr("Jane"), new IntAttr(30)}));
    // obj2->push_record(new Record({new IntAttr(4), new StringAttr("Jim"), new IntAttr(62)}));
    // obj2->print();
    // Relation *obj3 = new Relation();
    // obj3=obj2->difference(obj2, "id", "id2");
    // obj3->print();
    vector <Relation *> relations;      //vector of relations
    
    int choice;
    while(1){
        menu();
        cout<<"Enter your choice: ";
        cin>>choice;
        if(choice>=13){
            break;
        }
        choices(choice, relations);
    }
}