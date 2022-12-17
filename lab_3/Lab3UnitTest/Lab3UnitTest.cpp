#include "pch.h"
#include "CppUnitTest.h"
#include "../lab_3/Sort.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab3UnitTest
{
	TEST_CLASS(Lab3UnitTest)
	{
	public:
		
		TEST_METHOD(OneInsertSortTest)
		{
			int arrInsert[5]{ 8,12,6,2,9 };

			insertionSort(arrInsert, arrInsert + 5 - 1, [](int a, int b) {return a < b; });

			Assert::IsTrue(arrInsert[1] = 2);
		}

		TEST_METHOD(InsertSortIntTest)
		{
			int arrInsert[5]{ 8,12,6,2,9 };

			insertionSort(arrInsert, arrInsert + 5 - 1, [](int a, int b) {return a < b; });

			for (int i = 0; i < 4; i++) {
				Assert::IsTrue(arrInsert[i] <= arrInsert[i + 1]);
			}
		}

		TEST_METHOD(InsertSortOneStringTest)
		{
			std::string arrInsert[5]{ "8","12","6","2","9" };

			insertionSort(arrInsert, arrInsert + 5 - 1, [](std::string a, std::string b) {return a < b; });

			Assert::IsTrue(arrInsert[2] == "6");
		}


		TEST_METHOD(InsertSortStringTest)
		{
			std::string arrInsert[5]{ "8","12","6","2","9" };

			insertionSort(arrInsert, arrInsert + 5 - 1, [](std::string a, std::string b) {return a < b; });

			for (int i = 0; i < 4; i++) {
				Assert::IsTrue(arrInsert[i] <= arrInsert[i + 1]);
			}
		}

		TEST_METHOD(OneQuickSortTest)
		{
			int arrQuickSort[5]{ 8,12,6,2,9 };

			quickSort(arrQuickSort, arrQuickSort + 5 - 1, [](int a, int b) {return a < b; });

			Assert::IsTrue(arrQuickSort[1] = 2);
		}

		TEST_METHOD(QuickSortIntTest)
		{
			int arrQuickSort[5]{ 8,12,6,2,9 };

			quickSort(arrQuickSort, arrQuickSort + 5 - 1, [](int a, int b) {return a < b; });

			for (int i = 0; i < 4; i++) {
				Assert::IsTrue(arrQuickSort[i] <= arrQuickSort[i + 1]);
			}
		}

		TEST_METHOD(QuickSortOneStringTest)
		{
			std::string arrQuickSort[5]{ "8","12","6","2","9" };

			quickSort(arrQuickSort, arrQuickSort + 5 - 1, [](std::string a, std::string b) {return a < b; });

			Assert::IsTrue(arrQuickSort[2] == "6");
		}


		TEST_METHOD(QuickSortStringTest)
		{
			std::string arrQuickSort[5]{ "8","12","6","2","9" };

			quickSort(arrQuickSort, arrQuickSort + 5 - 1, [](std::string a, std::string b) {return a < b; });

			for (int i = 0; i < 4; i++) {
				Assert::IsTrue(arrQuickSort[i] <= arrQuickSort[i + 1]);
			}
		}

		TEST_METHOD(InsertSortAndQuickSortTest)
		{
			int arrInsert[5]{ 8,12,6,2,9 };
			int arrQuickSort[5]{ 12,8,6,2,9 };

			insertionSort(arrInsert, arrInsert + 5 - 1, [](int a, int b) {return a < b; });
			quickSort(arrInsert, arrInsert + 5 - 1, [](int a, int b) {return a < b; });

			for (int i = 0; i < 5; i++) {
				Assert::IsTrue(arrInsert[2] = arrQuickSort[2]);
			}

		}

		TEST_METHOD(SortStringIntTest)
		{
			std::string arrSort[5]{ "8","12","6","2","9" };
			sort(arrSort, arrSort + 5 - 1, [](std::string a, std::string b) {return a < b; });

			for (int i = 0; i < 4; i++) {
				Assert::IsTrue(arrSort[i] <= arrSort[i + 1]);
			}
		}

		TEST_METHOD(SortIntTest)
		{
			int arrSort[5]{ 8,12,6,2,9 };
			sort(arrSort, arrSort + 5 - 1, [](int a, int b) {return a < b; });

			for (int i = 0; i < 4; i++) {
				Assert::IsTrue(arrSort[i] <= arrSort[i + 1]);
			}
		}
	};
}
