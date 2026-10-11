#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include "Group.h"

/**
 * @brief Класс для хранения студента и результатов обучения
 */
class Student
{
private:
    std::string fullName;
    int age;
    double averageGrade;
    int sessionCount;
    bool studying;
    Group group;
    static int objectCount;

public:
    /**
     * @brief Создает студента с начальными значениями
     */
    Student();

    /**
     * @brief Создает студента без сданных сессий
     *
     * @param fullName Имя студента
     * @param age Возраст от 16 до 100 лет
     * @param group Учебная группа
     */
    Student(const std::string& fullName, int age, const Group& group);

    /**
     * @brief Создает студента с заданным средним баллом
     *
     * @param fullName Имя студента
     * @param age Возраст от 16 до 100 лет
     * @param averageGrade Ноль или средний балл от 2 до 5
     * @param group Учебная группа
     * @throws std::invalid_argument Если данные студента неправильные
     */
    Student(const std::string& fullName, int age,
            double averageGrade, const Group& group);

    /**
     * @brief Создает копию студента
     *
     * @param other Студент для копирования
     */
    Student(const Student& other);

    /**
     * @brief Копирует данные в существующего студента
     *
     * @param other Студент для копирования
     * @return Ссылка на измененный объект
     */
    Student& operator=(const Student& other) = default;

    /**
     * @brief Завершает время жизни студента и уменьшает счетчик
     */
    ~Student();

    /**
     * @brief Возвращает имя студента
     *
     * @return Имя студента
     */
    const std::string& getFullName() const;

    /**
     * @brief Возвращает возраст студента
     *
     * @return Возраст студента
     */
    int getAge() const;

    /**
     * @brief Возвращает средний балл
     *
     * @return Средний балл или ноль, если сессий не было
     */
    double getAverageGrade() const;

    /**
     * @brief Возвращает количество сданных сессий
     *
     * @return Количество сессий
     */
    int getSessionCount() const;

    /**
     * @brief Проверяет, учится ли студент
     *
     * @return true если студент учится
     */
    bool isStudying() const;

    /**
     * @brief Возвращает учебную группу
     *
     * @return Константная ссылка на группу
     */
    const Group& getGroup() const;

    /**
     * @brief Возвращает количество существующих студентов
     *
     * @return Количество объектов Student
     */
    static int getObjectCount();

    /**
     * @brief Добавляет результат сессии и пересчитывает средний балл
     *
     * @param grade Балл за сессию от 2 до 5
     * @return true если результат добавлен
     */
    bool passSession(double grade);

    /**
     * @brief Переводит студента в другую группу
     *
     * @param newGroup Новая учебная группа
     * @return true если перевод выполнен
     */
    bool transferToGroup(const Group& newGroup);

    /**
     * @brief Увеличивает возраст на один год
     *
     * @return true если возраст изменен
     */
    bool celebrateBirthday();

    /**
     * @brief Отчисляет студента
     *
     * @return true если студент отчислен
     */
    bool expel();

    /**
     * @brief Восстанавливает студента в указанной группе
     *
     * @param newGroup Группа для восстановления
     * @return true если студент восстановлен
     */
    bool restore(const Group& newGroup);

    /**
     * @brief Выводит информацию о студенте
     */
    void printInfo() const;
};

#endif
