#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

// Helper functions for table formatting
void printTableRow(const std::vector<std::string>& columns, const std::vector<int>& widths, char separator = '|');
void printTableSeparator(const std::vector<int>& widths, char separator = '|', char fill = '-');

#endif // UTILS_H 