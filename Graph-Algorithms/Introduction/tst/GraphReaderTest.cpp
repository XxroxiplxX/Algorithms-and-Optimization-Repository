//
// Created by kali on 3/15/23.
//
#include "gtest/gtest.h"
#include "GraphReader.h"
#include "Graph.h"
class GraphReaderTest : public testing::Test {
public:
    GraphReader* gr;
    Graph* graph;
    DirectedGraph* directedGraph;
    GraphReaderTest() {
        gr = new GraphReader("../../resources/3/g3-1.txt");
    }
    static bool areDirectIncidential(Vertex* u, Vertex* v) {
        for (auto neigh : u->neighbours) {
            if (neigh == v) {
                return true;
            }
        }
        return false;
    }
};
TEST_F(GraphReaderTest, ReadingDirectedGraphCorrectenss)
{
    gr->initialCheck();
    directedGraph = gr->buildDirectedGraph();
    for (int i = 1; i < 17; i++) {
        EXPECT_EQ(i, directedGraph->getVertex(i)->id);
    }
    EXPECT_TRUE(areDirectIncidential(directedGraph->getVertex(1),directedGraph->getVertex(6)));
    EXPECT_FALSE(areDirectIncidential(directedGraph->getVertex(6),directedGraph->getVertex(1)));
    EXPECT_TRUE(areDirectIncidential(directedGraph->getVertex(3),directedGraph->getVertex(2)));
    EXPECT_TRUE(areDirectIncidential(directedGraph->getVertex(2),directedGraph->getVertex(3)));
}