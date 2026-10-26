
#include "pch.h"
#include "CppUnitTest.h"
#include "../lb 6.4 it/lb 6.4 it.cpp"    

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace
{
  
    int Count(const double* a, int n, double A, double B)
    {
        return CountInRange(a, n, A, B);
    }

    int IdxMax(const double* a, int n)
    {
        return IndexOfMax(a, n);
    }

    double SumAfter(const double* a, int n, int index)
    {
        return SumAfterIndex(a, n, index);
    }

    void SortEven(double* a, int n)
    {
        SortEvenByModulusDesc(a, n);
    }

    const double EPS = 1e-9;
}

namespace UnitTest64Iterative
{
    TEST_CLASS(CountInRangeTests)
    {
    public:

        TEST_METHOD(Basic)
        {
            double a[] = { 1.0, 5.0, -2.0, 7.5, 3.0 };
            Assert::AreEqual(3, Count(a, 5, 1.0, 5.0));        // межі входять
            Assert::AreEqual(0, Count(a, 5, 100.0, 200.0));
            Assert::AreEqual(5, Count(a, 5, -10.0, 10.0));
        }

        TEST_METHOD(BoundariesAndSingle)
        {
            double a[] = { 2.0 };
            Assert::AreEqual(1, Count(a, 1, 2.0, 2.0));
            Assert::AreEqual(0, Count(a, 1, 2.1, 3.0));
        }

        TEST_METHOD(NegativeRange)
        {
            double a[] = { -4.0, -3.0, -1.0, 0.0, 2.0 };
            Assert::AreEqual(3, Count(a, 5, -4.0, -1.0));
        }
    };

    TEST_CLASS(MaxAndSumAfterMaxTests)
    {
    public:

        TEST_METHOD(IndexOfMaxFirstOccurrence)
        {
            double a[] = { 1.0, 9.0, 3.0, 9.0, -4.0 };
            Assert::AreEqual(1, IdxMax(a, 5));                 // перший з двох максимумів
        }

        TEST_METHOD(IndexOfMaxAllNegative)
        {
            double b[] = { -5.0, -2.0, -9.0 };
            Assert::AreEqual(1, IdxMax(b, 3));
        }

        TEST_METHOD(IndexOfMaxSingle)
        {
            double c[] = { 4.0 };
            Assert::AreEqual(0, IdxMax(c, 1));
        }

        TEST_METHOD(SumAfterIndex_Values)
        {
            double a[] = { 1.0, 2.0, 3.0, 4.0 };
            Assert::AreEqual(9.0, SumAfter(a, 4, 0), EPS);
            Assert::AreEqual(7.0, SumAfter(a, 4, 1), EPS);
            Assert::AreEqual(0.0, SumAfter(a, 4, 3), EPS);     // після останнього - нічого
        }

        TEST_METHOD(SumAfterMax_InMiddle)
        {
            double a[] = { 1.0, 9.0, 2.0, 3.0 };
            Assert::AreEqual(5.0, SumAfter(a, 4, IdxMax(a, 4)), EPS);
        }

        TEST_METHOD(SumAfterMax_AtEnd)
        {
            double b[] = { 1.0, 2.0, 9.0 };
            Assert::AreEqual(0.0, SumAfter(b, 3, IdxMax(b, 3)), EPS);
        }

        TEST_METHOD(SumAfterMax_AtStart)
        {
            double c[] = { 9.0, 1.0, 2.0 };
            Assert::AreEqual(3.0, SumAfter(c, 3, IdxMax(c, 3)), EPS);
        }
    };

    TEST_CLASS(SortEvenByModulusDescTests)
    {
    public:

        TEST_METHOD(EvenPositionsSortedByModulusDesc)
        {
            // парні індекси 0, 2, 4: 1.0, -5.0, 3.0 -> -5.0, 3.0, 1.0
            double a[] = { 1.0, 100.0, -5.0, 200.0, 3.0 };
            SortEven(a, 5);
            Assert::AreEqual(-5.0, a[0], EPS);
            Assert::AreEqual(3.0, a[2], EPS);
            Assert::AreEqual(1.0, a[4], EPS);
        }

        TEST_METHOD(OddPositionsAreUntouched)
        {
            double a[] = { 1.0, 100.0, -5.0, 200.0, 3.0, -7.0 };
            SortEven(a, 6);
            Assert::AreEqual(100.0, a[1], EPS);
            Assert::AreEqual(200.0, a[3], EPS);
            Assert::AreEqual(-7.0, a[5], EPS);
        }

        TEST_METHOD(ResultIsOrdered)
        {
            double a[] = { 0.5, 1, -8, 2, 3.5, 3, -2, 4, 9, 5, -0.1 };
            const int n = 11;
            SortEven(a, n);
            for (int i = 0; i + 2 < n; i += 2)
                Assert::IsTrue(fabs(a[i]) >= fabs(a[i + 2]));
        }

        TEST_METHOD(SmallArrays)
        {
            double one[] = { -3.0 };
            SortEven(one, 1);
            Assert::AreEqual(-3.0, one[0], EPS);

            double two[] = { 1.0, 2.0 };                       // лише один парний елемент
            SortEven(two, 2);
            Assert::AreEqual(1.0, two[0], EPS);
            Assert::AreEqual(2.0, two[1], EPS);
        }

        TEST_METHOD(SameElementsPreserved)
        {
            double a[] = { 4.0, 1.0, -9.0, 2.0, 6.0 };
            SortEven(a, 5);
            double sum = 0;
            for (int i = 0; i < 5; i++)
                sum += a[i];
            Assert::AreEqual(4.0 + 1.0 - 9.0 + 2.0 + 6.0, sum, EPS);
        }

        TEST_METHOD(AlreadySortedStaysTheSame)
        {
            double a[] = { -9.0, 0.5, 5.0, 0.5, 1.0 };
            SortEven(a, 5);
            Assert::AreEqual(-9.0, a[0], EPS);
            Assert::AreEqual(5.0, a[2], EPS);
            Assert::AreEqual(1.0, a[4], EPS);
        }
    };

    TEST_CLASS(DynamicArrayTests)
    {
    public:

        TEST_METHOD(CreateFillDestroy)
        {
            double* a = CreateArray(10);
            Assert::IsNotNull(a);
            FillRandom(a, 10, -10.0, 10.0);
            for (int i = 0; i < 10; i++)
            {
                Assert::IsTrue(a[i] >= -10.0);
                Assert::IsTrue(a[i] <= 10.0);
            }
            DestroyArray(a);
            Assert::IsNull(a);
        }
    };
}