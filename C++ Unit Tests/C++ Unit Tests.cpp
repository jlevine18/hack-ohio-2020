#include "pch.h"
#include "CppUnitTest.h"
#include "../graph-algorithms/DisjointSet.h"
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
}
