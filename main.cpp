#include <iostream>
#include <random>
#include <vector>
#include <map>

//Setting conditions of my random number generator.
constexpr int FLOAT_MIN = 0;
constexpr int FLOAT_MAX = 1;

//neighbourCount : what to do/rule.
std::map<int, bool> conditionMap = {
    {1, false},
    {2, true},
    {3, true},
    {4, false},
    {5, false},
    {6, false},
    {7, false},
    {8, false}
};

class gameOfLife{
    private:
        int width;
        int height;
        float probabilityOfCell = 0.2;

        void checkIndex(std::vector<int> coords);
        bool queryResponse(std::string conditionMapResp);

    public:
        std::vector<std::vector<bool>> theWorld;

        gameOfLife(std::vector<int> worldDimensions) {
            width = worldDimensions.at(0);
            height= worldDimensions.at(1);
            std::vector<bool> oneDimensionalPlane;
            oneDimensionalPlane.resize(width, false);
            theWorld.resize(height, oneDimensionalPlane);
        }

        void generateNewCells();
        void completeEvolution();
};

void gameOfLife::checkIndex(std::vector<int> coords) {
    if (coords.at(0) < width && coords.at(0) >= 0   &&   coords.at(1) < height && coords.at(1) >= 0) {
        bool isCellAlive = theWorld.at(coords.at(0)).at(coords.at(1));
        int neighbours = 0;

        if (isCellAlive == true){
            neighbours -= 1;
        }

        for (int y=-1; y<=1; y++) {
            for (int x=-1; x<=1; x++) {
                if (theWorld.at(coords.at(0)+x).at(coords.at(1)+y) == true) {
                    neighbours += 1;
                }
            }
        }

        theWorld.at(coords.at(0)).at(coords.at(1)) = conditionMap[neighbours];
    }
}

void gameOfLife::generateNewCells(){
    std::cout << "Iterating over: " << width*height << " indexes, please wait." << std::endl;
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<float> distr(FLOAT_MIN, FLOAT_MAX);

    for (int y=0; y<height; y++) {
        for (int x=0; x<width; x++) {
            if (distr(eng) < probabilityOfCell) {
                theWorld.at(x).at(y) = true; //New life has been created :)
            }
        }
    }
}

void gameOfLife::completeEvolution(){ 
    for (int y=0; y<height; y++) {
        for (int x=0; x<width; x++) {
            checkIndex({x,y});
        }
    }
}
