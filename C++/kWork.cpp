#include <iostream>
#include <stdexcept>
#include <string>
#include <iomanip>


class Date {
private:
    int day;
    int month;
    int year;

    // Проверка корректности даты
    bool isValidDate(int day, int month, int year) const {
        if (year < 0 || month < 1 || month > 12 || day < 1) return false;

        int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        
        // Учитываем високосные годы
        if (isLeapYear(year)) daysInMonth[1] = 29;

        return day <= daysInMonth[month - 1];
    }

    // Проверка на високосный год
    bool isLeapYear(int year) const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

public:
    // Конструктор по умолчанию
    Date() : day(1), month(1), year(1900) {}

    // Конструктор с параметрами
    Date(int day, int month, int year) {
        if (!isValidDate(day, month, year)) {
            throw std::invalid_argument("Invalid date");
        }
        this->day = day;
        this->month = month;
        this->year = year;
    }

    // Геттеры
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

    // Сеттеры
    void setDay(int day) {
        if (!isValidDate(day, month, year)) {
            throw std::invalid_argument("Invalid day");
        }
        this->day = day;
    }

    void setMonth(int month) {
        if (!isValidDate(day, month, year)) {
            throw std::invalid_argument("Invalid month");
        }
        this->month = month;
    }

    void setYear(int year) {
        if (!isValidDate(day, month, year)) {
            throw std::invalid_argument("Invalid year");
        }
        this->year = year;
    }

    // Метод для вывода даты в формате ДД-ММ-ГГГГ
    void printDate() const {
        std::cout << std::setfill('0') << std::setw(2) << day << "-"
                  << std::setfill('0') << std::setw(2) << month << "-"
                  << year << std::endl;
    }
};
