#include "..\StudentCores\Student.h"
#include "..\StudentCores\Student.cpp"

extern "C" {
    __declspec(dllexport) Student* _createGroup(int size) { return createGroup(size); }
    __declspec(dllexport) void _initDemoData(Student* group, int size) { initDemoData(group, size); }
    __declspec(dllexport) void _calculateAllAverages(Student* group, int size) { calculateAllAverages(group, size); }
    __declspec(dllexport) int _findBestStudent(const Student* group, int size) { return findBestStudent(group, size); }
    __declspec(dllexport) int _countDebtors(const Student* group, int size) { return countDebtors(group, size); }
    __declspec(dllexport) void _sortByAverage(Student* group, int size) { sortByAverage(group, size); }
    __declspec(dllexport) void _freeGroup(Student* group) { freeGroup(group); }
    __declspec(dllexport) void _printStudents(const Student* group, int size) { printStudents(group, size); }
    __declspec(dllexport) Student* _filterByAverage(const Student* group, int size, double threshold, int* outSize) { return filterByAverage(group, size, threshold, outSize); }
}