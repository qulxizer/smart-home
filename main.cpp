#include <chrono>
#include <ctime>
#include <iostream>
#include <limits>
#include <thread>
#include <vector>

using namespace std;

struct Device {
  string ID;
  bool Status;
  int PowerConsumption;
};

struct Room {
  int ID;
  Device Devices[4];
};

bool isInRange(int choice, int max) {
  if (choice > 0 && choice < max) {
    return true;
  }
  return false;
}

int getInt() {
  int value;
  while (!(cin >> value)) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Invalid input, enter a number: ";
  }
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  return value;
}

void clearCout() { std::cout << "\033[2J\033[H" << std::flush; }

int MainMenu();
int GetRoomCount();
bool Authenticate_User();
void SettingsMenu(vector<Room> Rooms);
void InitializeMenu(vector<Room> Rooms);
int ModeSelectionMenu();
void SelectRoom(vector<Room> *Rooms);

void App() {
  vector<Room> Rooms = {};
  int choice = MainMenu();

  if (!isInRange(choice, 4)) {
    cout << "Please select a choice between 1-4" << endl;
    this_thread::sleep_for(chrono::seconds(3));
    App();
  }

  switch (choice) {
  case 1:
    if (Authenticate_User() == false) {
      cout << "Unable to authenticate credentials This is possibly due to "
              "incorrect entry of password"
           << endl;
      App();
    }
    SettingsMenu(Rooms);
    break;
  case 2:
    break;
  case 3:
    break;
  case 4:
    break;
  }
}
int main() {
  App();
  return 0;
}

int MainMenu() {
  clearCout();
  int choice = 0;
  cout << "Welcome to mySmart Home" << endl;
  cout << "Main Menu:" << endl;
  cout << "Press" << endl;
  cout << "1. Settings \n2. Enquire device status\n3. Reports\n4. Trends"
       << endl;

  std::time_t now = std::time(nullptr);
  char buf[32];
  std::strftime(buf, sizeof(buf), "%-m/%-d/%Y\n%-I:%M %p",
                std::localtime(&now));
  std::cout << buf << endl;
  choice = getInt();
  return choice;
}

bool Authenticate_User() {
  clearCout();
  int password = 0;
  cout << "Enter Password:" << endl;
  for (int i = 3; i > 0; i--) {
    password = getInt();
    if (password == 5680) {
      return true;
    }
    cout << "Incorrect Password " << "'" << i - 1 << "'" << " attempts"
         << " remaining" << endl;
  }

  return false;
}

void SettingsMenu(vector<Room> rooms) {
  while (true) {
    clearCout();
    int choice = 0;
    cout << "Settings Menu" << endl;
    cout << "Press" << endl;
    cout << "1. Initialize the system" << endl;
    cout << "2. Update the features" << endl;
    cout << "3. Select modes" << endl;
    cout << "4. Exit" << endl;
    choice = getInt();

    switch (choice) {
    case 1:
      InitializeMenu(rooms);
      break;
    case 2:
      InitializeMenu(rooms);
      break;
    case 3:
      choice = ModeSelectionMenu();
      break;
    case 4:
      return;
    }
  }
}

int ModeSelectionMenu() {
  int choice = 0;
  cout << "Mode Selection Menu" << endl;
  cout << "Press" << endl;
  cout << "1. Manual Mode" << endl;
  cout << "2. Timer Mode" << endl;
  cout << "3. Exit" << endl;
  choice = getInt();
  return choice;
}

// Return the number of rooms
int GetRoomCount() {
  int Num;
  cout << "Enter the number of rooms" << endl;
  Num = getInt();
  return Num;
}

void InitializeMenu(vector<Room> rooms) {
  clearCout();
  int choice = 0;
  while (choice != 3) {
    cout << "Mode Initialize Menu" << endl;
    cout << "Press" << endl;
    cout << "1. Add number of rooms" << endl;
    cout << "2. Add device" << endl;
    cout << "3. Exit" << endl;
    choice = getInt();
    switch (choice) {
    case 1: {
      rooms.clear();
      int NRooms = GetRoomCount();
      for (int i = 0; i < NRooms; i++) {
        Room room = {};
        room.ID = i;
        rooms.push_back(room);
      }
      break;
    }
    case 2:
      SelectRoom(&rooms);
      break;
    case 3:
      return;
    default:
      cout << "incorrect choice" << endl;
      return;
    }
  }
}

void SelectRoom(vector<Room> *rooms) {
  clearCout();
  if (rooms->size() < 1) {
    cout << "Please add rooms first" << endl;
    return;
  }
  int room_number = 0;
  cout << "Select the room" << endl;
  for (int i = 1; i <= rooms->size(); i++) {
    cout << "- Room " << i << endl;
  }
  room_number = getInt();

  if (!isInRange(room_number, rooms->size())) {
    cout << "Room not in range" << endl;
    return;
  }
  Room room = (*rooms)[room_number];

  int number_of_devices = 0;
  cout << "Enter the number of devices" << endl;

  number_of_devices = getInt();
  int max_devices = sizeof(room.Devices) / sizeof(room.Devices[0]);
  if (number_of_devices > max_devices) {
    cout << "Max number of devices is " << max_devices << endl;
    return;
  }

  cout << "Enter the power rating for each device" << endl;
  for (int i = 0; i < number_of_devices; i++) {
    int power = 0;
    power = getInt();
    (*rooms)[room_number].Devices[i].PowerConsumption = power;
    cout << "power for device number " << i + 1 << " = " << power << endl;
  }
}
