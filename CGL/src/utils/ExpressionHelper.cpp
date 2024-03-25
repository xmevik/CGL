#include <cmath>
#include <functional>
#include <sstream>
#include <iomanip>

static double funcE(double x)
{
    return 0.5 + cos(x) - 2 * x * sin(x);
}

static std::wstring doubleToWStringW(double value, int precision)
{
    std::wstringstream stream;
    stream << std::fixed << std::setprecision(precision) << value;
    return stream.str();
}

// TODO: steel need to test this

// ���������� ������ ��������� ������� ��������
static double bisectionMethod(int a, int b, double e)
{
    if (funcE(a) * funcE(b) >= 0) {
        return -1.024;
    }

    double c = a, bTemp = b, aTemp = a;
    while ((bTemp - aTemp) / 2 > e) {

        c = (aTemp + bTemp) / 2;

        if (funcE(c) == 0.0)
            break;
        else if (funcE(c) * funcE(aTemp) < 0)
            bTemp = c;
        else
            aTemp = c;
    }
    return c;
}

// ���������� ������ ��������� ������� ����
static double chordMethod(int a, int b, double e)
{
    if (funcE(a) * funcE(b) >= 0) {
        return -1.024;
    }

    double c = a, aTemp = a, bTemp = b;
    while (abs(bTemp - aTemp) > e) {
        // ��������� ����� ����� ����������� ����� � ���� �������
        c = (aTemp * funcE(bTemp) - bTemp * funcE(aTemp)) / (funcE(bTemp) - funcE(aTemp));

        // ���������, � ������ ������� ����������� ������
        if (funcE(c) * funcE(aTemp) < 0) {
            bTemp = c;
        }
        else {
            aTemp = c;
        }
    }
    return c;
}