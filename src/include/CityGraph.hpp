#ifndef CITY_GRAPH_HPP
#define CITY_GRAPH_HPP

#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>

class CityGraph {
    private:
        std::unordered_map<std::string, std::list<std::pair<std::string, double>>> cityGraph;
    public:
        CityGraph(std::unordered_map<std::string, std::list<std::pair<std::string, double>>> cityGraph);
        
        void addEdge(const std::string source, const std::string destiny, double distance);
        std::vector<std::string> findShortestPath(const std::string start, const std::string end);
};

#endif