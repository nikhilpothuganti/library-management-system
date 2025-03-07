#include "../include/Utils.h"

using namespace std;

void printTableRow(const vector<string>& columns, const vector<int>& widths, char separator) {
    cout << separator;
    for(size_t i = 0; i < columns.size(); ++i) {
        cout << " " << left << setw(widths[i]) << columns[i] << " " << separator;
    }
    cout << "\n";
}

void printTableSeparator(const vector<int>& widths, char separator, char fill) {
    cout << separator;
    for(int width : widths) {
        cout << string(width + 2, fill) << separator;
    }
    cout << "\n";
} 