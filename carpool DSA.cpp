
#include <iostream>
#include <string>
#include <iomanip>
#include <climits>


using namespace std;
// a generic sort of queue which we can use however we want.
template <typename T>
class Queues {
public:
    T* arr;
    int back;
    int front;
    int n;

    Queues(int x) : n(x), arr(new T[x]), back(-1), front(-1) {}

    void enque(T x) {
        back++;
        arr[back] = x;

        if (back == n - 1) {
            cout << "No more space left." << endl;
        }

        if (front == -1) {
            front++;
        }
    }

    void deque() {
        if (front == -1 || front > back) {
            cout << "Empty list" << endl;
        }
        front++;
    }

    T Front() const {
        if (front == -1 || front > back) {
            cout << "Empty list" << endl;
            return T();
        }
        return arr[front];
    }

    bool IsEmpty() const {
        if (front == -1 || front > back) {
            return true;
        } else {
            return false;
        }
    }

    void displayQueue() const {
        if (front == -1 || front > back) {
            cout << "Empty list" << endl;
            return;
        }

        for (int i = front; i <= back; ++i) {
            cout << "Element " << i - front + 1 << ": " << arr[i].Name << ", " << arr[i].Contact << endl;
        }
    }
};

//takes basic user info.
class User {
public:
    string Name;
    string Contact;

    User() {
        cout << "Please enter your name: ";
        cin >> Name;
        cout << "Please enter your contact number: ";
        cin >> Contact;
    }
};

//takes driver info regarding route and other info.
class details {
public:
    string pickup;
    string dropOff;
    string pickTime;
    string Name;
    string Contact;
    string fare;
    string Car;
    details() {
        cout << "Please enter your name: ";
        cin >> Name;
        cout << "Please enter your contact number: ";
        cin >> Contact;
        cout << "Welcome, please enter your pickup location: ";
        cin >> pickup;
        cout << "Please enter your drop-off location: ";
        cin >> dropOff;
        cout << "Please enter your pick-up time: ";
        cin >> pickTime;
        cout << "Please enter your fare ";
        cin >> fare;
        cout << "Please enter your car ";
        cin >> Car;
    }
};


//Node for passengers in the car including driver
class passengerNodes {
    public:
        User user;
        details d;

        passengerNodes* next;

        passengerNodes(User& u) : user(u), next(nullptr) {}
    };


//a linked list managing passenger and drivers in the car.    
class RideSeats {
public:


    passengerNodes* driver;      // Head
    passengerNodes* passenger;   // Tail

    int limitPassenger;
    int limitDriver;
    int driverCount;
    int passengerCount;

    RideSeats() : driver(nullptr), passenger(nullptr), limitPassenger(4), limitDriver(1), driverCount(0), passengerCount(0) {}

    void InsertDriver(User& u) {
    if (driverCount < limitDriver) {
        passengerNodes* newDriver = new passengerNodes(u);
        if (driver == nullptr) {
            driver = newDriver;
            passenger = newDriver;
        } else {
            cout << "Driver already exists." << endl;
        }
        driverCount++;
    }
}

void InsertPassenger(User& u) {
    if (passengerCount < limitPassenger) {
        passengerNodes* newPassenger = new passengerNodes(u);
        if (passenger == nullptr) {
            driver = newPassenger;  // Change this line to passenger = newPassenger;
            passenger = newPassenger;
        } else {
            passenger->next = newPassenger;
            passenger = newPassenger;
        }
        passengerCount++;
    } else {
        cout << "No more seats available." << endl;
    }
}
void UpdateNode(int pos,User& updatedData){
        passengerNodes* newNode = new passengerNodes(updatedData);
        passengerNodes* temp = driver;
        int current_pos = 0;
        while(current_pos!= pos){
            temp = temp->next;
            current_pos++;
        }

        temp->user = updatedData;
    }
void deletePassenger(int index) {



    if (index == 0) {
        // Deleting the driver
        if (driver != nullptr) {
            passengerNodes* temp = driver;
            driver = driver->next;
            delete temp;
            cout << "Driver removed successfully." << endl;
        } else {
            cout << "No driver to delete." << endl;
        }
    } else {
        // Deleting a passenger
        int current_pos = 0;
        passengerNodes* temp = driver;

        // Traverse to the node just before the one to be deleted
        while (temp != nullptr && current_pos < index - 1) {
            temp = temp->next;
            current_pos++;
        }

        if (temp != nullptr && temp->next != nullptr) {
            // temp is now pointing to the node before the one to be deleted
            passengerNodes* nodeToDelete = temp->next;
            temp->next = nodeToDelete->next;
            delete nodeToDelete;
            cout << "Passenger at seat " << index << " removed successfully." << endl;
        } else {
            cout << "Invalid seat number or no passenger to delete." << endl;
        }
    }
}

// void displayPassengers(int selectedRideNumber) {
//     cout << "Car details" << endl;

//     // Find the selected ride
//     CarNode* temp = car;
//     int currentRideNumber = 1;

//     while (temp != nullptr && currentRideNumber < selectedRideNumber) {
//         temp = temp->next;
//         currentRideNumber++;
//     }

//     if (temp != nullptr && currentRideNumber == selectedRideNumber) {
//         // The selected ride is found
//         cout << "Ride Details:" << endl;
//         cout << "Name: " << temp->ride.Name << ", Contact: " << temp->ride.Contact << ", Car: " << temp->ride.Car
//              << ", Fare: " << temp->ride.fare << ", Pickup: " << temp->ride.pickup << ", Drop-off: " << temp->ride.dropOff
//              << ", Time: " << temp->ride.pickTime << endl;

//         // Display driver and passengers information using RideSeats instance
//         cout << "Driver: ";
//         if (temp->rideSeats.driver != nullptr) {
//             cout << temp->rideSeats.driver->user.Name << " (" << temp->rideSeats.driver->user.Contact << ")" << endl;
//         } else {
//             cout << "No driver assigned." << endl;
//         }

//         // Display other passengers
//         PassengerNode* passengerTemp = temp->rideSeats.passenger;
//         int passengerNumber = 1;

//         while (passengerTemp != nullptr) {
//             cout << "Passenger " << passengerNumber << ": " << passengerTemp->user.Name << " (" << passengerTemp->user.Contact << ")" << endl;
//             passengerTemp = passengerTemp->next;
//             passengerNumber++;
//         }

//         // If there are no passengers, inform the user
//         if (passengerNumber == 1) {
//             cout << "No passengers in the ride." << endl;
//         }
//     } else {
//         cout << "Invalid ride number. Please enter a valid ride number." << endl;
//         // You may want to add error handling or prompt the user again for a valid choice
//     }
// }


};


// class CarBooking {
// public:
//     RideSeats rideSeats;  // Assuming you have an instance of RideSeats in CarBooking

//     void Book(User& u) {
//         rideSeats.InsertPassenger(u);  // Assuming InsertPassenger is defined in RideSeats
//         cout << "Booking successful." << endl;
//     }

//     void Unbook() {
//         rideSeats.deletePassenger();  // Assuming you have a function to delete a passenger in RideSeats
//         cout << "Unbook successful." << endl;
//     }
// };

//variable defind for the mapping of locations in karachi.
const int points = 32;  
int vertArr[points + 1][points + 1];

//defining an array which includes all the major locations of karachi.
const string locationNames[points] = {
        "FAST", "HALT", "DRIGH", "HABIB", "CONTINENTAL", "JOHAR", "MODEL", "CP5", "SAFOORA",
        "MOSAMIYAT", "MILLENIUM", "SOLDIER", "SHAHRAH_FAISAL", "GULSHAN", "LUCKYONE", "WATERPUMP",
        "NAZIMABAD", "SAKHI", "NAGAN", "ANCHOLI", "UP_MOR", "POWERHOUSE", "KASHMIR", "GARDEN",
        "NUMAISH", "SHAHEED_E_MILLAT", "QUAIDEN", "PECHS", "DHORAJI", "BALOCH_PULL", "DHA", "CLIFTON"
    };

//class location which helps us in finding the optimal route.
class location{
    public:
    const int FAST = 1;
    const int HALT = 2;
    const int DRIGH = 3;
    const int HABIB = 4;
    const int CONTINENTAL = 5;
    const int JOHAR = 6;
    const int MODEL = 7;
    const int CP5 = 8;
    const int SAFOORA = 9;
    const int MOSAMIYAT = 10;
    const int MILLENIUM = 11;
    const int SOLDIER = 12;
    const int SHAHRAH_FAISAL = 13;
    const int GULSHAN = 14;
    const int LUCKYONE = 15;
    const int WATERPUMP = 16;
    const int NAZIMABAD = 17;
    const int SAKHI = 18;
    const int NAGAN = 19;
    const int ANCHOLI = 20;
    const int UP_MOR = 21;
    const int POWERHOUSE = 22;
    const int KASHMIR = 23;
    const int GARDEN = 24;
    const int NUMAISH = 25;
    const int SHAHEED_E_MILLAT = 26;
    const int QUAIDEN = 27;
    const int PECHS = 28;
    const int DHORAJI = 29;
    const int BALOCH_PULL = 30;
    const int DHA = 31;
    const int CLIFTON = 32;

    // Adding edges based on connections between major points



    void displayMatrix(int v) {
    // Display column indices at the top
    cout << setw(5) << " ";
    for (int j = 1; j <= v; j++) {
        cout << setw(5) << j;
    }
    cout << endl;

    for (int i = 1; i <= v; i++) {
        // Display row index on the left
        cout << setw(5) << i;

        for (int j = 1; j <= v; j++) {
            cout << setw(5) << vertArr[i][j];
        }
        cout << endl;
    }
}
int getLocationIndex(const string& locName) {


    for (int i = 0; i < points; ++i) {
        if (locationNames[i] == locName) {
            return i + 1; // Adding 1 to convert from 0-based index to 1-based index
        }
    }

    // If the location name is not found
    cout << "Location not found: " << locName << endl;
    return -1; // You may want to handle this case appropriately in your code
}


// void BFS(int start, int end, int v) {
//     Queues<int> q(points);
//     int visited[points + 1] = {0};
//     int parent[points + 1];
//     int distance[points + 1];



//     cout <<  locationNames[start - 1] << " to " << locationNames[end - 1] << ": ";

//     visited[start] = 1;
//     parent[start] = -1;
//     distance[start] = 0;
//     q.enque(start);

//     while (!q.IsEmpty()) {
//         int u = q.Front();
//         q.deque();

//         for (int i = 1; i <= v; i++) {
//             if (vertArr[u][i] != 0 && visited[i] == 0) {
//                 visited[i] = 1;
//                 parent[i] = u;
//                 distance[i] = distance[u] + vertArr[u][i];
//                 q.enque(i);
//             }
//         }
//     }

//     // Reconstruct the path from end to start
//     int path[points];
//     int pathLength = 0;
//     for (int at = end; at != -1; at = parent[at]) {
//         path[pathLength++] = at;
//     }

//     // Output the path in reverse order
//     cout << "Route: ";
//     for (int i = pathLength - 1; i >= 0; --i) {
//         cout << locationNames[path[i] - 1] << " (" << distance[path[i]] << " km)";
//         if (i > 0) {
//             cout << " -> ";
//         }
//     }

//     cout << endl;
// }

void DijkstraAlgo(int start, int end, int v) {
    // Create a priority queue for Dijkstra's algorithm
    Queues<int> q(points);

    // Arrays to store distance, visited status, and parent information
    int distance[points + 1];
    bool visited[points + 1];
    int parent[points + 1];

    // Initialization of arrays
    for (int i = 1; i <= v; i++) {
        distance[i] = INT_MAX;    // Initialize distances to infinity
        visited[i] = false;       // Mark all vertices as not visited
        parent[i] = -1;           // Set initial parent of all vertices to -1
    }

    // Distance from the start vertex to itself is 0
    distance[start] = 0;

    // Main loop for Dijkstra's algorithm
    for (int count = 0; count < v - 1; count++) {
        // Find the vertex with the minimum distance value
        int u = miniDist(distance, visited, v);
        visited[u] = true;  // Mark the selected vertex as visited

        // Update the distance and parent information of the adjacent vertices
        for (int i = 1; i <= v; i++) {
            if (!visited[i] && vertArr[u][i] && distance[u] != INT_MAX && distance[u] + vertArr[u][i] < distance[i]) {
                distance[i] = distance[u] + vertArr[u][i];
                parent[i] = u;
            }
        }
    }

    // Output the shortest path information
    cout << "Dijkstra's Shortest Path from " << locationNames[start - 1] << " to " << locationNames[end - 1] << ": ";

    // Reconstruct and output the shortest path
    int path[points];
    int pathLength = 0;
    //BACKTRACKING LOOP
    for (int LENGTH = end; LENGTH != -1; LENGTH = parent[LENGTH]) {
        path[pathLength++] = LENGTH;
    }

    cout << "Route: ";
    for (int i = pathLength - 1; i >= 0; --i) {
        cout << locationNames[path[i] - 1] << " (" << distance[path[i]] << " km)";
        if (i > 0) {
            cout << " -> ";
        }
    }

    cout << endl;
}

int miniDist(int distance[], bool visited[], int v) {
    int minimum = INT_MAX, ind;

    for (int k = 1; k <= v; k++) {
        if (visited[k] == false && distance[k] <= minimum) {
            minimum = distance[k];
            ind = k;
        }
    }
    return ind;
}


void add_edge(int u, int v,int distance) {
    vertArr[u][v] = distance;
    vertArr[v][u] = distance;
}



};

//this class is used to add edges in the graph of karachi.
class edge{
    public:
    location l;
    void addEdges(){



      l.add_edge(l.FAST, l.HALT, 10);
      l.add_edge(l.HALT, l.DRIGH, 6);
      l.add_edge(l.DRIGH, l.HABIB, 5);
      l.add_edge(l.DRIGH, l.MODEL, 9);
      l.add_edge(l.MODEL, l.CP5, 8);
      l.add_edge(l.CP5, l.SAFOORA, 5);
      l.add_edge(l.HABIB, l.CONTINENTAL, 3);
      l.add_edge(l.CONTINENTAL, l.JOHAR, 2);
      l.add_edge(l.DRIGH, l.MILLENIUM, 3);
      l.add_edge(l.DRIGH, l.SOLDIER, 12);
      l.add_edge(l.DRIGH, l.SHAHRAH_FAISAL, 1);
      l.add_edge(l.MILLENIUM, l.GULSHAN, 5);
      l.add_edge(l.GULSHAN, l.LUCKYONE, 5);
      // l.add_edge(l.GULSHAN, l.CP5, 2);

      l.add_edge(l.LUCKYONE, l.WATERPUMP, 4);
      l.add_edge(l.WATERPUMP, l.NAZIMABAD, 9);
      l.add_edge(l.NAZIMABAD, l.SAKHI, 6);
      l.add_edge(l.LUCKYONE, l.NAGAN, 6);
      // l.add_edge(l.NAGAN, l.MODEL, 1); //short route check

      l.add_edge(l.NAGAN, l.ANCHOLI, 5);
      l.add_edge(l.ANCHOLI, l.UP_MOR, 4);
      l.add_edge(l.NAGAN, l.POWERHOUSE, 2);
      l.add_edge(l.SOLDIER, l.KASHMIR, 9);
      l.add_edge(l.SHAHRAH_FAISAL, l.SHAHEED_E_MILLAT, 6);
      l.add_edge(l.SHAHRAH_FAISAL, l.BALOCH_PULL, 3);
      l.add_edge(l.SHAHEED_E_MILLAT, l.PECHS, 3);
      l.add_edge(l.BALOCH_PULL, l.DHA, 7);


      // l.add_edge(l.BALOCH_PULL, l.JOHAR, 5); //test case 2
      // l.add_edge(l.SHAHRAH_FAISAL, l.BALOCH_PULL, 20);

      l.add_edge(l.DHA, l.CLIFTON, 6);
      //l.add_edge(l.FAST, l.SAFOORA, 6);




}
};

//Node for creating a linked list of car running around the city.
class CarNode  {
public:
   // details ride;
    details ride;  
    RideSeats rideSeats;  // Add RideSeats instance
  //  CarNode* carHead;
    CarNode* next;

    CarNode(details& r) : ride(r), next(nullptr) {}
};

//linked list which helps us in inserting and eleting a car from the linked list.
class Rides {
public:
    CarNode* car;
    int totalRides;
    RideSeats s;
    location l;
    edge e;

    Rides()  : car(nullptr) {
            e.addEdges();
    }


    void InsertCar(details& r) { //inserting car on the basis of picktime.
        CarNode* newCar = new CarNode(r);
        if (car == nullptr || r.pickTime < car->ride.pickTime) {
            newCar->next = car;
            car = newCar;
        } else {
            CarNode* temp = car;
            while (temp->next != nullptr && temp->next->ride.pickTime < r.pickTime) {
                temp = temp->next;
            }
            newCar->next = temp->next;
            temp->next = newCar;
        }
            totalRides++;

    }


    void DeleteCar() {
        if (car != nullptr) {
            CarNode* temp = car;
            car = car->next;
            delete temp;
        } else {
            cout << "No car to delete." << endl;
        }
            totalRides--;

    }

    void DisplayRides() {
    int rideIndex = 0; // Index to display and reference rides

    CarNode* temp = car;
    while (temp != nullptr) {
        cout << "Ride " << rideIndex + 1 << ":" << endl;
        cout << "Name: " << temp->ride.Name << ", Number: " << temp->ride.Contact << ", Car: " << temp->ride.Car << ", Fare: " << temp->ride.fare << endl;
        cout << "Pickup: " << temp->ride.pickup << ", Destination: " << temp->ride.dropOff << ", Time: " << temp->ride.pickTime << endl;

            // Get start and end locations
        int start = l.getLocationIndex(temp->ride.pickup);
        int end = l.getLocationIndex(temp->ride.dropOff);

        // Call BFS for this ride
        l.DijkstraAlgo(start, end, points);

        temp = temp->next;
        rideIndex++;

    }
    cout << endl;
}

void DisplayPassengers(int selectedRideIndex){
int rideIndex = 1; // Index to display and reference rides

    CarNode* temp = car;
    while (temp != nullptr && rideIndex < selectedRideIndex) {
        temp = temp->next;
        rideIndex++;
    }

    if (temp != nullptr && rideIndex == selectedRideIndex) {
        // The selected ride is found

        cout << "Driver: ";
        if (s.driver != nullptr) {
            cout << s.driver->d.Name << " (" << s.driver->d.Contact << ")" << endl;
        } else {
            cout << "No driver assigned." << endl;
        }

        // Display information about passengers
        passengerNodes* passengerTemp = temp->rideSeats.passenger;
        int passengerNumber = 1;

        while (passengerTemp != nullptr) {
            cout << "Passenger " << passengerNumber << ": " << passengerTemp->user.Name << " (" << passengerTemp->user.Contact << ")" << endl;
            passengerTemp = passengerTemp->next;
            passengerNumber++;
        }

        // If there are no passengers, inform the user
        if (passengerNumber == 1) {
            cout << "No passengers in the ride." << endl;
        }
    } else {
        cout << "Invalid ride number. Please enter a valid ride number." << endl;
        // You may want to add error handling or prompt the user again for a valid choice
    }
}


// Function to get the total number of rides
    int getTotalRides() const {
        return totalRides;
    }


};

int main() {
    Rides rideManager;

    while (true) {
        cout << "Welcome to the Ride Management System!" << endl;
        cout << "1. Are you a Driver?" << endl;
        cout << "2. Are you a User?" << endl;
        cout << "3. Exit" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                details driverDetails;
                rideManager.InsertCar(driverDetails);
                RideSeats seat;

                // Insert driver into the passengerNodes linked list as a driver
                cout << "Please verify your details again."<<endl;
                User driverUser;
                seat.InsertDriver(driverUser);
                cout << "Driver details added successfully!" << endl;
                break;
            }

            case 2: {
                // Display all current rides
                rideManager.DisplayRides();

                // Ask user if they want to book, unbook, update, or delete
                cout << "1. Book a ride" << endl;
                cout << "2. Unbook a ride" << endl;
                cout << "3. Update booking" << endl;
                cout << "4. Display the passengers of a car." << endl;
                cout << "5. Exit"<< endl;

                int userChoice;
                cout << "Enter your choice: ";
                cin >> userChoice;

                switch (userChoice) {
                    case 1: {
                        RideSeats seat;
                        // Book a ride
                        cout << "Enter the number of the ride you want to interact with: ";
                        int selectedRideIndex;
                        cin >> selectedRideIndex;

                     if (selectedRideIndex >= 1 && selectedRideIndex <= rideManager.getTotalRides()) {
                     // Valid ride selection

                      // Now you can use selectedRideIndex to perform the desired operation on the specific ride
                      // For example, if the user wants to book a ride:
                       User user;
                       seat.InsertPassenger(user);  
                          cout << "Booking successful!" << endl;
                     } else {
                          cout << "Invalid ride selection. Please try again." << endl;
                                                                                       }
                        break;
                    }

                   case 2: {
                    // Unbook a ride
                    RideSeats seat;

                      // Display all current rides
                     rideManager.DisplayRides();

                     // Ask user to select a ride
                     cout << "Enter the number of the ride you want to unbook: ";
                     int selectedRideIndex;
                     cin >> selectedRideIndex;

                     if (selectedRideIndex >= 1 && selectedRideIndex <= rideManager.getTotalRides()) {
                     // Valid ride selection
                     // Now you can use selectedRideIndex to unbook the ride
                     seat.deletePassenger(selectedRideIndex);
                     cout << "Unbook successful." << endl;
                     } else {
                     cout << "Invalid ride selection. Please try again." << endl;
                         }
                      break;
                    }

                   case 3: {
                    // Update booking
                     User user;
                     int selectedRideIndex;
                     cout << "Enter the number of the ride you want to update: ";
                     cin >> selectedRideIndex;

                      if (selectedRideIndex >= 1 && selectedRideIndex <= rideManager.getTotalRides()) {
                                  // Valid ride selection
                      // Now you can use selectedRideIndex to update the booking
                     RideSeats seat;
                     seat.UpdateNode(selectedRideIndex,user);
                     cout << "Booking updated successfully!" << endl;
                        } else {
                     cout << "Invalid ride selection. Please try again." << endl;
                         }
                     break;
                        }

                  case 4: {
                    // Display all passengers of a selected ride
                     //RideSeats seat;

                     // Display all current rides
                    //  rideManager.DisplayRides();

                     // Ask user to select a ride
                      cout << "Enter the number of the ride to display passengers: ";
                      int selectedRideIndex;
                      cin >> selectedRideIndex;

                      if (selectedRideIndex >= 1 && selectedRideIndex <= rideManager.getTotalRides()) {
                      // Valid ride selection
                     // Now you can use selectedRideIndex to display passengers of the selected ride
                     rideManager.DisplayPassengers(selectedRideIndex);
                     } else {
                     cout << "Invalid ride selection. Please try again." << endl;
                     }
                     break;
                                }



                     case 5: {
                        cout << "Exiting..." << endl;
                        exit(0);
                    }

                    default:
                        cout << "Invalid choice. Please try again." << endl;
                }
                break;
            }

            case 3: {
                cout << "Exiting..." << endl;
                exit(0);
            }

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}


