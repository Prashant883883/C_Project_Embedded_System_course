#include <iostream>
#include <map>
using namespace std;

int main() {
    map<string, double> weather = {
        {"Monday", 5.2},
        {"Tuesday", 12.8},
        {"Wednesday", 18.3},
        {"Thursday", 21.5},
        {"Friday", 9.7},
        {"Saturday", 23.4},
        {"Sunday", 15.6}
    };

    map<string, char> condition = {
        {"Monday", 'R'},
        {"Tuesday", 'S'},
        {"Wednesday", 'S'},
        {"Thursday", 'S'},
        {"Friday", 'R'},
        {"Saturday", 'S'},
        {"Sunday", 'C'}
    };

    double total = 0;

    cout << "Weather Data:\n";
    for (auto &entry : weather) {
        cout << entry.first << ": " << entry.second 
             << "°C, Condition: " << condition[entry.first] << endl;
        total += entry.second;
    }

    double average = total / weather.size();
    cout << "\nAverage temperature: " << average << "°C" << endl;

    return 0;
}
