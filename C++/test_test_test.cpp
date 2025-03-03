#include <iostream> 
#include <windows.h> 
#include <windowsx.h> 
#include <wingdi.h> 
#include <stdlib.h> 
#include <vector> 
#include <stack> 
 
void draw_a_table(int high_of_cell, int width_of_cell, int amount_x_cell, int amount_y_cell, HDC hdc)  
{ 
    HPEN white_pen = GetStockPen(WHITE_PEN); 
    SelectPen(hdc, white_pen); 
    for (int j = amount_y_cell; j > 0; j--) //проходим по всем строкам таблицы 
    { 
        for (int i = 0; i < amount_x_cell; i++) //проходим по столбцам 
        { 
            MoveToEx(hdc, 0, high_of_cell * j, NULL); //позиция пера в начале строки 
            LineTo(hdc, width_of_cell * (i + 1), high_of_cell * j); //рисование горизонтальной линии до конца текущего столбца 
            LineTo(hdc, width_of_cell * (i + 1), 0); //рисует вертикальную линию вниз до начала таблицы 
            LineTo(hdc, 0, 0); //линия влево до начала таблицы 
            LineTo(hdc, 0, high_of_cell * j); //вертикальная линия вверх до начала строки 
        } 
    } 
    DeleteObject(white_pen); 
} 
 
void draw_a_square(int high_of_cell, int width_of_cell, int x_number_of_cell, int y_number_of_cell, HDC hdc)  
{ 
    HBRUSH brush = CreateSolidBrush(RGB(0, 255, 0)); 
    SelectBrush(hdc, brush); 
    Rectangle(hdc, width_of_cell * (x_number_of_cell - 1), high_of_cell * (y_number_of_cell - 1), width_of_cell * x_number_of_cell, high_of_cell * y_number_of_cell); //закрашивает 1 ячейку (кант) 
} 
 
void draw_a_square_ora(int high_of_cell, int width_of_cell, int x_number_of_cell, int y_number_of_cell, HDC hdc) //кисть для заливки 
{ 
    HBRUSH brush_ora = CreateSolidBrush(RGB(255, 165, 0)); 
    SelectBrush(hdc, brush_ora); 
    Rectangle(hdc, width_of_cell * (x_number_of_cell - 1), high_of_cell * (y_number_of_cell - 1), width_of_cell * x_number_of_cell, high_of_cell * y_number_of_cell); //закрашивает 1 ячейку (заливка) 
} 
 
void Line(int high_of_cell, int width_of_cell, int x_start, int y_start, int x_end, int y_end, HDC hdc) //треугольник 
{ 
    int dx = abs(x_end - x_start); //разница между начальной и конечной точками по х 
    int dy = abs(y_end - y_start); //разница между начальной и конечной точками по у 
    int sx = x_start < x_end ? 1 : -1;  //направление 
    int sy = y_start < y_end ? 1 : -1; 
    int error = dx - dy; //инициализация ошибки 
    int x = x_start; 
    int y = y_start; 
 
    while (true)  
    { 
        draw_a_square_ora(high_of_cell, width_of_cell, x, y, hdc); //рисует треугольник 
 
        if (x == x_end && y == y_end) //условие выхода из цикла 
        { 
            break; 
        } 
        //проверка ошибок 
        int error2 = error * 2; 
        if (error2 > -dy)  
        { 
            error -= dy; 
            x += sx; 
        } 
        if (error2 < dx)  
        { 
            error += dx; 
            y += sy; 
        } 
    } 
} 
 
void circ_8(int ix0, int iy0, int x, int y, HDC hdc, int high_of_cell, int width_of_cell, int amount_y_cell) //рисуем круг 
{ 
    int x1 = ix0 + x, y1 = iy0 + y, x2 = ix0 - x, y2 = iy0 - y, xy1 = ix0 + y, yx1 = iy0 + x, xy2 = ix0 - y, yx2 = iy0 - x; 
 
    draw_a_square_ora(high_of_cell, width_of_cell, x1, y1, hdc); 
    draw_a_square_ora(high_of_cell, width_of_cell, x2, y1, hdc); 
    draw_a_square_ora(high_of_cell, width_of_cell, x2, y2, hdc); 
    draw_a_square_ora(high_of_cell, width_of_cell, x1, y2, hdc); 
    draw_a_square_ora(high_of_cell, width_of_cell, xy1, yx1, hdc); 
    draw_a_square_ora(high_of_cell, width_of_cell, xy2, yx1, hdc); 
    draw_a_square_ora(high_of_cell, width_of_cell, xy2, yx2, hdc); 
    draw_a_square_ora(high_of_cell, width_of_cell, xy1, yx2, hdc); 
} 
 
void circ(int ix0, int iy0, int ir, HDC hdc, int high_of_cell, int width_of_cell, int amount_y_cell) //алгоритм Брезенхема для круга 
{ 
    int x, y, d; 
    x = 0; y = ir; d = 3 - (ir << 1); 
    while (x < y) 
    { 
        circ_8(ix0, iy0, x, y, hdc, high_of_cell, width_of_cell, amount_y_cell); 
        if (d < 0) d += (x << 2) + 6; 
        else 
        { 
            d += ((x - y) << 2) + 10; 
            --y; 
        } 
        x++; 
    }  
    x = y; 
    circ_8(ix0, iy0, x, y, hdc, high_of_cell, width_of_cell, amount_y_cell); 
} 
 
void empti_triangle(HDC hdc, int x1, int y1, int x2, int y2, int x3, int y3, int high_of_cell) //закрашиваем  
{ 
    Line(high_of_cell, high_of_cell, x1, y1, x2, y2, hdc); 
    Line(high_of_cell, high_of_cell, x2, y2, x3, y3, hdc); 
    Line(high_of_cell, high_of_cell, x3, y3, x1, y1, hdc); 
} 
 
void y_convert(int* y, int amount_y_cell) //преобразуем y для правильного отображения 
{ 
    *y = amount_y_cell - *y + 1; 
} 
 
void filling(int seedX, int seedY, int fillColor, int oldColor, HDC hdc, int high_of_cell)  
{ 
    std::stack<std::pair<int, int>> pixelsStack; //стек для пикселей 
    pixelsStack.push(std::make_pair(seedX, seedY)); //начальный пиксель 
    while (!pixelsStack.empty()) //проверяем наполненность стека 
    { 
        std::pair<int, int> currentPixel = pixelsStack.top(); //первый пиксель из вершины 
        int x = currentPixel.first; //координата первого пикселя (x) 
        int y = currentPixel.second; //координата первого пикселя (y) 
        pixelsStack.pop(); //забрали пиксель, удалили 
        int c = GetPixel(hdc, high_of_cell * x - high_of_cell / 2, high_of_cell * y - high_of_cell / 2); //цвет пикселя 
        //if (c != RGB(255, 255, 0) && c != RGB(255, 0, 0) && c > 0) { 
        if (c == 789516) //совпадение цвета пикселя 
        { 
            //std::cout << c << " " ; 
            draw_a_square(high_of_cell, high_of_cell, x, y, hdc); //квадрат в пикселе 
            pixelsStack.push(std::make_pair(x + 1, y)); //соседние пиксели в стек для обработки 
            pixelsStack.push(std::make_pair(x - 1, y));  
            pixelsStack.push(std::make_pair(x, y + 1)); 
            pixelsStack.push(std::make_pair(x, y - 1)); 
        } 
    } 
} 
 
int main()  
{ 
    HWND hwnd = GetConsoleWindow(); //индификатор окна  
    HDC hdc = GetDC(hwnd); //контекст отображения 
    HBRUSH black_brush = GetStockBrush(BLACK_BRUSH);  
    SelectBrush(hdc, black_brush); 
    FloodFill(hdc, 0, 0, RGB(0, 0, 1)); 
    int high_of_cell, width_of_cell, amount_x_cell, amount_y_cell, x1, y1, x2, y2, x3, y3, x_start, y_start, radius, figures_amount; //ввод переменных  
     
    std::cout << "input high and width of your cell(2 znach):"; //высота и ширина ячейки (сетки) 
    std::cin >> high_of_cell >> width_of_cell;  
    std::cout << "input amount of cell of your table(x and y):"; //количество клеток по х, по y  
    std::cin >> amount_x_cell >> amount_y_cell; 
    std::cout << "1) Draw triygonlik, 2) Draw kryg, 0) Viyti i narisovat':"; //команды 
    std::cin >> figures_amount; 
    std::vector<int> figures; 
 
    while (figures_amount) //собирает донные введенных команд 
    { 
        if (figures_amount == 1) //треугольник 
        { 
            std::cout << "Enter x1, y1 coord: ";  
            std::cin >> x1 >> y1; 
            std::cout << "Enter x2 y2 coord "; 
            std::cin >> x2 >> y2; 
            std::cout << "Enter x3 y3 coord: "; 
            std::cin >> x3 >> y3; 
 
            y_convert(&y1, amount_y_cell); //преобразуем координаты для правильного отображения 
            y_convert(&y2, amount_y_cell); 
            y_convert(&y3, amount_y_cell); 
            figures.push_back(-6); //начало данных треугольника 
            figures.push_back(x1); //добавляем все координаты 
            figures.push_back(y1); 
            figures.push_back(x2); 
            figures.push_back(y2); 
            figures.push_back(x3); 
            figures.push_back(y3); 
        } 
 
        else //рисуем круг 
        { 
            std::cout << "input center of circle (x y coordinates) and radius:";  
            std::cin >> x_start >> y_start >> radius; 
            y_convert(&y_start, amount_y_cell); //преобразует координату 
            figures.push_back(-3); //начало круга 
            figures.push_back(x_start); 
            figures.push_back(y_start); 
            figures.push_back(radius); 
        } 
        std::cout << "1) Draw triygonlik, 2) Draw kryg, 0) Viyti i narisovat': "; 
        std::cin >>figures_amount; 
    } 
 
    system("cls"); //очистка консоли для рисования 
    draw_a_table(high_of_cell, width_of_cell, amount_x_cell, amount_y_cell, hdc); //рисование поля 
 
    for (std::vector<int>::iterator i = figures.begin(); i != figures.end(); i++) //рисует фигуры из вектора 
    { 
        if (*i == -6)  
        { 
            empti_triangle(hdc, *(i + 1), *(i + 2), *(i + 3), *(i + 4), *(i + 5), *(i + 6), high_of_cell); 
            i += 6; 
        } 
        else { 
            circ(*(i + 1), *(i + 2), *(i + 3), hdc, high_of_cell, width_of_cell, amount_y_cell); 
            i += 3; 
        } 
    } 
 
    int fil_x, fil_y; 
    std::cout << "Nachalnaya yacheyka zalivki: "; 
    std::cin >> fil_x >> fil_y; 
    y_convert(&fil_y, amount_y_cell); 
    system("cls"); //очищает консоль 
    draw_a_table(high_of_cell, width_of_cell, amount_x_cell, amount_y_cell, hdc); //рисуем таблицу 
 
    for (std::vector<int>::iterator i = figures.begin(); i != figures.end(); i++)  
    { 
        if (*i == -6) //проверка на начало данных треугольника 
        { 
            empti_triangle(hdc, *(i + 1), *(i + 2), *(i + 3), *(i + 4), *(i + 5), *(i + 6), high_of_cell); //рисует треугольник 
            i += 6; 
        } 
        else  
        { 
            circ(*(i + 1), *(i + 2), *(i + 3), hdc, high_of_cell, width_of_cell, amount_y_cell); //рисует круг 
            i += 3; 
        } 
    } 
 
    filling(fil_x, fil_y, RGB(255, 165, 0), RGB(0, 0, 1), hdc, high_of_cell); //заполняет область, начиная с указанной ячейки 
    ReleaseDC(hwnd, hdc); 
    int i; 
    std::cin >> i; 
    return 0; 
}