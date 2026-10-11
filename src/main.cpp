#include <iostream>
#include <stdexcept>
#include <windows.h>
#include "Student.h"

/**
 * @brief Проверяет основные действия студента
 *
 * @return 0 если проверки прошли
 */
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "Лабораторная работа №2. Вариант 4\n\n";

    {
        Group group("ИВТ-41", 4);
        Student first;
        Student second("Иван Петров", 20, group);
        Student third("Анна Иванова", 21, 4.5, group);

        std::cout << "Начальное состояние:\n";
        first.printInfo();
        second.printInfo();
        third.printInfo();

        if (Student::getObjectCount() != 3 ||
            !first.passSession(4.0) || !first.celebrateBirthday() ||
            !first.transferToGroup(group))
        {
            return 1;
        }

        std::cout << "После правильных действий:\n";
        first.printInfo();

        if (first.passSession(6.0) || second.getAge() != 20 ||
            second.getAverageGrade() != 0.0 || third.getAverageGrade() != 4.5)
        {
            return 1;
        }

        try
        {
            Student wrong(" ", 10, group);
            return 1;
        }
        catch (const std::invalid_argument& error)
        {
            std::cout << "Неправильный студент: " << error.what() << '\n';
        }

        std::cout << "После неправильных действий:\n";
        first.printInfo();
        std::cout << "Существующих студентов: " << Student::getObjectCount() << '\n';
    }

    std::cout << "После выхода из блока: " << Student::getObjectCount() << '\n';
    return Student::getObjectCount() == 0 ? 0 : 1;
}
