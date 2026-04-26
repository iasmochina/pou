#include "Utils.h"
#define RED "\033[31m"
#define RESET "\033[0m"
#include <iostream>
using namespace std;

void proceed() {
    cout << "Press ENTER to proceed";
    cin.ignore();
    cin.get();
}
int getSafeIntOption() {
    int x;
    while (!(cin >> x)) {
        cout << RED << "Use only numbers!" << RESET << endl << "Your value: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    return x;
}

int getIntInRange(int min, int max) {
    int x = getSafeIntOption();
    while (x < min || x > max) {
        cout << RED << "Enter a number between " << min << " and " << max << "!" << RESET << endl << "Your value: ";
        x = getSafeIntOption();
    }
    return x;
}

