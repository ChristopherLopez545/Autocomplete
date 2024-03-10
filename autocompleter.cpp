#include "autocompleter.h"

Autocompleter::Autocompleter()
{
    //set root to have new node  
    root= new Node;
    count=0;
}
// maintains the vector to be in a sorted order 
void Autocompleter:: sortVec(vector<Entry> &x, Entry y)
{
    if(x.size()==0)
    {
        x.push_back(y);    
    }
    else if (x.size()==1)
    {
        x.push_back(y);
        if(x[0].freq<x[1].freq)
        {
            swap(x[0],x[1]);
        }
    }
    else if (x.size()==2)
    {
        x.push_back(y);
         if(x[2].freq>x[1].freq)
         {
            swap(x[1],x[2]);
            if(x[1].freq> x[0].freq)
            {
                swap(x[0],x[1]);
            }
         }
    }
    else{ // when the vector already has three elements and we want ot add one more 

        // Case 1: what if the new entry has a higher freq than the top 
        if(y.freq>x[0].freq)
        { // shift everything down
            x[2]= x[1];
            x[1]=x[0];
            x[0]=y;
        }
        else if(y.freq<x[0].freq && y.freq>x[1].freq)
        {
            x[2]= x[1];
            x[1]=y;
        }
        else if (y.freq<x[0].freq && y.freq< x[1].freq && y.freq> x[2].freq)
        {
            x[2]=y;
        }
    }
}


// Adds a string x to the dictionary.
		// If x is already in the dictionary, does nothing.
		//
		// Must run in O(1) time.
void Autocompleter::insert(string x, int freq)
{
Entry aux;
aux.freq=freq;
aux.s=x;

// node used for traverse 
Node* p= root;
// push the entry into the root node to keep track of top strings 
sortVec(root->top,aux);

// use for loop to go over x string 
for(int i =0;i<aux.s.size();++i)
{
    // when it hits a nullptr , make new node 
        if(p->children[aux.s[i]] == nullptr)
        {
            p->children[aux.s[i]] = new Node;
            
        }

        //  traverse pointer 
        p=p->children[aux.s[i]];
        // push the current entry into the top vector 
        sortVec(p->top,aux);
}
// mark the node 
p->marked=true;
// since we added a string to the trie, increment count
++count;
}

int Autocompleter:: size()
{
    return count;// count has the number of strings in the trie
}

void Autocompleter::completions(string x , vector<string> &T)
{
    T.clear(); // clear vector 
Node* p= root;// traverse node 
    //go to the last pointer in the x string and grab the top entries there 
    for(int i =0; i < x.size(); ++i)
    {
        // Case 1: what if it lands on a node that does not exist 
        if(p->children[x[i]]== nullptr)
        {
            return; // do nothing 
        }
        // traverse 
        p=p->children[x[i]];
    }
// we are landed on that pointer, grab the entries 

for(int i=0;i<p->top.size();++i)
{
    T.push_back(p->top[i].s); // grabbing the three elements and pushing it into T vector 
}

}
