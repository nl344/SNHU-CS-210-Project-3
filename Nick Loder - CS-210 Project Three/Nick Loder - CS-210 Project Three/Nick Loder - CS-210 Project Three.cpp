#include <iostream>
#include <map>
#include <fstream>
#include <string>

using namespace std;

class GroceryFrequency {
//declares public functions
public:
    //reads the input file and generates the frequency data
    void processInputFile(string filename) {
        ifstream input(filename);
        if (input.fail()) { //error trapping in case input file doesn't open
            cout << "Error: could not open file" << filename << endl;
            return;
        }
        string item;
        while (input >> item) {
            freqData[item]++;
        }
        input.close();
    }

    int getItemFrequency(string item) {
        return freqData[item];
    }

    //prints a list of all items and their frequencies
    void printFrequencyList() {
        for (auto it = freqData.begin(); it != freqData.end(); ++it) {
            cout << it->first << ": " << it->second << endl;
        }
    }

    //prints a histogram of all items and their frequencies
    void printFrequencyHistogram() {
        for (auto it = freqData.begin(); it != freqData.end(); ++it) {
            cout << it->first << " ";
            for (int i = 0; i < it->second; i++) {
                cout << "*";
            }
            cout << endl;
        }
    }

    //writes the frequency data to a backup file
    void backupFrequencyData(string filename) {
        ofstream output(filename);
        if (output.fail()) {
            cout << "Error: Could not open file " << filename << endl;
            return;
        }
        for (auto it = freqData.begin(); it != freqData.end(); ++it) {
            output << it->first << ": " << it->second << endl;
        }
        output.close();
    }

 //declares private function
private:
    map<string, int> freqData;
};

int main() {
    GroceryFrequency grocery;

    //processes the input file
    grocery.processInputFile("CS210_Project_Three_Input_File.txt");
    
    //user interface loop
    bool running = true;
    while (running) {
        //prints menu options
        cout << "Please select an option:" << endl;
        cout << "1. Look up an item's frequency" << endl;
        cout << "2. Print list of all items and frequencies" << endl;
        cout << "3. Print histogram of item frequencies" << endl;
        cout << "4. Exit the program" << endl;

        //collects user input
        int choice;
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        //switch to perform action based on user input
        switch (choice) {
            case 1: {
                string item;
                cout << "Enter the item to look up: ";
                cin >> item;
                int freq = grocery.getItemFrequency(item);
                cout << endl << "Frequency of " << item << ": " << freq << endl << endl;
                break;
            }
            case 2: {
                cout << endl;
                grocery.printFrequencyList();
                cout << endl;
                break;
            }
            case 3: {
                cout << endl;
                grocery.printFrequencyHistogram();
                cout << endl;
                break;
            }
            case 4: {
                grocery.backupFrequencyData("frequency.dat");
                running = false;
                break;
            }
            //error trapping in case user input is invalid
            default: {
                cout << endl;
                cout << "Invalid choice, please enter a number between 1 and 4." << endl;
                cin.clear();
                cin.ignore();
                cout << endl;
                break;
            }
        }
    }
    return 0;
}