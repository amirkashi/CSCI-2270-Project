#ifndef CLIMATE_H
#define CLIMATE_H

#include <iostream>


struct climateNode{
    std::string time;
    int temperature;
    int precipitation;
    int rain;
    int snow;
    int WindDir;
    int WindSpeed;
    std::string skyCover;
    bool isRed;
    climateNode *parent;
    climateNode *right;
    climateNode *left;

    climateNode(){};

    climateNode(std::string in_time, int temr, int prcp, int ran, int snw, int wdir,int wspd, std::string skyc )
    {
        time = in_time;
        temperature = temr;
        precipitation = prcp;
        rain = ran;
        snow = snw;
        WindDir = wdir;
        WindSpeed = wspd;
        skyCover = skyc;

    }

};

class ClimateTree{

    public:
        ClimateTree();
        //virtual ~MovieTree();

        void readFile();
        //void addMovieNode(int ranking, string title, int releaseYear, int quantity);
        //void printMovieInventory();
        //void countMovieNodes();
        //void deleteMovieNode(string title);

        //void findMovie(string title);
        //void rentMovie(string title);
        //bool isValid();
        //int countLongestPath();
        //use this to return the json object from the class when you are ready to write it to a file
        //json_object* getJsonObject();
        //void rbValid();
        //bool quit(int userChoise);
    //protected:

    private:
        //void rbAddFixup(MovieNode * node); // called after insert to fix tree
        //void DeleteAll(MovieNode * node); //use this for the post-order traversal deletion of the tree
        //void printMovieInventory(MovieNode * node, json_object * traverseLog);

        //void leftRotate(MovieNode * x);
        //void rbDelete(MovieNode * z);
        //void rightRotate(MovieNode * x);
        //void rbDeleteFixup(MovieNode * node);
        //MovieNode *searchMovieTree(MovieNode *node, string title, json_object *traverseLog);
        //MovieNode *rentMovie(MovieNode* root, string movieForRent, json_object *findLog);
        //void deleteNode(MovieNode *cursor);
        //void rbTransplant(MovieNode * u, MovieNode * v);
        //int rbValid(MovieNode * node);
        //int countMovieNodes(MovieNode *node);
        //int countLongestPath(MovieNode *node);
        //MovieNode *treeMin(MovieNode *root);

        climateNode *root;
        climateNode *nil;

        // Count of how many operations we have done.
        //including the json_object in the class makes it global within the class, much easier to work with
        //json_object * Assignment6Output;


};

#endif // CLIMATE_H
