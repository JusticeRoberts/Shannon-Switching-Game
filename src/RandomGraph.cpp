#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include "Graphs/Headers/AdjacencyLists.h"

#define STATISTICALLY_SIGNIFICANT_CONSTANT 30

int main (int argc, char ** argv)
{
    srand(time(0));

    float maxNodes;
    float probabilityStep;
    float maxProbability;
    std::cout << "Enter maximum nodes: ";
    std::cin >> maxNodes;
    std::cout << "Enter probability step: ";
    std::cin >> probabilityStep;
    std::cout << "Enter max probability: ";
    std::cin >> maxProbability;

    std::vector<float> X{};
    std::vector<float> Y{};
    std::vector<float> Z{};

    for(float i = 0; i < maxNodes; ++i)
    {
        for(float j = 0; j < maxProbability; j += probabilityStep)
        {
            float avgComponents = 0;
            for(int k = 0; k < STATISTICALLY_SIGNIFICANT_CONSTANT; ++k)
            {
                AdjacencyLists<int,int>* graph = AdjacencyLists<int,int>::GenerateRandomGraph(int(i), j);
                avgComponents += graph->GetConnectedComponents();
                delete graph;
            }
            avgComponents /= STATISTICALLY_SIGNIFICANT_CONSTANT;
            X.push_back(i / maxNodes);
            Y.push_back(j);
            Z.push_back(avgComponents / maxNodes);
        }
    }
    std::stringstream ss{};
    ss << "X = [";
    for(float i : X)
        ss << i << ",";
    ss << "]\n";

    ss << "Y = [";
    for(float i : Y)
        ss << i << ",";
    ss << "]\n";

    ss << "Z = [";
    for(float i : Z)
        ss << i << ",";
    ss << "]\n";

    std::cout << ss.str();

    int numProbabilitySteps = (int) maxProbability/probabilityStep;
    
    std::vector<float> YBase;
    std::vector<float> MaxXIndices;
    std::vector<float> MaxZs;
    std::cout << "Maximum X and Z per Y:\n";
    for(int i = 0; i < numProbabilitySteps; ++i)
    {
        float maxZ = 0;
        float maxXIndex = 0;
        for (int j = 0; j < maxNodes; ++j) {
            if(Z[i*maxNodes+j] > maxZ) {
                maxZ = Z[i*maxNodes+j];
                maxXIndex = j;
            }
            MaxXIndices.push_back(float(maxXIndex)/maxNodes);
            YBase.push_back(float(i)*probabilityStep);
            MaxZs.push_back(maxZ);
        }

    }

    ss.clear();
    ss << "X_2 = [";
    for(float i : YBase)
        ss << i << ",";
    ss << "]\n";

    ss << "Y_2 = [";
    for(float i : MaxXIndices)
        ss << i << ",";
    ss << "]\n";

    ss << "Z_2 = [";
    for(float i : MaxZs)
        ss << i << ",";
    ss << "]\n";

    std::cout << ss.str();
    return 0;
}