#include <iostream>
#include <random>
#include <vector>
#include <map>

//Setting conditions of my random number generator.
constexpr int FLOAT_MIN = 0;
constexpr int FLOAT_MAX = 1;

//neighbourCount : what to do/rule.
std::map<int, std::string> conditionMap = {
    {1, "underPop"},
    {2, "LifeOn"},
    {3, "newLife"},
    {4, "overPop"},
    {5, "overPop"},
    {6, "overPop"},
    {7, "overPop"},
    {8, "overPop"}
};

class gameOfLife{
    private:
        int width;
        int height;
        float probabilityOfCell = 0.2;

        void checkIndex(std::vector<int> coords);

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
        
};

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

void gameOfLife::checkIndex(std::vector<int> coords) {
    if (coords.at(0) < width && coords.at(0) >= 0   &&   coords.at(1) < height && coords.at(1) >= 0) {
        bool isCellAlive = theWorld.at(coords.at(0)).at(coords.at(1));
        std::vector<bool> neighbours;

    }
}
