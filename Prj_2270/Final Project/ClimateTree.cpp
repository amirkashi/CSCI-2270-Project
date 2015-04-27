#include <iostream>
#include <string>
#include "ClimateTree.h"
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;
/*
Function description:
This is the constructor, it initializes the nil.
*/
ClimateTree::ClimateTree(){
    nil = new climateNode;
    nil->parent = nil;
    nil->right = nil;
    nil->left = nil;
    nil->isRed = false;
    root = nil;
}
/*
Function prototype:
void ClimateTree::readFile()

Function description:
This function opens the csv file, reads in the data and assigns each data category to their respective variable.
Averages and sums of each variable are taken and are added to the insert into the red black tree function.

Example:
ClimateTree climate_obj;
climate_obj.readFile();

Precondition:
The function does not take any parameters, since we only wanted to examine the data from 2012.


Postcondition:
The function does not return anything and it creates the red black tree.

*/
void ClimateTree::readFile(){

    ifstream inputFile;
    inputFile.open("DataPRT.csv");   // initiate a variable type for input file

    int lineCounter = 0; // count number of line of the file

    string strSave,token; // strSave saves one line , token saves column of each line like prcp
    string time, timePRV,  tempStr; // time = time of each line, timePRV = time of previous line, temprPrv = save word on line
    float wDirPrv = 0.0, wSpdPrv = 0.0, temprPrv = 0.0, prcpPrv = 0.0; // save climate info of previous lines


    getline(inputFile,strSave); // ignore first line (info names)

    bool wDirStr = false, wSpdStr = false, TmpStr = false; // for checking if a value is * or not, * means no data
    float  wDirCo = 0.0,      wSpdCo = 0.0,      TmpCo = 0.0; // count how many value we have for each time

    while(getline(inputFile,strSave)){

            istringstream ss(strSave); // ss is stream of string that help us to use get line for the line, this line is for seperating with comma

            float wDir = 0.0, wSpd = 0.0, tempr = 0.0, prcp = 0.0; // saving climate property of each line

            int colNum = 0; // count number of column (data between ,) for each line
            // getting climate info for each line
            while (getline(ss,token,',')){

                if(colNum == 2){ //time
                    time = token.substr(0,10);
                }

                if(colNum == 3){   //      wind direction
                    tempStr = token;
                    if(tempStr == "***"){
                        wDirStr = true;
                    }else{
                        wDir = stoi(tempStr);
                        wDirStr = false;
                    }
                }
                if(colNum == 4){ // wind speed
                    tempStr = token;
                    if(tempStr == "***"){
                        wSpdStr = true;
                    }else{
                        wSpd = stoi(tempStr);
                        wSpdStr = false;
                    }
                }

                if(colNum == 21){ // temperature
                    tempStr = token;
                    if(tempStr == "****"){
                        TmpStr = true;
                    }else{
                        tempr =stoi(tempStr);
                        TmpStr = false;
                    }
                }
                if(colNum == 28){ // prcp
                    tempStr = token;
                    if(tempStr == "*****"){
                        prcp = 0.0;
                    }else{
                        prcp = stof(tempStr);
                    }
                }
                colNum++;
            }

            // comparing time of previous line and current line
            if(timePRV == time || lineCounter == 0){
                timePRV = time;

                if(wDirStr == false){
                    wDirPrv += wDir;
                    wDirCo++;
                }
                if(wSpdStr == false){
                    wSpdPrv += wSpd;
                    wSpdCo++;
                }

                if(TmpStr == false){
                    temprPrv += tempr;
                    TmpCo++;
                }

                prcpPrv += prcp;

                wDirStr = false;
                wSpdStr = false;
                TmpStr = false;

            }else{
                // these if statements is for avoiding 0/0
                if(wDirCo == 0) {
                    wDirCo = 1;
                }
                if(wSpdCo == 0){
                    wSpdCo = 1;
                   }
                if(TmpCo == 0){
                    TmpCo = 1;
                }


                wDirPrv = wDirPrv/wDirCo;
                wSpdPrv = wSpdPrv/wSpdCo;
                temprPrv = temprPrv/TmpCo;

                float snow = 0.0;
                float rain = 0.0;


                //cout<<timePRV<<"|"<<wDirPrv<<" : "<<wDirCo<<"|"<<wSpdPrv<<" : "<<wSpdCo <<"|"<<tempr<<":"<<TmpCo<<"|"<<prcpPrv<< endl;
                //cout<<timePRV<<":"<<wDirPrv<<":"<<wSpdPrv<<":"<<temprPrv<<":"<<prcpPrv<<endl;
                addDayNode(timePRV, temprPrv, prcpPrv, rain, snow, wDirPrv, wSpdPrv);
                timePRV = time;
                wDirPrv = wDir;
                wSpdPrv = wSpd;
                temprPrv = tempr;
                prcpPrv = prcp;

                wDirCo = 1;
                wSpdCo = 1;
                TmpCo = 1;

                wDirStr = false;
                wSpdStr = false;
                TmpStr = false;
            }

        lineCounter++;
    }
}
/*
Function prototype:
void ClimateTree::addDayNode(string, float, float, float, float, float, float)

Function description:
This function adds in the climateNode's attributes into a red-black tree. Since the data is inserted into a
red-black tree, the rbAddFixup is called to fix the insertion of each node according to the red-black tree rules.

Example:
ClimateTree climate_obj;
climate_obj.addDayNode(2012053020, 55.5, 11.6, 4.9, 6.9, 4.2, 7.7);

Precondition:
The function takes 7 parameters, the time is read in as a string, and the rest of the data
points are read in as floats.

Postcondition:
The function does not return anything and it adds the nodes to the red-black tree, fixing
the tree with every time a node is added.

*/

void ClimateTree::addDayNode(string tim, float tem, float prc, float ran, float snw, float wdir,float wspd){


    climateNode *y = nil;
    climateNode *x = root;

    while(x != nil){
        y = x;

        if(tim.compare(x->time)<0){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }

    climateNode *newDay = new climateNode;

    newDay->time = tim;
    newDay->temperature = tem;
    newDay->precipitation = prc;
    newDay->rain = ran;
    newDay->snow = snw;
    newDay->WindDir = wdir;
    newDay->WindSpeed = wspd;
    newDay->parent = y;
    newDay->isRed = true;
    newDay->left = nil;
    newDay->right = nil;

    if(y == nil){
        root = newDay;
    }
    else if(tim.compare(y->time)<0){
        y->left = newDay;
    }
    else{
        y->right = newDay;
    }

    rbAddFixup(newDay);
}
/*
Function prototype:
void ClimateTree::rbAddFixup(climateNode *rootAdd)

Function description:
This primary intent of this function is to fix the inserted nodes of a tree according to the red-black tree rules.
Furthermore, this function calls the rightRotate and leftRotate functions every time the insertions
are not aligned with the red-black tree rules.
Example:
ClimateTree climate_obj;
climate_obj.rbAddFixup(root);

Precondition:
The function takes a climateNode* as a parameter as it start fixing the insertions in the addDayNode function.

Postcondition:
The function does not return anything, it fixes the tree according to red-black tree rules and is called in the
addDayNode function.

*/
void ClimateTree::rbAddFixup(climateNode *rootAdd){

    climateNode *z = rootAdd;

    while(z != root && z->parent->isRed == true){


        if(z->parent == z->parent->parent->left){
            climateNode *y = z->parent->parent->right;

            if(y->isRed == true){
                z->parent->isRed = false;
                y->isRed = false;
                z->parent->parent->isRed = true;
                z = z->parent->parent;

            }else {
                if(z == z->parent->right){
                    z = z->parent;
                    leftRotate(z);
                }

                z->parent->isRed = false;
                z->parent->parent->isRed = true;
                rightRotate(z->parent->parent);
            }
        }else{

            climateNode *y = z->parent->parent->left;

            if(y->isRed == true){
                z->parent->isRed = false;
                y->isRed = false;
                z->parent->parent->isRed = true;
                z = z->parent->parent;

            }else{
                if(z == z->parent->left){
                    z = z->parent;
                    rightRotate(z);

                }
                z->parent->isRed = false;
                z->parent->parent->isRed = true;
                leftRotate(z->parent->parent);
            }
        }
    }


    root->isRed = false;

}

// ----------------------------------------------------------------------- left rotate
/*
Function prototype:
void ClimateTree::leftRotate(climateNode *cursor)

Function description:
The primary function of the leftRotate and rightRotate are red-black tree balancing. They are both called
in the rbAddFixUp function and they ensure that the red-black tree rules are held.
Example:
ClimateTree climate_obj;
climate_obj.leftRotate(root);

Precondition:
The function takes a climateNode* as a parameter as it balances the red-black tree.

Postcondition:
The function does not return anything, it fixes the tree according to red-black tree rules and is called in the
rbAddFixUp function.

*/
void ClimateTree::leftRotate(climateNode *cursor){
    climateNode *x = cursor;
    climateNode *y = x->right;

    x->right = y->left;

    if (y->left != nil){
        y->left->parent = x;
    }
    y->parent = x->parent;

    if(x->parent == nil){
         root = y;
    }else{
        if(x == x->parent->left){
            x->parent->left = y;
        }else{
            x->parent->right = y;
        }
    }
    y->left = x;
    x->parent = y;
}

// ----------------------------------------------------------------------- right rotate
/*
Function prototype:
void ClimateTree::rightRotate(climateNode *cursor)

Function description:
The primary function of the leftRotate and rightRotate are red-black tree balancing. They are both called
in the rbAddFixUp function and they ensure that the red-black tree rules are held.
Example:
ClimateTree climate_obj;
climate_obj.rightRotate(root);

Precondition:
The function takes a climateNode* as a parameter as it balances the red-black tree.

Postcondition:
The function does not return anything, it fixes the tree according to red-black tree rules and is called in the
rbAddFixUp function.

*/
void ClimateTree::rightRotate(climateNode *cursor){
    climateNode *x = cursor;
    climateNode *y = x->left;

    x->left = y->right;

    if (y->right != nil){
        y->right->parent = x;
    }
    y->parent = x->parent;

    if(x->parent == nil){
         root = y;
    }else{
        if(x == x->parent->right){
            x->parent->right = y;
        }else{
            x->parent->left = y;
        }
    }
    y->right = x;
    x->parent = y;
}

// --------------- snow calculation
/*
Function prototype:
void ClimateTree::ClimateTree::excludeSnowRain()

Function description:
User has the option not to read in snow and rain data by excluding them. We created a boolean variable (snowCalcYes).
When this variable is "false", the code does not show snow and rain calculations.

Precondition:
snowCalcYes = true, the function does not take any parameters.

Postcondition:
snowCalcYes = false, this function does not return anything.

*/
void ClimateTree::excludeSnowRain(){
    snowCalcYes = false;
}
/*
Function prototype:
void ClimateTree::setSnowRain_0(climateNode* node)

Function description:
This function initialize values for snow and rain before calculation. This prevents adding snow or rain to previous values when user
calculates (or runs seperateSnowRain function) more than once.

Precondition:
snow and rain values could be 0 or more.

Postcondition:
snow and rain values are set to 0.

*/
void ClimateTree::setSnowRain_0(climateNode* node){

    if(node == nil)
        return;

    if(node != nil){
        node->snow = 0.0;
        node->rain = 0.0;
    }

    if(node->left != nil){
        setSnowRain_0(node->left);
    }

    if(node->right != nil){
        setSnowRain_0(node->right);
    }

}
/*
Function prototype:
climateNode* ClimateTree::seperateSnowRain(climateNode* node)

Function description:
This function gives the user the option to exclude rain and snow while viewing the data. Its main
purpose is to facilitate viewing data for the user.

Example:
ClimateTree climate_obj;
climate_obj.seperateSnowRain(root);

Precondition:
The function takes a climateNode* as a parameter. As we start from the root and traverse the tree
to check for snow when temperatures are below 32F and precipitation above 0 and rain when those conditions fail.
We also assigned climateNode attributes snow and rain in this function.

Postcondition:
The function does not return anything, it assigns snow and rain climateNode variables according to our conditionals.
*/

void ClimateTree::seperateSnowRain(climateNode* node){

    if(node == nil)
        return;

    if(node != nil){
        if(node->temperature <= 32 && node->precipitation > 0.0){
            node->snow = node->precipitation;
        }else{
            node->rain = node->precipitation;
        }
    }

    if(node->left != nil){
        seperateSnowRain(node->left);
    }

    if(node->right != nil){
        seperateSnowRain(node->right);
    }
}

void ClimateTree::seperateSnowRain(){
    snowCalcYes = true;
    setSnowRain_0(root);
    seperateSnowRain(root);
}


// ---------------- hourly calculation
/*
Function prototype:
climateNode* ClimateTree::searchClimateData(climateNode* node, string time)

Function description:
This function searches for a specific node in the red black tree. First, it checks the the very first element,
if the node is not found, then the function recursively calls itself and finds the data by checking the right
and left sub trees.

Example:
ClimateTree climate_obj;
climate_obj.searchClimateData(root, 2012053008);

Precondition:
The function takes two parameters the root and the desired data value to search. This method is created for
the getHourlyClimateInfo(string time).

Postcondition:
The function returns the climateNode of the desired data point.

*/

climateNode* ClimateTree::searchClimateData(climateNode* node, string time){

    if (node->time == ""){
        return nil;
    }else if(node->time==time){
        return node;
    }else{
        if (time.compare(node->time)<0){
            return searchClimateData(node->left, time);
        }else{
            return searchClimateData(node->right, time);
        }
    }
}
/*
Function prototype:
void ClimateTree::getHourlyClimateInfo(string time)

Function description:
The intent for this method is to print out the hourly information from the data. The function first search the
red-black tree by calling the searchClimateData function. The function is set, such that if the search function
finds the desired data, the function will print out the specific data pertaining to that day and hour, otherwise
it will ask the user to request another date.

Example:
ClimateTree climate_obj;
climate_obj.getHourlyClimateInfo(2012053008);

Precondition:
The function takes a string as parameter and when it prints the information it rounds up the values for efficiency
and makes the data easier to read.

Postcondition:
The function does not return anything, just prints to the screen the desired information.
*/

void ClimateTree::getHourlyClimateInfo(string time){

    climateNode* findClimate= searchClimateData(root, time);
    if (findClimate!=nil){

        cout<<"Climate Information for: "<<time.substr(4,2)<<"/"<<time.substr(6,2)<<"/"<<
                time.substr(0,4)<<" at hour : "<<stoi(time.substr(8,2))<< " was "<< endl;
        cout<<"Temperature (F): "<< setprecision(0) << fixed<<findClimate->temperature<<endl;
        cout<<"Precipitation (in): "<<setprecision(2) << fixed<<findClimate->precipitation<<endl;
        if(snowCalcYes == true){
            cout<<"Rain (in): "<<setprecision(2) << fixed<<findClimate->rain<<endl;
            cout<<"Snow (in): "<<setprecision(2) << fixed<<findClimate->snow<<endl;
        }
        cout<<"Wind Speed (Miles/Hour): "<<setprecision(1) << fixed<<findClimate->WindSpeed<<endl;
        cout<<"Wind Direction (Degrees): "<<setprecision(0) << fixed<<findClimate->WindDir<<endl;
    }else{
        cout<<"The date you were looking for does not exist, please try again"<<endl;
    }

}
/*
Function prototype:
void ClimateTree::settotalNodeDay()

Function description:
The main purpose of this function is to set the node count to 0. The reason we implemented this was to avoid
over calculating the counting of each node.

Example:
ClimateTree climate_obj;
climate_obj.settotalNodeDay();

Precondition:
The function does not take any parameters.

Postcondition:
The function does not return anything, and sets totalNodeCount to 0.
*/
void ClimateTree::settotalNodeDay(){
    totalNodeCount = 0;
}
/*
Function prototype:
void ClimateTree::setDailySummary_0()

Function description:
This function sets the climateNode attributes to 0. This prevents over calculating the attributes for more
than one day.

Precondition:
The function does not take any parameters, the attributes could take on various values.

Postcondition:
The function does not return anything, just sets the attributes back to 0.

*/
void ClimateTree:: setDailySummary_0(){
    DailySumary->precipitation = 0.0;
    DailySumary->temperature = 0.0;
    DailySumary->rain = 0.0;
    DailySumary->snow = 0.0;
    DailySumary->WindDir = 0.0;
    DailySumary->WindSpeed = 0.0;
    DailySumary->totalNodes = 0.0;
}

/*
Function prototype:
void ClimateTree::GetDailySummary(climateNode*, string )

Function description:
The main purpose of the function is to get the daily summary of the data points. The function first retrieves for
the first 8 character which include up to the day. Next, it search adds up all the data points for that specific
day.

Example:
ClimateTree climate_obj;
climate_obj.GetDailySummary(root,20120304);

Precondition:
The function takes two parameters the root and the desired day to search. This method is created for
the GetDailySummary(string) that displays the daily information. Also, totalNodeCount is incremented each
time and it is intended for the averages in the data.

Postcondition:
The function does not return anything.
*/
void ClimateTree::GetDailySummary(climateNode* node, string day){

    if(node == nil)
        return;

    if(node != nil){
        if(node->time.substr(0,8) == day){
            DailySumary->precipitation += node->precipitation;
            DailySumary->temperature += node->temperature;
            DailySumary->rain += node->rain;
            DailySumary->snow += node->snow;
            DailySumary->WindDir += node->WindDir;
            DailySumary->WindSpeed += node->WindSpeed;
            totalNodeCount++;

        }
    }


    if(node->left != nil){
        GetDailySummary(node->left, day);
    }

    if(node->right != nil){
        GetDailySummary(node->right, day);
    }

}
/*
Function prototype:
void ClimateTree::GetDailySummary(string)

Function description:
The main purpose of the function is to print to the screen the information for a given day in 2012. The
function first calls the GetDailySummary(climateNode*, string) to first calculate the sums and averages, then
prints out the calculated information.

Example:
ClimateTree climate_obj;
climate_obj.GetDailySummary(20120304);

Precondition:
The function takes a string parameter. It also adjusts the precision of the floats to facilitate reading the
information for the user.

Postcondition:
The function does not return anything, it just displays the data.
*/
void ClimateTree::GetDailySummary(string day){
    settotalNodeDay();
    setDailySummary_0();
    GetDailySummary(root, day);
    //cout<<getNumberOfNodes(root)<<endl;
    //cout<<totalNodeCount<<endl;
    //cout<<"Climate Information for "<<DailySumary->time.substr(4,2)<<"/"<<DailySumary->time.substr(6,2)<<"/2012"<<endl;
    cout<<"Temperature (F): "<< setprecision(0) << fixed<<(DailySumary->temperature)/totalNodeCount<<endl;
    cout<<"Total Precipitation (in): "<<setprecision(2) << fixed<<DailySumary->precipitation<<endl;
    if(snowCalcYes == true){
        cout<<"Rain (in): "<<setprecision(2) << fixed<<(DailySumary->rain)<<endl;
        cout<<"Snow (in): "<<setprecision(2) << fixed<<(DailySumary->snow)<<endl;
    }
    cout<<"Wind Speed (Miles/Hour): "<<setprecision(1) << fixed<<(DailySumary->WindSpeed)/totalNodeCount<<endl;
    cout<<"Wind Direction (Degrees): "<<setprecision(0) << fixed<<(DailySumary->WindDir)/totalNodeCount<<endl;

    //cout<<"total "<<DailySumary->totalNodes<<endl;
}
// -------------------------         Monthly
/*
Function prototype:
void ClimateTree::setMonthlySummary_0()

Function description:
This function sets the climateNode attributes to 0. This prevents over calculating the attributes for more
than one month.

Example:
ClimateTree climate_obj;
climate_obj.setMonthlySummary_0();

Precondition:
The function does not take any parameters, the attributes could take on various values.

Postcondition:
The function does not return anything, just sets the attributes back to 0.

*/
void ClimateTree::setMontlhySummary_0(){
    for(int i = 0; i < 12; i++){
        mont[i].precipitation = 0.0;
        mont[i].temperature = 0.0;
        mont[i].rain = 0.0;
        mont[i].snow = 0.0;
        mont[i].WindDir = 0.0;
        mont[i].WindSpeed = 0.0;
        mont[i].totalNodes = 0.0;
    }
}
/*
Function prototype:
void ClimateTree::AssignMonthNumberStr()

Function description:
This function assigns numerical string values to the time attribute in the climateNode.
We created a private climateNode array that stores each month and stores as numerical strings. The main purpose
of this function is to compare each month inserted into the tree with the values in the array. This way, we can keep
track of the months and get the desired data values.

Example:
ClimateTree climate_obj;
climate_obj.AssignMonthNumberStr();

Precondition:
The function does not take any parameters and assigns the private value time the string monthly numbers.

Postcondition:
The function does not return anything and it assigns string numerical values to time.
*/
void ClimateTree::AssignMonthNumberStr(){
    string monthStr[12] = {"01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12"};
    for(int i = 0; i < 12; i++){
        mont[i].time = monthStr[i];
    }
}
/*
Function prototype:
void ClimateTree::GetMonthlySummary(climateNode* node, string month, int arN)

Function description:
This function calculates all the climateNode attributes for all the months and saves them as a month node
in the array. It also keeps track of the nodes visited to allow us to calculate attribute averages for each month.

Example:
ClimateTree climate_obj;
climate_obj.GetMonthlySummary(root, 05, 1);

Precondition:
The function takes three parameters, climateNode*, string, and integer which indicates the position of the node in
the array.

Postcondition:
The function does not return anything, it just updates the calculated attributes for each month.
*/

void ClimateTree::GetMonthlySummary(climateNode* node, string month, int arN){

        //cout<<"Before If ;  "<<month<<" = "<<arN<<endl;
        if(node == nil)
            return;

        if(node != nil){
        //cout<<node->time.substr(4,2)<<"       "<<mont[arN].time<<endl;
            if(node->time.substr(4,2) == month){


                mont[arN].precipitation += node->precipitation;
                mont[arN].temperature += node->temperature;
                mont[arN].rain += node->rain;
                mont[arN].snow += node->snow;
                mont[arN].WindDir += node->WindDir;
                mont[arN].WindSpeed += node->WindSpeed;
                mont[arN].totalNodes = ++totalNodeCount;
                //cout<<mont[arN].time<<"    "<<arN<<"    "<<node->precipitation<<endl;
                //cout<<node->time.substr(4,2)<<" "<<month<<endl;
            }

        }

        if(node->left != nil){
            GetMonthlySummary(node->left, month, arN);
        }

        if(node->right != nil){
            GetMonthlySummary(node->right, month, arN);
        }

}
/*
Function prototype:
void ClimateTree::AssignMonthNumberStr()()

Function description:
The main purpose of the function is to print to the screen the information for all the months. The
function first calls the AssignMonthNumberStr(), setMontlhySummary_0(), and settotalNodeDay() that calculate
the needed averages and the desired sums for the attributes in climateNode.

Example:
ClimateTree climate_obj;
climate_obj.GetMonthlySummary();

Precondition:
The function does not take anything as parameter, it calls the  AssignMonthNumberStr(), setMontlhySummary_0(),settotalNodeDay()
that calculates the desired numbers to get averages and sums for each individual month.

Postcondition:
The function does not return anything, it just displays the data for each month.
*/
void ClimateTree::GetMonthlySummary(){
    AssignMonthNumberStr();
    setMontlhySummary_0();

    settotalNodeDay();
    for(int arN = 0; arN < 12; arN++){

        GetMonthlySummary(root, mont[arN].time, arN);
        settotalNodeDay();

    }
    cout<<endl;
    cout<<"|Month\t\t\t\t\t";
    cout<<"| "<<"Jan\t"<<"| "<<"Feb\t"<<"| "<<"Mar\t"
        <<"| "<<"Apr\t"<<"| "<<"May\t"<<"| "<<"Jun\t"
        <<"| "<<"Jul\t"<<"| "<<"Aug\t"<<"| "<<"Sep\t"
        <<"| "<<"Oct\t"<<"| "<<"Nov\t"<<"| "<<"Dec\t"<<"|"<<endl;

    cout<<"|Average Temperature (F)\t\t";
    for(int j = 0; j<12; j++){
        cout<<"| "<<setprecision(0) << fixed<<(mont[j].temperature/mont[j].totalNodes)<<"\t";

    }
    cout<<"|"<<endl;

    cout<<"|Total Precipitation (in)\t\t";
    for(int j = 0; j<12; j++){
        cout<<"| "<<setprecision(2) << fixed <<mont[j].precipitation<<"\t";

    }
    cout<<"|"<<endl;

    if(snowCalcYes == true){
        cout<<"|Total rain (in)\t\t\t";
        for(int j = 0; j<12; j++){
            cout<<"| "<<setprecision(2) << fixed <<mont[j].rain<<"\t";
        }
        cout<<"|"<<endl;

        cout<<"|Total Snow (in)\t\t\t";
        for(int j = 0; j<12; j++){
            cout<<"| "<<setprecision(2) << fixed <<mont[j].snow<<"\t";
        }
        cout<<"|"<<endl;
    }


    cout<<"|Average Wind Speed (Mile/Hour)\t\t";
    for(int j = 0; j<12; j++){
        cout<<"| "<<setprecision(1) << fixed << (mont[j].WindSpeed/mont[j].totalNodes)<<"\t";

    }
    cout<<"|"<<endl;


    cout<<"|Average Wind Direction (Degrees)\t";
    for(int j = 0; j<12; j++){
        cout<<"| "<<setprecision(0) << fixed<<(mont[j].WindDir/mont[j].totalNodes)<<"\t";

    }
    cout<<"|"<<endl;
    cout<<endl;

}


// -------------------------         annual
/*
Function prototype:
void ClimateTree::setAnnualSummary_0()

Function description:
This function sets the climateNode attributes to 0. This prevents over calculating the attributes.

Example:
ClimateTree climate_obj;
climate_obj.setAnnualSummary_0();


Precondition:
The function does not take any parameters, the attributes could take on various values.

Postcondition:
The function does not return anything, just sets the attributes back to 0.

*/
void ClimateTree::setAnnualSummary_0(){

    AnnualSumary->precipitation = 0.0;
    AnnualSumary->temperature = 0.0;
    AnnualSumary->rain = 0.0;
    AnnualSumary->snow = 0.0;
    AnnualSumary->WindDir = 0.0;
    AnnualSumary->WindSpeed = 0.0;
    AnnualSumary->totalNodes = 0.0;

}
/*
Function prototype:
int ClimateTree::getNumberOfNodes(climateNode *n)

Function description:
This function traverses through the entire red-black tree to find the number of inserted nodes. Then it adds
1 to the traversals from the right and left sub trees to include the node n itself.
This was primarily created to find the weighted averages of the climateNode attributes.

Example:
ClimateTree climate_obj;
climate_obj.getNumberOfNodes(root);

Precondition:
The function takes a climateNode* as a parameter and starts adding up nodes from the root of the tree.

Postcondition:
The function returns an integer, total, which sums up the nodes as it traverses through the red-black tree.
*/

int ClimateTree::getNumberOfNodes(climateNode *n){
    int total = 0;
    if (n == nil){
        return  0;
    }else{
            total=1+getNumberOfNodes(n->left)+getNumberOfNodes(n->right);

    }
    return total;
}
/*
Function prototype:
void ClimateTree::GetAnnulSummary(climateNode* node)

Function description:
This function sums up the attributes of the climateNode such as temperature and wind direction for the year
of 2012. This was created primarily to give the user an outlook for weather in 2012.

Example:
ClimateTree climate_obj;
climate_obj.GetAnnulSummary(root);

Precondition:
The function takes the climateNode* as parameter and calculates the annual summary of the whole data.
Its called in the GetAnnulSummary() function that prints out the found information.

Postcondition:
The function does not return anything it simply adds up the attributes of the climateNode for the entire year.
*/

void ClimateTree::GetAnnulSummary(climateNode* node){

    if(node == nil)
        return;

    if(node != nil){

        AnnualSumary->precipitation += node->precipitation;
        AnnualSumary->temperature += node->temperature;
        AnnualSumary->rain += node->rain;
        AnnualSumary->snow += node->snow;
        AnnualSumary->WindDir += node->WindDir;
        AnnualSumary->WindSpeed += node->WindSpeed;
    }


    if(node->left != nil){
        GetAnnulSummary(node->left);
    }

    if(node->right != nil){
        GetAnnulSummary(node->right);
    }


}
/*
Function prototype:
void ClimateTree::GetAnnulSummary()

Function description:
This method calls the GetAnnulSummary(climateNode*) function which adds up all the attributes of the climateNode
for the entire year. The purpose for this function is to print out to the screen that information.

Example:
ClimateTree climate_obj;
climate_obj.GetAnnulSummary(root);

Precondition:
This function does not take any parameters.

Postcondition:
It is called in the FinalProject.cpp file, for when the user requests data for the entire year.
*/
void ClimateTree::GetAnnulSummary(){
    setAnnualSummary_0();
    GetAnnulSummary(root);
    //cout<<getNumberOfNodes(root)<<endl;
    float tot = getNumberOfNodes(root);
    cout<<"Climate Information for 2012"<<endl;
    cout<<"Average Temperature (F): "<<setprecision(0) << fixed<<(AnnualSumary->temperature)/tot<<endl;
    cout<<"Total Precipitation (in): "<<setprecision(2) << fixed<<AnnualSumary->precipitation<<endl;
    if(snowCalcYes == true){
        cout<<"Rain (in): "<<setprecision(2) << fixed<<(AnnualSumary->rain)<<endl;
        cout<<"Snow (in): "<<setprecision(2) << fixed<<(AnnualSumary->snow)<<endl;
    }
    cout<<"Wind Speed (Mile/Hour): "<<setprecision(1) << fixed<<(AnnualSumary->WindSpeed)/tot<<endl;
    cout<<"Wind Direction (Degrees): "<<setprecision(0) << fixed<<(AnnualSumary->WindDir)/tot<<endl;



}


/*
Function prototype:
int ClimateTree::rbValid(climateNode * root)

Function description:
We primarily used this function to make sure that our red-black tree was properly created. The function returns
an integer if the red-black tree is properly created.

Example:
ClimateTree climate_obj;
climate_obj.rbValid(root);

Precondition:
The function takes the root of the red-black tree as a parameter.

Postcondition:
The function returns an int if the red-black is tree correctly created.
*/
int ClimateTree::rbValid(climateNode * root)
{
    int lh = 0;
    int rh = 0;

    // If we are at a nil node just return 1
    if (root == nil)
        return 1;

    else
    {
        // First check for consecutive red links.
        if (root->isRed)
        {
            if(root->left->isRed || root->right->isRed)
            {
                cout << "This tree contains a red violation" << endl;
                return 0;
            }
        }

        // Check for valid binary search tree.
        if ((root->left != nil && root->left->time.compare(root->time) > 0) || (root->right != nil && root->right->time.compare(root->time) < 0))
        {
            cout<<" binary violation 1"<<endl;
            cout << "This tree contains a binary tree violation" << endl;
            return 0;
        }

        // Deteremine the height of let and right children.
        lh = rbValid(root->left);
        rh = rbValid(root->right);

        // black height mismatch
        if (lh != 0 && rh != 0 && lh != rh)
        {
            cout<<" binary violation 2"<<endl;
            cout << "This tree contains a black height violation" << endl;
            return 0;
        }

        // If neither height is zero, incrament if it if black.
        if (lh != 0 && rh != 0)
        {
                if (root->isRed)
                    return lh;
                else
                    return lh+1;
        }
        else
            return 0;
    }
}
void ClimateTree::rbValid(){
    cout<<rbValid(root)<<endl;
}

/*
void ClimateTree::test(climateNode *n){


    cout<<n->time<<endl;
    cout<<n->left->time<<endl;
    cout<<n->left->left->time<<endl;
    cout<<n->left->left->left->time<<endl;
    cout<<n->right->time<<endl;
    cout<<n->right->right->time<<endl;
    cout<<n->right->right->right->time<<endl;
}

void ClimateTree::test(){
    test(root);
}
*/
