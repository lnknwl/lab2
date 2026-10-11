#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>
#include "Student.h"

int Student::objectCount = 0;

/**
 * @brief Создает студента с начальными значениями
 */
Student::Student()
    : Student("Новый студент", 18, Group())
{
}

/**
 * @brief Создает студента без сданных сессий
 *
 * @param fullName Имя студента
 * @param age Возраст студента
 * @param group Учебная группа
 */
Student::Student(const std::string& fullName, int age, const Group& group)
    : Student(fullName, age, 0.0, group)
{
}

/**
 * @brief Создает студента с заданным средним баллом
 *
 * @param fullName Имя студента
 * @param age Возраст студента
 * @param averageGrade Средний балл
 * @param group Учебная группа
 */
Student::Student(const std::string& fullName, int age,
                 double averageGrade, const Group& group)
    : fullName(fullName), age(age), averageGrade(averageGrade),
      sessionCount(averageGrade == 0.0 ? 0 : 1), studying(true), group(group)
{
    if (fullName.find_first_not_of(" \t\n\r\f\v") == std::string::npos)
    {
        throw std::invalid_argument("Имя студента не должно быть пустым");
    }

    if (age < 16 || age > 100)
    {
        throw std::invalid_argument("Возраст должен быть от 16 до 100 лет");
    }

    if (!std::isfinite(averageGrade) ||
        (averageGrade != 0.0 && (averageGrade < 2.0 || averageGrade > 5.0)))
    {
        throw std::invalid_argument("Средний балл должен быть нулем или от 2 до 5");
    }

    ++objectCount;
}

/**
 * @brief Создает копию студента
 *
 * @param other Студент для копирования
 */
Student::Student(const Student& other)
    : fullName(other.fullName), age(other.age), averageGrade(other.averageGrade),
      sessionCount(other.sessionCount), studying(other.studying), group(other.group)
{
    ++objectCount;
}

/**
 * @brief Завершает время жизни студента и уменьшает счетчик
 */
Student::~Student()
{
    --objectCount;
}

/**
 * @brief Возвращает имя студента
 *
 * @return Имя студента
 */
const std::string& Student::getFullName() const
{
    return fullName;
}

/**
 * @brief Возвращает возраст студента
 *
 * @return Возраст студента
 */
int Student::getAge() const
{
    return age;
}

/**
 * @brief Возвращает средний балл
 *
 * @return Средний балл
 */
double Student::getAverageGrade() const
{
    return averageGrade;
}

/**
 * @brief Возвращает количество сданных сессий
 *
 * @return Количество сессий
 */
int Student::getSessionCount() const
{
    return sessionCount;
}

/**
 * @brief Проверяет, учится ли студент
 *
 * @return true если студент учится
 */
bool Student::isStudying() const
{
    return studying;
}

/**
 * @brief Возвращает учебную группу
 *
 * @return Константная ссылка на группу
 */
const Group& Student::getGroup() const
{
    return group;
}

/**
 * @brief Возвращает количество существующих студентов
 *
 * @return Количество объектов Student
 */
int Student::getObjectCount()
{
    return objectCount;
}

/**
 * @brief Добавляет результат сессии и пересчитывает средний балл
 *
 * @param grade Балл за сессию от 2 до 5
 * @return true если результат добавлен
 */
bool Student::passSession(double grade)
{
    if (!studying || !std::isfinite(grade) || grade < 2.0 || grade > 5.0 ||
        sessionCount == std::numeric_limits<int>::max())
    {
        return false;
    }

    averageGrade = (averageGrade * sessionCount + grade) / (sessionCount + 1);
    ++sessionCount;
    return true;
}

/**
 * @brief Переводит студента в другую группу
 *
 * @param newGroup Новая учебная группа
 * @return true если перевод выполнен
 */
bool Student::transferToGroup(const Group& newGroup)
{
    if (!studying)
    {
        return false;
    }

    group = newGroup;
    return true;
}

/**
 * @brief Увеличивает возраст на один год
 *
 * @return true если возраст изменен
 */
bool Student::celebrateBirthday()
{
    if (age >= 100)
    {
        return false;
    }

    ++age;
    return true;
}

/**
 * @brief Отчисляет студента
 *
 * @return true если студент отчислен
 */
bool Student::expel()
{
    if (!studying)
    {
        return false;
    }

    studying = false;
    return true;
}

/**
 * @brief Восстанавливает студента в указанной группе
 *
 * @param newGroup Группа для восстановления
 * @return true если студент восстановлен
 */
bool Student::restore(const Group& newGroup)
{
    if (studying)
    {
        return false;
    }

    group = newGroup;
    studying = true;
    return true;
}

/**
 * @brief Выводит информацию о студенте
 */
void Student::printInfo() const
{
    std::cout << "Студент: " << fullName << '\n';
    std::cout << "Возраст: " << age << '\n';
    std::cout << "Средний балл: " << averageGrade << '\n';
    std::cout << "Сдано сессий: " << sessionCount << '\n';
    std::cout << "Состояние: " << (studying ? "учится" : "отчислен") << '\n';
    group.printInfo();
    std::cout << '\n';
}
