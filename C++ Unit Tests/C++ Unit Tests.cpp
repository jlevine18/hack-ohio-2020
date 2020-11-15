#include "pch.h"
#include "CppUnitTest.h"
#include "DisjointSet.h"
#include "UndirectedWeightedGraph.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CUnitTests
{
	TEST_CLASS(DisjointSetTest)
	{
	public:
		
		TEST_METHOD(TestInit)
		{
			DisjointSet<int> ds;
			ds.AddValue(1);
			Assert::AreEqual(1, ds.Find(1));
		}
		TEST_METHOD(TestJoin) {
			DisjointSet<std::string> ds;
			ds.AddValue("abc");
			ds.AddValue("def");
			ds.AddValue("ghi");
			ds.Union("abc", "def");
			Assert::AreEqual(std::string("abc"), ds.Find("def"));
			ds.Union("ghi", "def");
			Assert::AreEqual(std::string("abc"), ds.Find("def"));
			Assert::AreEqual(std::string("abc"), ds.Find("ghi"));
		}
		TEST_METHOD(TestCompareRoots) {
			DisjointSet<double> ds;
			ds.AddValue(.1);
			ds.AddValue(.2);
			ds.AddValue(.3);
			ds.AddValue(.4);
			ds.AddValue(.5);

			ds.Union(.1, .2);
			ds.Union(.5, .1);
			ds.Union(.4, .3);
			Assert::IsTrue(ds.CheckDisjoint(.5, .3));
			Assert::IsFalse(ds.CheckDisjoint(.5, .2));
			Assert::IsFalse(ds.CheckDisjoint(.4, .3));
		}
	};

	TEST_CLASS(TestGraph) 
	{
	public:
		TEST_METHOD(GraphInit) {
			
			UndirectedWeightedGraph* uwg = new UndirectedWeightedGraph();
			std::map<std::string, double> map_1;
			map_1["index"] = 1;
			GraphNode* node_1 = new GraphNode(map_1);
			map_1["index"] = 2;
			GraphNode* node_2 = new GraphNode(map_1);
			uwg->AddNode(node_1);
			uwg->AddNode(node_2);
			uwg->AddEdge(new UndirectedWeightedGraphEdge(node_1, node_2, 4));
			Assert::AreEqual((size_t)2, (uwg->GetNodes()).size());
			Assert::AreEqual((size_t)1, (uwg->GetEdges()).size());
			Assert::AreEqual((double)4, uwg->GetEdgeBetweenNodes(node_1, node_2).GetWeight());
			delete uwg;
		}
		TEST_METHOD(Kruskal){
			UndirectedWeightedGraph uwg;
			std::map<std::string, double> map_1;
			map_1["index"] = 0;
			GraphNode* node_0 = new GraphNode(map_1);
			map_1["index"] = 1;
			GraphNode* node_1 = new GraphNode(map_1);
			map_1["index"] = 2;
			GraphNode* node_2 = new GraphNode(map_1);
			map_1["index"] = 3;
			GraphNode* node_3 = new GraphNode(map_1);
			map_1["index"] = 4;
			GraphNode* node_4 = new GraphNode(map_1);
			map_1["index"] = 5;
			GraphNode* node_5 = new GraphNode(map_1);
			map_1["index"] = 6;
			GraphNode* node_6 = new GraphNode(map_1);
			map_1["index"] = 7;
			GraphNode* node_7 = new GraphNode(map_1);
			map_1["index"] = 8;
			GraphNode* node_8 = new GraphNode(map_1);
			map_1["index"] = 9;
			GraphNode* node_9 = new GraphNode(map_1);
			map_1["index"] = 10;
			GraphNode* node_10 = new GraphNode(map_1);
			uwg.AddNode(node_0);
			uwg.AddNode(node_1);
			uwg.AddNode(node_2);
			uwg.AddNode(node_3);
			uwg.AddNode(node_4);
			uwg.AddNode(node_5);
			uwg.AddNode(node_6);
			uwg.AddNode(node_7);
			uwg.AddNode(node_8);
			uwg.AddNode(node_9);
			uwg.AddNode(node_10);
			uwg.AddEdge(new UndirectedWeightedGraphEdge(node_0, node_4, 17));
			uwg.AddEdge(new UndirectedWeightedGraphEdge(node_0, node_10, 26));
			uwg.AddEdge(new UndirectedWeightedGraphEdge(node_0, node_6, 5));
			uwg.AddEdge(new UndirectedWeightedGraphEdge(node_10, node_3, 1));
			uwg.AddEdge(new UndirectedWeightedGraphEdge(node_10, node_4, 6));
			uwg.AddEdge(new UndirectedWeightedGraphEdge(node_4, node_2, 47));
			uwg.AddEdge(new UndirectedWeightedGraphEdge(node_4, node_8, 24));
			uwg.AddEdge(new UndirectedWeightedGraphEdge(node_4, node_9, 10));
			uwg.AddEdge(new UndirectedWeightedGraphEdge(node_3, node_6, 3));
			uwg.AddEdge(new UndirectedWeightedGraphEdge(node_3, node_5, 4));
			uwg.AddEdge(new UndirectedWeightedGraphEdge(node_3, node_2, 8));
			uwg.AddEdge(new UndirectedWeightedGraphEdge(node_2, node_1, 31));
			uwg.AddEdge(new UndirectedWeightedGraphEdge(node_8, node_9, 2));
			uwg.AddEdge(new UndirectedWeightedGraphEdge(node_8, node_1, 7));
			uwg.AddEdge(new UndirectedWeightedGraphEdge(node_9, node_7, 9));
			uwg.AddEdge(new UndirectedWeightedGraphEdge(node_1, node_7, 13));
			uwg.AddEdge(new UndirectedWeightedGraphEdge(node_1, node_5, 19));

			UndirectedWeightedGraph mst = uwg.FindMinimumSpanningTree();
			Assert::AreEqual((size_t)10, mst.GetEdges().size());
			double count = 1;
			for (UndirectedWeightedGraphEdge* edge : mst.GetEdges()) {
				Assert::AreEqual(count, edge->GetWeight());
				count++;
			}
		}
	};
}
