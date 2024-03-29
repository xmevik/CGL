#include <cmath>
#include <functional>
#include <sstream>
#include <iomanip>

#define ERR_NO_SUCH_ROOTS -0.102420484096

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

// Вычисление корня уравнения методом бисекции
static double bisectionMethod(int a, int b, double e)
{
    if (funcE(a) * funcE(b) >= 0) {
        return ERR_NO_SUCH_ROOTS;
    }

    double c = a, bTemp = b, aTemp = a;
    while ((bTemp - aTemp) >= e) {

        c = (aTemp + bTemp) / 2;

        if (funcE(c) == 0.0)
            return c;
        else if (funcE(c) * funcE(aTemp) < 0)
            bTemp = c;
        else
            aTemp = c;
    }
    return (aTemp + bTemp) / 2;
}

// Вычисление корня уравнения методом хорд
static double chordMethod(int a, int b, double e)
{
    if (funcE(a) * funcE(b) >= 0) {
        return ERR_NO_SUCH_ROOTS;
    }

    double c = a, aTemp = a, bTemp = b;
    while (abs(funcE(bTemp)) >= e) {
        // Вычисляем новую точку пересечения хорды с осью абсцисс
        c = aTemp - (funcE(aTemp) * (bTemp - aTemp)) / (funcE(bTemp) - funcE(aTemp));

        aTemp = bTemp;
        bTemp = c;
    }
    return bTemp;
}