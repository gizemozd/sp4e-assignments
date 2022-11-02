#include <iostream>
#include <sstream>      // std::stringstream
#include <cstring>
#include <string>
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

    ComputeArithmetic arithmetic_series;
    ComputePi pi_series;

    std::stringstream ss;

    std::string exerciseType;
    unsigned long maxIter, freq;
    std::string separatorType;
    std::string outputOption;
    std::string seriesType;
    double lowerLimit, upperLimit;
    std::string functionType;

    std::cout << argc << std::endl;
    std::cout << argv[1] << std::endl;

    if (strcmp(argv[1], "series") == 0) {
        std::cout << argv[1] << "series" << std::endl;

        ss << argv[1] << ' ' << argv[2] << ' ' << argv[3] << ' ' << argv[4] << ' ' << argv[5] << ' ' << argv[6]
           << std::endl;
        ss >> exerciseType >> maxIter >> freq >> seriesType >> outputOption >> separatorType;

        std::cout << "exerciseType: " << exerciseType << std::endl;
        std::cout << "maxIter: " << maxIter << std::endl;
        std::cout << "freq: " << freq << std::endl;
        std::cout << "seriesType: " << seriesType << std::endl;
        std::cout << "outputOption: " << outputOption << std::endl;
        std::cout << "separatorType: " << separatorType << std::endl;

        char separator;
        if (separatorType == "comma") {
            separator = ',';
        } else if (separatorType == "pipe") {
            separator = '|';
        } else if (separatorType == "space" || separatorType == "tab") {
            separator = ' ';
        }

        double result;
        if (seriesType == "arithmetic") {
            result = arithmetic_series.compute(maxIter);
            std::cout << result << std::endl;
        } else if (seriesType == "pi") {
            result = pi_series.compute(maxIter);
            std::cout << result << std::endl;
        } else {
            std::cout << "Invalid series type choice is given" << std::endl;
        }

        if (outputOption == "print") {
            PrintSeries printingseriestest(pi_series, maxIter, freq);
            printingseriestest.dump();
        } else if (outputOption == "write") {
            WriteSeries testFileToOutput(pi_series, maxIter);
            testFileToOutput.setSeparator(separator);
            testFileToOutput.dump();
        } else {
            std::cout << "Invalid output choice is given" << std::endl;
        }
    } else if (strcmp(argv[1], "integral") == 0) {
        std::cout << argv[1] << "integral" << std::endl;

        ss << argv[1] << ' ' << argv[2] << ' ' << argv[3] << ' ' << argv[4] << std::endl;
        ss >> exerciseType >> lowerLimit >> upperLimit >> functionType;

        std::cout << "exerciseType: " << exerciseType << std::endl;
        std::cout << "lowerLimit: " << lowerLimit << std::endl;
        std::cout << "upperLimit: " << upperLimit << std::endl;
        std::cout << "functionType: " << functionType << std::endl;

        if (functionType == "cube") {
            // Case 1 - cube - min N needed: 1e2 for 2 digits: 0.255025
            auto calcCube = [](double x) { return 1.0 * x * x * x; };
            RiemannIntegral riemannCube(lowerLimit, upperLimit, calcCube);
            double resInt1 = riemannCube.compute();
            std::cout << "Cube " << resInt1 << std::endl;
        } else if (functionType == "cos") {
            // Case 2 - cosine - min N needed: 1e3 for 2 digits: -0.00314159
            auto cosine = [](double x) { return std::cos(x); };
            RiemannIntegral riemannCos(lowerLimit, upperLimit, cosine);
            double resInt2 = riemannCos.compute();
            std::cout << "Cosine" << resInt2 << std::endl;
        } else if (functionType == "sin") {
            // Case 3 - sine - min N needed: 1e2 for 2 digits: 1.00266
            auto sine = [](double x) { return std::sin(x); };
            RiemannIntegral riemannSin(lowerLimit, upperLimit, sine);
            double resInt3 = riemannSin.compute();
            std::cout << "Sine " << resInt3 << std::endl;
        }
    }
};