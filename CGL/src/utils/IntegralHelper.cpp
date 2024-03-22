#include <cmath>
#include <functional>

namespace IgHelper
{
    const int N = 1000000;

    // ������� ��� ����������
    static double func(double x) {
        return std::cos(x) / (x * x + 1);
    }

    // ������� ���������� �������������� ������� ��������
    static double trapezoidalIntegral(int a, int b) {
        double h = (static_cast<double>(b) - a) / N; // ��� ��������������
        double integral = 0.5 * (func(a) + func(b));

        for (int i = 1; i < N; ++i) {
            double x_i = a + i * h;
            integral += func(x_i);
        }

        integral *= h;
        return integral;
    }

    // ������� ���������� �������������� ������� ��������
    static double simpsonIntegral(int a, int b) 
    {
        double h = (static_cast<double>(b) - a) / N;
        double integral = func(a) + func(b);

        for (int i = 1; i < N; i += 2) {
            double x_i = a + i * h;
            integral += 4 * func(x_i);
        }

        for (int i = 2; i < N - 1; i += 2) {
            double x_i = a + i * h;
            integral += 2 * func(x_i);
        }

        integral *= h / 3;
        return integral;
    }

    // ������� ���������� �������������� ������� ������� ���������������
    static double midpointIntegral(int a, int b) 
    {
        double h = (static_cast<double>(b) - a) / N;
        double integral = 0.0;

        for (int i = 0; i < N; ++i) {
            double x_i = a + (i + 0.5) * h;
            integral += func(x_i);
        }

        integral *= h;
        return integral;
    }
}