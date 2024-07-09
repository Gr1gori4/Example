// vect.срр -- методы класса Vector
#include <cmath>
#include "vect.h" // включает <iostream>
using std::atan;
using std::cos;
using std::cout;
using std::sin;
using std::sqrt;
using std::atan2;

namespace VECTOR
{
    // Вычисляет количество градусов в одном радиане
    const double Rad_to_deg = 45.0 / atan(1.0); // должно быть приблизительно равно 57 .29577 95130823

    // Закрытые методы
    // Вычисляет модуль из х и у
    void Vector::set_mag()
    {
        mag = sqrt(x * x + у * у);
    }
    void Vector::set_ang()
    {
        if (x == 0.0 && у == 0.0)
            ang = 0.0;
        else
            ang = atan2(у, x);
    }
    // Устанавливает х по полярным координатам
    void Vector::set_x()
    {
        x = mag * cos(ang);
    }

    // Устанавливает у по полярным координатам
    void Vector::set_y()
    {
        у = mag * sin(ang);
    }

    // Открытые методы
    Vector::Vector() // конструктор по умолчанию
    {
        x = у = mag = ang = 0.0;
        mode = RECT;
    }
    // Конструирует вектор по прямоугольным координатам, если form равно RECT
    // (по умолчанию) , или по полярным координатам, если form равно POL
    Vector::Vector(double nl, double n2, Mode form)
    {
        mode = form;
        if (form == RECT)
        {
            x = nl;
            у = n2;
            set_mag();
            set_ang();
        }
        else if (form == POL)
        {
            mag = nl;
            ang = n2 / Rad_to_deg;
            set_x();
            set_y();
        }
        else
        {
            // Некорректный третий аргумент Vector(); вектор устанавливается в О
            cout << " Incorrect Зrd argument to Vector () -- ";
            cout << "vector set to 0\n";
            x = у = mag = ang = 0.0;
            mode = RECT;
        }
    }
    // Устанавливает вектор по прямоугольным координатам, если form равно RECT
    // ( по умолчанию) , или по полярным координатам, если если form равно POL
    void Vector::reset(double n1, double n2, Mode form)
    {
        mode = form;
        if (form == RECT)
        {
            x = n1;
            у = n2;
            set_mag();
            set_ang();
        }
        else if (form == POL)
        {
            mag = n1;
            ang = n2 / Rad_to_deg;
            set_x();
            set_y();
        }
        else
        {
            cout << " Incorrect Зrd argument to Vector () -- ";
            cout << "vector set to 0 \n ";
            x = у = mag = ang = 0.0;
            mode = RECT;
        }
    }
    Vector::~Vector() // деструктор
    {
    }
    void Vector::polar_mode() // устанавливает режим полярных координат
    {
        mode = POL;
    }
    void Vector::rect_mode() // устанавливает режим прямоуголь ных координат
    {
        mode = RECT;
    }
    // Перегрузка операций
    // Сложение двух векторов
    Vector Vector::operator+(const Vector &b) const
    {
        return Vector(x + b.x, у + b.у);
    }
    // Вычитание вектора Ь из а
    Vector Vector::operator-(const Vector &b) const
    {
        return Vector(x - b.x, у - b.у);
    }
    // Смена знака вектора на противоположный
    Vector Vector::operator-() const
    {
        return Vector(-x, -у);
    }
    // Умножение вектора на n
    Vector Vector::operator*(double n) const
    {
        return Vector(n * x, n * у);
    }
    // Дружественные методы
    // Умножение n на вектор а
    Vector operator*(double n, const Vector &а)
    {
        return а * n;
    }
    // Отображает прямоугольные координаты, если mode равно RECT,
    // или отображает полярные координаты, если mode равно POL
    std::ostream & operator<<(std::ostream & os, const Vector & v)
    {
        if (v.mode == Vector::RECT)
        {
            os << " (х , у) = (" << v.x << ", " /*<< v.y <<  ") "*/;
        }
        else if (v.mode == Vector::POL)
        {
            os << " (m,a) = (" << v.mag << "," << v.ang * Rad_to_deg << ") ";
        }
        else
        {
            os << "Vector obj ect mode is invalid"; // недопустимый режим объекта Vector
        }
        return os;
    }
}
// конец пространства имен VECTOR