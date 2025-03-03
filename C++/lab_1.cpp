#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

void showMenu() {
    cout << "\nЭлектронная запись:" << endl;
    cout << "1. Зарегистрировать аккаунт" << endl;
    cout << "2. Добавить запись" << endl;
    cout << "3. Показать записи" << endl;
    cout << "4. Удалить запись" << endl;
    cout << "5. Показать все аккаунты" << endl;
    cout << "6. Выход" << endl;
    cout << "Выберите опцию: ";
}

int main() {
    map<string, vector<string>> userAppointments;
    string username;
    int choice;
    string date;
    
    do {
        showMenu();
        cin >> choice;
        cin.ignore(); // очистка буфера
        
        switch (choice) {
            case 1:
                cout << "Введите имя пользователя: ";
                getline(cin, username);
                if (userAppointments.find(username) == userAppointments.end()) {
                    userAppointments[username] = {};
                    cout << "Аккаунт зарегистрирован." << endl;
                } else {
                    cout << "Такой аккаунт уже существует." << endl;
                }
                break;
            case 2:
                cout << "Введите имя пользователя: ";
                getline(cin, username);
                if (userAppointments.find(username) != userAppointments.end()) {
                    cout << "Введите дату записи (дд.мм.гггг чч:мм): ";
                    getline(cin, date);
                    userAppointments[username].push_back(date);
                    cout << "Запись добавлена." << endl;
                } else {
                    cout << "Аккаунт не найден. Сначала зарегистрируйтесь." << endl;
                }
                break;
            case 3:
                cout << "Введите имя пользователя: ";
                getline(cin, username);
                if (userAppointments.find(username) != userAppointments.end()) {
                    if (userAppointments[username].empty()) {
                        cout << "Записей нет." << endl;
                    } else {
                        cout << "Список записей для " << username << ":" << endl;
                        for (size_t i = 0; i < userAppointments[username].size(); ++i) {
                            cout << i + 1 << ". " << userAppointments[username][i] << endl;
                        }
                    }
                } else {
                    cout << "Аккаунт не найден." << endl;
                }
                break;
            case 4:
                cout << "Введите имя пользователя: ";
                getline(cin, username);
                if (userAppointments.find(username) != userAppointments.end()) {
                    if (!userAppointments[username].empty()) {
                        int index;
                        cout << "Введите номер записи для удаления: ";
                        cin >> index;
                        if (index > 0 && index <= userAppointments[username].size()) {
                            userAppointments[username].erase(userAppointments[username].begin() + index - 1);
                            cout << "Запись удалена." << endl;
                        } else {
                            cout << "Неверный номер записи." << endl;
                        }
                    } else {
                        cout << "Список пуст." << endl;
                    }
                } else {
                    cout << "Аккаунт не найден." << endl;
                }
                break;
            case 5:
                cout << "Зарегистрированные аккаунты:" << endl;
                for (const auto& pair : userAppointments) {
                    cout << "- " << pair.first << endl;
                }
                break;
            case 6:
                cout << "Выход из программы." << endl;
                break;
            default:
                cout << "Некорректный ввод. Попробуйте снова." << endl;
        }
    } while (choice != 6);
    
    return 0;
}