#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include "Graphs/Headers/Graph.h"
#include "Graphs/Headers/AdjacencyLists.h"

#define STATISTICALLY_SIGNIFICANT_CONSTANT 30

int main (int argc, char ** argv)
{
    srand(time(0));

    float maxNodes;
    float probabilityStep;
    std::cout << "Enter maximum nodes: ";
    std::cin >> maxNodes;
    std::cout << "Enter probability step: ";
    std::cin >> probabilityStep;

    std::vector<float> X{};
    std::vector<float> Y{};
    std::vector<float> Z{};

    for(float i = 0; i < maxNodes; ++i)
    {
        for(float j = 0; j < 1; j += probabilityStep)
        {
            float avgComponents = 0;
            for(int k = 0; k < STATISTICALLY_SIGNIFICANT_CONSTANT; ++k)
            {
                AdjacencyLists<int,int>& graph = AdjacencyLists<int,int>::GenerateRandomGraph(int(i), j);
                avgComponents += graph.GetConnectedComponents();
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
    return 0;
}