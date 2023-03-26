// implementation for the multi-chain single linked list

#include "linkedlist.h"

//Node Constructors
LinkList::Node::Node(){
    nextTime = nullptr;
    nextTemp = nullptr;
    nextWind = nullptr;
    prevTime = nullptr;
    prevTemp = nullptr;
    prevWind = nullptr;
}

LinkList::Node::Node(const WeatherData& adata) {
    data = adata;
    nextTime = nullptr;
    nextTemp = nullptr;
    nextWind = nullptr;
    prevTime = nullptr;
    prevTemp = nullptr;
    prevWind = nullptr;
}


//Linked list Constructors
LinkList::LinkList()
{
    headTime = nullptr;
    headTemp = nullptr;
    headWind = nullptr;
    size = 0;
}

LinkList::LinkList(const LinkList &aData){
    int    count = 0;
    size = aData.size;

    if (aData.headTime){
        headTime = new Node(aData.headTime->data);
        
        Node    *dest = headTime;
        Node    *src = aData.headTime->nextTime;   
        while (src){
            dest->nextTime = new Node(src->data);
            
            src = src->nextTime;    
            dest = dest->nextTime;
        }
       
       Node     *curr = headTemp;
       dest = headTime;
       src = aData.headTemp;
       while (src && count != aData.size){
            int     temp = dest->data.getTemperature();
            int     srcTemp = src->data.getTemperature();
            if (srcTemp == temp){
                if (!headTemp){
                    headTemp = dest;
                    curr = headTemp;
                }
                else{
                    curr->nextTemp = dest;
                    curr = curr->nextTemp;
                }
                src = src->nextTemp;
                dest = headTime;
                count++;
            }else{
                dest = dest->nextTime;
            }
       }

       count = 0;
       curr = headWind;
       dest = headTime;
       src = aData.headWind;
       while (src && count != aData.size){
            int     wind = dest->data.getWindSpeed();
            int     srcWind = src->data.getWindSpeed();
            if (srcWind == wind){
                if (!headWind){
                    headWind = dest;
                    curr = headWind;
                }
                else{
                    curr->nextWind = dest;
                    curr = curr->nextWind;
                }
                src = src->nextWind;
                dest = headTime;
                count++;
            }else{
                dest = dest->nextTime;
            }
       }
    }
}

//Linked list destructor
LinkList::~LinkList()
{
    Node *curr = headTime;  
    Node *prev = nullptr;
    headTemp = nullptr;
    headWind = nullptr;
    if (headTime)
    {
        while (curr)
        {
            prev = curr;
            curr = curr->nextTime;
            delete prev;
            prev = curr;
        } 
    }   
}

void LinkList::insert(WeatherData& adata)
{ 
    bool    found = false;
    Node    *newNode = new Node(adata);

   
       //starts list or continues it
    if (!headTime)
    {
        headTime = newNode;
        headTemp = newNode;
        headWind = newNode;

        size++;
    }
    else
    {
        Node* curr = headTime;
        Node* prev = nullptr;
        //check to find insertion position in Timestamp chain
        while(!found)
        {
            if (!curr)
            {
                prev->nextTime = newNode;
                newNode->prevTime = prev;
                found = true;
            }
            else if (adata.getTimeStamp() <= curr->data.getTimeStamp()){
                if (curr == headTime){
                    headTime = newNode;
                    newNode->nextTime = curr;
                    curr->prevTime = newNode;
                }else{
                    newNode->nextTime = curr;
                    newNode->prevTime = prev;

                    prev->nextTime = newNode;
                    curr->prevTime = newNode;
                }
                found = true; 
            }
            else
            {
                prev = curr;
                curr = curr->nextTime;
            }
        }  

        found = false;
        curr = headTemp;
        prev = nullptr;
        while (!found)
        {
            if (!curr)
            {
                prev->nextTemp = newNode;
                newNode->prevTemp = prev;
                found = true;
            }
            else if (adata.getTemperature() <= curr->data.getTemperature()) {
                if (curr == headTemp) {
                    headTemp = newNode;
                    newNode->nextTemp = curr;
                    curr->prevTemp = newNode;
                }
                else {
                    newNode->nextTemp = curr;
                    newNode->prevTemp = prev;

                    prev->nextTemp = newNode;
                    curr->prevTemp = newNode;
                }
                found = true;
            }
            else
            {
                prev = curr;
                curr = curr->nextTemp;
            }
        }
        
        found = false;
        curr = headWind;
        prev = nullptr;
        while (!found)
        {
            if (!curr)
            {
                prev->nextWind = newNode;
                newNode->prevWind = prev;
                found = true;
            }
            else if (adata.getWindSpeed() <= curr->data.getWindSpeed()) {
                if (curr == headWind) {
                    headWind = newNode;
                    newNode->nextWind = curr;
                    curr->prevWind = newNode;
                }
                else {
                    newNode->nextWind = curr;
                    newNode->prevWind = prev;

                    prev->nextWind = newNode;
                    curr->prevWind = newNode;
                }
                found = true;
            }
            else
            {
                prev = curr;
                curr = curr->nextWind;
            }
        }
        size++;
     }
}

bool LinkList::retrieve(const int& timeStamp)
{
    Node    *curr;
    int     tStamp;
    
    //checks for the timestamp in the timestamp chain
    for (curr = headTime; curr; curr = curr->nextTime)
    {
        tStamp = curr->data.getTimeStamp();
        if (tStamp == timeStamp)
            return true;
    }
    return false;
}

bool LinkList::remove(const int& timeStamp)
{
    int     dataTime;
    Node    *deleteNode = headTime;
    bool    found = false;
 
    //checks for timestamp in the list
    while (!found && deleteNode != nullptr)
    {
        dataTime = deleteNode->data.getTimeStamp();
        if (dataTime == timeStamp)
        {
            //makes sure all repetitions are deleted
            do
            {
                found = true;

                //redirects the timestamp chain
                if (deleteNode == headTime)
                    headTime = deleteNode->nextTime;
                else if (deleteNode->nextTime == nullptr)
                    deleteNode->prevTime->nextTime = nullptr;
                else 
                {
                    deleteNode->prevTime->nextTime = deleteNode->nextTime;
                    deleteNode->nextTime->prevTime = deleteNode->prevTime;
                }
            
                //redirects the temperature chain
                if (deleteNode == headTemp)
                    headTemp = deleteNode->nextTemp;
                else if (deleteNode->nextTemp == nullptr)
                     deleteNode->prevTemp->nextTemp = nullptr;
                else
                {
                    deleteNode->prevTemp->nextTemp = deleteNode->nextTemp;
                    deleteNode->nextTemp->prevTemp = deleteNode->prevTemp;
                }

                //redirects the windspeed chain
                if (deleteNode == headWind)
                    headWind = deleteNode->nextWind;
                else if (deleteNode->nextWind == nullptr)
                    deleteNode->prevWind->nextWind = nullptr;
                else
                {
                    deleteNode->prevWind->nextWind = deleteNode->nextWind;
                    deleteNode->nextWind->prevWind = deleteNode->prevWind;
                }
                
                //delete the node and move the pointer to the next node to check for copies
                Node* removeNode = deleteNode;
                deleteNode = deleteNode->nextTime;
                delete removeNode;
                removeNode = nullptr;
                size--;

            }while (deleteNode && deleteNode->data.getTimeStamp() == timeStamp);
            return true;
        }
        else
        {
            deleteNode = deleteNode->nextTime;
        }
    }
   return false;
}

int LinkList::entriesLessThanFifty()
{
    int     count = 0;
    Node    *curr = headTemp;
    while (curr)
    {
        if (curr->data.getTemperature() < -500)
            count++;
        curr = curr->nextTemp;
    }
    return count;
}


int LinkList::entriesMoreThanZero()
{
    int     count = 0;
    Node    *curr = headTemp;
    //counts the entries that are more than zero
    while (curr)
    {
        if (curr->data.getTemperature() > 0)
            count++;
        curr = curr->nextTemp;
    }
    return count;
}

int LinkList::mostCommonTemp()
{
    Node    *curr = headTemp;
    int     maxCount = 0;
    int     mostCommon = curr->data.getTemperature();
    //Enters a first loop to check every number
    for (curr; curr; curr= curr->nextTemp)
    {
        int    tempCommon = curr->data.getTemperature();
        int    tempCount = 1;
        
        //enters second loop to compare rest of numbers and add up most common
        for (Node *currTwo = curr->nextTemp; currTwo; currTwo = currTwo->nextTemp)
        {       
             if (tempCommon == currTwo->data.getTemperature())
                    tempCount++;
        }
        //checks count and assigns most common temperature
        if (maxCount < tempCount)
        {
                maxCount = tempCount;
                mostCommon = tempCommon;
        }     
    }
    return mostCommon;
}

int LinkList::entriesZeroWindspeed()
{
    int     count = 0;
    Node    *curr = headWind;
    //checks for entries that are more than zero windspeed
    while (curr)
    {
        if (curr->data.getWindSpeed() == 0)
            count++;
        curr = curr->nextWind;
    }
    return count;
}

int LinkList::entriesMoreThanTwentyFive()
{
    int     count = 0;
    Node    *curr = headWind;
    //checks for entries more than 25 m/s windspeed
    while (curr)
    {
        if (curr->data.getWindSpeed() > 2500)
            count++;
        curr = curr->nextWind;
    }
    return count;
}

int LinkList::mostCommonWind()
{
    Node    *curr = headWind;
    int     maxCount = 0;
    int     mostCommon = curr->data.getWindSpeed();
    //Enters a first loop to check every number
    for (curr; curr; curr= curr->nextWind)
    {
        int    tempCommon = curr->data.getWindSpeed();
        int    tempCount = 1;
        
        //enters second loop to compare rest of numbers and add up most common
        for (Node *currTwo = curr->nextWind; currTwo; currTwo = currTwo->nextWind)
        {       
             if (tempCommon == currTwo->data.getWindSpeed())
                    tempCount++;
        }
        //checks count and assigns most common windspeed
        if (maxCount < tempCount)
        {
                maxCount = tempCount;
                mostCommon = tempCommon;
        }     
    }
    return mostCommon;
}

int LinkList::averageRangeTemp(int first, int second)
{
    int     sum = 0;
    int     target = 0;
    Node    *curr = headTemp;
    
    //moves pointer to position in list to start from
    while (curr && target != first)
    {   
        target++;
        curr = curr->nextTemp;
    }
    //begins to sum the total of the temperatures
    for (target; target <= second; target++)
    {
        
        sum += (curr->data.getTemperature());
        curr = curr->nextTemp;
    } 
    return sum;
}

int LinkList::averageRangeWind(int first, int second)
{
    int     sum = 0;
    int     target = 0;
    Node    *curr = headWind;
    
    //moves pointer to position in list to start from
    while (curr && target != first)
    {   
        target++;
        curr = curr->nextWind;
    }
    //begins to sum the total temperatures
    for (target; target <= second; target++)
    {
        sum += curr->data.getWindSpeed();
        curr = curr->nextWind;
    } 
    return sum;
}

//Class accessor functions
const int LinkList::getSize()
{
    return size;
}
  
int LinkList::getTimeTail()
{
    Node    *curr = headTime;
    while (curr->nextTime != nullptr)
        curr = curr->nextTime;
    return curr->data.getTimeStamp(); 
}

int LinkList::getTimeHead()
{
    return headTime->data.getTimeStamp();
}

int LinkList::getHeadTemp()
{
    return headTemp->data.getTemperature();
}

int LinkList::getHeadWind()
{
    return headWind->data.getWindSpeed();
}


