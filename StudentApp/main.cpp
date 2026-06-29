#include <iostream>
#include <windows.h>

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    HMODULE hDll = nullptr;
    bool dllLoaded = false;
    int choice;

    while (true) {
        std::cout << "\n=== СИСТЕМА УПРАВЛЕНИЯ СТУДЕНТАМИ ===" << std::endl;
        std::cout << "1. Загрузить DLL" << std::endl;
        std::cout << "2. Создать группу студентов" << std::endl;
        std::cout << "3. Заполнить демо-данными" << std::endl;
        std::cout << "4. Показать всех студентов" << std::endl;
        std::cout << "5. Рассчитать средние баллы" << std::endl;
        std::cout << "6. Найти лучшего студента" << std::endl;
        std::cout << "7. Показать должников" << std::endl;
        std::cout << "9. Отсортировать по среднему баллу" << std::endl;
        std::cout << "10. Выгрузить DLL" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "Выберите пункт: ";
        std::cin >> choice;

        if (choice == 0) break;

        if (choice == 1) {
            hDll = LoadLibraryA("StudentDLL.dll");
            if (hDll) {
                dllLoaded = true;
                std::cout << "DLL загружена!" << std::endl;
            }
            else {
                std::cout << "Ошибка: DLL не найдена!" << std::endl;
            }
        }
        else if (!dllLoaded) {
            std::cout << "Сначала загрузите DLL (пункт 1)!" << std::endl;
        }
        else if (choice == 10) {
            FreeLibrary(hDll);
            dllLoaded = false;
            hDll = nullptr;
            std::cout << "DLL выгружена!" << std::endl;
        }
    }
    return 0;
}