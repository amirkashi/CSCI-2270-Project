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
    while (choose!=10){
    cout<<"=========Main Menu========="<<endl;
    cout<<"1. Create a red-black tree"<<endl;
    cout<<"2. Data for a specific Hour"<<endl;
    cout<<"3. Data for a specific Day"<<endl;
    cout<<"4. Get Monthly Summary"<<endl;
    cout<<"5. Get Annual Summary"<<endl;
    //cout<<"4. About us"<<endl;
    cin>>choose;
    if (choose==1)
    {
        climate_object.readFile();
        //climate_object.rbValid();
        cout<<"Tree Was Created"<<endl;

    }else if (choose==2){
        string time;
        cout<<"Enter a hour that you'd like to look for data in the following order 2012MMDDHH"<<endl;
        cout<<"Hours starts from 00 to 23 for each day"<<endl;
        cin>>time;
        climate_object.getHourlyClimateInfo(time);

    }else if (choose==3){
        cout<<"Please enter day in the following order 2012MMDD"<<endl;
        string day;
        cin>>day;
        climate_object.settotalNodeDay();
        climate_object.GetDailySummary(day);
    }else if (choose==4){
        //climate_object.AssingMonthNumberStr();
        climate_object.GetMontlySummary();

    }else if (choose==5){
        climate_object.GetAnnulSummary();
    }else if (choose==5){
        cout<<"This project was created my Amir Kashipazha and Hamid Ashtiani. \n"
        "We used data from the Boulder Municipal Airport and collected\n"
        "5,375 observations. We wanted to provide weather data in Boulder, Colorado\n"
        "from 2012. This allows us to keep track of inconsistencies in weather and could\n"
        "perhaps allow us to make weather predictions for future days."<<endl;
    }
    if(choose == 5){


    }
    cout<<"Thanks for visiting us!"<<endl;

    }
}
