#pragma once
#include <string>
#include <ctime>
#include <stdexcept>
#include <sstream>
#include <iomanip>

class Date {
    private:
        int _day;
        int _month;
        int _year;

    public:
        
        Date(int d, int m, int y);                     
        Date(const std::string &dateStr);              
        Date();                                       
        
        int getDay() const;
        int getMonth() const;
        int getYear() const;

        
        void setDay(int day);
        void setMonth(int month);
        void setYear(int year);

        
        std::string toString() const;

        Date operator*(int multiplier) const;
        Date operator/(int divisor) const;

        int operator-(const Date& d) const;
        Date operator+(int days) const;


        Date operator*(int factor) const;
        Date operator/(int divisor) const;
        
        Date& operator+=(int days);
        Date& operator-=(int days);
    private:
        
        void validateDate();
};
