#ifndef CLIMATE_H
#define CLIMATE_H

#include <iostream>


struct climateNode{
    std::string time;
    float temperature;
    float precipitation;
    float rain;
    float snow;
    float WindDir;
    float WindSpeed;
    float totalNodes;

    bool isRed;
    climateNode *parent;
    climateNode *right;
    climateNode *left;

    climateNode(){
        climateNode("",0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,0.0, 0);
    }

    climateNode(std::string in_time, float temr, float prcp, float ran, float snw, float wdir, float wspd, float nd)
    {

        time = in_time;
        temperature = temr;
        precipitation = prcp;
        rain = ran;
        snow = snw;
        WindDir = wdir;
        WindSpeed = wspd;
        totalNodes = nd;

    }

};

class ClimateTree{

    public:
        ClimateTree();
        void readFile();
        void addDayNode(std::string in_time,  float temr, float prcp, float ran, float snw, float wdir, float wspd);

        void seperateSnowRain();
        void excludeSnowRain();

        int getNumberOfNodes(climateNode *n);

        void getHourlyClimateInfo(std::string time);

        void setDailySummary_0();
        void GetDailySummary(std::string day);

        void setMontlhySummary_0();
        void AssignMonthNumberStr();
        void GetMonthlySummary();

        void settotalNodeDay();

        void setAnnualSummary_0();
        void GetAnnulSummary();

        void rbValid();


    private:
        void rbAddFixup(climateNode * node); // called after insert to fix tree
        void leftRotate(climateNode * x);
        void rightRotate(climateNode * x);
        climateNode *searchClimateData(climateNode* node, std::string time);
        void GetAnnulSummary(climateNode* node);
        //void test(climateNode *n);
        void GetDailySummary(climateNode* node, std::string day);
        climateNode *searchDailyData(climateNode* node, std::string day);
        int getNumberOfHourInDay(climateNode *n, std::string day);
        void GetMonthlySummary(climateNode* node, std::string month, int arN);
        void seperateSnowRain(climateNode* node);
        void setSnowRain_0(climateNode* node);


        climateNode *DailySumary = new climateNode;
        climateNode *AnnualSumary = new climateNode;
        climateNode mont[12] = {};
        float totalNodeCount = 0;
        bool snowCalcYes = false;

        int rbValid(climateNode * node);

        climateNode *root;
        climateNode *nil;

};

#endif // CLIMATE_H
