#include <iostream>

using namespace std;

struct tapeSquare{
    //ie 0,1,A,B
    char symbol;
    //pointer to right tape square
    tapeSquare * right;
    //pointer to left tape square
    tapeSquare * left;
};
//initializes new tape
tapeSquare * createTape()
{
    tapeSquare * current;
    current = new tapeSquare;
    current->right = NULL;
    current->left = NULL;
    
    return current;
}
//writes string to existing tape
void writeString(string str,int currentIndex,tapeSquare * LefttapePtr)
{
    //print 1st symbol on initialized tape square
    if(currentIndex == 0)
    {
        LefttapePtr->symbol = str[0];
        currentIndex++;
    }
    //print empty symbol after string is exhausted
    if(str[currentIndex]=='\0')
    {
       tapeSquare * current;
       current = new tapeSquare;
       current->left = LefttapePtr;
       current->right = NULL;
       current->symbol = ' ';
      
       LefttapePtr->right = current;
    }
    //recursivly call writeString until string is exhausted
    if(str[currentIndex]!='\0')
    {
       tapeSquare * current;
       current = new tapeSquare;
       current->left = LefttapePtr;
       current->right = NULL;
       current->symbol = str[currentIndex];
      
       LefttapePtr->right = current;
       
       //recursive call
       writeString(str,++currentIndex,current);
       
    }
    
}
//reads current state and symbol, writes new symbol and recursivly passes itself new state and moves along tape. Halts when reaching state 4 (qAccept)
//if it doesnt know what to do with an input, just returns
void configurationController(int currState, tapeSquare * ptr)
{
    
    //cout<<"state: "<<currState<<" symbol: "<<ptr->symbol<<endl;
        if(currState == 0)
        {
            if(ptr->symbol == '0')
            {
                ptr->symbol = 'A';
                
                configurationController(1, ptr->right);
            }
            if(ptr->symbol == 'B')
            {
                ptr->symbol = 'B';
                
                configurationController(3, ptr->right);
            }
        }    
        if(currState == 1)
        {
            if(ptr->symbol == '0')
            {
               ptr->symbol = '0';  
               
               configurationController(1, ptr->right);
            }
             if(ptr->symbol == 'B')
            {
               ptr->symbol = 'B';  
               
                configurationController(1, ptr->right);
            }
             if(ptr->symbol == '1')
            {
               ptr->symbol = 'B';  
               
                configurationController(2, ptr->left);
            }
        }   
        if(currState == 2)
        {
            if(ptr->symbol == 'A')
            {
                ptr->symbol = 'A';
                
                configurationController(0, ptr->right);
            }
            if(ptr->symbol == 'B')
            {
                ptr->symbol = 'B';
                
                configurationController(2, ptr->left);
            }
            if(ptr->symbol == '0')
            {
                ptr->symbol = '0';
               
                configurationController(2, ptr->left);
            }
        }   
        if(currState == 3)
        {
           if(ptr->symbol == 'B')
            {
                ptr->symbol = 'B';
                
                configurationController(3, ptr->right);
            }
            if(ptr->symbol == ' ')
            {
                ptr->symbol = ' ';
                configurationController(4, ptr);
            }
        }    
        if(currState == 4)
        {
             cout<<"string accepted"<<endl;
        }
        
    
}
//calls config manager and initializes currState to 0
void turingMachine(tapeSquare * ptr)
{
    int currState = 0;
    configurationController(currState,ptr);
    
}


int main()
{
while(true)
{
   cout<<"enter string of 0s followed by 1s"<<endl;
   //string to write on tape
   string s;
   //input string
   cin>>s;
   //create tape
   tapeSquare * TapeHead;
   TapeHead = createTape();
   //write string to tape
   writeString(s,0,TapeHead);
   //pass tape into turing machine
   turingMachine(TapeHead);
}
    return 0;
}
