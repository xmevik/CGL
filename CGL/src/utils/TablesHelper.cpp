#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>

namespace TbHelper
{
    double a = -M_PI, b = M_PI, n = 20;

    static double F1(double x) { return 2-cos(x); }
    static double F2(double x) { return sqrt(x+4); }

    static double getMeanDistance() { return fabs(a-b)/(n); }
    
    //  _____________________
    //  |_0_|___1___|___2___|
    //  |_x_|_F1(x)_|_F2(x)_|
    static std::vector<std::vector<double>> getVectorDatas()
    {
        std::vector<std::vector<double>> result;
        std::vector<double> temp;
        for(double i = a; i <= b; i+=getMeanDistance())
        {
			temp.clear();
            temp.push_back(i);
            temp.push_back(F1(i));
            temp.push_back(F2(i));
            result.push_back(temp);
        }

        return result;
    }
}