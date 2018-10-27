#include <iostream>
#include <string>
#include <cstdlib>
#include "ClimateTree.h"
using namespace std;


void menue(){
    cout<<"=========Main Menu========="<<endl;
    cout<<"1. Create a red-black tree"<<endl;
    cout<<"2. Separate Snow and Rain "<<endl;
    cout<<"3. Exclude Snow and Rain "<<endl;
    cout<<"4. Data for a specific Hour"<<endl;
    cout<<"5. Data for a specific Day"<<endl;
    cout<<"6. Get Monthly Summary"<<endl;
    cout<<"7. Get Annual Summary"<<endl;
    cout<<"8. Quit"<<endl;
}

int main(){
    ClimateTree climate_object= ClimateTree();
    string user_name;
    int choose = 0;
    cout<<"Welcome to Climate Data for the Year of 2012"<<endl;
    bool treeCreated = false;
    bool quitProgram =  false;
    while (quitProgram == false){
        menue();
        cin>>choose;
        if (choose == 1){
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
        }else if (choose == 2){
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
        }else if (choose == 3){
            if(treeCreated == false){
                cout<<endl;
                cout<<"Please Create Tree"<<endl;
                cout<<endl;
            }else{
                cout<<endl;
                cout<<"Snow and Rain Was Excluded"<<endl;
                climate_object.excludeSnowRain();
                cout<<endl;
            }
        }else if (choose == 4){
            if(treeCreated == false){
                cout<<endl;
                cout<<"Please Create Tree"<<endl;
                cout<<endl;
            }else{
                string month, day, hour, time;
                cout<<endl;
                cout<<"Please enter the data in the following order"<<endl;
                cout<<endl;
                cout<<"Enter a month (MM): ";
                cin>>month;
                cout<<"Enter a day (DD): ";
                cin>>day;
                cout<<"Enter an hour (please enter in the form of 00 to 23): ";
                cin>>hour;
                time="2012"+month+day+hour;
                cout<<endl;
                climate_object.getHourlyClimateInfo(time);
                cout<<endl;
            }
        }else if (choose == 5){
            if(treeCreated == false){
                cout<<endl;
                cout<<"Please Create Tree"<<endl;
                cout<<endl;
            }else{
                cout<<endl;
                string month, day, time;
                cout<<"Enter a month (MM): ";
                cin>>month;
                cout<<"Enter a day (DD): ";
                cin>>day;
                time= "2012"+month+day;
                cout<<endl;
                cout<<"Climate Information for "<<month<<"/"<<day<<"/2012"<<endl;
                climate_object.GetDailySummary(time);
                cout<<endl;
            }
        }else if (choose == 6){
            if(treeCreated == false){
                cout<<endl;
                cout<<"Please Create Tree"<<endl;
                cout<<endl;
            }else{
                cout<<endl;
                climate_object.GetMonthlySummary();
                cout<<endl;
            }
        }else if (choose == 7){
            if(treeCreated == false){
                cout<<endl;
                cout<<"Please Create Tree"<<endl;
                cout<<endl;
            }else{
                cout<<endl;
                climate_object.GetAnnulSummary();
                cout<<endl;
            }
        }else if (choose == 8){
            cout<<endl;
            cout<<"Goodbye!"<<endl;
            cout<<"Thanks for using our software!"<<endl;
            quitProgram = true;
        }else{
            cout<<endl;
            cout<<"Invalid Input"<<endl;
            cout<<endl;
        }
    }
}
