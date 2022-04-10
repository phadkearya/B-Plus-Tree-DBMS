#include <bits/stdc++.h>

using namespace std;



class dataNode{
    public:
        dataNode()=delete;
        dataNode(int);
        bool atMinCapacity();
        bool atMaxCapacity();
        bool insertElement(int);
        void copyData(vector<int>&);
        void clearDataContents();
        void printDataContents();
        virtual ~dataNode();

    protected:

    private:
        vector <int> dataContent;
        int d;

};

dataNode::dataNode(int n){
    d=n;
}

bool dataNode::atMinCapacity(){
    if (dataContent.size()==d){
        //cout<<"At min capacity\n";
        return true;
    }
    return false;
}

bool dataNode::atMaxCapacity(){
    if (dataContent.size()==2*d){
        //cout<<"At max capacity\n";
        return true;
    }
    return false;
}

bool dataNode::insertElement(int n){
    // we will have to insert and then sort the elements
    dataContent.push_back(n);
    sort(dataContent.begin(),dataContent.end());
    return true;
}

void dataNode::copyData(vector<int>& v){
    int i;
    for(i=0;i<dataContent.size();i++){
        v.push_back(dataContent[i]);
    }
}

void dataNode::clearDataContents(){
    dataContent.clear();
}

void dataNode::printDataContents(){
    int i;
    for(i=0;i<dataContent.size();i++){
        cout<<dataContent[i]<<" ";
    }
    cout<<'\n';
}

dataNode::~dataNode(){
    //dtor
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class indexNode{
    public:
        indexNode()=delete;
        indexNode(int);
        bool setParent(indexNode*);
        indexNode* getParent();
        bool atMinCapacity();
        bool atMaxCapacity();
        indexNode* getIndexNode(int);
        dataNode* getDataNode(int);
        int findCorrectPointer(int);
        int getIndexPointersSize();
        int getDataPointersSize();
        bool setLastDataPointer(dataNode*);
        indexNode* getLastIndexPointer();
        void clearElements();
        void clearDataPointers();
        void clearIndexPointers();
        void copyContents(vector<int>&);
        void copyDataPointers(vector<dataNode*>&);
        void copyIndexPointers(vector<indexNode*>&);
        void insertInteger(int);
        void insertDataPointer(dataNode*);
        void insertIndexPointer(indexNode*);
        bool indexPointersIsEmpty();
        int classify(int);
        int insertIntoBottommostLevel(int,dataNode*,dataNode*,int&);
        int insertIntoIndexNode(int,indexNode*,indexNode*,int&,bool&);
        void printIndexNodeContents();
        virtual ~indexNode();

    protected:

    private:
        vector <int> elements;
        vector <indexNode*> indexPointers;
        vector <dataNode*> dataPointers;
        indexNode* parent;
        int t;

};

indexNode::indexNode(int n){
    t=n;
    parent=nullptr;
}

bool indexNode::setParent(indexNode* n1){
    parent=n1;
    return true;
}

indexNode* indexNode::getParent(){
    return (parent);
}

bool indexNode::atMinCapacity(){
    if (elements.size()==t){
        //cout<<"At min capacity\n";
        return true;
    }
    return false;
}

bool indexNode::atMaxCapacity(){
    if (elements.size()==(2*t)+1){
        //cout<<"At max capacity\n";
        return true;
    }
    return false;
}

indexNode* indexNode::getIndexNode(int n){
    return (indexPointers[n]);
}

dataNode* indexNode::getDataNode(int n){
    return (dataPointers[n]);
}

int indexNode::getIndexPointersSize(){
    return (indexPointers.size());
}

int indexNode::getDataPointersSize(){
    return (dataPointers.size());
}

void indexNode::clearElements(){
    elements.clear();
}

void indexNode::clearDataPointers(){
    dataPointers.clear();
}

void indexNode::clearIndexPointers(){
    indexPointers.clear();
}

void indexNode::copyContents(vector<int>& v){
    int i;
    for(i=0;i<elements.size();i++){
        v.push_back(elements[i]);
    }
}

void indexNode::copyDataPointers(vector<dataNode*>& v){
    int i;
    for(i=0;i<dataPointers.size();i++){
        v.push_back(dataPointers[i]);
    }
}

void indexNode::copyIndexPointers(vector<indexNode*>& v){
    int i;
    for(i=0;i<indexPointers.size();i++){
        v.push_back(indexPointers[i]);
    }
}

void indexNode::insertInteger(int k){
    elements.push_back(k);
}

void indexNode::insertIndexPointer(indexNode* k){
    indexPointers.push_back(k);
}

void indexNode::insertDataPointer(dataNode* k){
    dataPointers.push_back(k);
}

bool indexNode::indexPointersIsEmpty(){
    if (indexPointers.empty()){
        return true;
    }
    return false;
}

indexNode* indexNode::getLastIndexPointer(){
    indexNode* ans = indexPointers[indexPointers.size()-1];
    indexPointers.pop_back();
    return (ans);
}

int indexNode::classify(int n){
    int i;
    for(i=0;i<elements.size();i++){
        if (elements[i]>=n){
            return (i-1);
        }
    }
    return (elements.size());
}

int indexNode::findCorrectPointer(int n){
    int i;
    if (n<elements[0]){
        return 0;
    }
    for(i=0;i<elements.size()-1;i++){
        if (elements[i]<n && elements[i+1]>=n){
            return (i+1);
        }
    }
    if (n>=elements[elements.size()-1]){
        return (elements.size());
    }
}

bool indexNode::setLastDataPointer(dataNode* d1){
    dataPointers.push_back(d1);
}

int indexNode::insertIntoIndexNode(int n, indexNode* ptr1, indexNode* ptr2, int& num, bool& checkVariable){

    //cout<<"contents of parent index node are: ";
    printIndexNodeContents();

    int i,j,k;
    indexNode* x;
    int sep;
    if (!(atMaxCapacity())){
        k = findCorrectPointer(n);

        elements.insert(elements.begin()+k,n);
        //cout<<"pointer should be inserted at index "<<k+1<<'\n';

        if (k==0){
            // insert n at the beginning and insert ptr2 at position 1 in the vector
            indexPointers.insert(indexPointers.begin()+k+1,ptr2);
        }
        else if (k==elements.size()){
            // insert both at the end
            //elements.push_back(n);
            indexPointers.push_back(ptr2);
        }
        else{
            // insert in between
            indexPointers.insert(indexPointers.begin()+k+1,ptr2);

        }
        return -1;
    }
    else{

        //cout<<"splitting index node\n";

        // now index node is at maxCapacity
        // split index node and return the seperator
        vector<int> temp;
        vector<indexNode*> temp1;

        copyContents(temp);
        temp.push_back(n);
        sort(temp.begin(),temp.end());

        for(i=0;i<indexPointers.size();i++){
            if (indexPointers[i]==ptr1){
                break;
            }
        }
        copyIndexPointers(temp1);
        temp1.insert(temp1.begin()+i+1,ptr2);

        clearElements();
        clearIndexPointers();

        indexNode* newNode;
        newNode = new indexNode(t);
        num++;

        newNode->setParent(getParent());

        for(i=0;i<t;i++){
            insertInteger(temp[i]);
        }
        sep = temp[t];
        for(i=t+1;i<temp.size();i++){
            newNode->insertInteger(temp[i]);
        }

        for(i=0;i<t+1;i++){
            insertIndexPointer(temp1[i]);
        }

        for(i=t+1;i<temp1.size();i++){
            newNode->insertIndexPointer(temp1[i]);
        }

        // printIndexNodeContents();
        // newNode->printIndexNodeContents();

        // still need to add the case if parent is nullptr

        if (getParent()==nullptr){
            checkVariable=true;
            insertIndexPointer(newNode);
        }

        else{
            getParent()->insertIndexPointer(newNode);
        }

        return sep;
    }
}

int indexNode::insertIntoBottommostLevel(int n, dataNode* ptr1, dataNode* ptr2, int& num){

    // cout<<"number to be inserted is: "<<n<<'\n';
    // cout<<"contents of parent index node are: ";
    // printIndexNodeContents();

    int i,j,k;
    dataNode* x;
    int sep;
    if (!(atMaxCapacity())){
        k = findCorrectPointer(n);
        elements.insert(elements.begin()+k,n);

        // cout<<"pointer2 should be inserted at index "<<k+1<<'\n';
        // cout<<"size of datapointers before inserting "<<dataPointers.size()<<'\n';

        if (k==0){
            // insert n at the beginning and insert ptr2 at position 1 in the vector
            dataPointers.insert(dataPointers.begin()+k+1,ptr2);
        }
        else if (k==elements.size()){
            // insert both at the end
            dataPointers.push_back(ptr2);
        }
        else{
            // insert in between
            dataPointers.insert(dataPointers.begin()+k+1,ptr2);
        }

        return -1;
    }
    else{
        // now index node is at maxCapacity
        // split index node and return the seperator
        vector<int> temp;
        vector<dataNode*> temp1;

        copyContents(temp);
        temp.push_back(n);
        sort(temp.begin(),temp.end());

        for(i=0;i<dataPointers.size();i++){
            if (dataPointers[i]==ptr1){
                break;
            }
        }
        copyDataPointers(temp1);
        temp1.insert(temp1.begin()+i+1,ptr2);

        clearElements();
        clearDataPointers();

        indexNode* newNode;
        newNode = new indexNode(t);
        num++;

        newNode->setParent(getParent());

        for(i=0;i<t;i++){
            insertInteger(temp[i]);
        }
        sep = temp[t];
        for(i=t+1;i<temp.size();i++){
            newNode->insertInteger(temp[i]);
        }

        for(i=0;i<t+1;i++){
            insertDataPointer(temp1[i]);
        }

        for(i=t+1;i<temp1.size();i++){
            newNode->insertDataPointer(temp1[i]);
        }

        // cout<<"first node data pointers size: "<<getDataPointersSize()<<'\n';
        // cout<<"second node data pointers size: "<<newNode->getDataPointersSize()<<'\n';

        // still need to add the case if parent is nullptr

        if (getParent()==nullptr){
            insertIndexPointer(newNode);
        }

        else{
            getParent()->insertIndexPointer(newNode);
        }

        return sep;
    }
}

void indexNode::printIndexNodeContents(){
    int i;
    for(i=0;i<elements.size();i++){
        cout<<elements[i]<<" ";
    }
    cout<<'\n';
}

indexNode::~indexNode(){
    //dtor
}



class bPlusTree{
    public:
        bPlusTree()=delete;
        bPlusTree(int,int);
        bool atMinCapacity();
        bool atMaxCapacity();
        bool insertData(int);
        void printbPlusTree();
        virtual ~bPlusTree();

    protected:

    private:
        indexNode* root1;
        dataNode* root2;
        int d;
        int t;
        int numIndex;
        int numData;
        vector <int> tempData;

};

bPlusTree::bPlusTree(int n,int m){
    t=n;
    d=m;
    numIndex=0;
    numData=0;
    root1=nullptr;
    root2=nullptr;
}


bool bPlusTree::insertData(int n){
    indexNode* ptr1 = root1;
    dataNode* ptr2 = root2;
    dataNode* ptr3;
    indexNode* ptr4;
    indexNode* ptr5;
    int i,j,k;
    int sep;
    if (ptr1==nullptr){
        // means there is no index node
        if (ptr2==nullptr){
            // means we have to create a data node and insert it into the tree
            //cout<<"creating first data node\n";
            dataNode* n1 = new dataNode(d);
            numData++;
            n1->insertElement(n);
            root2=n1;
            return true;
        }
        else{
            // means first data node exists we have to insert into it
            // now two cases : if it is at MaxCapacity or not
            //cout<<"inserting into first data node\n";
            if (!(ptr2->atMaxCapacity())){
                ptr2->insertElement(n);
                return true;
            }
            else{
                // only one data node exists and it is full
                // now we will have to split the data node
                ptr2->copyData(tempData);
                tempData.push_back(n);
                sort(tempData.begin(),tempData.end());
                ptr2->clearDataContents();
                ptr3 = new dataNode(d);
                numData++;

                for(i=0;i<d;i++){
                    ptr2->insertElement(tempData[i]);
                }
                sep=tempData[d];
                for(i=d;i<tempData.size();i++){
                    ptr3->insertElement(tempData[i]);
                }
                tempData.clear();
                // call function to insert in bottom most index leaves with 3 arguments : sep,ptr2,ptr3

                // here there is no index leaf so we will have to create it and it will be root1

                ptr4 = new indexNode(t);
                numIndex++;
                root1 = ptr4;

                ptr4->insertInteger(sep);
                ptr4->insertDataPointer(ptr2);
                ptr4->insertDataPointer(ptr3);

                return true;

            }
        }
    }
    else{
        // now proper tree structure is there, ptr1 points to root. traverse through all index nodes to reach the correct data node
        while(!(ptr1->indexPointersIsEmpty())){
            k = ptr1->findCorrectPointer(n);
            ptr1=ptr1->getIndexNode(k);
        }
        k = ptr1->findCorrectPointer(n);

        //cout<<"Parent index node contents: ";
        //ptr1->printIndexNodeContents();

        //cout<<"before insertion, number of data pointers: "<<ptr1->getDataPointersSize()<<'\n';
        //cout<<"before insertion, number of index pointers: "<<ptr1->getIndexPointersSize()<<'\n';
        ptr2 = ptr1->getDataNode(k);

        //cout<<"Destination data node contents: ";
        //ptr2->printDataContents();

        // ptr1 is the parent index node of ptr2
        // ptr2 contains the correct data node

        if (!(ptr2->atMaxCapacity())){
            ptr2->insertElement(n);
            return true;
        }
        else{
            // now we will have to split the data node
            ptr2->copyData(tempData);
            tempData.push_back(n);
            sort(tempData.begin(),tempData.end());
            ptr2->clearDataContents();
            ptr3 = new dataNode(d);
            numData++;

            for(i=0;i<d;i++){
                ptr2->insertElement(tempData[i]);
            }
            sep=tempData[d];
            for(i=d;i<tempData.size();i++){
                ptr3->insertElement(tempData[i]);
            }
            tempData.clear();

            // ptr1 is the above index node

            // cout<<"Data node 1 after rearrangement: ";
            // ptr2->printDataContents();

            // cout<<"Data node 2 after rearrangement: ";
            // ptr3->printDataContents();


            int s1,s2;
            s1 = ptr1->getIndexPointersSize();

            // call function to insert in bottom most index leaves with 3 arguments : sep,ptr2,ptr3
            // index node function : parameters : sep,ptr2,ptr3
            sep = ptr1->insertIntoBottommostLevel(sep,ptr2,ptr3,numIndex);

            // cout<<"contents of parent index node after insertion into first level: ";
            // ptr1->printIndexNodeContents();

            s2 = ptr1->getIndexPointersSize();

            ptr5 = ptr1->getParent();

            if (s2==s1+1){
                //cout<<"after insertion, number of data pointer: "<<ptr1->getDataPointersSize()<<'\n';
                // means root needs to be inserted with ptr1 and last index pointer of ptr1 as children
                //cout<<"inserting new root with element "<<sep<<'\n';
                indexNode* ptr6;
                indexNode* ptr7;
                ptr6 = new indexNode(t);
                numIndex++;
                ptr6->insertInteger(sep);
                ptr7 = ptr1->getLastIndexPointer();
                ptr6->insertIndexPointer(ptr1);
                ptr6->insertIndexPointer(ptr7);
                ptr1->setParent(ptr6);
                ptr7->setParent(ptr6);
                root1=ptr6;
                //root1->printIndexNodeContents();
                //cout<<"after insertion, number of data pointer: "<<ptr1->getDataPointersSize()<<'\n';
                return true;
            }

            // store the new node inserted into ptr4
            if (sep!=-1){
                ptr4 = ptr5->getLastIndexPointer();
                // cout<<"after insertion, number of data pointer: "<<ptr1->getDataPointersSize()<<'\n';
                // cout<<"after insertion, number of data pointer: "<<ptr4->getDataPointersSize()<<'\n';
            }

            // now we have sep, ptr1 and ptr4 to be inserted into ptr5 where all are index nodes
            // this will have to be called recursively
            // this will return sep and in ptr5, the last indexnode in the vector will be the new node inserted

            bool checkVariable=false;

            while(sep!=-1){
                s1 = ptr5->getIndexPointersSize();
                // cout<<"value of s1 is "<<s1<<'\n';
                // cout<<"before insertion2, number of index pointer: "<<ptr5->getIndexPointersSize()<<'\n';
                // cout<<"in the recursive loop\n";
                sep=ptr5->insertIntoIndexNode(sep,ptr1,ptr4,numIndex,checkVariable);
                if (sep==-1){
                    break;
                }
                // cout<<"after insertion2, number of index pointer: "<<ptr5->getIndexPointersSize()<<'\n';
                s2 = ptr5->getIndexPointersSize();

                // this condition is wrong needs to be changed

                if (checkVariable){
                    // cout<<"inserting new index node as root\n";
                    indexNode* ptr6;
                    indexNode* ptr7;
                    ptr6 = new indexNode(t);
                    numIndex++;
                    ptr6->insertInteger(sep);
                    ptr7 = ptr5->getLastIndexPointer();
                    ptr6->insertIndexPointer(ptr5);
                    ptr6->insertIndexPointer(ptr7);
                    ptr5->setParent(ptr6);
                    ptr7->setParent(ptr6);
                    root1=ptr6;
                    break;
                }
                if (sep==-1){
                    break;
                }
                ptr1 = ptr5;
                ptr5 = ptr1->getParent();
                ptr4 = ptr1->getLastIndexPointer();
            }
        }
    }
    return true;
}

void bPlusTree::printbPlusTree(){
    cout<<numIndex<<" ";
    cout<<numData<<" ";

    if (root1!=nullptr){
        // output contents of index node root1
        root1->printIndexNodeContents();
    }
    else{
        // output contents of data node root2
        root2->printDataContents();
    }
}


bPlusTree::~bPlusTree(){
    //dtor
}

////////////////////////////////////////////////////////////////////////////////////////

int main(){

    int d,t;
    cin>>d>>t;

    bPlusTree* b;
    b = new bPlusTree(t,d);

    int x,y;

    while(1){
        cin>>x;
        if (x==1){
            cin>>y;
            b->insertData(y);
        }
        else if (x==2){
            b->printbPlusTree();
        }
        else{
            break;
        }
    }


    return 0;
}