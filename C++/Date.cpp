#include "Date1_1970.h"
#include <ctime>
#include <stdexcept>

Date::Date(int d, int m, int y) : _day(d), _month(m), _year(y) {
    validateDate();
}

Date::Date(const std::string &dateStr) {
    std::istringstream iss(dateStr);
    char dot1, dot2;
    if (!(iss >> _day >> dot1 >> _month >> dot2 >> _year) || dot1 != '.' || dot2 != '.' || !iss.eof()) {
        throw std::invalid_argument("Invalid format date");
    }
    if (_year < 100) _year += 2000;
    validateDate();
}

Date::Date() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    _day = ltm->tm_mday;
    _month = 1 + ltm->tm_mon ;
    _year = 1900 + ltm->tm_year;
}

int Date::getDay() const {
    return _day;
}
int Date::getMonth() const { 
    return _month; 
}
int Date::getYear() const {
    return _year;
}

void Date::setDay(int day) {
    _day = day;
    validateDate();
}

void Date::setMonth(int month) {
    _month = month;
    validateDate();
}

void Date::setYear(int year) {
    _year = year;
    validateDate();
}

std::string Date::toString() const {
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << _day << "."
        << std::setw(2) << std::setfill('0') << _month << "."
        << std::setw(4) << std::setfill('0') << _year;
    return oss.str();
}


int Date::operator-(const Date& d) const {
    tm thisDate = {0, 0, 0, _day, _month - 1, _year - 1900};
    tm otherDate = {0, 0, 0, d._day, d._month - 1, d._year - 1900};
    time_t thisTime = mktime(&thisDate);
    time_t otherTime = mktime(&otherDate);

    return difftime(thisTime, otherTime) / (60 * 60 * 24); 
}

Date Date::operator+(int days) const {
    tm thisDate = {0, 0, 0, _day, _month - 1, _year - 1900};
    time_t currentTime = mktime(&thisDate);
    currentTime += days * 24 * 60 * 60;
    tm *newDate = localtime(&currentTime);
    
    return Date(newDate->tm_mday, newDate->tm_mon + 1, newDate->tm_year + 1900);
}


void Date::validateDate() {
    if (_year < 1900 || _month < 1 || _month > 12 || _day < 1 || _day > 31) {
        throw std::invalid_argument("Invalid date");
    }
    if (_month == 2) {
        bool leapYear = (_year % 4 == 0 && (_year % 100 != 0 || _year % 400 == 0));
        if (_day > (leapYear ? 29 : 28)) {
            throw std::invalid_argument("Invalid date");
        }
    } else if (_month == 4 || _month == 6 || _month == 9 || _month == 11) {
        if (_day > 30) {
            throw std::invalid_argument("Invalid date");
        }
    }
}
