#include <iostream>
#include "../include/CityGraph.hpp"

#include <queue>
#include <algorithm>
#include <limits>

CityGraph::CityGraph(std::unordered_map<std::string, std::list<std::pair<std::string, double>>> cityGraph) {
    this->cityGraph = cityGraph;
}

void CityGraph::addEdge(const std::string source, const std::string destiny, double distance) {
    this->cityGraph[source].emplace_back(destiny, distance);
    this->cityGraph[destiny].emplace_back(source, distance);
}

std::vector<std::string> CityGraph::findShortestPath(const std::string start, const std::string end) {
    std::unordered_map<std::string, double> distances;
    std::unordered_map<std::string, std::string> parent;
    std::priority_queue<std::pair<double, std::string>, 
        std::vector<std::pair<double, std::string>>, 
        std::greater<std::pair<double, std::string>>> pq;

    for (const auto& pair : cityGraph) {
        distances[pair.first] = std::numeric_limits<double>::infinity();
    }
    distances[start] = 0.0;
    pq.emplace(0.0, start);

    while (!pq.empty()) {
        std::pair<double, std::string> top = pq.top();
        double currentDistance = top.first;
        std::string current = top.second;
        pq.pop();

        if (current == end) {
            std::vector<std::string> path;
            for (std::string at = end; at != ""; at = parent[at]) {
                path.push_back(at);
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (const auto& neighborPair : cityGraph[current]) {
            std::string neighbor = neighborPair.first;
            double weight = neighborPair.second;
            double distance = currentDistance + weight;
            if (distance < distances[neighbor]) {
                distances[neighbor] = distance;
                parent[neighbor] = current;
                pq.emplace(distance, neighbor);
            }
        }
    }

    return {};
}
