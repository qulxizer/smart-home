#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

struct Device {
  string Name;
  bool Status;
  int PowerConsumption;
};

struct Room {
  int ID;
  Device Devices[4];
};

bool isInRange(int choice, int max) {
  if (choice > 0 || choice < max) {
    return true;
  }
  return false;
}

int MainMenu();
int EnterRoomNumber();
bool Authenticate_User();
int SettingsMenu();
void InitializeMenu(vector<Room> Rooms);
int ModeSelectionMenu();
void SelectRoom(vector<Room> *Rooms);

void App() {

  vector<Room> Rooms = {};

  int choice = MainMenu();
  if (choice < 1 || choice > 4) {
    cout << "Please select a choice between 1-4" << endl;
    return;
  }
  if (choice == 1) {
    if (Authenticate_User() == false) {
      cout << "Unable to authenticate credentials This is possibly due to "
              "incorrect entry of password";
      App();
    }
    // User is authed

    choice = SettingsMenu();
    if (choice == 1 || choice == 2) {
      InitializeMenu(Rooms);
    }
    if (choice == 3) {
      choice = ModeSelectionMenu();
    }
    if (choice == 4) {
      App();
    }
  }
  if (choice == 2) {
  }
}
int main() {
  App();
  return 0;
}

int MainMenu() {
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
  cin >> choice;
  return choice;
}

bool Authenticate_User() {
  int password = 0;
  cout << "Enter Password" << endl;
  cin >> password;
  for (int i = 2; i > 0; i--) {
    if (password == 5680) {
      return true;
    }
    cout << "Incorrect Password " << "'" << i << "'" << " attempts"
         << " remaining" << endl;

    cin >> password;
  }

  return false;
}

int SettingsMenu() {
  int choice = 0;
  cout << "Settings Menu" << endl;
  cout << "Press" << endl;
  cout << "1. Initialize the system" << endl;
  cout << "2. Update the features" << endl;
  cout << "3. Select modes" << endl;
  cout << "4. Exit" << endl;
  cin >> choice;
  return choice;
}

int ModeSelectionMenu() {
  int choice = 0;
  cout << "Mode Selection Menu" << endl;
  cout << "Press" << endl;
  cout << "1. Manual Mode" << endl;
  cout << "2. Timer Mode" << endl;
  cout << "3. Exit" << endl;
  cin >> choice;
  return choice;
}

void InitializeMenu(vector<Room> Rooms) {
  int choice = 0;
  while (choice != 3) {
    cout << "Mode Initialize Menu" << endl;
    cout << "Press" << endl;
    cout << "1. Add number of rooms" << endl;
    cout << "2. Add device" << endl;
    cout << "3. Exit" << endl;
    cin >> choice;
    if (choice == 1) {
      Rooms.clear();
      int NRooms = EnterRoomNumber();
      for (int i = 0; i < NRooms; i++) {
        Room room = {};
        room.ID = i;
        Rooms.push_back(room);
      }
    }
    if (choice == 2) {
      SelectRoom(&Rooms);
      // cout << room;
    }

    if (choice == 3) {
      for (auto i : Rooms)
        cout << i.Devices->PowerConsumption << " ";
      SelectRoom(&Rooms);
      // cout << room;
    }
  }
}
// Return the number of rooms
int EnterRoomNumber() {
  int Num;
  cout << "Enter the number of rooms" << endl;
  cin >> Num;
  return Num;
}

int EnterNumberOfDevices() {
  int Num;
  cout << "Enter the number of devices" << endl;
  cin >> Num;
  return Num;
}

int EnterDevice() {
  int Num;
  cout << "Enter the number of rooms" << endl;
  cin >> Num;
  return Num;
}

void SelectRoom(vector<Room> *Rooms) {
  int room_number = 0;
  cout << "Select the room" << endl;
  for (int i = 1; i <= Rooms->size(); i++) {
    cout << "Room " << i << endl;
  }
  cin >> room_number;

  if (!isInRange(room_number, Rooms->size())) {
    cout << "Room not in range" << endl;
    return;
  }
  Room room = (*Rooms)[room_number];

  int number_of_devices = 0;
  cout << "Enter the number of devices" << endl;
  cin >> number_of_devices;
  int max_devices = sizeof(room.Devices) / sizeof(room.Devices[0]);
  if (number_of_devices > max_devices) {
    cout << "Max number of devices is " << max_devices;
    return;
  }

  cout << "Enter the power rating for each device" << endl;
  for (int i = 0; i < number_of_devices; i++) {
    int power = 0;
    cin >> power;
    (*Rooms)[room_number].Devices[i].PowerConsumption = power;
    cout << "power for device number: " << i << " = " << power << endl;
  }
  // Rooms[Num].Devices
}
