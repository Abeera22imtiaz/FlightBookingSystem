#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>

using namespace std;

class Flight {
public:
    string flightNumber;
    string departureCity;
    string arrivalCity;
    int availableSeats;

    Flight(string number, string departure, string arrival, int seats)
        : flightNumber(number), departureCity(departure), arrivalCity(arrival), availableSeats(seats) {}
};

class Passenger {
public:
    string name;
    string flightNumber;
    int seatNumber;

    Passenger(string passengerName, string flightNum, int seatNum)
        : name(passengerName), flightNumber(flightNum), seatNumber(seatNum) {}
};

vector<Flight> flights;
list<Passenger> passengers;
queue<Passenger> bookingQueue;
stack<Passenger> cancellationStack;

void initializeFlights() {
    flights.push_back(Flight("F101", "New York", "London", 100));
    flights.push_back(Flight("F102", "Los Angeles", "Paris", 150));
    flights.push_back(Flight("F103", "Chicago", "Tokyo", 200));
    flights.push_back(Flight("F104", "San Francisco", "Sydney", 120));
    flights.push_back(Flight("F105", "Toronto", "Dubai", 180));
    flights.push_back(Flight("F106", "London", "New York", 100));
    flights.push_back(Flight("F107", "Paris", "Los Angeles", 150));
    flights.push_back(Flight("F108", "Tokyo", "Chicago", 200));
    flights.push_back(Flight("F109", "Sydney", "San Francisco", 120));
    flights.push_back(Flight("F110", "Dubai", "Toronto", 180));

    // Additional flights to/from Pakistan
    flights.push_back(Flight("PK101", "Karachi", "Lahore", 150));
    flights.push_back(Flight("PK102", "Lahore", "Islamabad", 100));
    flights.push_back(Flight("PK103", "Islamabad", "Karachi", 200));
    flights.push_back(Flight("PK104", "Karachi", "Dubai", 120));
    flights.push_back(Flight("PK105", "Lahore", "Dubai", 180));
    flights.push_back(Flight("PK106", "Islamabad", "Istanbul", 150));

    // Flights to/from Palestine
    flights.push_back(Flight("PAL101", "Tel Aviv", "Ramallah", 100));
    flights.push_back(Flight("PAL102", "Tel Aviv", "Gaza City", 150));
    flights.push_back(Flight("PAL103", "Amman", "Ramallah", 200));
    flights.push_back(Flight("PAL104", "Cairo", "Gaza City", 120));
    flights.push_back(Flight("PAL105", "Istanbul", "Ramallah", 180));
    flights.push_back(Flight("PAL106", "Dubai", "Gaza City", 150));
}

void displayFlightMenu() {
    cout << "Available Flights:" << endl;
    for (const Flight& flight : flights) {
        cout << flight.flightNumber << " - " << flight.departureCity << " to " << flight.arrivalCity
             << " (Available Seats: " << flight.availableSeats << ")" << endl;
    }
}

void bookReservation() {
    string name, flightNumber;
    cout << "Enter Passenger Name: ";
    cin.ignore();
    getline(cin, name);

    displayFlightMenu();

    cout << "Enter Flight Number: ";
    getline(cin, flightNumber);

    flightNumber.erase(flightNumber.find_last_not_of(" \n\r\t") + 1);
    flightNumber.erase(0, flightNumber.find_first_not_of(" \n\r\t"));

    bool flightFound = false;

    for (Flight& flight : flights) {
        if (flight.flightNumber == flightNumber) {
            flightFound = true;
            if (flight.availableSeats > 0) {
                int seatNumber = 100 - flight.availableSeats + 1;
                flight.availableSeats--;
                passengers.push_back(Passenger(name, flightNumber, seatNumber));
                cout << "Reservation booked successfully! Your seat number is " << seatNumber << "." << endl;
            } else {
                cout << "No available seats on this flight." << endl;
                bookingQueue.push(Passenger(name, flightNumber, -1));
            }
            break;
        }
    }

    if (!flightFound) {
        cout << "Flight not found." << endl;
    }
}

void cancelReservation() {
    if (passengers.empty()) {
        cout << "No reservations to cancel." << endl;
        return;
    }

    string name;
    cout << "Enter Passenger Name for Cancellation: ";
    cin.ignore();
    getline(cin, name);

    for (auto it = passengers.begin(); it != passengers.end(); ++it) {
        if (it->name == name) {
            for (Flight& flight : flights) {
                if (flight.flightNumber == it->flightNumber) {
                    flight.availableSeats++;
                    break;
                }
            }
            cancellationStack.push(*it);
            it = passengers.erase(it);
            cout << "Reservation canceled successfully." << endl;
            return;
        }
    }
    cout << "No matching reservation found for " << name << "." << endl;
}

int main() {
    initializeFlights();

    while (true) {
        cout << "\nFlight Booking System" << endl;
        cout << "1. View Flight Menu" << endl;
        cout << "2. Flight Reservation" << endl;
        cout << "3. Cancel Reservation" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                displayFlightMenu();
                break;
            case 2:
                bookReservation();
                break;
            case 3:
                cancelReservation();
                break;
            case 4:
                exit(0);
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}
