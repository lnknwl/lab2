#include <iostream>
#include <stdexcept>
#include <windows.h>
#include "Group.h"

/**
 * @brief Проверяет создание и изменение учебной группы
 *
 * @return 0 если проверки прошли
 */
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Group first;
    Group second("ИВТ-41", 4);
    Group last("ИВТ-61", 6);

    first.printInfo();
    second.printInfo();

    if (!second.advanceCourse() || second.getCourse() != 5 ||
        first.getCourse() != 1 || last.advanceCourse())
    {
        std::cout << "Ошибка проверки группы\n";
        return 1;
    }

    try
    {
        Group wrong(" ", 0);
        return 1;
    }
    catch (const std::invalid_argument& error)
    {
        std::cout << "Неправильная группа: " << error.what() << '\n';
    }

    second.printInfo();
    std::cout << "Проверки группы выполнены\n";
    return 0;
}
