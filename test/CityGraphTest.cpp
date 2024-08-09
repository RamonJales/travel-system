#include <gtest/gtest.h>
#include "../src/include/CityGraph.hpp"
#include <unordered_map>
#include <list>
#include <string>
#include <vector>

TEST(CityGraphTest, ShortestPathExists_ReturnsCorrectPath) {
    std::unordered_map<std::string, std::list<std::pair<std::string, double>>> cityGraph = {
        {"A", {{"B", 1.0}, {"C", 4.0}}},
        {"B", {{"A", 1.0}, {"C", 2.0}, {"D", 5.0}}},
        {"C", {{"A", 4.0}, {"B", 2.0}, {"D", 1.0}}},
        {"D", {{"B", 5.0}, {"C", 1.0}}}
    };

    CityGraph graph(cityGraph);
    std::vector<std::string> expectedPath = {"A", "B", "C", "D"};
    std::vector<std::string> resultPath = graph.findShortestPath("A", "D");

    EXPECT_EQ(expectedPath, resultPath);
}

TEST(CityGraphTest, SingleNodeGraph_ReturnsSingleNode) {
    std::unordered_map<std::string, std::list<std::pair<std::string, double>>> cityGraph = {
        {"A", {{"B", 1.0}}},
        {"B", {{"A", 1.0}}},
        {"C", {{"D", 1.0}}},
        {"D", {{"C", 1.0}}}
    };

    CityGraph graph(cityGraph);
    std::vector<std::string> resultPath = graph.findShortestPath("A", "D");

    EXPECT_TRUE(resultPath.empty());
}

TEST(CityGraphTest, TwoConnectedNodes_ReturnsCorrectPath) {
    std::unordered_map<std::string, std::list<std::pair<std::string, double>>> cityGraph = {
        {"A", {}}
    };

    CityGraph graph(cityGraph);
    std::vector<std::string> expectedPath = {"A"};
    std::vector<std::string> resultPath = graph.findShortestPath("A", "A");

    EXPECT_EQ(expectedPath, resultPath);
}

TEST(CityGraphTest, FindShortestPathTwoNodes) {
    std::unordered_map<std::string, std::list<std::pair<std::string, double>>> cityGraph = {
        {"A", {{"B", 1.0}}},
        {"B", {{"A", 1.0}}}
    };

    CityGraph graph(cityGraph);
    std::vector<std::string> expectedPath = {"A", "B"};
    std::vector<std::string> resultPath = graph.findShortestPath("A", "B");

    EXPECT_EQ(expectedPath, resultPath);
}