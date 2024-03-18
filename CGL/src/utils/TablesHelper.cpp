#include <cmath>
#include <vector>

namespace TbHelper
{
    static double F1(double x) { return 2 - cos(x); }
    static double F2(double x) { return sqrt(x + 4); }

    static double getMeanDistance(double a, double b, double n) { return fabs(a - b) / (n); }

    //  _____________________________________
	//  |_0_|___1___|___2___|___3___|___4___|
    //  |_x_|_F1(x)_|_F2(x)_|__sum__|__avg__|
    static std::vector<std::vector<double>> getVectorDatas(double a, double b, double n)
    {
        std::vector<std::vector<double>> result;
        std::vector<double> temp;
        for (double i = a; i <= b; i += getMeanDistance(a,b,n))
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

    static std::vector<std::vector<double>> addAvgData(std::vector<std::vector<double>> data)
    {

    }
}