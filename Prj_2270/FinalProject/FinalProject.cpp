//Amir Kashipazha and Hamid Ashtiani
//04-20-2015
//Final Project
//Rhonda Hoenigman

#include <iostream>
#include <string>
#include <cstdlib>
#include "ClimateTree.h"
using namespace std;
int main(){
    ClimateTree climate_object= ClimateTree();
    string user_name;
    int choose=0;
    cout<<"Welcome to Climate Data for the Year of 2012"<<endl;
    //cout<<"Please enter your name: ";
    //cin>>user_name;
    //cout<<"Hi "<<user_name<<"! Please select from the following menu."<<endl;
    bool treeCreated = false;
    bool quitProgram =  false;

    while (quitProgram == false){
    cout<<"=========Main Menu========="<<endl;
    cout<<"1. Create a red-black tree"<<endl;
    cout<<"2. Separate Snow and Rain "<<endl;
    cout<<"3. Exclude Snow and Rain "<<endl;
    cout<<"4. Data for a specific Hour"<<endl;
    cout<<"5. Data for a specific Day"<<endl;
    cout<<"6. Get Monthly Summary"<<endl;
    cout<<"7. Get Annual Summary"<<endl;
    cout<<"8. Quit"<<endl;
    //cout<<"4. About us"<<endl;
    cin>>choose;
    if (choose==1){
        if(treeCreated == false){
            climate_object.readFile();
            cout<<endl;
            cout<<"Tree Was Created"<<endl;
            cout<<endl;
            treeCreated = true;
        }else{
            cout<<endl;
            cout<<"Tree Was Already Created"<<endl;
            cout<<endl;
        }

    }else if (choose==2){
        if(treeCreated == false){
            cout<<endl;
            cout<<"Please Create Tree"<<endl;
            cout<<endl;
        }else{
            climate_object.seperateSnowRain();
            cout<<endl;
            cout<<"Snow and Rain Was Separated"<<endl;
            cout<<endl;
        }

    }else if (choose==3){
        if(treeCreated == false){
            cout<<endl;
            cout<<"Please Create Tree"<<endl;
            cout<<endl;
        }else{
            climate_object.excludeSnowRain();
            cout<<endl;
            cout<<"Snow and Rain Was Excluded"<<endl;
            cout<<endl;
        }


    }else if (choose==4){
        if(treeCreated == false){
            cout<<endl;
            cout<<"Please Create Tree"<<endl;
            cout<<endl;
        }else{
            string time;
            cout<<endl;
            cout<<"Enter a hour that you'd like to look for data in the following order 2012MMDDHH"<<endl;
            cout<<"Hours starts from 00 to 23 for each day"<<endl;
            cin>>time;
            cout<<endl;
            climate_object.getHourlyClimateInfo(time);
            cout<<endl;
        }


    }else if (choose==5){
        if(treeCreated == false){
            cout<<endl;
            cout<<"Please Create Tree"<<endl;
            cout<<endl;
        }else{
            cout<<endl;
            cout<<"Please enter day in the following order 2012MMDD"<<endl;
            string day;
            cin>>day;
            cout<<endl;
            climate_object.GetDailySummary(day);
            cout<<endl;
        }

    }else if (choose==6){
        if(treeCreated == false){
            cout<<endl;
            cout<<"Please Create Tree"<<endl;
            cout<<endl;
        }else{
            cout<<endl;
            climate_object.GetMontlySummary();
            cout<<endl;
        }

    }else if (choose==7){
        if(treeCreated == false){
            cout<<endl;
            cout<<"Please Create Tree"<<endl;
            cout<<endl;
        }else{
            cout<<endl;
            climate_object.GetAnnulSummary();
            cout<<endl;
        }
    }else if (choose==8){
        quitProgram = true;
    }else{
        cout<<endl;
        cout<<"Invalid Input"<<endl;
        cout<<endl;
    }
    }
}

