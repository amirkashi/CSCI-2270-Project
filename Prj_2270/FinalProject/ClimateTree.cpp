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
    root = nil;
}

//void elimnateSpace(){

//}

void ClimateTree::readFile(){

    ifstream inputFile;
    inputFile.open("DataPRT.csv");   // initiate a variable type for input file
    //string fileDelimate1, fileDelimate2, fileDelimate3, fileDelimate4;

    int lineCounter = 0;

    string strSave,token;
    string time, timePRV, skyPrv, tempStr;
    float wDirPrv = 0, wSpdPrv = 0, temprPrv = 0;
    float prcpPrv = 0.0;


    getline(inputFile,strSave); // ignore first line

    //int couter = 0;
    bool wDirStr = false, wSpdStr = false, TmpStr = false;
    float  wDirCo = 0,      wSpdCo = 0,      TmpCo = 0;

    while(getline(inputFile,strSave)){

            istringstream ss(strSave); // ss is stream of string that help us to use get line for the line, this line is for seperating with comma

            float wDir = 0, wSpd = 0, tempr = 0;
            float prcp = 0.0;
            string sky;
            int colNum = 0;
            while (getline(ss,token,',')){

                if(colNum == 2){
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
                /*
                if(colNum == 7){  // sky cover
                    sky = token;
                }*/
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
            //cout<<"outside if"<<wDirStr<<":"<<wSpdStr<<":"<<TmpStr<<endl;
            //cout<<wDirCo<<":"<<wSpdCo<<":"<<TmpCo<<endl;
            //cout << time << "the stars for '" << tempStr << "'" <<wDirCo<< endl;
            //cout<<time<<endl;
            //cout<<time<<":"<<wDir<<":"<<wSpd<<":"<<tempr<<":"<<prcp<<endl;
            if(timePRV == time || lineCounter == 0){
                timePRV = time;
                //if(time == "2012010816"){
                  //  cout<<prcpPrv<<endl;
               // }

                if(wDirStr == false){
                    wDirPrv += wDir;
                    wDirCo++;
                }
                if(wSpdStr == false){
                    wSpdPrv += wSpd;
                    wSpdCo++;
                }

                //skyPrv = sky;

                if(TmpStr == false){
                    temprPrv += tempr;
                    TmpCo++;
                }

                prcpPrv += prcp;
                //cout<<"inside if"<<wDirStr<<":"<<wSpdStr<<":"<<TmpStr<<endl;
                //couter++;
                //cout<<timePRV<<":"<<wDirPrv<<":"<<wSpdPrv<<":"<<temprPrv<<":"<<prcpPrv<<endl;
                //cout<<timePRV<<":"<<wDirPrv<<":"<<wDirCo<<":"<<wSpdPrv<<":"<<wSpdCo<<":"<<temprPrv<<":"<<TmpCo<<":"<<prcpPrv<<endl;
                //cout<<wDirCo<<":"<<wSpdCo<<":"<<TmpCo<<endl;
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

                //cout<<"hi"<<endl;
                wDirPrv = wDirPrv/wDirCo;
                wSpdPrv = wSpdPrv/wSpdCo;
                temprPrv = temprPrv/TmpCo;
                //cout<<wDirCo<<":"<<wSpdCo<<":"<<TmpCo<<endl;

                // snow calculation
                float snow = 0;
                float rain = 0;
                if(temprPrv < 32 && prcpPrv > 0){
                    snow = prcpPrv;
                }else{
                    rain = prcpPrv;
                }

                //cout<<timePRV<<"|"<<wDirPrv<<" : "<<wDirCo<<"|"<<wSpdPrv<<" : "<<wSpdCo <<"|"<<tempr<<":"<<TmpCo<<"|"<<prcpPrv<< endl;
                //cout<<timePRV<<":"<<wDirPrv<<":"<<wSpdPrv<<":"<<temprPrv<<":"<<prcpPrv<<endl;
                addDayNode(timePRV, temprPrv, prcpPrv, rain, snow, wDirPrv, wSpdPrv);
                timePRV = time;
                //skyPrv = sky;
                wDirPrv = wDir;
                wSpdPrv = wSpd;
                temprPrv = tempr;
                prcpPrv = prcp;
                //couter = 1;
                //cout<<wDirCo<<":"<<wSpdCo<<":"<<TmpCo<<endl;

                wDirCo = 1;
                wSpdCo = 1;
                TmpCo = 1;
                //cout<<"hi"<<endl;
                wDirStr = false;
                wSpdStr = false;
                TmpStr = false;
            }

        lineCounter++;
    }
}


void ClimateTree::addDayNode(string tim, float tem, float prc, float ran, float snw, float wdir,float wspd){


    climateNode *y = nil; // y is parent of x or one node before x
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


    //cout<<newMovi->time<<endl;
    //cout<<newMovi->parent->isRed<<endl;
    rbAddFixup(newDay);
}

void ClimateTree::rbAddFixup(climateNode *rootAdd){

    climateNode *z = rootAdd; // is the new node we are adding to the tree

    while(z != root && z->parent->isRed == true){

        /*if parent of z in in left side of its parent   */
        if(z->parent == z->parent->parent->left){ // if parent of z is in the left node of z grand parent
            climateNode *y = z->parent->parent->right; // y = uncle of z in the right

            if(y->isRed == true){ // if uncle of z is red change color of z parent and uncle to black and grand parent to red
                z->parent->isRed = false;
                y->isRed = false;
                z->parent->parent->isRed = true; // why we changed the color of grand parent to black 2 line before
                z = z->parent->parent; // move node z to its grand parent

            }else { // if uncle of z is not red
                if(z == z->parent->right){ // if z is right child of his parent
                    z = z->parent; // move z to parent and then left rotate on parent
                    leftRotate(z);
                }
            // so if if and else was not right
                z->parent->isRed = false;  // z-parent = black
                z->parent->parent->isRed = true; // z-gparent = balck
                rightRotate(z->parent->parent); // right rotate on grant parent of z
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
// ---------------- beginning of rent movie

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


void ClimateTree::getHourlyClimateInfo(string time){

    climateNode* findClimate= searchClimateData(root, time);
    if (findClimate!=nil){

        cout<<"Climate Information for: "<<time.substr(4,2)<<"/"<<time.substr(0,4)<<"/"<<
                time.substr(6,2)<<" at hour : "<<stoi(time.substr(8,2))<< " was: "<< endl;
        cout<<"Temperature: "<< findClimate->temperature<<endl;
        cout<<"Wind Direction: "<<findClimate->WindDir<<endl;
        cout<<"Wind Speed: "<<findClimate->WindSpeed<<endl;
        cout<<"Precipitation: "<<findClimate->precipitation<<endl;
        cout<<"Rain: "<<findClimate->rain<<endl;
        cout<<"Snow: "<<findClimate->snow<<endl;
    }else{
        cout<<"The date you were looking for does not exist, please try again"<<endl;
    }

}
// -----------------------  daily
/*
int ClimateTree::getNumberOfHourInDay(climateNode *n, string day){
    float total = 0;
    if (n == nil){
        return  0;
    }else{
        if(n->time.substr(0,8) == day)
            total=1+getNumberOfNodes(n->left)+getNumberOfNodes(n->right);

    }
    return total;
}
*/
void ClimateTree::settotalNodeDay(){
    totalNodeDay = 0;
}


void ClimateTree::GetDailySummary(climateNode* node, string day){

    if(node == nil)
        return;
    //float i = 0;
    //i++;
    if(node != nil){
        if(node->time.substr(0,8) == day){
            DailySumary->precipitation += node->precipitation;
            DailySumary->temperature += node->temperature;
            DailySumary->rain += node->rain;
            DailySumary->snow += node->snow;
            DailySumary->WindDir += node->WindDir;
            DailySumary->WindSpeed += node->WindSpeed;
            totalNodeDay++;

        }
    }


    if(node->left != nil){
        GetDailySummary(node->left, day);
    }

    if(node->right != nil){
        GetDailySummary(node->right, day);
    }

}

void ClimateTree::GetDailySummary(string day){
    GetDailySummary(root, day);
    //cout<<getNumberOfNodes(root)<<endl;

    cout<<"Climate Information for 2012"<<endl;
    cout<<"Temperature: "<< (DailySumary->temperature)/totalNodeDay<<endl;
    cout<<"Total Precipitation: "<<DailySumary->precipitation<<endl;
    cout<<"Rain: "<<(DailySumary->rain)<<endl;
    cout<<"Snow: "<<(DailySumary->snow)<<endl;
    cout<<"Wind Direction: "<<(DailySumary->WindDir)/totalNodeDay<<endl;
    cout<<"Wind Speed: "<<(DailySumary->WindSpeed)/totalNodeDay<<endl;
    //cout<<"total "<<DailySumary->totalNodes<<endl;
}
// -------------------------         Monthly
void ClimateTree::AssingMonthNumberStr(){
    string monthStr[12] = {"01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12"};
    for(int i = 0; i < 12; i++){
        mont[i].time = monthStr[i];
    }

}


void ClimateTree::GetMontlySummary(climateNode* node, string month, int arN){


        if(node == nil)
            return;

        if(node != nil){
        //cout<<node->time.substr(4,2)<<"       "<<mont[arN].time<<endl;
            if(node->time.substr(4,2) == mont[arN].time){

                mont[arN].precipitation += node->precipitation;
                mont[arN].temperature += node->temperature;
                mont[arN].rain += node->rain;
                mont[arN].snow += node->snow;
                mont[arN].WindDir += node->WindDir;
                mont[arN].WindSpeed += node->WindSpeed;

            }
        }

        if(node->left != nil){
            GetMontlySummary(node->left, month, arN);
        }

        if(node->right != nil){
            GetMontlySummary(node->right, month, arN);
        }

}

void ClimateTree::GetMontlySummary(){
    AssingMonthNumberStr();

    for(int arN = 0; arN < 12; arN++){

        GetMontlySummary(root, mont[arN].time, arN);
    }

    for(int j = 0; j<12; j++){
        cout<<mont[j].temperature<<endl;
    }
/*

    float tot = 24.0;
    cout<<"Climate Information for JAN"<<endl;
    cout<<"Temperature: "<<mont[0]<<endl;
    cout<<"Total Precipitation: "<<DailySumary->precipitation<<endl;
    cout<<"Rain: "<<(DailySumary->rain)<<endl;
    cout<<"Snow: "<<(DailySumary->snow)<<endl;
    cout<<"Wind Direction: "<<(DailySumary->WindDir)/tot<<endl;
    cout<<"Wind Speed: "<<(DailySumary->WindSpeed)/tot<<endl;
    //cout<<"total "<<DailySumary->totalNodes<<endl;*/
}


// -------------------------         annual
int ClimateTree::getNumberOfNodes(climateNode *n){
    int total = 0;
    if (n == nil){
        return  0;
    }else{
            total=1+getNumberOfNodes(n->left)+getNumberOfNodes(n->right);

    }
    return total;
}


void ClimateTree::GetAnnulSummary(climateNode* node){

    if(node == nil)
        return;

    if(node != nil){

        AnnualSumary->precipitation += node->precipitation;
        AnnualSumary->temperature += node->temperature;
        AnnualSumary->rain += node->rain;
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

void ClimateTree::GetAnnulSummary(){
    GetAnnulSummary(root);
    //cout<<getNumberOfNodes(root)<<endl;
    float tot = getNumberOfNodes(root);
    cout<<"Climate Information for 2012"<<endl;
    cout<<"Temperature: "<< (AnnualSumary->temperature)/tot<<endl;
    cout<<"Total Precipitation: "<<AnnualSumary->precipitation<<endl;
    cout<<"Rain: "<<(AnnualSumary->rain)<<endl;
    cout<<"Snow: "<<(AnnualSumary->snow)<<endl;
    cout<<"Wind Direction: "<<(AnnualSumary->WindDir)/tot<<endl;
    cout<<"Wind Speed: "<<(AnnualSumary->WindSpeed)/tot<<endl;


}


// Returns 0 if the tree is invalid, otherwise returns the black node height.
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
