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
    //std::string skyCover;
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
        //skyCover = skyc;

    }

};

class ClimateTree{

    public:
        ClimateTree();
        //virtual ~MovieTree();

        void readFile();
        void addDayNode(std::string in_time,  float temr, float prcp, float ran, float snw, float wdir, float wspd);
        void getHourlyClimateInfo(std::string time);

        void GetAnnulSummary();
        int getNumberOfNodes(climateNode *n);
        void GetDailySummary(std::string day);
        void AssingMonthNumberStr();
        void GetMontlySummary();
        void settotalNodeDay();

        //void printMovieInventory();
        //void countclimateNodes();
        //void deleteclimateNode(string title);

        //void findMovie(string title);
        //void rentMovie(string title);
        //bool isValid();
        //int countLongestPath();
        //use this to return the json object from the class when you are ready to write it to a file
        //json_object* getJsonObject();
        void rbValid();
        //void test();
        //bool quit(int userChoise);
    //protected:

    private:
        void rbAddFixup(climateNode * node); // called after insert to fix tree
        void leftRotate(climateNode * x);
        void rightRotate(climateNode * x);
        climateNode *searchClimateData(climateNode* node, std::string time);
        void GetAnnulSummary(climateNode* node);
        void test(climateNode *n);
        void GetDailySummary(climateNode* node, std::string day);
        climateNode *searchDailyData(climateNode* node, std::string day);
        int getNumberOfHourInDay(climateNode *n, std::string day);
        void GetMontlySummary(climateNode* node, std::string month, int arN);


        climateNode *DailySumary = new climateNode;
        climateNode *AnnualSumary = new climateNode;
        climateNode mont[12] = {};
        float totalNodeDay = 0;
        //void DeleteAll(climateNode * node); //use this for the post-order traversal deletion of the tree
        //void printMovieInventory(climateNode * node, json_object * traverseLog);


        //void rbDelete(climateNode * z);

        //void rbDeleteFixup(climateNode * node);
        //climateNode *searchMovieTree(climateNode *node, string title, json_object *traverseLog);
        //climateNode *rentMovie(climateNode* root, string movieForRent, json_object *findLog);
        //void deleteNode(climateNode *cursor);
        //void rbTransplant(climateNode * u, climateNode * v);
        int rbValid(climateNode * node);
        //int countclimateNodes(climateNode *node);
        //int countLongestPath(climateNode *node);
        //climateNode *treeMin(climateNode *root);

        climateNode *root;
        climateNode *nil;

        // Count of how many operations we have done.
        //including the json_object in the class makes it global within the class, much easier to work with
        //json_object * Assignment6Output;


};

#endif // CLIMATE_H
