
#include "utils.h"

int main(int argc, char* argv[])
{
    for (int n : {1000, 5000, 20000})
    {
        for (int delimeter : {1, 2, 4, 100, n})
        {
            int k = n / delimeter;
            std::cout << "*****************************************************************" << std::endl;
            std::cout << "GenerateData: n = " << n << " k=" << k << std::endl;
            auto data = GenerateData(n, k);
            MeasureTime(data);
            std::cout << "*****************************************************************" << std::endl << std::endl;
        }
    }
}
