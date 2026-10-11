#ifndef GROUP_H
#define GROUP_H

#include <string>

/**
 * @brief Класс для хранения учебной группы
 */
class Group
{
private:
    std::string name;
    int course;

public:
    /**
     * @brief Создает группу с начальными значениями
     */
    Group();

    /**
     * @brief Создает группу с заданным названием и курсом
     *
     * @param name Название группы
     * @param course Курс от 1 до 6
     * @throws std::invalid_argument Если данные группы неправильные
     */
    Group(const std::string& name, int course);

    /**
     * @brief Завершает время жизни группы
     */
    ~Group();

    /**
     * @brief Возвращает название группы
     *
     * @return Название группы
     */
    const std::string& getName() const;

    /**
     * @brief Возвращает номер курса
     *
     * @return Номер курса
     */
    int getCourse() const;

    /**
     * @brief Переводит группу на следующий курс
     *
     * @return true если переход выполнен
     */
    bool advanceCourse();

    /**
     * @brief Выводит информацию о группе
     */
    void printInfo() const;
};

#endif
