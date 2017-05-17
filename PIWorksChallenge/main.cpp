//
//  main.cpp
//  PIWorksChallenge
//
//  Created by Huseyin Yusuf on 11/05/2017.
//  Copyright © 2017 Huseyin Yusuf. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include "InputObject.h"
#include "distictCount.h"
#include "FinalOutput.h"
#include <vector>
#include <string>
using namespace std;
int main(int argc, const char * argv[]) {
    // insert code here...
    FILE *fp;
    fp = fopen("exhibitA-input.csv", "r+");
    vector<InputObject> inputVector;
    vector<FinalOutput> finalOutput;
    int index=0;
    InputObject* tmp = new InputObject();
    distinctCount* tmp2 = new distinctCount();
    FinalOutput* tmp3 = new FinalOutput();
    int songId;
    while (fgetc(fp) != EOF){
        if (index==0){
            fscanf(fp, "%s %s %s %s\n",tmp->playId, tmp->playId,tmp->playId,tmp->playId);
            index++;
            continue;
        }
        fscanf(fp, "%s %d %d %s\n",tmp->playId, &tmp->songId,&tmp->clientId,tmp->date);
        index++;
        if(strcmp(tmp->date,"10/08/2016")==0){
            inputVector.push_back(*tmp);
        }
    }
    cout<<"initial size: "<<index<<endl;
    cout<<"Date Filter: "<<inputVector.size()<<endl;
    bool exist = 0;
    bool existingsong=0;
    vector<distinctCount> interArray;
    int clientIndex = -4;
    for(int i=0;i<inputVector.size();i++){
        tmp2->clientId=inputVector.at(i).clientId;
        songId=inputVector.at(i).songId;
        for(int j=0;j<interArray.size();j++){
            if(interArray.at(j).clientId==tmp2->clientId){
                clientIndex=j;
                exist=1;
                break;
            }else{
                exist=0;
            }
        }
        if(exist==0){
            tmp2->clientId=inputVector.at(i).clientId;
            tmp2->songVector.push_back(inputVector.at(i).songId);
            interArray.push_back(*tmp2);
        }else{
            for(int k=0;k<interArray.at(clientIndex).songVector.size();k++){
                if(interArray.at(clientIndex).songVector.at(k)==songId){
                    existingsong=1;
                    break;
                }else{
                    existingsong=0;
                }
            }
            if(existingsong==0){
                interArray.at(clientIndex).songVector.push_back(songId);
            }
        }
    }
    cout<<"Cliet Number"<<interArray.size()<<endl;
    
    bool distinctCountExist=0;
    int distinctPlayCountIndex=-2;
    for(int i=0;i<interArray.size();i++){
        tmp3->distinctPlayCount=interArray.at(i).songVector.size();
        for(int j=0;j<finalOutput.size();j++){
            if (finalOutput.at(j).distinctPlayCount==tmp3->distinctPlayCount){
                distinctPlayCountIndex=j;
                distinctCountExist=1;
                break;
            }else{
                distinctCountExist=0;
            }
        }
        if(distinctCountExist==0){
            tmp3->clientCount=1;
            finalOutput.push_back(*tmp3);
        }else{
            finalOutput.at(distinctPlayCountIndex).clientCount+=1;
        }
    }
    
    for(int i=0;i<finalOutput.size();i++){
        cout<<finalOutput.at(i).distinctPlayCount<<" - "<<finalOutput.at(i).clientCount<<endl;
    }
    return 0;
}
