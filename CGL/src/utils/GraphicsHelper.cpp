#include <cmath>
#include <vector>

namespace GhHelper 
{
    static double F1(double x) { return 2 - cos(x); }
    static double F2(double x) { return sqrt(x + 4); }

    static double getMeanDistance(double a, double b, double n) { return fabs(a - b) / (n); }

    static std::vector<std::vector<double>> getVectorDatas(double a, double b, double n)
    {
        std::vector<std::vector<double>> result;
        std::vector<double> temp;
        for (double i = a; i <= b; i += getMeanDistance(a, b, n))
        {
            double f1 = F1(i);
            double f2 = F2(i);
            temp.clear();
            temp.push_back(i);
            temp.push_back(f1);
            temp.push_back(f2);
            result.push_back(temp);
        }

        return result;
    }
}