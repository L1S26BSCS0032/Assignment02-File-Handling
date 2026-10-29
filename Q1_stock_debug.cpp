/*
 * Name       : Tayyabah Khawaja
 * Reg No     : L1S26BSCS0032
 * Assignment : 02 - File Handling
 * Question   : Q1 - Stock Report (Debugging)
 */

#include <iostream>
#include <fstream>   //missing header file
using namespace std;

int main() {
    ifstream inFile("stock.txt");
    if (!inFile) {   // file is present but printed error message
        cout << "stock.txt not found!" << endl;
        return 1;
    }

    //data is required to be kept so appending it
    ofstream reorder("reorder.txt", ios::app);

    // unnecessary first line skipping 
    inFile.ignore(67, '\n');


    char code[10];
    int qty, count = 0, low = 0;
    double price; //price is double
    double total = 0; //using double to print exact prices


    while (count < 50 && inFile >> code >> qty >> price) {

        count++;
        total = total + qty * price;
        if (qty < 10) {
            reorder << code << " " << qty << endl; //adding endl
            low++;
        }
    }
    inFile.close();
    reorder.close();

    cout << "Items: " << count << endl;
    cout << "Total stock value: " << total << endl;
    cout << "Low stock items: " << low << endl;
    return 0;
}