#include <iostream>
#include <random>
#include <vector>
#include <stdlib.h>
#include <Windows.h>
#include <map>

//Setting conditions of my random number generator.
constexpr int FLOAT_MIN = 0;
constexpr int FLOAT_MAX = 1;

//neighbourCount : what to do/rule.
std::map<int, bool> continueConditionMap = {
    {1, false},
    {2, true},
    {3, true},
    {4, false},
    {5, false},
    {6, false},
    {7, false},
    {8, false}
};

std::map<int, bool> newCellConditionMap = {
    {1, false},
    {2, false},
    {3, true},
    {4, false},
    {5, false},
    {6, false},
    {7, false},
    {8, false}
};


void set_cursor(bool visible){
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = visible;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void gotoxy(int x, int y) {
    COORD c = { x, y };  
    SetConsoleCursorPosition(  GetStdHandle(STD_OUTPUT_HANDLE), c);
}

class gameOfLife{
    private:
        int printOutputWidth = 100;
        int printOutputHeight =100;

        int width;
        int height;
        float probabilityOfCell = 0.1;

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
        void printSegment(int xOffSet, int yOffSet);
};

void gameOfLife::checkIndex(std::vector<int> coords) {

    bool isCellAlive = theWorld.at(coords.at(0)).at(coords.at(1));
    int neighbours = 0;

    if (isCellAlive == true){
        neighbours -= 1;
    }
    
    for (int y=-1; y<=1; y++) {
        for (int x=-1; x<=1; x++) {
            if (coords.at(0)+x < width && coords.at(0)+x >= 0   &&   coords.at(1)+y < height && coords.at(1)+y >= 0) {
                if (theWorld.at(coords.at(0)+x).at(coords.at(1)+y) == true) {
                    neighbours += 1;
                }
            }
        }
    }
    if (theWorld.at(coords.at(0)).at(coords.at(1)) == true) {
        theWorld.at(coords.at(0)).at(coords.at(1)) = continueConditionMap[neighbours];
    }
    else {
        theWorld.at(coords.at(0)).at(coords.at(1)) = newCellConditionMap[neighbours];
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

void gameOfLife::printSegment(int xOffSet, int yOffSet) {
    for (int y=0; y<printOutputHeight; y++) {
        for (int x=0; x<printOutputWidth; x++) {
            gotoxy(x*2,y);
            if (theWorld.at(x+xOffSet).at(y+yOffSet) == true) {
                std::cout << "[]";
            }
            else {
                std::cout << "  ";
            }
        }
        std::cout<<std::endl;
    }
}

int main() {
    set_cursor(false);

    gameOfLife GOLObj({100,100});
    GOLObj.generateNewCells();

    while (true) {
        GOLObj.printSegment(0,0); //The values used as offsets can be edited, for example you could have them set to a variable.
        GOLObj.completeEvolution();
    }
}
