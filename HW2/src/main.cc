#include <iostream>
#include <sstream>      // std::stringstream
#include <cstring>
#include <string>
#include <memory>
#include <fstream>
#include "Series.hh"
#include "ComputeArithmetic.hh"
#include "ComputePi.hh"
#include "DumperSeries.hh"
#include "PrintSeries.hh"
#include "WriteSeries.hh"
#include "RiemannIntegral.hh"

/*!
 * @brief main function of series and integral examples
 * @param argc argument count
 * @param argv argument vector
 * @return
 */
int main(int argc, char *argv[]) {

    std::stringstream ss;

    std::string exerciseType;
    unsigned long maxIter, freq;
    std::string separatorType;
    std::string outputOption;
    std::string seriesType;
    double lowerLimit, upperLimit;
    std::string functionType;

    // Argument parsing
    if (strcmp(argv[1], "series") == 0)
    {
        ss << argv[1] << ' ' << argv[2] << ' ' << argv[3] << ' ' << argv[4] << ' ' << argv[5] << ' ' << argv[6] << std::endl;
        ss >> exerciseType >> maxIter >> freq >> seriesType >> outputOption >> separatorType;

        std::cout << "exercise type: " << exerciseType << std::endl;
        std::cout << "maximum iteration: " << maxIter << std::endl;
        std::cout << "frequency: " << freq << std::endl;
        std::cout << "series type: " << seriesType << std::endl;
        std::cout << "output option: " << outputOption << std::endl;
        std::cout << "separator type: " << separatorType << std::endl;

        char separator;
        if (separatorType == "comma") {
            separator = ',';
        } else if (separatorType == "pipe") {
            separator = '|';
        } else if (separatorType == "space" || separatorType == "tab") {
            separator = ' ';
        }

        // EXERCISE 2
        // Shared pointers
        std::shared_ptr<Series> sharedSeries;

        double result;
        if (seriesType == "arithmetic") {
            auto seriesTypeSelected = std::make_shared<ComputeArithmetic>();
            sharedSeries = seriesTypeSelected;
        }
        else if (seriesType == "pi")
        {
            auto seriesTypeSelected = std::make_shared<ComputePi>();
            sharedSeries = seriesTypeSelected;
        }
        else
        {
            std::cerr << "Invalid series type choice is given" << std::endl;
        }
        // Compute the series and print the result
        result = sharedSeries->compute(maxIter);
        std::cout << "The result of summation is: " << result << std::endl;

        // EXERCISE 3
        // Shared pointers
        if (outputOption == "print") {
            PrintSeries printingSeries(sharedSeries, maxIter, freq);
            printingSeries.dump();

            std::string fileName = "output_ex4";
            std::string relativePath = "..\\..\\";
            std::string fileExt = ".txt";

            relativePath = relativePath + fileName + fileExt;
            // Exercise 4
            std::ofstream myfile(relativePath);
            myfile << printingSeries;
            myfile.close();
            std::cout << "EXERCISE 4: File is saved in " << relativePath << std::endl;

        }
        else if (outputOption == "write") {
            WriteSeries writeSeries(sharedSeries, maxIter);
            writeSeries.setSeparator(separator);
            writeSeries.dump();
        }
        else {
            std::cerr << "Invalid output choice is given" << std::endl;
        }
    }
    // EXERCISE 6
    else if (strcmp(argv[1], "integral") == 0)
    {
        ss << argv[1] << ' ' << argv[2] << ' ' << argv[3] << ' ' << argv[4] << std::endl;
        ss >> exerciseType >> lowerLimit >> upperLimit >> functionType;

        std::cout << "exercise type: " << exerciseType << std::endl;
        std::cout << "lower limit: " << lowerLimit << std::endl;
        std::cout << "upper limit: " << upperLimit << std::endl;
        std::cout << "function type: " << functionType << std::endl;
        // Define the function
        std::function<double(double)> func;

        if (functionType == "cube")
        {
            // Case 1 - cube - min N needed: 1e2 for 2 digits: 0.255025
            auto calcCube = [](double x) { return 1.0 * x * x * x; };
            func = calcCube;
        }
        else if (functionType == "cos") {
            // Case 2 - cosine - min N needed: 1e3 for 2 digits: -0.00314159
            auto cosine = [](double x) { return std::cos(x); };
            func = cosine;
        }
        else if (functionType == "sin") {
            // Case 3 - sine - min N needed: 1e2 for 2 digits: 1.00266
            auto sine = [](double x) { return std::sin(x); };
            func = sine;
        }
        RiemannIntegral riemannInt(lowerLimit, upperLimit, func);
        double result = riemannInt.compute();
        std::cout << "Integral of function " << functionType << " " << result << std::endl;


    }
};