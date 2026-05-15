/*
 * ============================================================
 *        CARBON FOOTPRINT CALCULATOR
 *        SDG Goal 12 - Responsible Consumption & Production
 *
 *  Author  : Mohith Sripathi
 *  Language: C++
 *  Purpose : Calculate yearly carbon footprint based on
 *            transport, diet, and home energy usage,
 *            and suggest ways to reduce it.
 * ============================================================
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <ctime>

using namespace std;

// ─────────────────────────────────────────────
//  CONSTANTS (emission factors in kg CO2/unit)
// ─────────────────────────────────────────────
const double CAR_PETROL_PER_KM    = 0.21;   // kg CO2 per km
const double CAR_DIESEL_PER_KM    = 0.17;
const double CAR_ELECTRIC_PER_KM  = 0.05;
const double BUS_PER_KM           = 0.089;
const double FLIGHT_SHORT_PER_KM  = 0.255;  // <3 hrs
const double FLIGHT_LONG_PER_KM   = 0.195;  // >3 hrs

const double DIET_MEAT_HEAVY      = 3.3;    // kg CO2 per day
const double DIET_AVERAGE         = 2.5;
const double DIET_VEGETARIAN      = 1.7;
const double DIET_VEGAN           = 1.5;

const double ELECTRICITY_PER_KWH  = 0.82;   // India grid avg (kg CO2/kWh)
const double LPG_PER_KG           = 2.983;  // kg CO2 per kg of LPG

// ─────────────────────────────────────────────
//  HELPER: Print a styled separator line
// ─────────────────────────────────────────────
void printLine(char ch = '-', int len = 55) {
    for (int i = 0; i < len; i++) cout << ch;
    cout << endl;
}

// ─────────────────────────────────────────────
//  HELPER: Print a section heading
// ─────────────────────────────────────────────
void printHeading(string title) {
    cout << endl;
    printLine('=');
    cout << "  " << title << endl;
    printLine('=');
}

// ─────────────────────────────────────────────
//  CLASS: TransportData
//  Stores and calculates transport emissions
// ─────────────────────────────────────────────
class TransportData {
public:
    double carKmPerWeek;
    int    carFuelType;     // 1=Petrol, 2=Diesel, 3=Electric
    double busKmPerWeek;
    double shortFlightsPerYear;
    double longFlightsPerYear;

    TransportData() {
        carKmPerWeek = busKmPerWeek = 0;
        carFuelType = 1;
        shortFlightsPerYear = longFlightsPerYear = 0;
    }

    void getInput() {
        printHeading("SECTION 1: TRANSPORT");

        cout << "\nDo you use a personal car? (1 = Yes, 0 = No): ";
        int useCar;
        cin >> useCar;

        if (useCar == 1) {
            cout << "  Fuel type? (1=Petrol  2=Diesel  3=Electric): ";
            cin >> carFuelType;
            cout << "  How many km do you drive per week? : ";
            cin >> carKmPerWeek;
        }

        cout << "\nHow many km do you travel by bus per week? : ";
        cin >> busKmPerWeek;

        cout << "\nHow many SHORT flights (under 3 hrs) per year? : ";
        cin >> shortFlightsPerYear;
        cout << "How many LONG flights (over 3 hrs) per year?  : ";
        cin >> longFlightsPerYear;
    }

    double calculateEmissions() {
        double carEmission = 0;

        if (carFuelType == 1)
            carEmission = carKmPerWeek * 52 * CAR_PETROL_PER_KM;
        else if (carFuelType == 2)
            carEmission = carKmPerWeek * 52 * CAR_DIESEL_PER_KM;
        else
            carEmission = carKmPerWeek * 52 * CAR_ELECTRIC_PER_KM;

        double busEmission    = busKmPerWeek * 52 * BUS_PER_KM;
        // Avg short flight distance ~800km, long ~5000km
        double flightEmission = (shortFlightsPerYear * 800 * FLIGHT_SHORT_PER_KM)
                              + (longFlightsPerYear  * 5000 * FLIGHT_LONG_PER_KM);

        return carEmission + busEmission + flightEmission;
    }
};

// ─────────────────────────────────────────────
//  CLASS: DietData
//  Stores and calculates diet emissions
// ─────────────────────────────────────────────
class DietData {
public:
    int dietType;   // 1=Heavy meat, 2=Average, 3=Vegetarian, 4=Vegan

    DietData() { dietType = 2; }

    void getInput() {
        printHeading("SECTION 2: DIET");

        cout << "\nWhat best describes your diet?" << endl;
        cout << "  1 - Heavy meat eater (daily meat in every meal)" << endl;
        cout << "  2 - Average (meat a few times a week)" << endl;
        cout << "  3 - Vegetarian" << endl;
        cout << "  4 - Vegan" << endl;
        cout << "Your choice: ";
        cin >> dietType;
    }

    double calculateEmissions() {
        double dailyEmission = DIET_AVERAGE;

        if      (dietType == 1) dailyEmission = DIET_MEAT_HEAVY;
        else if (dietType == 2) dailyEmission = DIET_AVERAGE;
        else if (dietType == 3) dailyEmission = DIET_VEGETARIAN;
        else if (dietType == 4) dailyEmission = DIET_VEGAN;

        return dailyEmission * 365;
    }
};

// ─────────────────────────────────────────────
//  CLASS: HomeEnergyData
//  Stores and calculates home energy emissions
// ─────────────────────────────────────────────
class HomeEnergyData {
public:
    double electricityUnitsPerMonth;  // kWh
    double lpgKgPerMonth;

    HomeEnergyData() {
        electricityUnitsPerMonth = 0;
        lpgKgPerMonth = 0;
    }

    void getInput() {
        printHeading("SECTION 3: HOME ENERGY");

        cout << "\nMonthly electricity consumption (units/kWh)? : ";
        cin >> electricityUnitsPerMonth;
        cout << "Monthly LPG gas usage (kg)? (0 if not used) : ";
        cin >> lpgKgPerMonth;
    }

    double calculateEmissions() {
        double electricityEmission = electricityUnitsPerMonth * 12 * ELECTRICITY_PER_KWH;
        double lpgEmission         = lpgKgPerMonth * 12 * LPG_PER_KG;
        return electricityEmission + lpgEmission;
    }
};

// ─────────────────────────────────────────────
//  FUNCTION: Show breakdown + suggestions
// ─────────────────────────────────────────────
void showResults(double transport, double diet, double energy, string name) {
    double total = transport + diet + energy;
    double avgIndian  = 1900;  // kg CO2 per year (approx)
    double avgGlobal  = 4000;

    printHeading("YOUR CARBON FOOTPRINT RESULTS");

    cout << fixed << setprecision(2);
    cout << "\n  Name          : " << name << endl;
    printLine();
    cout << "  Transport     : " << setw(10) << transport << " kg CO2/year" << endl;
    cout << "  Diet          : " << setw(10) << diet      << " kg CO2/year" << endl;
    cout << "  Home Energy   : " << setw(10) << energy    << " kg CO2/year" << endl;
    printLine();
    cout << "  TOTAL         : " << setw(10) << total     << " kg CO2/year" << endl;
    printLine();

    cout << "\n  For reference:" << endl;
    cout << "    Avg Indian  : " << avgIndian << " kg CO2/year" << endl;
    cout << "    Avg Global  : " << avgGlobal << " kg CO2/year" << endl;

    // Compare with averages
    cout << endl;
    if (total < avgIndian)
        cout << "  STATUS : GREAT! Your footprint is BELOW the Indian average." << endl;
    else if (total < avgGlobal)
        cout << "  STATUS : MODERATE. You are below global avg but above Indian avg." << endl;
    else
        cout << "  STATUS : HIGH. Your footprint is above the global average." << endl;

    // ── Suggestions ──
    printHeading("PERSONALIZED SUGGESTIONS TO REDUCE FOOTPRINT");

    cout << endl;

    // Transport suggestion
    if (transport > 1000) {
        cout << "  [TRANSPORT]" << endl;
        cout << "  >> Your transport emissions are HIGH (" << transport << " kg/yr)." << endl;
        cout << "     Try carpooling, switching to bus, or using an electric vehicle." << endl;
        cout << "     Even cutting car km by 20% saves ~"
             << (transport * 0.20) << " kg CO2/year." << endl;
        cout << endl;
    }

    // Diet suggestion
    if (diet > DIET_VEGETARIAN * 365) {
        cout << "  [DIET]" << endl;
        cout << "  >> Switching to a vegetarian diet can save up to "
             << (diet - DIET_VEGETARIAN * 365)
             << " kg CO2/year." << endl;
        cout << "     Even 2 meat-free days per week makes a big difference!" << endl;
        cout << endl;
    }

    // Energy suggestion
    if (energy > 800) {
        cout << "  [HOME ENERGY]" << endl;
        cout << "  >> Your home energy emissions are HIGH (" << energy << " kg/yr)." << endl;
        cout << "     Use LED bulbs, unplug devices on standby," << endl;
        cout << "     and consider solar panels to reduce grid dependency." << endl;
        cout << "     A 20% reduction saves ~" << (energy * 0.20) << " kg CO2/year." << endl;
        cout << endl;
    }

    if (total < avgIndian) {
        cout << "  You are doing great! Keep maintaining your low-carbon lifestyle." << endl;
    }
}

// ─────────────────────────────────────────────
//  FUNCTION: Save report to a .txt file
// ─────────────────────────────────────────────
void saveReport(string name, double transport, double diet, double energy) {
    double total = transport + diet + energy;

    ofstream file("carbon_report.txt");
    if (!file) {
        cout << "\n  [!] Could not save report to file." << endl;
        return;
    }

    file << "============================================\n";
    file << "   CARBON FOOTPRINT REPORT\n";
    file << "============================================\n";
    file << "Name         : " << name << "\n";
    file << "Transport    : " << fixed << setprecision(2) << transport << " kg CO2/year\n";
    file << "Diet         : " << diet      << " kg CO2/year\n";
    file << "Home Energy  : " << energy    << " kg CO2/year\n";
    file << "--------------------------------------------\n";
    file << "TOTAL        : " << total     << " kg CO2/year\n";
    file << "============================================\n";
    file << "SDG Goal 12 - Responsible Consumption & Production\n";

    file.close();
    cout << "\n  [✓] Report saved to 'carbon_report.txt'" << endl;
}

// ─────────────────────────────────────────────
//  MAIN FUNCTION
// ─────────────────────────────────────────────
int main() {
    printLine('*');
    cout << "   CARBON FOOTPRINT CALCULATOR" << endl;
    cout << "   SDG Goal 12 - Responsible Consumption" << endl;
    printLine('*');

    string userName;
    cout << "\nEnter your name: ";
    cin >> userName;

    // Create objects for each category
    TransportData  transport;
    DietData       diet;
    HomeEnergyData energy;

    // Collect input
    transport.getInput();
    diet.getInput();
    energy.getInput();

    // Calculate emissions
    double transportEmissions = transport.calculateEmissions();
    double dietEmissions      = diet.calculateEmissions();
    double energyEmissions    = energy.calculateEmissions();

    // Show results and suggestions
    showResults(transportEmissions, dietEmissions, energyEmissions, userName);

    // Save report option
    cout << endl;
    printLine();
    cout << "\nDo you want to save the report to a file? (1=Yes / 0=No): ";
    int saveChoice;
    cin >> saveChoice;

    if (saveChoice == 1) {
        saveReport(userName, transportEmissions, dietEmissions, energyEmissions);
    }

    printLine('*');
    cout << "  Thank you for calculating your carbon footprint!" << endl;
    cout << "  Small steps today = A better planet tomorrow." << endl;
    printLine('*');
    cout << endl;

    return 0;
}
