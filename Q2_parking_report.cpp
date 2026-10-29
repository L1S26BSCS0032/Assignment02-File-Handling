/*
 * Name       : Tayyabah Khawaja
 * Reg No     : L1S26BSCS0032
 * Assignment : 02 - File Handling
 * Question   : Q2 - Parking Report
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    ifstream inFile("parking.txt");

    if (!inFile) {
        cout << "parking.txt not found!" << endl;
        return 1;
    }

    int d, m, y;
    char slash;

    inFile >> d >> slash >> m >> slash >> y;

    inFile.ignore(100, '\n');   
    inFile.ignore(100, '\n');   

    ofstream receipt("receipts.txt");
    if (!receipt) {
        cout << "Could not create receipts.txt!" << endl;
        return 1;
    }

  
    cout << "Parking report for "
        << d << "/" << m << "/" << y << endl;

   
    receipt << "Receipts for "
        << d << "/" << m << "/" << y << endl;

    string plate, longestPlate;
    char type;

    int inHour, inMin;
    int outHour, outMin;

    int vehicles = 0;
    int cars = 0;
    int bikes = 0;
    int totalCollected = 0;

    int longestMinutes = -1;

    while (inFile >> plate >> type >> inHour >> slash >> inMin
        >> outHour >> slash >> outMin)
    {
        int inTotal = inHour * 60 + inMin;
        int outTotal = outHour * 60 + outMin;
        int minutes = outTotal - inTotal;

        if (minutes < 0) {        
            minutes += 24 * 60;
        }

        int hrCharge = (minutes + 59) / 60;

        if (hrCharge == 0) { 
            hrCharge = 1;
        }

        type = toupper(type);   

        int fee;

        if (type == 'C') {
            fee = hrCharge * 100;
            cars++;
        }
        else {
            fee = hrCharge * 40;
            bikes++;
        }

        int actualHours = minutes / 60;
        int actualMinutes = minutes % 60;

        cout << plate << " "
            << (type == 'C' ? "Car" : "Bike")  
            << " " << actualHours
            << " h " << actualMinutes << " min Fee: " << fee << endl;

        receipt << plate << " " << fee << endl;
        vehicles++;
        totalCollected += fee;

        if (minutes > longestMinutes) {
            longestMinutes = minutes;
            longestPlate = plate;
        }
    }

    inFile.close();
    receipt.close();

    if (vehicles == 0) {
        cout << "No vehicles found!" << endl;
        return 0;
    }

    cout << "Vehicles: " << vehicles << endl;
    cout << "Cars: " << cars << " Bikes: " << bikes << endl;
    cout << "Total collected: " << totalCollected << endl;
    cout << "Longest stay: "
        << longestPlate << " (" << longestMinutes / 60 << " h "
        << longestMinutes % 60 << " min)" << endl;

    return 0;
}