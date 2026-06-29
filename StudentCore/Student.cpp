#include "Student.h"

#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>

using namespace std;

Student* createGroup(int size)
{
    if (size <= 0)
        return nullptr;

    return new Student[size];
}

void freeGroup(Student* group)
{
    delete[] group;
}

void initDemoData(Student* group, int size)
{
    if (group == nullptr || size <= 0)
        return;

    for (int i = 0; i < size; i++)
    {
        group[i].id = i + 1;

        string name = "Student " + to_string(i + 1);
        strcpy_s(group[i].fullName, sizeof(group[i].fullName), name.c_str());

        for (int j = 0; j < 5; j++)
            group[i].scores[j] = 2 + rand() % 4;

        group[i].averageScore = 0;
    }
}

void calculateAllAverages(Student* group, int size)
{
    if (group == nullptr || size <= 0)
        return;

    for (int i = 0; i < size; i++)
    {
        int sum = 0;

        for (int j = 0; j < 5; j++)
            sum += group[i].scores[j];

        group[i].averageScore = sum / 5.0;
    }
}

int findBestStudent(const Student* group, int size)
{
    if (group == nullptr || size <= 0)
        return -1;

    int best = 0;

    for (int i = 1; i < size; i++)
    {
        if (group[i].averageScore > group[best].averageScore)
            best = i;
    }

    return group[best].id;
}

int countDebtors(const Student* group, int size)
{
    if (group == nullptr || size <= 0)
        return 0;

    int count = 0;

    for (int i = 0; i < size; i++)
    {
        bool debtor = false;

        for (int j = 0; j < 5; j++)
        {
            if (group[i].scores[j] < 3)
            {
                debtor = true;
                break;
            }
        }

        if (debtor)
            count++;
    }

    return count;
}

Student* filterByAverage(const Student* group,
    int size,
    double threshold,
    int* outSize)
{
    if (group == nullptr || size <= 0 || outSize == nullptr)
    {
        if (outSize)
            *outSize = 0;

        return nullptr;
    }

    int count = 0;

    for (int i = 0; i < size; i++)
    {
        if (group[i].averageScore >= threshold)
            count++;
    }

    *outSize = count;

    if (count == 0)
        return nullptr;

    Student* result = new Student[count];

    int index = 0;

    for (int i = 0; i < size; i++)
    {
        if (group[i].averageScore >= threshold)
        {
            result[index++] = group[i];
        }
    }

    return result;
}

void sortByAverage(Student* group, int size)
{
    if (group == nullptr || size <= 0)
        return;

    sort(group, group + size,
        [](const Student& a, const Student& b)
        {
            return a.averageScore > b.averageScore;
        });
}

void printStudents(const Student* group, int size)
{
    if (group == nullptr || size <= 0)
        return;

    for (int i = 0; i < size; i++)
    {
        cout << "ID: " << group[i].id << endl;
        cout << "ФИО: " << group[i].fullName << endl;

        cout << "Оценки: ";

        for (int j = 0; j < 5; j++)
            cout << group[i].scores[j] << " ";

        cout << endl;

        cout << "Средний балл: " << group[i].averageScore << endl;

        cout << "-----------------------------" << endl;
    }
}