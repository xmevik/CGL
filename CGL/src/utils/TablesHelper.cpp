#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

struct TbHelper
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
            double sum = f1 + f2;
            double mean = sum / 2;
            temp.clear();
            temp.push_back(i);
            temp.push_back(f1);
            temp.push_back(f2);
            temp.push_back(sum);
            temp.push_back(mean);
            result.push_back(temp);
        }

        return result;
    }

    static std::vector<std::vector<std::wstring>> getMinMaxData(std::vector<std::vector<double>> data)
    {
        std::wstring minName = L"MIN";
        std::wstring maxName = L"MAX";
        double minFirst = data[0][1];
        double maxFirst = data[0][1];
        double minSecond = data[0][2];
        double maxSecond = data[0][2];
        std::vector<std::vector<std::wstring>> result;
        std::vector<std::wstring> temp;

        for (auto& temporary : data)
        {
            minFirst = min(minFirst, temporary[1]);
            maxFirst = max(maxFirst, temporary[1]);
            minSecond = min(minSecond, temporary[2]);
            maxSecond = max(maxSecond, temporary[2]);
        }

        temp.push_back(minName);
        temp.push_back(to_wstring(minFirst));
        temp.push_back(to_wstring(minSecond));
        result.push_back(temp);

        temp.clear();

        temp.push_back(maxName);
        temp.push_back(to_wstring(maxFirst));
        temp.push_back(to_wstring(maxSecond));
        result.push_back(temp);

        return result;
    }
};