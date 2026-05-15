#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

#define BUS_PER_KM 0.089
#define BIKE_PER_KM 0.103
#define TRAIN_PER_KM 0.041

#define DIET_NONVEG 3.3
#define DIET_AVERAGE 2.5
#define DIET_VEGETARIAN 1.7

#define ELECTRICITY_PER_KWH 0.82
#define LPG_PER_KG 2.983

void printLine(char symbol = '-') {
    for (int i = 0; i < 60; i++)
        cout << symbol;

    cout << endl;
}

void printHeading(string title) {
    cout << endl;

    printLine('=');

    cout << "  " << title << endl;

    printLine('=');
}

class TransportData {
private:
    double busKmPerWeek;
    double bikeKmPerWeek;
    double trainKmPerWeek;

public:
    TransportData() {
        busKmPerWeek = 0;
        bikeKmPerWeek = 0;
        trainKmPerWeek = 0;
    }

    void getInput() {
        printHeading("SECTION 1 : TRANSPORT");

        cout << "\nBus travel per week (km)   : ";
        cin >> busKmPerWeek;

        cout << "Bike travel per week (km)  : ";
        cin >> bikeKmPerWeek;

        cout << "Train travel per week (km) : ";
        cin >> trainKmPerWeek;
    }

    double calculateEmissions() {
        double bus =
            busKmPerWeek * 52 * BUS_PER_KM;

        double bike =
            bikeKmPerWeek * 52 * BIKE_PER_KM;

        double train =
            trainKmPerWeek * 52 * TRAIN_PER_KM;

        return bus + bike + train;
    }
};

class DietData {
private:
    int dietType;

public:
    DietData() {
        dietType = 2;
    }

    void getInput() {
        printHeading("SECTION 2 : DIET");

        cout << "\n1. Non-Vegetarian" << endl;
        cout << "2. Average Mixed Diet" << endl;
        cout << "3. Vegetarian" << endl;

        cout << "\nEnter your choice : ";
        cin >> dietType;
    }

    double calculateEmissions() {
        double dailyEmission = DIET_AVERAGE;

        if (dietType == 1)
            dailyEmission = DIET_NONVEG;

        else if (dietType == 3)
            dailyEmission = DIET_VEGETARIAN;

        return dailyEmission * 365;
    }
};

class HomeEnergyData {
private:
    double electricityUnitsPerMonth;
    double lpgKgPerMonth;

public:
    HomeEnergyData() {
        electricityUnitsPerMonth = 0;
        lpgKgPerMonth = 0;
    }

    void getInput() {
        printHeading("SECTION 3 : HOME ENERGY");

        cout << "\nElectricity usage per month (kWh) : ";
        cin >> electricityUnitsPerMonth;

        cout << "LPG usage per month (kg)          : ";
        cin >> lpgKgPerMonth;
    }

    double calculateEmissions() {
        double electricity =
            electricityUnitsPerMonth * 12 * ELECTRICITY_PER_KWH;

        double lpg =
            lpgKgPerMonth * 12 * LPG_PER_KG;

        return electricity + lpg;
    }
};

void showResults(
    double transport,
    double diet,
    double energy,
    string name
) {
    double total =
        transport + diet + energy;

    double avgIndian = 1900;
    double avgGlobal = 4000;

    printHeading("CARBON FOOTPRINT RESULTS");

    cout << fixed << setprecision(2);

    cout << "\nName : " << name << endl;

    printLine();

    cout << "Transport Emissions : "
         << setw(10)
         << transport
         << " kg CO2/year"
         << endl;

    cout << "Diet Emissions      : "
         << setw(10)
         << diet
         << " kg CO2/year"
         << endl;

    cout << "Home Energy         : "
         << setw(10)
         << energy
         << " kg CO2/year"
         << endl;

    printLine();

    cout << "Total Footprint     : "
         << setw(10)
         << total
         << " kg CO2/year"
         << endl;

    printLine();

    cout << "\nIndian Average : "
         << avgIndian
         << " kg CO2/year"
         << endl;

    cout << "Global Average : "
         << avgGlobal
         << " kg CO2/year"
         << endl;

    if (total < avgIndian) {
        cout << "\nStatus : Excellent! Below Indian average."
             << endl;
    }

    else if (total < avgGlobal) {
        cout << "\nStatus : Moderate footprint."
             << endl;
    }

    else {
        cout << "\nStatus : High carbon footprint."
             << endl;
    }

    printHeading("SUGGESTIONS");

    if (transport > 500) {
        cout << "\nUse public transport more often."
             << endl;

        cout << "Possible reduction : "
             << transport * 0.20
             << " kg CO2/year"
             << endl;
    }

    if (diet > DIET_VEGETARIAN * 365) {
        cout << "\nReduce meat consumption."
             << endl;

        cout << "Potential savings : "
             << (diet - DIET_VEGETARIAN * 365)
             << " kg CO2/year"
             << endl;
    }

    if (energy > 800) {
        cout << "\nUse energy-efficient appliances."
             << endl;

        cout << "Possible reduction : "
             << energy * 0.20
             << " kg CO2/year"
             << endl;
    }

    if (total < avgIndian) {
        cout << "\nGreat job maintaining a low footprint!"
             << endl;
    }
}

void saveReport(
    string name,
    double transport,
    double diet,
    double energy
) {
    double total =
        transport + diet + energy;

    ofstream file("carbon_report.txt");

    if (!file) {
        cout << "\nUnable to save report."
             << endl;

        return;
    }

    file << fixed << setprecision(2);

    file << "========================================\n";
    file << "      CARBON FOOTPRINT REPORT\n";
    file << "========================================\n";

    file << "Name          : " << name << "\n";
    file << "Transport     : " << transport << " kg CO2/year\n";
    file << "Diet          : " << diet << " kg CO2/year\n";
    file << "Home Energy   : " << energy << " kg CO2/year\n";

    file << "----------------------------------------\n";

    file << "Total         : " << total << " kg CO2/year\n";

    file << "========================================\n";

    file.close();

    cout << "\nReport saved successfully."
         << endl;
}

int main() {
    printLine('*');

    cout << "         CARBON FOOTPRINT CALCULATOR"
         << endl;

    printLine('*');

    string userName;

    cout << "\nEnter your name : ";
    cin >> userName;

    TransportData transport;
    DietData diet;
    HomeEnergyData energy;

    transport.getInput();
    diet.getInput();
    energy.getInput();

    double transportEmission =
        transport.calculateEmissions();

    double dietEmission =
        diet.calculateEmissions();

    double energyEmission =
        energy.calculateEmissions();

    showResults(
        transportEmission,
        dietEmission,
        energyEmission,
        userName
    );

    int choice;

    cout << "\nSave report to file? (1 = Yes, 0 = No) : ";
    cin >> choice;

    if (choice == 1) {
        saveReport(
            userName,
            transportEmission,
            dietEmission,
            energyEmission
        );
    }

    printLine('*');

    cout << " Thank you for using the calculator!"
         << endl;

    printLine('*');

    return 0;
}