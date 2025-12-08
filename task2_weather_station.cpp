#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <sstream>

using namespace std;

// template that is used for the  average calculation
template <class T>
T getAverage(T* arr, int size) 
{
    if (size == 0) {
        throw runtime_error("Can't calculate average with no readings");
    }

    T sum = 0;
    for(int i = 0; i < size; i++){
        sum += arr[i];
    }
    return sum / size;
}

class WeatherStation
{
private:
    string location;
    float* data;    //This means the dynamic mmemory
    int count;
    int capacity;

public:

    WeatherStation(string loc, int cap = 50)
    {
        location = loc;
        capacity = cap;
        count = 0;
        data = new float[capacity];
    }

    // this is a copy constructor that is needed for loading from a file 
    WeatherStation(const WeatherStation &other)
    {
        location = other.location;
        capacity = other.capacity;
        count = other.count;

        data = new float[capacity];
        for(int i = 0; i < count; i++){
            data[i] = other.data[i];
        }
    }

    ~WeatherStation()
    {
        delete[] data;
    }

    void addReading(float v)
    {
        if (count >= capacity){
            throw runtime_error("No space for more readings");
        }
        data[count] = v;
        count++;
    }

    void printReadings() const
    {
        cout << "Readings: ";
        for (int i = 0; i < count; i++){
            cout << data[i] << " ";
        }
        cout << endl;
    }

    void sortReadings()
    {
        sort(data, data + count);
    }

    int countAbove(float t) const
    {
        return count_if(data, data + count, [t](float r){
            return r > t;
        });
    }

    void saveToFile(string filename)
    {
        ofstream file(filename);

        if (!file.is_open()){
            throw runtime_error("Could not open file");
        }

        file << location << "\n";

        for(int i = 0; i < count; i++){
            file << data[i] << " ";
        }
        file << "\n";

        file.close();
    }

    static WeatherStation loadFromFile(string filename)
    {
        ifstream file(filename);

        if (!file.is_open()){
            throw runtime_error("Failed to read file");
        }

        string loc;
        getline(file, loc);

        WeatherStation ws(loc);

        string line;
        getline(file, line);

        stringstream ss(line);
        float temp;

        while (ss >> temp) {
            ws.addReading(temp);
        }

        return ws;
    }

    float calculateAverage()
    {
        return getAverage(data, count);
    }

    string getLocation() const
    {
        return location;
    }
};

int main()
{
    try {
        WeatherStation station("Lahti");

        station.addReading(22.5);
        station.addReading(24.0);
        station.addReading(26.3);
        station.addReading(21.8);
        station.addReading(25.7);

        station.sortReadings();

        cout << "Location: " << station.getLocation() << endl;
        station.printReadings();

        float avg = station.calculateAverage();
        cout << "Average: " << avg << endl;

        int above = station.countAbove(25.0f);
        cout << "Readings above 25°C: " << above << endl;

        string file = "lahti_readings.txt";
        station.saveToFile(file);

        cout << "Saved to file: " << file << endl;

        // Loading back
        WeatherStation w2 = WeatherStation::loadFromFile(file);

    } catch (exception &e) {
        cout << e.what() << endl;
    }

    return 0;
}
