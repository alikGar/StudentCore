#include <iostream>
#include <windows.h>

struct Student {
    int id;
    char fullName[100];
    int scores[5];
    double averageScore;
};

typedef Student* (*CreateGroupFunc)(int);
typedef void (*InitDemoDataFunc)(Student*, int);
typedef void (*CalculateAllAveragesFunc)(Student*, int);
typedef int (*FindBestStudentFunc)(const Student*, int);
typedef int (*CountDebtorsFunc)(const Student*, int);
typedef Student* (*FilterByAverageFunc)(const Student*, int, double, int*);
typedef void (*SortByAverageFunc)(Student*, int);
typedef void (*FreeGroupFunc)(Student*);
typedef void (*PrintStudentsFunc)(const Student*, int);

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    HMODULE hDll = nullptr;
    bool dllLoaded = false;
    Student* group = nullptr;
    int groupSize = 0;

    CreateGroupFunc _createGroup = nullptr;
    InitDemoDataFunc _initDemoData = nullptr;
    CalculateAllAveragesFunc _calculateAllAverages = nullptr;
    FindBestStudentFunc _findBestStudent = nullptr;
    CountDebtorsFunc _countDebtors = nullptr;
    FilterByAverageFunc _filterByAverage = nullptr;
    SortByAverageFunc _sortByAverage = nullptr;
    FreeGroupFunc _freeGroup = nullptr;
    PrintStudentsFunc _printStudents = nullptr;

    int choice;

    while (true) {
        std::cout << "\n=== СИСТЕМА УПРАВЛЕНИЯ СТУДЕНТАМИ ===" << std::endl;
        std::cout << "1. Загрузить DLL" << std::endl;
        std::cout << "2. Создать группу студентов (ввод размера)" << std::endl;
        std::cout << "3. Заполнить демо-данными" << std::endl;
        std::cout << "4. Показать всех студентов" << std::endl;
        std::cout << "5. Рассчитать средние баллы" << std::endl;
        std::cout << "6. Найти лучшего студента" << std::endl;
        std::cout << "7. Показать должников" << std::endl;
        std::cout << "8. Отфильтровать по баллу (> 4.0)" << std::endl;
        std::cout << "9. Отсортировать по среднему баллу" << std::endl;
        std::cout << "10. Выгрузить DLL" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "Выберите пункт: ";
        std::cin >> choice;

        if (choice == 0) break;

        if (choice == 1) {
            hDll = LoadLibraryA("StudentDLL.dll");
            if (hDll) {
                _createGroup = (CreateGroupFunc)GetProcAddress(hDll, "_createGroup");
                _initDemoData = (InitDemoDataFunc)GetProcAddress(hDll, "_initDemoData");
                _calculateAllAverages = (CalculateAllAveragesFunc)GetProcAddress(hDll, "_calculateAllAverages");
                _findBestStudent = (FindBestStudentFunc)GetProcAddress(hDll, "_findBestStudent");
                _countDebtors = (CountDebtorsFunc)GetProcAddress(hDll, "_countDebtors");
                _filterByAverage = (FilterByAverageFunc)GetProcAddress(hDll, "_filterByAverage");
                _sortByAverage = (SortByAverageFunc)GetProcAddress(hDll, "_sortByAverage");
                _freeGroup = (FreeGroupFunc)GetProcAddress(hDll, "_freeGroup");
                _printStudents = (PrintStudentsFunc)GetProcAddress(hDll, "_printStudents");

                if (_createGroup && _initDemoData && _calculateAllAverages &&
                    _findBestStudent && _countDebtors && _filterByAverage &&
                    _sortByAverage && _freeGroup && _printStudents) {
                    dllLoaded = true;
                    std::cout << "DLL загружена успешно!" << std::endl;
                }
                else {
                    std::cout << "Ошибка: не удалось найти все функции в DLL!" << std::endl;
                    FreeLibrary(hDll);
                    hDll = nullptr;
                }
            }
            else {
                std::cout << "Ошибка: DLL не найдена! Проверьте что StudentDLL.dll находится рядом с программой." << std::endl;
            }
            continue;
        }

        if (!dllLoaded) {
            std::cout << "Сначала загрузите DLL (пункт 1)!" << std::endl;
            continue;
        }

        switch (choice) {
        case 2: {
            std::cout << "Введите размер группы: ";
            std::cin >> groupSize;
            if (group) _freeGroup(group);
            group = _createGroup(groupSize);
            std::cout << "Группа создана!" << std::endl;
            break;
        }
        case 3: {
            if (group) {
                _initDemoData(group, groupSize);
                std::cout << "Данные заполнены!" << std::endl;
            }
            else {
                std::cout << "Сначала создайте группу (пункт 2)!" << std::endl;
            }
            break;
        }
        case 4: {
            if (group) _printStudents(group, groupSize);
            else std::cout << "Группа не создана!" << std::endl;
            break;
        }
        case 5: {
            if (group) {
                _calculateAllAverages(group, groupSize);
                std::cout << "Средние баллы рассчитаны!" << std::endl;
            }
            else {
                std::cout << "Группа не создана!" << std::endl;
            }
            break;
        }
        case 6: {
            if (group) {
                int bestId = _findBestStudent(group, groupSize);
                std::cout << "ID лучшего студента: " << bestId << std::endl;
            }
            else {
                std::cout << "Группа не создана!" << std::endl;
            }
            break;
        }
        case 7: {
            if (group) {
                int debtors = _countDebtors(group, groupSize);
                std::cout << "Количество должников: " << debtors << std::endl;
            }
            else {
                std::cout << "Группа не создана!" << std::endl;
            }
            break;
        }
        case 8: {
            if (group) {
                int filteredSize = 0;
                Student* filtered = _filterByAverage(group, groupSize, 4.0, &filteredSize);
                std::cout << "Студентов с баллом > 4.0: " << filteredSize << std::endl;
                if (filtered) {
                    _printStudents(filtered, filteredSize);
                    _freeGroup(filtered);
                }
            }
            else {
                std::cout << "Группа не создана!" << std::endl;
            }
            break;
        }
        case 9: {
            if (group) {
                _sortByAverage(group, groupSize);
                std::cout << "Студенты отсортированы по среднему баллу!" << std::endl;
            }
            else {
                std::cout << "Группа не создана!" << std::endl;
            }
            break;
        }
        case 10: {
            if (group) {
                _freeGroup(group);
                group = nullptr;
            }
            FreeLibrary(hDll);
            hDll = nullptr;
            dllLoaded = false;
            _createGroup = nullptr;
            std::cout << "DLL выгружена! Загрузите её снова (пункт 1) чтобы продолжить." << std::endl;
            break;
        }
        default:
            std::cout << "Неизвестный пункт меню!" << std::endl;
        }
    }

    if (group && dllLoaded && _freeGroup) _freeGroup(group);
    if (hDll) FreeLibrary(hDll);

    return 0;
}