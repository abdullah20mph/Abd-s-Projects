#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
/* 1) OPERATOR OVERLOADING CAN BE IMPLENTED ON BILLING WHEN A CUSTOMER WANTS TO
PAY FOR MORE THAN 1 ROOM. it will add the thing.. 2) FRIEND FUNCTION 3) FUNCTION
OVERRIDING/OVERLOADING 4) VECTORS 5) VIRTUAL FUNCTIONS 6) template

*/

using namespace std;

class filing {
public:
  void saveFile(string data) {
    fstream outfile;
    outfile.open("UserDataBase.txt", ios::out | ios::app);
    if (outfile.is_open()) {
      outfile << data << endl;
      outfile << " ";
      outfile.close();
    } else {
      cout << "Error opening file." << endl;
    }
  }

  void staffFile(string data) {
    fstream outfile;

    outfile.open("staffData.txt", ios::out | ios::app);

    if (outfile.is_open()) {
      outfile << data << endl;
      outfile << " ";
      outfile.close();
    } else {
      cout << "cant open the file.";
    }
  }

  void readFile(string username, string password) {
    fstream input;
    input.open("UserDataBase.txt", ios::in);

    string line;
    bool found = false;

    while (getline(input, line)) {
      if (line.find("userName: " + username) != string::npos) {
        getline(input, line);
        if (line.find("password: " + password) != string::npos) {
          cout << "Logged in successfully." << endl;
          found = true;
          break;
        }
      }
    }

    if (!found) {
      cout << "Username or password not found. Please register yourself."
           << endl;
    }

    input.close();
  }
  void readFile(string username){ //function overloading shown here.
    fstream input;
    input.open("UserDataBase.txt", ios::in);

    string line;
    bool found = false;
    
    while (getline(input, line)) {
      if (line.find("userName: " + username) != string::npos) {
        getline(input, line);
          cout << "correct info , your username is : "<< username << endl;
          found = true;
          break;
        
      }
    }
    
    if(!found){
        cout << "wrong username.";
    }
    
    input.close();
  }

  void Userdisplay(string username) {
    // Open the file for reading
    ifstream infile("UserDataBase.txt");

    // Check if the file was opened successfully
    if (!infile) {
      cerr << "Error: Unable to open file." << endl;
      return;
    }

    string line;
    bool found = false;

    // Loop through the file line by line
    while (getline(infile, line)) {
      // Check if the line contains the password
      if (line.find(" username " + username) != string::npos) {
        // Read the next three lines (name, number, and unique_id)
        string name, number, unique_id;
        getline(infile, name);
        getline(infile, number);
        getline(infile, unique_id);

        // Print the user data
        cout << "Name: " << name.substr(6) << endl;
        cout << "Number: " << number.substr(8) << endl;
        cout << "Unique ID: " << unique_id.substr(11) << endl;

        found = true;
        break;
      }
    }
        if (!found) {
      cout << "Username not found. Please register yourself."
           << endl;
    }
    // Close the file
    infile.close();

    // If the data was not found, print an error message
    if (!found) {
      cout << "Error: Data not found." << endl;
    }
  }
};

class userLoginSignup : public filing {
public:
  string username;
  string password;
  static int Usercount;
  string name;
  string number;
  string unique_id;

  void userLogin() {
    cout << "Choose one of the following options:" << endl;
    cout << "1. Sign up or register" << endl;
    cout << "2. Login" << endl;
   // cout << "3. To display Data." << endl;

    int choice;
    cin >> choice;

    if (choice == 1) {
      cout << "Enter your username: ";
      cin >> username;
      this->saveFile("userName: " + username);

      cout << "Enter your password: ";
      cin >> password;
      this->saveFile("password: " + password);

      cout << "Please enter your name: ";
      cin >> name;
      this->saveFile("Name: " + name);

      cout << "Please enter your cell phone number: ";
      cin >> number;
      this->saveFile("number: " + number); // this is the difference.

      unique_id = number.substr(7, 4);
      this->saveFile("unique id: " + unique_id);

      Usercount++;
    } else if (choice == 2) {
      cout << "Enter your username: ";
      cin >> username;

      cout << "Enter your password: ";
      cin >> password;

      filing f2; // association here calling an object of filing and using it
                 // function...

      f2.readFile(username, password);
    } else if (choice == 3) {
      cout << "enter your username.";
      cin >> username;

      filing f2;

      f2.Userdisplay(username); // association here calling an object of filing
                                // and using it function...
    }
  }
};

int userLoginSignup::Usercount = 0;

class RoomInfo {
  // an abstract class which only has details.
  virtual void BookRoom() = 0;

public:
  string roomType[3] = {"Suite", "Royal", "Delux"};
  int suitePrice = 100; // price per night for a suite room
  int royalPrice = 150; // price per night for a royal room
  int deluxPrice = 200; // price per night for a delux room
  int suiteRoomNumbers[5] = {101, 102, 103, 104,
                             105}; // room numbers for each suite room
  int royalRoomNumbers[10] = {
      201, 202, 203, 204, 205,
      206, 207, 208, 209, 210}; // room numbers for each royal room
  int deluxRoomNumbers[20] = {301, 302, 303, 304, 305, 306, 307,
                              308, 309, 310, 401, 402, 403, 404,
                              405, 406, 407, 408, 409, 410}; // room numbers for
                                                             // each delux room
  static int countSuite;
  static int countRoyal;
  static int countDelux;
};

int RoomInfo::countSuite = 0;
int RoomInfo::countRoyal = 0;
int RoomInfo::countDelux = 0;

class RoomBook : public RoomInfo, public userLoginSignup {
protected:
  int roomNo;
  bool roomAvailibility;
  string CheckIn;
  string Checkout;
  int choice;
  int noOfGuest;
  int nights;
  bool allottedRooms[5] = {false};
  int lastallotedroomSuite = 100;
  int lastallotedroomRoyal = 200;
  int lastallotedroomDelux = 300;


public:
  void BookRoom() {
    cout << "Which type of room do you want ? " << endl;
    cout << "enter 1 for suite \n enter 2 for Royal \n enter 3 for Delux.";
    cin >> choice;

    if (choice == 1) {
      cout << "How many guest do you have ? ";
      cin >> noOfGuest;
      countSuite++;
      if (noOfGuest <= 4) {
        cout << "Please enter your Check in date.(format : DD/MM/YY)";
        cin >> CheckIn;
        cout << "Please enter your Check out date.(format : DD/MM/YY)";
        cin >> Checkout;
        cout << "total no of niights ? ";
        cin >> nights;

        if (countSuite < 5) {
          fstream outfile;

          outfile.open("UserDataBase.txt", ios::out | ios::app);

          outfile << "Type of Room : royal " << endl;
          outfile << "No of guest." << noOfGuest << endl;
          outfile << "Check in date." << CheckIn << endl;
          outfile << "Check out date" << Checkout << endl;
          outfile << "total nights : " << nights << endl;
          outfile << "rooms occupied. : " << countSuite << endl;
          
          
          for (int i = 0; i < 5; i++) { 
            if (!allottedRooms[i]) {
              allottedRooms[i] = true;
              lastallotedroomSuite++;
              outfile << "lastallotedroom. : " << lastallotedroomSuite<< "   \n    " << endl;
              outfile  << "   " ;
              break; // Exit the loop after allotting a room
            }
          }

          outfile.close();

        } else {
          cout << "All of the rooms are booked.";
        }
       
      } else {
        cout << "sorry we have a limit of 4 guests.";
      }
    }

    else if (choice == 2) {
      cout << "How many guest do you have ? ";
      cin >> noOfGuest;
                countRoyal++;
      if (noOfGuest <= 4) {
        cout << "Please enter your Check in date.(format : DD/MM/YY)";
        cin >> CheckIn;
        cout << "Please enter your Check out date.(format : DD/MM/YY)";
        cin >> Checkout;
        cout << "total no of niights ? ";
        cin >> nights;

        if (countRoyal < 10) {
          fstream outfile;

          outfile.open("UserDataBase.txt", ios::out | ios::app);

          outfile << "Type of Room : royal " << endl;
          outfile << "No of guest." << noOfGuest << endl;
          outfile << "Check in date." << CheckIn << endl;
          outfile << "Check out date" << Checkout << endl;
          outfile << "total nights : " << nights << endl;
          outfile << "rooms occupied. : " << countRoyal++ << endl;
          
          
          for (int i = 0; i < 5; i++) { /* The loop iterates through five elements of the array allottedRooms. For each iteration, the if statement checks if the current element is false (meaning the room is empty).
                                           If the current element is false, the code inside the if statement is executed.
                                           Inside the if statement, the current element is set to true (meaning the room is now occupied), and lastallotedroom is incremented by 1.
                                           The values of lastallotedroom and a new line character are written to an output file using the << operator.
                                           The loop is exited using the break statement, as soon as an empty room is found and allotted to a customer. */
            if (!allottedRooms[i]) {
              allottedRooms[i] = true;
              lastallotedroomRoyal++;
              outfile << "lastallotedroom. : " << lastallotedroomRoyal<< "   \n    " << endl;
              outfile  << "   " ;
              break; // Exit the loop after allotting a room
            }
          }

          outfile.close();

        } else {
          cout << "All of the rooms are booked.";
        }
       
      } else {
        cout << "sorry we have a limit of 4 guests.";
      }
    } else if (choice == 3) {
      cout << "How many guest do you have ? ";
      cin >> noOfGuest;
      if (noOfGuest <= 2) {
        cout << "Please enter your Check in date.(format : DD/MM/YY)";
        cin >> CheckIn;
        cout << "Please enter your Check out date.(format : DD/MM/YY)";
        cin >> Checkout;
        cout << "total no of niights ? ";
        cin >> nights;
        cout << "  ";

        if (countDelux < 20) {
          fstream outfile;

          outfile.open( "UserDataBase.txt", ios::out | ios::app); // opening a file in output and append method to
                                                              // make sure data is going out in the databse file.

          outfile << "Type of Room : delux " << endl;
          outfile << "No of guest." << noOfGuest << endl;
          outfile << "Check in date." << CheckIn << endl;
          outfile << "Check out date" << Checkout << endl;
          outfile << "total nights : " << nights << endl;
          countDelux++; // counter to count the number of delux rooms that are
                        // getting occupied.
          outfile << "rooms occupied. : " << countDelux << endl;
          
           for (int i = 0; i < 5; i++) { 
            if (!allottedRooms[i]) {
              allottedRooms[i] = true;
              lastallotedroomDelux++;
              outfile << "lastallotedroom. : " << lastallotedroomDelux<< "   \n    " << endl;
              outfile  << "   " ;
              break; // Exit the loop after allotting a room
            }
          }

          outfile.close();

        } else {
          cout << "All of the rooms are booked.";
        }

      } else {
        cout << "sorry no more than 2 guests allowed.";
      }
    }
  }
};

class Checkout :  public RoomBook {
    
    protected:
    string checkId;
    string choice;
    public:

    int roomNumber;
    void customerCheckout(){
    cout << "please provide us your username.";
    cin >> username;
        
    fstream input;
    input.open("UserDataBase.txt", ios::in);

    string line;
    bool found = false;
    
        
    while (getline(input, line)) {
      if (line.find("userName: " + username) != string::npos) {
        getline(input, line);
          cout << "correct info , your username is : "<< username << endl;
          found = true;
            // Extract fields from the file
            string password,noOfGuest, name, number, uniqueId, roomType, checkInDate, checkOutDate, nights, roomsOccupied, lastAllotedRoom;
            getline(input, line); // password
            password = line.substr(line.find(": ") + 2);
            getline(input, line); // name
            name = line.substr(line.find(": ") + 2);
            getline(input, line); // number
            number = line.substr(line.find(": ") + 2);
            getline(input, line); // unique id
            uniqueId = line.substr(line.find(": ") + 2);
            getline(input, line); // room type
            roomType = line.substr(line.find(": ") + 2);
            getline(input, line); // no of guests
            getline(input, line); // check in date
            checkInDate = line.substr(line.find(".")+1);
            getline(input, line); // check out date
            checkOutDate = line.substr(line.find(".")+1);
            getline(input, line); // total nights
            nights = line.substr(line.find(": ") + 2);
            int totalNights = stoi(nights); 
            getline(input, line); // rooms occupied
            roomsOccupied = line.substr(line.find(": ") + 2);
            getline(input, line); // last allotted room
            lastAllotedRoom = line.substr(line.find(": ") + 2);
            
            // Output the extracted fields
            cout << "Name: " << password << endl;
            cout << "Number: " << name << endl;
            cout << "Unique ID: : " << number << endl;
           // cout << "Room Type " << uniqueId << endl;
            cout << "noOfGuest " << roomType << endl;
            cout << "No. of Guests: " << noOfGuest << endl;
           // cout << "Check-in Date: " << checkInDate << endl;
            cout << "Check-out Date: " << checkOutDate << endl;
            cout << "Total Nights: " << nights << endl;
            cout << "Rooms Occupied: " << roomsOccupied << endl;
            cout << "Last Allotted Room: " << lastAllotedRoom << endl;
            cout << "enter your room type.";
            cin >> choice;
            if(choice == "royal" ){
                cout << " your total bill will be : " << totalNights * royalPrice<<endl;
            }
            else if(choice == "suite" ){
                cout << " your total bill will be : " << totalNights * suitePrice<<endl;
            }
            else if (choice == "delux" ){
                cout << " your total bill will be : " << totalNights * deluxPrice<<endl;
            }
          break;
        
      }
    }
    
    if(!found){
        cout << "wrong username.";
    }
    
    input.close();
    }
        
       

};

template <typename T>
class staffManagment : public filing { // using templates here.
protected:
  string name;
  int age;
  string jobTitle;
  float hoursWorked;
  static int staffcount;
  static vector<T> staff; // making a vector staff so we can save staff on the
                          // basis of their number of name.

public:
  // Getters
  void employeProfile() {
    cout << "enter your name." << endl;
    cin >> name;
    this->staffFile("name : " + name);
    cout << "enter your age." << endl;
    cin >> age;
    this->staffFile("age : " + age);
    cout << "enter your job title." << endl;
    cin >> jobTitle;
    this->staffFile("jobTitle : " + jobTitle);
  }
  string getName() const { return name; }

  int getAge() const { return age; }

  string getJobTitle() const { return jobTitle; }

  float getHoursWorked() const { return hoursWorked; }

  // Setters
  void setName(string name) { name = name; }

  void setAge(int _age) { age = age; }

  void setJobTitle(string _jobTitle) { jobTitle = jobTitle; }

  void setHoursWorked(T hoursWorked) { hoursWorked = hoursWorked; }

  void salarycalculator() {
    cout << "enter your job position.";
    cin >> jobTitle;
    cout << "enter your working hour for the month.";
    cin >> hoursWorked;

    if (jobTitle == "CEO") {
      cout << " Your salary will be : " << hoursWorked * 100;
    } else if (jobTitle == "employee") {
      cout << " Your salary will be : " << hoursWorked * 20;
    } else {
      cout << "invalid job title.";
    }
  }

  static void addRemoveEmployee() {
    string input;
    T val;
    cout << "Do you want to add or remove an employee ? ";
    cin >> input;
    if (input == "add") {
      cout << "enter the name or employee number.";
      cin >> val;
      staff.push_back(val);
      cout << "employee added." << endl;
    } else if (input == "remove") {
      cout << "enter the name or employee number.";
      cin >> val;
      staff.pop_back();
      cout << "employee removed.";
    }
  }

  static void displayEmployee() {
    for (int i = 0; i < staff.size(); i++) {
      cout << " employees : " << staff[i] << endl;
    }
  }

  // staffManagment operator == (staffManagment &obj){
};
template <class T> int staffManagment<T>::staffcount = 0;
template <class T> vector<T> staffManagment<T>::staff;

struct Item {
  string name;
  int quantity;
  double price;
};

class inventory {
private:
  vector<Item> items;

public:
  void addItem(const string &name, int quantity, double price) {
    Item newItem;
    newItem.name = name;
    newItem.quantity = quantity;
    newItem.price = price;
    items.push_back(newItem);
  }

  void removeItem(const string &name) {
    items.erase(remove_if(items.begin(), items.end(),
                          [&](const Item &item) { return item.name == name; }),
                items.end());
  }

  void displayinventory() {
    cout << "Current Inventory Levels:\n";
    for (const auto &item : items) {
      cout << "Item: " << item.name << ", Quantity: " << item.quantity
           << ", Price: " << item.price << endl;
    }
  }

  void manageInventory(const string &name, int quantity) {
    for (auto &item : items) {
      if (item.name == name) {
        item.quantity += quantity;
        break;
      }
    }
  }

  void generateInventoryReport() {
    cout << "Inventory Report:\n";
    for (const auto &item : items) {
      cout << "Item: " << item.name << ", Quantity: " << item.quantity
           << ", Value: " << (item.quantity * item.price) << endl;
    }

  }

  void orderInventory(const string &name, int quantity) {
    cout << "Ordering " << quantity << " units of " << name
         << " from supplier.\n";
    //  purchase orders and sending them to
    // suppliers can be added here
  }

  void trackInventoryUsage() {
    cout << "Inventory Usage Tracking:\n";
    // code can be wrriten here to track item usage can be 
  }
// Function overloading
  void addItem(const Item& newItem) {
    items.push_back(newItem);
  }

  void removeItem(const Item& item) {
    items.erase(remove_if(items.begin(), items.end(),
                          [&](const Item &i) { return i.name == item.name; }),
                items.end());
  }

  // operator overloading
inventory operator+(const Item& item) {
    addItem(item);
    return *this;
  }

  inventory operator-(const string& name) {
    removeItem(name);
    return *this;
  }
 

};



int main() {
  string choice;
  int input;

  cout << "Welcome to the Hotel Managment System." << endl;
  cout << "Are you a user or an employee.";
  cout << "press 1 for user and 2 for employee.";
  cin >> input;
  if (input == 1) {
    cout << "Following are the options that we have." << endl;
    cout << "Enter 1 to Book a room" << endl;
    cout << "Enter 2 for billing." << endl;
    cout << "Enter 3 to Search for a customer." << endl;
    cout << "Enter 4 to Sign in or Register.)" << endl;

    while (true) {
      cout << "Enter 0 to exit or 9 to restart the menu..";
      cin >> input;

      if (input == 9) {
        continue;
      }

      if (input == 0) {
        break;
      } else if (input == 1) {
        userLoginSignup u;
        u.userLogin();
        RoomBook r;
        r.BookRoom();
      } else if (input == 2) {
        Checkout c;
        c.customerCheckout();
      } else if (input == 3) {
        CustomerData d;
      }  else if (input == 4) {
        userLoginSignup u;
      }
    }
  } else if (input == 2) {
    cout << "press 1 for staff managment." << endl;
    cout << "press 2 for inventory managment." << endl;
    cin >> input;
    if (input == 1) {
      staffManagment<string> s;
      s.employeProfile();
      cout << "1) Calculate your salary.";
      cout << "2) Add/Remove employee";
      cin >> input;
      if(input == 1){
          s.salarycalculator();
      }
      else if (input == 2){
          s.addRemoveEmployee();
      }
    } else if (input == 2) {
      inventory inv;
      inv.addItem("Apple", 10, 1.50);
      inv.addItem("Banana", 5, 1.00);
      inv.addItem("Orange", 8, 2.00);
      cout << "What does customer wants ? ";
      
      inv.displayinventory();
      
    }
  }

  return 0;
}
