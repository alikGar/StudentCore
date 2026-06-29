#pragma once

struct Student
{
    int id;
    char fullName[100];
    int scores[5];
    double averageScore;
};

// Создание массива студентов
Student* createGroup(int size);

// Инициализация демо-данными
void initDemoData(Student* group, int size);

// Расчет среднего балла
void calculateAllAverages(Student* group, int size);

// Лучший студент (возвращает id)
int findBestStudent(const Student* group, int size);

// Количество должников
int countDebtors(const Student* group, int size);

// Фильтрация
Student* filterByAverage(
    const Student* group,
    int size,
    double threshold,
    int* outSize);

// Сортировка
void sortByAverage(Student* group, int size);

// Освобождение памяти
void freeGroup(Student* group);

// Вывод
void printStudents(const Student* group, int size);