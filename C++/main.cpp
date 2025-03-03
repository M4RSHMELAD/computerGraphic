#include<iostream>
#include "Date1_1970.h"



int main() {
    try {
        Date date1(28, 12, 2024); 
        Date date2("29.12.2025"); 
        Date date3;               

        std::cout << "Date 1: " << date1.toString() << std::endl;
        std::cout << "Date 2: " << date2.toString() << std::endl;
        std::cout << "Today Date: " << date3.toString() << std::endl;

        int difference = date1 - date2; 
        std::cout << "Difference in days between date 1 and date 2: " << difference << " days" << std::endl;

        Date newDate = date1 + 10;
        std::cout << "Date 1 + 10 days: " << newDate.toString() << std::endl;

        Date multipliedDate = date1 * 2;
        std::cout << "Date 1 * 2: " << multipliedDate.toString() << std::endl;

        Date dividedDate = date2 / 2;
        std::cout << "Date 2 / 2: " << dividedDate.toString() << std::endl;

        date1 += 20;
        std::cout << "Date 1 after += 20 days: " << date1.toString() << std::endl;

        date2 -= 30;
        std::cout << "Date 2 after -= 30 days: " << date2.toString() << std::endl;

        if (date1 == date2) {
            std::cout << "Date 1 and Date 2 are equal." << std::endl;
        } else {
            std::cout << "Date 1 and Date 2 are not equal." << std::endl;
        }

        if (date1 != date3) {
            std::cout << "Date 1 and Date 3 are not equal." << std::endl;
        }

    } catch (const std::exception &ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
}