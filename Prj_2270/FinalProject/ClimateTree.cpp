#include <iostream>
#include <string>
#include "ClimateTree.h"
#include <fstream>
#include <sstream>


using namespace std;

ClimateTree::ClimateTree(){
    nil = new climateNode;
    nil->parent = nil; //
    nil->right = nil;
    nil->left = nil;
    nil->isRed = false;
//    nil->title = "nil";

    root = nil;

}

//void elimnateSpace(){

//}

void ClimateTree::readFile(){

    ifstream inputFile;
    inputFile.open("data.txt");   // initiate a variable type for input file
    string fileDelimate1, fileDelimate2, fileDelimate3, fileDelimate4;

    int lineCounter = 0;

    string strSave,token;
    string time, timePRV, skyPrv, tempStr;
    int wDirPrv = 0, wSpdPrv = 0, temprPrv = 0, prcpPrv = 0;

    getline(inputFile,strSave);
    //inputFile.ignore(1); // ignoring first line
    int couter = 0;
    while(getline(inputFile,strSave)){

            istringstream ss(strSave); // ss is stream of string that help us to use get line for the line, this line is for seperating with comma

            int wDir = 0, wSpd = 0, tempr = 0, prcp = 0;
            string sky;
            int colNum = 0;
            while (getline(ss,token,' ')){

                //cout<<token<<endl;
                //cout<<colNum<<endl;
                if(colNum == 2){
                    time = token.substr(0,10);
                }
                //cout<<"1:   "<<time<<endl;
                if(colNum == 3){
                    tempStr = token;
                    if(tempStr == "***"){
                    wDir = 0;
                    }else{
                    wDir = stoi(tempStr);
                    }
                }
                if(colNum == 4){
                    tempStr = token;
                    if(tempStr == "***"){
                        wSpd = 0;
                    }else{
                        wSpd = stoi(tempStr);
                    }
                }
                if(colNum == 7){
                    sky = token;
                }
                if(colNum == 21){
                    tempr = stoi(token);
                }
                if(colNum == 28){
                    tempStr = token;
                    if(tempStr == "*****"){
                    prcp =0;
                    }else{
                    prcp = stoi(tempStr);
                    }
                }
                colNum++;
            }

            //cout<<time<<endl;
            if(timePRV == time || lineCounter == 0){
                timePRV = time;
                wDirPrv += wDir;
                wSpdPrv += wSpd;
                skyPrv = sky;
                temprPrv += tempr;
                prcpPrv += prcp;
                couter++;

            }else{
                wDirPrv = wDirPrv/couter;
                wSpdPrv = wSpdPrv/couter;
                temprPrv = temprPrv/couter;
                cout<<timePRV<<"   "<<wDirPrv<<endl;
                int snow;
                int rain;
                if(temprPrv < 0 && prcpPrv > 0){
                    snow = prcpPrv;
                }else{
                    rain = prcpPrv;
                }

                //        addMovieNode(ranking, title, year, quantity);
                timePRV = time;
                skyPrv = sky;
                wDirPrv = wDir;
                wSpdPrv = wSpd;
                temprPrv = tempr;
                prcpPrv = prcp;
                couter = 1;
            }





        lineCounter++;

    }



}

