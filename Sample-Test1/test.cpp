#include "pch.h"
#include "gtest/gtest.h"
#include "../Lab1/TritSet.h"
#include "../Lab1/Trit.h"

TEST(MemoryTest, ConstructorAllocationTest)
{
	for (ull i = 0; i <= 1000; ++i)
	{
		TritSet set(i + 1);
		size_t allocLength = set.capacity();
		EXPECT_GE(allocLength, i * 2 / 8 / sizeof(uint));
	}
}

TEST(MemoryTest, TritMemoryUnknown)
{
	TritSet set(5);
	EXPECT_TRUE(set[4] == Unknown);
}

TEST(MemoryTest, TritMemory)
{
	TritSet set(6);
	set[0] = True;
	set[1] = Unknown;
	set[2] = False;
	set[3] = False;
	set[4] = Unknown;
	set[5] = False;
	EXPECT_TRUE(set[0] == True);
	EXPECT_TRUE(set[1] == Unknown);
	EXPECT_TRUE(set[2] == False);
	EXPECT_TRUE(set[3] == False);
	EXPECT_TRUE(set[4] == Unknown);
	EXPECT_TRUE(set[5] == False);
}

TEST(MemoryTest, UnknownOutOfBound)
{
	TritSet set(1000);
	size_t allocLength = set.capacity();
	set[2000] = Unknown;
	EXPECT_EQ(allocLength, set.capacity());
}

TEST(MemoryTest, ComparingOutOfBound)
{
	TritSet set(1000);
	size_t allocLength = set.capacity();
	EXPECT_FALSE(set[2000] == True);
	EXPECT_EQ(allocLength, set.capacity());
}

TEST(MemoryTest, OutOfBoundsAllocation)
{
	TritSet set(1000);
	size_t allocLength = set.capacity();
	set[2000] = True;
	EXPECT_LT(allocLength, set.capacity());
}

TEST(MemoryTest, ShrinkTest)
{
	TritSet set(1000);
	set[2000] = True;
	set[2000] = Unknown;

	ull a;
	a = 10 * (8 * sizeof(uint) / 2);
	uint x = 2 * a / (sizeof(uint) * 8) + 1;
	set[a] = True;
	set.shrink();
	EXPECT_EQ(x, set.capacity());
	EXPECT_EQ(a + 1, set.setSize());
	set[a] = Unknown;

	a = 8 * sizeof(uint) / 2 - 1;
	x = 2 * a / (sizeof(uint) * 8) + 1;
	set[a] = False;
	set.shrink();
	EXPECT_EQ(x, set.capacity());
	EXPECT_EQ(a + 1, set.setSize());
	set[a] = Unknown;

	set[0] = Unknown;
	set.shrink();
	EXPECT_EQ(0, set.capacity());
	EXPECT_EQ(0, set.setSize());
}

TEST(MemoryTest, TritOperationAllocation)
{
	TritSet setA(1000);
	TritSet setB(2000);
	TritSet setC = setA & setB;
	EXPECT_EQ(setC.capacity(), setB.capacity());
}

TEST(LogicOperation, ANDTest)
{
	TritSet setA(9);
	TritSet setB(9);

	setA[0] = False;
	setA[1] = False;
	setA[2] = False;
	setA[3] = Unknown;
	setA[4] = Unknown;
	setA[4] = Unknown;
	setA[6] = True;
	setA[7] = True;
	setA[8] = True;

	setB[0] = False;
	setB[1] = Unknown;
	setB[2] = True;
	setB[3] = False;
	setB[4] = Unknown;
	setB[5] = True;
	setB[6] = False;
	setB[7] = Unknown;
	setB[8] = True;

	TritSet setC = setA & setB;

	EXPECT_TRUE(setC[0] == False);
	EXPECT_TRUE(setC[1] == False);
	EXPECT_TRUE(setC[2] == False);
	EXPECT_TRUE(setC[3] == False);
	EXPECT_TRUE(setC[4] == Unknown);
	EXPECT_TRUE(setC[5] == Unknown);
	EXPECT_TRUE(setC[6] == False);
	EXPECT_TRUE(setC[7] == Unknown);
	EXPECT_TRUE(setC[8] == True);
}

TEST(LogicOperation, ORTest)
{
	TritSet setA(9);
	TritSet setB(9);

	setA[0] = False;
	setA[1] = False;
	setA[2] = False;
	setA[3] = Unknown;
	setA[4] = Unknown;
	setA[4] = Unknown;
	setA[6] = True;
	setA[7] = True;
	setA[8] = True;

	setB[0] = False;
	setB[1] = Unknown;
	setB[2] = True;
	setB[3] = False;
	setB[4] = Unknown;
	setB[5] = True;
	setB[6] = False;
	setB[7] = Unknown;
	setB[8] = True;

	TritSet setC = setA | setB;

	EXPECT_TRUE(setC[0] == False);
	EXPECT_TRUE(setC[1] == Unknown);
	EXPECT_TRUE(setC[2] == True);
	EXPECT_TRUE(setC[3] == Unknown);
	EXPECT_TRUE(setC[4] == Unknown);
	EXPECT_TRUE(setC[5] == True);
	EXPECT_TRUE(setC[6] == True);
	EXPECT_TRUE(setC[7] == True);
	EXPECT_TRUE(setC[8] == True);
}

TEST(LogicOperation, NOTTest)
{
	TritSet setA(3);
	setA[0] = False;
	setA[1] = Unknown;
	setA[2] = True;

	TritSet setB = !setA;

	EXPECT_TRUE(setB[0] == True);
	EXPECT_TRUE(setB[1] == Unknown);
	EXPECT_TRUE(setB[2] == False);
}

TEST(OtherFunctionsTest, CardinalityTest)
{
	TritSet set(5);
	set[0] = False;
	set[1] = Unknown;
	set[2] = True;
	set[3] = True;
	set[4] = Unknown;

	EXPECT_EQ(1, set.cardinality(False));
	EXPECT_EQ(1, set.cardinality(Unknown));
	EXPECT_EQ(2, set.cardinality(True));
}

TEST(OtherFunctionsTest, CardinalityMapTest)
{
	TritSet set(10);

	set[0] = True;
	set[1] = False;
	set[2] = Unknown;
	set[3] = True;
	set[4] = True;
	set[5] = Unknown;
	auto a = set.cardinality();
	EXPECT_EQ(1, a[False]);
	EXPECT_EQ(1, a[Unknown]);
	EXPECT_EQ(3, a[True]);
}

TEST(OtherFunctionsTest, TrimTest)
{
	TritSet set(5);

	set[0] = True;
	set[1] = False;
	set[2] = False;
	set[3] = Unknown;
	set[4] = True;

	set.trim(2);
	EXPECT_TRUE((set[2] == Unknown) && (set[3] == Unknown) && (set[4] == Unknown));
}

TEST(OtherFunctionsTest, LengthTest)
{
	TritSet set(4);
	set[0] = True;
	set[1] = Unknown;
	set[2] = False;
	set[3] = Unknown;
	EXPECT_EQ(set.length(), 3);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}