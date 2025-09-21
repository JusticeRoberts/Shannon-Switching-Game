#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include "Graphs/Headers/AdjacencyLists.h"
#include "Graphs/Headers/Graph.h"


float GetAverageAndMaxDegree(Graph<int, int> & graph, int& maxDegree) {
    srand(time(0));
    float avg = 0;
    auto vertices = graph.GetVertices();
    for(auto vertex : vertices)
    {
        auto neighbors = graph.GetNeighbors(vertex);
        avg += neighbors.size();
        if(neighbors.size() > (long unsigned int) maxDegree)
            maxDegree = neighbors.size();
    }
    avg /= vertices.size();
    return avg;
}

int main()
{
    int maxNodes;
    float probabilityStep, maxProbability;
    std::cout << "Enter max number of nodes\n";
    std::cin >> maxNodes;
    std::cout << "Enter probability step\n";
    std::cin >> probabilityStep;
    std::cout << "Enter Max Probability\n";
    std::cin >> maxProbability;

    std::vector<float> X;
    std::vector<float> Y;
    std::vector<float> Z;

    for(int i = 1; i < maxNodes; ++i)
    {
        for(float j = 0; j < maxProbability; j += probabilityStep)
        {
            float avgAverage = 0;
            int max = 0;
            for(int k = 0; k < 30; ++k)
            {
                AdjacencyLists<int, int> * graph = AdjacencyLists<int, int>::GenerateRandomGraph(i, j);
                avgAverage += GetAverageAndMaxDegree(*graph, max);
                delete graph;
            }
            avgAverage /= 30;
            X.push_back(float(i));
            Y.push_back(j);
            // if(max > 0)
            //     Z.push_back(avgAverage / max);
            // else
            Z.push_back(avgAverage);
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
}