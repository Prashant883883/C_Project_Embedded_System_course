#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

int main() {
    vector<string> days= {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
    vector<double> temperature ={21,19,15.2,10.4,11.4,8,8.6};

    std::cout <<"Weekly Weather Report" <<std::endl;
    std::cout << "\n";


    for (int i=0; i < days.size(); i++) {
        std::cout << days[i] << "=" << temperature[i] << "°C - Weather is";

        if (temperature[i]<10)
            std::cout << " COLD";
        else if (temperature[i]<=20)
            std::cout <<" OK";
        else
            std::cout <<" WARM"; 
        
        std::cout << endl;
    }

    double max_temperature = temperature[0];
    string WarmestDay= days[0];

    for (int i=1; i< days.size(); i++) {
        if (temperature[i] > max_temperature) {
            max_temperature= temperature[i];
            WarmestDay= days[i];

        }
    }
    tuple<string, double> warmest=make_tuple(WarmestDay,max_temperature);

    std::cout << "\n Warmest Day =" << get<0>(warmest)
      <<"("<<get<1>(warmest)<<"°C)" << endl;

    return 0;
}