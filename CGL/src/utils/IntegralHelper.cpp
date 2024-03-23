#include <cmath>
#include <functional>
#include <sstream>
#include <iomanip>

namespace IgHelper
{
    const int N = 1000000;

    // Функция под интегралом
    static double funct(double x) {
        return std::cos(x) / (x * x + 1);
    }

    // Функция численного интегрирования методом трапеций
    static double trapezoidalIntegral(int a, int b) {
        double h = (static_cast<double>(b) - a) / N; // Шаг интегрирования
        double integral = 0.5 * (funct(a) + funct(b));

        for (int i = 1; i < N; ++i) {
            double x_i = a + i * h;
            integral += funct(x_i);
        }

        integral *= h;
        return integral;
    }

    // Функция численного интегрирования методом Симпсона
    static double simpsonIntegral(int a, int b) 
    {
        double h = (static_cast<double>(b) - a) / N;
        double integral = funct(a) + funct(b);

        for (int i = 1; i < N; i += 2) {
            double x_i = a + i * h;
            integral += 4 * funct(x_i);
        }

        for (int i = 2; i < N - 1; i += 2) {
            double x_i = a + i * h;
            integral += 2 * funct(x_i);
        }

        integral *= h / 3;
        return integral;
    }

    // Функция численного интегрирования методом средних прямоугольников
    static double midpointIntegral(int a, int b) 
    {
        double h = (static_cast<double>(b) - a) / N;
        double integral = 0.0;

        for (int i = 0; i < N; ++i) {
            double x_i = a + (i + 0.5) * h;
            integral += funct(x_i);
        }

        integral *= h;
        return integral;
    }

    static std::wstring doubleToWString(double value, int precision = 2) 
    {
        std::wstringstream stream;
        stream << std::fixed << std::setprecision(precision) << value;
        return stream.str();
    }
}