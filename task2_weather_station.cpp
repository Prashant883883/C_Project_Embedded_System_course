#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <sstream>
using namespace std;

// ==========================
// TEMPLATE FOR AVERAGE
// ==========================
template<typename T>
T computeAverage(const T* arr, int size) {
    if (size == 0) {
        throw runtime_error("Error: No readings available. Cannot calculate average.");
    }
    
    T sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum / size;
}

// ==========================
// WEATHER STATION CLASS
// ==========================
class WeatherStation {
private:
    string location;
    float* readings;  // dynamic memory
    int count;        // how many readings added
    int capacity;     // max number of readings

public:

    // Constructor
    WeatherStation(string loc, int cap = 50)
        : location(loc), count(0), capacity(cap)
    {
        readings = new float[capacity];
    }

    // Copy constructor (needed for reconstruction)
    WeatherStation(const WeatherStation& other) {
        location = other.location;
        count = other.count;
        capacity = other.capacity;

        readings = new float[capacity];
        for (int i = 0; i < count; i++) {
            readings[i] = other.readings[i];
        }
    }

    // Destructor
    ~WeatherStation() {
        delete[] readings;
    }

    // Add a reading
    void addReading(float value) {
        if (count >= capacity) {
            throw runtime_error("Error: Capacity reached.");
        }
        readings[count++] = value;
    }

    // Print readings
    void printReadings() const {
        cout << "Readings: ";
        for (int i = 0; i < count; i++) {
            cout << readings[i] << " ";
        }
        cout << endl;
    }

    // Sort the readings
    void sortReadings() {
        sort(readings, readings + count);
    }

    // Count readings above threshold
    int countAbove(float threshold) const {
        return count_if(readings, readings + count,
                        [threshold](float r) { return r > threshold; });
    }

    // Save to file
    void saveToFile(const string& filename) {
        ofstream file(filename);

        if (!file.is_open()) {
            throw runtime_error("Error: Could not open file for writing.");
        }

        file << location << endl;

        for (int i = 0; i < count; i++) {
            file << readings[i] << " ";
        }
        file << endl;

        file.close();
    }

    // Recreate WeatherStation from file
    static WeatherStation loadFromFile(const string& filename) {
        ifstream file(filename);

        if (!file.is_open()) {
            throw runtime_error("Error: Cannot open file for reading.");
        }

        string loc;
        getline(file, loc);

        WeatherStation ws(loc);

        string line;
        if (getline(file, line)) {
            stringstream ss(line);
            float value;
            while (ss >> value) {
                ws.addReading(value);
            }
        }

        file.close();
        return ws;
    }

    string getLocation() const { return location; }

    float getAverage() {
        return computeAverage(readings, count);
    }
};

// ==========================
// MAIN FUNCTION
// ==========================
int main() {
    try {
        WeatherStation ws("Lahti");

        // Add manually the readings required in assignment
        ws.addReading(22.5);
        ws.addReading(24.0);
        ws.addReading(26.3);
        ws.addReading(21.8);
        ws.addReading(25.7);

        // Sorting
        ws.sortReadings();

        cout << "Location: " << ws.getLocation() << endl;
        ws.printReadings();

        float avg = ws.getAverage();
        cout << "Average: " << avg << endl;

        int above25 = ws.countAbove(25.0);
        cout << "Readings above 25°C: " << above25 << endl;

        string filename = "lahti_readings.txt";
        ws.saveToFile(filename);

        cout << "Saved to file: " << filename << endl;

        // (Optional) load back
        WeatherStation loaded = WeatherStation::loadFromFile(filename);

    } catch (exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}
