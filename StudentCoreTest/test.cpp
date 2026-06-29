#include "pch.h"
#include <gtest/gtest.h>
#include "..\StudentCore\Student.h"
#include <cstring>

TEST(StudentCoreTest, CreateAndFreeGroup)
{
    Student* group = createGroup(5);

    ASSERT_NE(group, nullptr);

    freeGroup(group);
}

TEST(StudentCoreTest, AverageCalculation)
{
    Student* group = createGroup(1);

    group[0].scores[0] = 5;
    group[0].scores[1] = 4;
    group[0].scores[2] = 3;
    group[0].scores[3] = 5;
    group[0].scores[4] = 3;

    calculateAllAverages(group, 1);

    ASSERT_DOUBLE_EQ(group[0].averageScore, 4.0);

    freeGroup(group);
}

TEST(StudentCoreTest, FindBestStudent)
{
    Student* group = createGroup(3);

    group[0].id = 1;
    strcpy_s(group[0].fullName, "Ivanov");
    group[0].averageScore = 3.5;

    group[1].id = 2;
    strcpy_s(group[1].fullName, "Petrov");
    group[1].averageScore = 4.8;

    group[2].id = 3;
    strcpy_s(group[2].fullName, "Sidorov");
    group[2].averageScore = 4.2;

    ASSERT_EQ(findBestStudent(group, 3), 2);

    freeGroup(group);
}

TEST(StudentCoreTest, DebtorsCount)
{
    Student* group = createGroup(2);

    for (int i = 0; i < 5; i++)
        group[0].scores[i] = 5;

    group[1].scores[0] = 2;
    group[1].scores[1] = 5;
    group[1].scores[2] = 5;
    group[1].scores[3] = 5;
    group[1].scores[4] = 5;

    ASSERT_EQ(countDebtors(group, 2), 1);

    freeGroup(group);
}

TEST(StudentCoreTest, FilterByAverage)
{
    Student* group = createGroup(3);

    group[0].averageScore = 4.5;
    group[1].averageScore = 3.2;
    group[2].averageScore = 4.9;

    int newSize = 0;

    Student* result = filterByAverage(group, 3, 4.0, &newSize);

    ASSERT_EQ(newSize, 2);
    ASSERT_NE(result, nullptr);

    freeGroup(result);
    freeGroup(group);
}

TEST(StudentCoreTest, FilterEmptyResult)
{
    Student* group = createGroup(2);

    group[0].averageScore = 3.0;
    group[1].averageScore = 2.5;

    int newSize = 0;

    Student* result = filterByAverage(group, 2, 4.0, &newSize);

    ASSERT_EQ(newSize, 0);
    ASSERT_EQ(result, nullptr);

    freeGroup(group);
}

TEST(StudentCoreTest, SortByAverage)
{
    Student* group = createGroup(3);

    group[0].averageScore = 3.1;
    group[1].averageScore = 4.9;
    group[2].averageScore = 4.0;

    sortByAverage(group, 3);

    ASSERT_DOUBLE_EQ(group[0].averageScore, 4.9);
    ASSERT_DOUBLE_EQ(group[1].averageScore, 4.0);
    ASSERT_DOUBLE_EQ(group[2].averageScore, 3.1);

    freeGroup(group);
}

TEST(StudentCoreTest, NullPointerHandling)
{
    EXPECT_EQ(findBestStudent(nullptr, 0), -1);
    EXPECT_EQ(countDebtors(nullptr, 0), 0);

    calculateAllAverages(nullptr, 0);

    int size = 1;
    Student* result = filterByAverage(nullptr, 0, 4.0, &size);

    EXPECT_EQ(result, nullptr);
    EXPECT_EQ(size, 0);
}