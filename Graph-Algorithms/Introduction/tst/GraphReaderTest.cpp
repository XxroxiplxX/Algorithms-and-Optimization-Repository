//
// Created by kali on 3/15/23.
//
#include "gtest/gtest.h"
#include "GraphReader.h"
#include "Graph.h"
#include "Algorithms.h"
#include <cstdlib>
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

    EXPECT_EQ(16,directedGraph->vertices.size());
    for (int i = 1; i < 17; i++) {
        EXPECT_EQ(i, directedGraph->getVertex(i)->id);
    }
    EXPECT_TRUE(areDirectIncidential(directedGraph->getVertex(1),directedGraph->getVertex(6)));
    EXPECT_FALSE(areDirectIncidential(directedGraph->getVertex(6),directedGraph->getVertex(1)));
    EXPECT_TRUE(areDirectIncidential(directedGraph->getVertex(3),directedGraph->getVertex(2)));
    EXPECT_TRUE(areDirectIncidential(directedGraph->getVertex(2),directedGraph->getVertex(3)));
    BFS(directedGraph->getVertex(2));
    directedGraph->saveTreeToCSV("ReadingDirectedGraphCorrectenss");
    system("python ../../src/TestPrinter.py D ReadingDirectedGraphCorrectenss");
    delete directedGraph;
}
TEST_F(GraphReaderTest, DirectedGraphTransposition)
{
    gr->initialCheck();
    directedGraph = gr->buildDirectedGraph();

    EXPECT_EQ(16,directedGraph->vertices.size());
    for (int i = 1; i < 17; i++) {
        EXPECT_EQ(i, directedGraph->getVertex(i)->id);
    }
    EXPECT_TRUE(areDirectIncidential(directedGraph->getVertex(1),directedGraph->getVertex(6)));
    EXPECT_FALSE(areDirectIncidential(directedGraph->getVertex(6),directedGraph->getVertex(1)));
    EXPECT_TRUE(areDirectIncidential(directedGraph->getVertex(3),directedGraph->getVertex(2)));
    EXPECT_TRUE(areDirectIncidential(directedGraph->getVertex(2),directedGraph->getVertex(3)));
    directedGraph->saveToCSV("DirectedGraphTransposition_PreTranspose");
    system("python ../../src/TestPrinter.py D DirectedGraphTransposition_PreTranspose");
    auto transposedGraph = directedGraph->transpose();
    auto originallyTransposedDirectedGraph = gr->buildTransposedDirectedGraph();
    EXPECT_EQ(16,transposedGraph->vertices.size());
    for (int i = 1; i < 17; i++) {
        EXPECT_EQ(i, transposedGraph->getVertex(i)->id);
    }
    EXPECT_FALSE(areDirectIncidential(transposedGraph->getVertex(1),transposedGraph->getVertex(6)));
    EXPECT_TRUE(areDirectIncidential(transposedGraph->getVertex(6),transposedGraph->getVertex(1)));
    EXPECT_TRUE(areDirectIncidential(transposedGraph->getVertex(3),transposedGraph->getVertex(2)));
    EXPECT_TRUE(areDirectIncidential(transposedGraph->getVertex(2),transposedGraph->getVertex(3)));

    for (int i = 0; i < originallyTransposedDirectedGraph->vertices.size(); i++) {
        for (int j = 0; j < originallyTransposedDirectedGraph->vertices[i].neighbours.size(); j++) {
            int v = originallyTransposedDirectedGraph->vertices[i].id;
            int u = originallyTransposedDirectedGraph->vertices[i].neighbours[j]->id;
            EXPECT_TRUE(areDirectIncidential(transposedGraph->getVertex(v), transposedGraph->getVertex(u)));
        }
    }

    originallyTransposedDirectedGraph->saveToCSV("OriginallyTransposedDirectedGraph");
    system("python ../../src/TestPrinter.py D OriginallyTransposedDirectedGraph");
    transposedGraph->saveToCSV("DirectedGraphTransposition_PostTranspose");
    system("python ../../src/TestPrinter.py D DirectedGraphTransposition_PostTranspose");
    delete directedGraph;
    delete transposedGraph;
    delete originallyTransposedDirectedGraph;
}