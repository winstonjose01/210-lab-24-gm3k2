// COMSC 210 | Lab 23 | Winston Jose
// IDE Used: Visual Studio Code
// Github link : https://github.com/winstonjose01/210-lab-23-gmk3001/commits/main/  


#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
using namespace std;

// Constant values for the size of names and colors arrays, and age range for goats
const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20, MIN = 5, MAX = 20;

// F
int select_goat(list<Goat> trip); // Function to select a goat based on user input
void delete_goat(list<Goat> &trip, int i); // Function to delete a goat from the list
void add_goat(list<Goat> &trip, string [], string []); // Functio to add a goat to the list
void display_trip(list<Goat> trip);     // Function to display the current goats on the trip
int main_menu();                    

int main() {
    srand(time(0));  // Seed the random number generator
    bool again;
    int choice;

    // Read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]); // Reading all names from the file into the array
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]); // Reading all colors from the file into the array
    fin1.close();

    list <Goat> goat_gang;  // A list to store Goat objects 

    // Randomly generate an initial set of goats with random names, ages, and colors
    for (int i = 0; i < (MIN + rand() % (MAX-MIN + 1)); i++){
        goat_gang.push_back(Goat(names[rand() % SZ_NAMES], rand() % (MAX_AGE+1), colors[rand() % SZ_COLORS]));
    }

    // Main loop to handle user input and perform corresponding actions
    while (true){
        choice = main_menu(); // Display the menu and get user choice
        switch (choice){
            case 1: // Add a new goat to the list and display updated list
                    add_goat(goat_gang, names, colors);
                    display_trip (goat_gang);
                break;

            case 2: {  // Check if there are any goats to delete
                    if (goat_gang.size() == 0){
                         cout << "There are no goats on the trip. Pls add a goat" << endl;
                         cout << endl;
                         break;
                    }
                    int selection = select_goat(goat_gang);
                    int i = 1;
                    for (auto goat : goat_gang){
                        if (i == selection){
                            cout << "\n\t---Removing goat " << goat.get_name() << " (" << goat.get_age() << ", " << goat.get_color() << ")" << " from the trip---" << endl;
                            break;
                        }
                        i++;
                    }
                    delete_goat(goat_gang, selection);
                    display_trip (goat_gang);
                }
                break;

            case 3: // Check if there are any goats to delete
                display_trip(goat_gang);
                break;

            case 4: // Exit the program
                cout << endl;
                return 0;

            default: // Handle invalid menu choices
            cout << "Invalid input\n";
                break;
        }
    }
    return 0;
}

// Function to display the main menu and get user's choice
// arguments: None
// returns: Returns the choice selected by the user
int main_menu(){
    int choice = 0;
    cout << "\n*** GOAT MANAGER 3001 ***" << endl;
    cout << "[1] Add a goat" << endl;
    cout << "[2] Delete a goat" << endl;
    cout << "[3] List goats" << endl;
    cout << "[4] Quit" << endl;
    cout << "Choice --> ";
    cin >> choice;
    return choice;
    }

// Function to add a randomly generated goat to the trip
// arguments: list of <Goat> objects, string array of names, string array of colors
// retrusn: No returns
void add_goat(list<Goat> &trip, string n[], string c[]){
    // Add a goat with a random name, age (0 to MAX_AGE), and color
    trip.push_back(Goat(n[rand() % SZ_NAMES], rand() % (MAX_AGE+1), c[rand() % SZ_COLORS]));
}

// Function to display the main menu and get user's choice
// arguments: None
// returns: Returns the choice selected by the user
void display_trip (list<Goat> trip){
    cout << "\tThere are " << trip.size() << " goats on this trip:" << endl;
    int i = 1;
    for (auto goat : trip){
        cout << setw(15) << "[" << i++ << "] " << goat.get_name() << " (" << goat.get_age() << ", " << goat.get_color() << ")" << endl;
    }
}

// Function to delete a goat from the list based on its position
// arguments: list of <Goat> objects, string array of names, string array of colors
// retrusn: No returns
void delete_goat (list<Goat> &trip, int selection){
    int size_trip = trip.size();
     // Remove the first goat
    if (selection == 1)
        trip.pop_front();

    // Remove the last goat
    else if (selection == size_trip)
        trip.pop_back();

    // Remove a goat in the middle of the list
    else{
        int k = 1;
        for (auto it = trip.begin(); it != trip.end(); ++it){
            if (k == selection){
                trip.erase(it);
                break;
            }
            k++;
        }
    }
}

// Function to select a goat by displaying the trip and getting valid user input
// arguments: A list of <Goat> objects
// returns: returns a selection value entered by the user
int select_goat (list <Goat> trip){ 
    int selection;
    display_trip(trip);
    cout << "\tWhich goat is staying behind ? --> ";
    while (true) {
        cin >> selection;
        if (cin.fail() || selection > trip.size() || selection < 1){
            cin.clear();
            cin.ignore();
            cout << "Invalid input: Choose another goat -->";
        }
        else{
            break;
            }
    }
    return selection;
}