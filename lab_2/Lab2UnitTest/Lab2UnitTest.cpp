#include "pch.h"
#include "CppUnitTest.h"
#include "../lab_2/Array.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab2UnitTest
{
	TEST_CLASS(Lab2UnitTest)
	{
	public:
		
		TEST_METHOD(IntTest)
		{
			Array<int> arrayTest;
			Assert::AreEqual(0, arrayTest.size());
			for (int i = 0; i < 10; i++) {
				arrayTest.insert(i + 1);
			}
			Assert::AreEqual(10, arrayTest.size());


		}


		TEST_METHOD(StringTestAndRemove)
		{
			Array<std::string> arrayTest;

			arrayTest.insert("TESTTESTTESTTESTTESTTESTTESTTESTTEST");
			arrayTest.insert("GOODGOODGOODGOODGOODGOODGOODGOODGOOD");
			arrayTest.insert("WORKWORKWORKWORKWORKWORKWORKWORKWORK");

			arrayTest.remove(1);

			Assert::IsTrue(arrayTest[0] == "TESTTESTTESTTESTTESTTESTTESTTESTTEST");
			Assert::IsTrue(arrayTest[1] == "WORKWORKWORKWORKWORKWORKWORKWORKWORK");
			Assert::AreEqual(arrayTest.size(), 2);
		}


		TEST_METHOD(CopyConstructorTest)
		{
			Array<int> arrayTestA;
			Assert::AreEqual(0, arrayTestA.size());
			for (int i = 0; i < 10; i++) {
				arrayTestA.insert(i + 1);
			}

			Array<int> arrayTestB(arrayTestA);

			Assert::AreEqual(arrayTestA.size(), arrayTestB.size());
			Assert::AreEqual(arrayTestA.capacity(), arrayTestB.capacity());

			for (int i = 0; i < arrayTestA.size(); i++) {
				Assert::AreEqual(arrayTestA[i], arrayTestB[i]);
			}
		}

		TEST_METHOD(MoveConstructorTest) {
			Array<int> arrayTestA;
			Assert::AreEqual(0, arrayTestA.size());
			for (int i = 0; i < 10; i++) {
				arrayTestA.insert(i);
			}

			int arrayASize = arrayTestA.size();
			int arrayACapacity = arrayTestA.capacity();

			Array<int> arrayTestB = std::move(arrayTestA);

			Assert::AreEqual(arrayASize, arrayTestB.size());
			Assert::AreEqual(arrayACapacity, arrayTestB.capacity());

			for (int i = 0; i < arrayTestB.size(); i++) {
				Assert::AreEqual(arrayTestB[i], i);
			}
		}
	};
}
