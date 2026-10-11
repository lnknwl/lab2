#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <windows.h>
#include "Student.h"

/**
 * @brief Выводит результат проверки
 *
 * @param condition Результат проверяемого условия
 * @param message Название проверки
 * @param errors Количество ошибок
 */
void check(bool condition, const std::string& message, int& errors)
{
    std::cout << (condition ? "[OK] " : "[Ошибка] ") << message << '\n';

    if (!condition)
    {
        ++errors;
    }
}

/**
 * @brief Сравнивает все данные двух студентов
 *
 * @param first Первый студент
 * @param second Второй студент
 * @return true если данные одинаковые
 */
bool sameState(const Student& first, const Student& second)
{
    return first.getFullName() == second.getFullName() &&
           first.getAge() == second.getAge() &&
           std::abs(first.getAverageGrade() - second.getAverageGrade()) < 0.000001 &&
           first.getSessionCount() == second.getSessionCount() &&
           first.isStudying() == second.isStudying() &&
           first.getGroup().getName() == second.getGroup().getName() &&
           first.getGroup().getCourse() == second.getGroup().getCourse();
}

/**
 * @brief Проверяет отказ при неправильных данных студента
 *
 * @param name Имя студента
 * @param age Возраст студента
 * @param grade Средний балл
 * @param group Учебная группа
 * @return true если объект не создан и счетчик не изменился
 */
bool rejectsStudent(const std::string& name, int age,
                    double grade, const Group& group)
{
    int count = Student::getObjectCount();

    try
    {
        Student wrong(name, age, grade, group);
    }
    catch (const std::invalid_argument&)
    {
        return Student::getObjectCount() == count;
    }

    return false;
}

/**
 * @brief Проверяет отказ при неправильных данных группы
 *
 * @param name Название группы
 * @param course Курс группы
 * @return true если объект не создан
 */
bool rejectsGroup(const std::string& name, int course)
{
    try
    {
        Group wrong(name, course);
    }
    catch (const std::invalid_argument&)
    {
        return true;
    }

    return false;
}

/**
 * @brief Проверяет класс студента и время жизни объектов
 *
 * @return 0 если все проверки прошли, иначе 1
 */
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int errors{};
    std::cout << "Лабораторная работа №2. Вариант 4\n\n";
    check(Student::getObjectCount() == 0, "До создания студентов счетчик равен 0", errors);

    {
        Group defaultGroup;
        Group group("ИВТ-41", 4);
        Student first;
        Student second("Иван Петров", 20, group);
        Student third("Анна Иванова", 21, 4.5, group);

        std::cout << "\nНачальное состояние:\n";
        first.printInfo();
        second.printInfo();
        third.printInfo();

        check(Student::getObjectCount() == 3, "Созданы три студента разными конструкторами", errors);
        check(first.getFullName() == "Новый студент" && first.getAge() == 18 &&
              first.getAverageGrade() == 0.0 && first.getSessionCount() == 0 &&
              first.isStudying() && first.getGroup().getName() == "Без группы" &&
              first.getGroup().getCourse() == 1,
              "Студент без аргументов имеет правильное состояние", errors);
        check(defaultGroup.getName() == "Без группы" && defaultGroup.getCourse() == 1,
              "Группа без аргументов имеет правильное состояние", errors);
        check(second.getSessionCount() == 0 && third.getSessionCount() == 1,
              "Количество сессий соответствует начальному баллу", errors);

        {
            const Student savedSecond(second);
            const Student savedThird(third);

            std::cout << "\nПравильные действия:\n";
            check(first.passSession(4.0), "Первая сессия с баллом 4", errors);
            check(first.passSession(5.0), "Вторая сессия с баллом 5", errors);
            check(first.getAverageGrade() == 4.5 && first.getSessionCount() == 2,
                  "Средний балл двух сессий равен 4.5", errors);
            check(first.celebrateBirthday() && first.getAge() == 19,
                  "Возраст увеличился на один год", errors);
            check(first.transferToGroup(group), "Перевод в группу ИВТ-41", errors);
            first.printInfo();

            std::cout << "Неправильные действия:\n";
            const Student savedFirst(first);
            const double badGrades[] = {
                -1.0, 0.0, 1.0, 5.1,
                std::numeric_limits<double>::quiet_NaN(),
                std::numeric_limits<double>::infinity()
            };

            for (double grade : badGrades)
            {
                check(!first.passSession(grade) && sameState(first, savedFirst),
                      "Неправильный балл отклонен, данные не изменились", errors);
            }

            check(!first.restore(group) && sameState(first, savedFirst),
                  "Нельзя восстановить студента, который уже учится", errors);

            std::cout << "\nПосле неправильных действий:\n";
            first.printInfo();

            std::cout << "Проверка независимости:\n";
            second.printInfo();
            third.printInfo();
            check(sameState(second, savedSecond) && sameState(third, savedThird),
                  "Изменение первого студента не изменило остальных", errors);
            check(group.getName() == "ИВТ-41" && group.getCourse() == 4,
                  "Исходная группа не изменилась", errors);
            check(group.advanceCourse() && first.getGroup().getCourse() == 4 &&
                  second.getGroup().getCourse() == 4 && third.getGroup().getCourse() == 4,
                  "Изменение исходной группы не изменило группы студентов", errors);
        }

        check(Student::getObjectCount() == 3, "Временные копии уничтожены, счетчик равен 3", errors);

        std::cout << "\nПроверка конструкторов:\n";
        check(rejectsStudent("", 20, 4.0, group), "Пустое имя отклонено", errors);
        check(rejectsStudent(" \t", 20, 4.0, group), "Имя из пробелов отклонено", errors);
        check(rejectsStudent("Иван", 15, 4.0, group), "Возраст меньше 16 отклонен", errors);
        check(rejectsStudent("Иван", 101, 4.0, group), "Возраст больше 100 отклонен", errors);

        const double badAverages[] = {
            -1.0, 1.0, 5.1,
            std::numeric_limits<double>::quiet_NaN(),
            std::numeric_limits<double>::infinity()
        };

        for (double grade : badAverages)
        {
            check(rejectsStudent("Иван", 20, grade, group),
                  "Неправильный средний балл отклонен, счетчик сохранен", errors);
        }

        try
        {
            Student wrong("Иван", 15, group);
            check(false, "Короткий конструктор проверяет возраст", errors);
        }
        catch (const std::invalid_argument&)
        {
            check(Student::getObjectCount() == 3,
                  "Короткий конструктор проверяет возраст и сохраняет счетчик", errors);
        }

        check(rejectsGroup("", 1) && rejectsGroup(" \t", 1),
              "Пустое название группы отклонено", errors);
        check(rejectsGroup("ИВТ", 0) && rejectsGroup("ИВТ", 7),
              "Курс за пределами от 1 до 6 отклонен", errors);

        std::cout << "\nОтчисление и восстановление:\n";
        check(first.expel(), "Студент отчислен", errors);
        first.printInfo();

        {
            const Student expelled(first);
            check(!first.expel() && !first.passSession(5.0) &&
                  !first.transferToGroup(group) && sameState(first, expelled),
                  "Повторное отчисление, сессия и перевод отклонены", errors);
        }

        check(first.restore(group) && first.isStudying() &&
              first.getGroup().getCourse() == 5 && first.getAverageGrade() == 4.5,
              "Студент восстановлен, результаты обучения сохранены", errors);
        first.printInfo();

        std::cout << "Проверка граничных значений:\n";
        {
            Student youngest("Младший студент", 16, 2.0, Group("ИВТ-11", 1));
            Student oldest("Старший студент", 100, 5.0, Group("ИВТ-61", 6));
            const Student savedOldest(oldest);
            check(youngest.getAge() == 16 && youngest.passSession(2.0) &&
                  youngest.getAverageGrade() == 2.0,
                  "Минимальный возраст и балл допустимы", errors);
            check(oldest.getAge() == 100 && oldest.passSession(5.0) &&
                  oldest.getAverageGrade() == 5.0,
                  "Максимальный возраст и балл допустимы", errors);
            const Student beforeBirthday(oldest);
            check(!oldest.celebrateBirthday() && sameState(oldest, beforeBirthday),
                  "Возраст не может стать больше 100", errors);
            check(savedOldest.getSessionCount() == 1 && oldest.getSessionCount() == 2,
                  "Изменение студента не изменило его копию", errors);

            Group lastGroup("ИВТ-61", 6);
            check(!lastGroup.advanceCourse() && lastGroup.getCourse() == 6,
                  "Группа не может перейти выше шестого курса", errors);
        }

        std::cout << "\nКопирование и счетчик объектов:\n";
        {
            Student copy(second);
            check(Student::getObjectCount() == 4 && sameState(copy, second),
                  "Копирование создало четвертого студента", errors);
            check(copy.passSession(3.0) && second.getAverageGrade() == 0.0 &&
                  second.getSessionCount() == 0,
                  "Изменение копии не изменило оригинал", errors);
            third = copy;
            check(Student::getObjectCount() == 4 && sameState(third, copy),
                  "Присваивание скопировало данные и не изменило счетчик", errors);
            const Student& sameCopy = copy;
            copy = sameCopy;
            check(Student::getObjectCount() == 4 && sameState(copy, third),
                  "Присваивание самому себе сохраняет данные", errors);
            check(third.celebrateBirthday() && copy.getAge() == 20,
                  "После присваивания студенты независимы", errors);
        }

        std::cout << "Существующих студентов: " << Student::getObjectCount() << '\n';
        check(Student::getObjectCount() == 3, "После уничтожения копии осталось три студента", errors);
    }

    std::cout << "После выхода из блока: " << Student::getObjectCount() << '\n';
    check(Student::getObjectCount() == 0, "Деструкторы уменьшили счетчик до 0", errors);
    std::cout << "\nКоличество ошибок: " << errors << '\n';
    std::cout << (errors == 0 ? "Все проверки выполнены\n" : "Есть ошибки проверки\n");
    return errors == 0 ? 0 : 1;
}
