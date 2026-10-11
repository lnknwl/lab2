#include <iostream>
#include <stdexcept>
#include "Group.h"

/**
 * @brief Создает группу с начальными значениями
 */
Group::Group()
    : name("Без группы"), course(1)
{
}

/**
 * @brief Создает группу с заданным названием и курсом
 */
Group::Group(const std::string& name, int course)
    : name(name), course(course)
{
    if (name.find_first_not_of(" \t\n\r\f\v") == std::string::npos)
    {
        throw std::invalid_argument("Название группы не должно быть пустым");
    }

    if (course < 1 || course > 6)
    {
        throw std::invalid_argument("Курс должен быть от 1 до 6");
    }
}

/**
 * @brief Завершает время жизни группы
 */
Group::~Group()
{
}

/**
 * @brief Возвращает название группы
 *
 * @return Название группы
 */
const std::string& Group::getName() const
{
    return name;
}

/**
 * @brief Возвращает номер курса
 *
 * @return Номер курса
 */
int Group::getCourse() const
{
    return course;
}

/**
 * @brief Переводит группу на следующий курс
 *
 * @return true если переход выполнен
 */
bool Group::advanceCourse()
{
    if (course >= 6)
    {
        return false;
    }

    ++course;
    return true;
}

/**
 * @brief Выводит информацию о группе
 */
void Group::printInfo() const
{
    std::cout << "Группа: " << name << ", курс: " << course << '\n';
}
