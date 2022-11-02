#include <iostream>
#include <string>
#include <fstream>
#include "WriteSeries.hh"

/*!
 * @brief constructor
 * @param series series taken into consideration
 * @param maxIter maximum iteration
 */
WriteSeries::WriteSeries(Series &series, unsigned long maxIter) : DumperSeries(series) {
    this->maxIter = maxIter;
};

/*!
 * @brief setting the separator for the output file
 * @param c separator character
 */
void WriteSeries::setSeparator(char c) {
    this->separator = c;
};

/*!
 * @brief dump method to output
 * @param os output stream
 */
void WriteSeries::dump(std::ostream &os) {

    std::string fileName = "output";
    std::string relativePath = "..\\..\\";
    std::string fileExt = "";


    if (this->separator == ',') {
        fileExt += ".csv";
        separator = ',';
    } else if (this->separator == ' ' || this->separator == '\t') {
        fileExt += ".txt";
        separator = ' ';
    } else if (this->separator == '|') {
        fileExt += ".psv";
        separator = '|';
    } else {
        std::cout << "Invalid separator" << std::endl;
    }


    relativePath = relativePath + fileName + fileExt;
    std::cout << relativePath << std::endl;

    std::ofstream myFile(relativePath);

    myFile << "Steps" << this->separator << "Convergence Value" << this->separator << "Analytical prediction" << "\n";

    if (myFile.is_open()) {
        for (unsigned long i = 1; i <= this->maxIter; i++) {
            myFile << i << this->separator << series.compute(i) << this->separator << series.getAnalyticPrediction()
                   << std::endl;
        }
        myFile.close();
    } else std::cout << "Unable to open file";

};
