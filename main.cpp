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
  time_t OnTime;
  time_t OffTime;
  int PowerConsumption;
};

struct Room {
  int ID;
  vector<Device> Devices;
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
double getDeviceHours(const Device &d);
void EnquireStatus(vector<Room> *rooms);
void Reports(vector<Room> *rooms);
void Trends(vector<Room> *rooms);
void TimerMode(vector<Room> *rooms);
void SettingsMenu(vector<Room> *Rooms);
void InitializeMenu(vector<Room> *Rooms);
void ModeSelectionMenu(vector<Room> *rooms);
void ManualMode(vector<Room> *rooms);
void SelectRoom(vector<Room> *Rooms);

void App() {
  vector<Room> Rooms = {};
  while (true) {
    int choice = MainMenu();
    if (choice < 1 || choice > 4) {
      cout << "Please select a choice between 1-4" << endl;
      this_thread::sleep_for(chrono::seconds(2));
      continue;
    }

    switch (choice) {
    case 1:
      if (!Authenticate_User()) {
        cout << "Unable to authenticate credentials This is possibly due to "
                "incorrect entry of password"
             << endl;
        this_thread::sleep_for(chrono::seconds(2));
        continue;
      }
      SettingsMenu(&Rooms);
      break;
    case 2:
      EnquireStatus(&Rooms);
      break;
    case 3:
      Reports(&Rooms);
      break;
    case 4:
      Trends(&Rooms);
      break;
    }
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

void SettingsMenu(vector<Room> *rooms) {
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
      ModeSelectionMenu(rooms);
      break;
    case 4:
      return;
    }
  }
}

void ModeSelectionMenu(vector<Room> *rooms) {
  int choice = 0;
  cout << "Mode Selection Menu" << endl;
  cout << "Press" << endl;
  cout << "1. Manual Mode" << endl;
  cout << "2. Timer Mode" << endl;
  cout << "3. Exit" << endl;
  choice = getInt();
  switch (choice) {
  case 1:
    ManualMode(rooms);
    break;
  case 2:
    TimerMode(rooms);
    break;
  case 3:
    return;
  }
}

// Return the number of rooms
int GetRoomCount() {
  int Num;
  cout << "Enter the number of rooms" << endl;
  Num = getInt();
  return Num;
}

void InitializeMenu(vector<Room> *rooms) {
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
      rooms->clear();
      int NRooms = GetRoomCount();
      for (int i = 0; i < NRooms; i++) {
        Room room = {};
        room.ID = i;
        rooms->push_back(room);
      }
      break;
    }
    case 2:
      SelectRoom(rooms);
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
  cout << "Select the room" << endl;
  for (int i = 1; i <= rooms->size(); i++) {
    cout << "- Room " << i << endl;
  }
  int room_number = getInt();

  if (!isInRange(room_number, rooms->size())) {
    cout << "Room not in range" << endl;
    return;
  }

  cout << "Enter the number of devices" << endl;
  int number_of_devices = getInt();

  auto &devices = (*rooms)[room_number - 1].Devices;
  devices.clear();

  cout << "Enter the power rating for each device" << endl;
  for (int i = 0; i < number_of_devices; i++) {
    Device d = {};
    d.PowerConsumption = getInt();
    devices.push_back(d);
    cout << "power for device number " << i + 1 << " = " << d.PowerConsumption
         << endl;
  }
}

void ManualMode(vector<Room> *rooms) {
  if (rooms->empty()) {
    cout << "Please add rooms first" << endl;
    return;
  }

  cout << "Enter the room number" << endl;
  int room = getInt();
  if (!isInRange(room, rooms->size())) {
    cout << "Please choose a room between 1 and " << rooms->size() << endl;
    return;
  }

  auto &devices = (*rooms)[room - 1].Devices;
  if (devices.empty()) {
    cout << "No devices in this room yet" << endl;
    return;
  }

  cout << "Enter the device number" << endl;
  int device = getInt();
  if (!isInRange(device, devices.size())) {
    cout << "Please choose a device between 1 and " << devices.size() << endl;
    return;
  }

  cout << "Press" << endl;
  cout << "1. ON" << endl;
  cout << "2. OFF" << endl;
  int status = getInt();
  if (!isInRange(status, 3)) {
    cout << "Please press either 1 or 2" << endl;
    this_thread::sleep_for(chrono::seconds(3));
    return;
  }

  switch (status) {
  case 1:
    devices[device - 1].Status = true;
    devices[device - 1].OnTime = time(nullptr);
    cout << "Room No " << room << " & Device No " << device << " is ON" << endl;
    this_thread::sleep_for(chrono::seconds(3));
    break;
  case 2:
    devices[device - 1].Status = false;
    devices[device - 1].OffTime = time(nullptr);
    cout << "Room No " << room << " & Device No " << device << " is OFF"
         << endl;
    this_thread::sleep_for(chrono::seconds(3));
    break;
  default:
    cout << "Incorrect choice" << endl;
    return;
  }
}
time_t getTimeInput() {
  int hour, min;
  while (true) {
    cout << "Enter time (24h format, e.g. 14 30): ";
    if (cin >> hour >> min && hour >= 0 && hour <= 23 && min >= 0 &&
        min <= 59) {
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      time_t now = time(nullptr);
      tm *t = localtime(&now);
      t->tm_hour = hour;
      t->tm_min = min;
      t->tm_sec = 0;
      return mktime(t);
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Invalid time, try again.\n";
  }
}

void TimerMode(vector<Room> *rooms) {
  if (rooms->empty()) {
    cout << "Please add rooms first" << endl;
    return;
  }

  cout << "Enter the room number" << endl;
  int room = getInt();
  if (room < 1 || room > (int)rooms->size()) {
    cout << "Please choose a room between 1 and " << rooms->size() << endl;
    return;
  }

  auto &devices = (*rooms)[room - 1].Devices;
  if (devices.empty()) {
    cout << "No devices in this room yet" << endl;
    return;
  }

  cout << "Enter the device number" << endl;
  int device = getInt();
  if (device < 1 || device > (int)devices.size()) {
    cout << "Please choose a device between 1 and " << devices.size() << endl;
    return;
  }

  cout << "Enter the ON time (T_on):" << endl;
  time_t tOn = getTimeInput();

  cout << "Enter the OFF time (T_off):" << endl;
  time_t tOff = getTimeInput();

  if (tOff <= tOn) {
    tOff += 24 * 3600;
  }

  auto &d = devices[device - 1];
  d.OnTime = tOn;
  d.OffTime = tOff;

  time_t now = time(nullptr);
  d.Status = (now >= tOn && now < tOff);

  double hours = difftime(tOff, tOn) / 3600.0;
  cout << "The Room No " << room << " & Device No " << device
       << " will be ON for " << hours << " hours" << endl;
  this_thread::sleep_for(chrono::seconds(3));
}

double getDeviceHours(const Device &d) {
  if (d.OnTime == 0)
    return 0.0;
  time_t end = (d.OffTime > d.OnTime) ? d.OffTime : time(nullptr);
  double sec = difftime(end, d.OnTime);
  return (sec > 0) ? sec / 3600.0 : 0.0;
}

void EnquireStatus(vector<Room> *rooms) {
  clearCout();
  if (rooms->empty()) {
    cout << "Please add rooms first" << endl;
    this_thread::sleep_for(chrono::seconds(2));
    return;
  }

  cout << "Enter the room number" << endl;
  int room = getInt();
  if (room < 1 || room > (int)rooms->size()) {
    cout << "Room not in range" << endl;
    this_thread::sleep_for(chrono::seconds(2));
    return;
  }

  auto &devices = (*rooms)[room - 1].Devices;
  if (devices.empty()) {
    cout << "No devices in this room yet" << endl;
    this_thread::sleep_for(chrono::seconds(2));
    return;
  }

  cout << "Enter the device number" << endl;
  int device = getInt();
  if (device < 1 || device > (int)devices.size()) {
    cout << "Device not in range" << endl;
    this_thread::sleep_for(chrono::seconds(2));
    return;
  }

  auto &d = devices[device - 1];
  time_t now = time(nullptr);
  bool isOn =
      (d.OffTime > d.OnTime) ? (now >= d.OnTime && now < d.OffTime) : d.Status;

  cout << "Room " << room << " Device " << device << " is "
       << (isOn ? "ON" : "OFF") << endl;
  cout << "Press Enter to continue...";
  cin.get();
}

void Reports(vector<Room> *rooms) {
  clearCout();
  cout << "Welcome to mySmart Home\nReports\n" << endl;
  if (rooms->empty()) {
    cout << "No rooms configured." << endl;
    this_thread::sleep_for(chrono::seconds(2));
    return;
  }

  double totalEnergy = 0.0;
  for (int i = 1; i <= (int)rooms->size(); i++) {
    double roomEnergy = 0.0;
    auto &devices = (*rooms)[i - 1].Devices;
    for (int j = 1; j <= (int)devices.size(); j++) {
      auto &d = devices[j - 1];
      roomEnergy += (d.PowerConsumption * getDeviceHours(d)) / 1000.0;
    }
    cout << "Energy consumed in Room-" << i << ": " << roomEnergy << " kWh"
         << endl;
    totalEnergy += roomEnergy;
  }

  double rate =
      (totalEnergy <= 3000) ? 0.003 : (totalEnergy <= 5000 ? 0.009 : 0.016);
  double costBD = (totalEnergy * rate) + 1.000;

  cout << "\nTotal Energy: " << totalEnergy << " kWh" << endl;
  cout << "Estimated Bill (incl. 1.000 BD fixed): " << costBD << " BD" << endl;
  cout << "\nPress Enter to continue...";
  cin.get();
}

void Trends(vector<Room> *rooms) {
  clearCout();
  cout << "Welcome to mySmart Home\nTrends\n" << endl;
  if (rooms->empty()) {
    cout << "No rooms configured." << endl;
    this_thread::sleep_for(chrono::seconds(2));
    return;
  }

  int maxRoom = -1, maxDevRoom = -1, maxDev = -1, maxTimeRoom = -1,
      maxTimeDev = -1;
  double maxRoomEnergy = -1.0, maxDevEnergy = -1.0, maxHours = -1.0;

  for (int i = 1; i <= (int)rooms->size(); i++) {
    double roomEnergy = 0.0;
    auto &devices = (*rooms)[i - 1].Devices;
    for (int j = 1; j <= (int)devices.size(); j++) {
      auto &d = devices[j - 1];
      double hrs = getDeviceHours(d);
      double energy = (d.PowerConsumption * hrs) / 1000.0;
      roomEnergy += energy;

      if (energy > maxDevEnergy) {
        maxDevEnergy = energy;
        maxDevRoom = i;
        maxDev = j;
      }
      if (hrs > maxHours) {
        maxHours = hrs;
        maxTimeRoom = i;
        maxTimeDev = j;
      }
    }
    if (roomEnergy > maxRoomEnergy) {
      maxRoomEnergy = roomEnergy;
      maxRoom = i;
    }
  }

  cout << "Which room consumes more energy? Room-" << maxRoom << " ("
       << maxRoomEnergy << " kWh)" << endl;
  if (maxDev != -1) {
    cout << "Which device consumes more energy? Room-" << maxDevRoom
         << " Device-" << maxDev << " (" << maxDevEnergy << " kWh)" << endl;
    cout << "Which device is activated for more time? Room-" << maxTimeRoom
         << " Device-" << maxTimeDev << " (" << maxHours << " hrs)" << endl;
  } else {
    cout << "No devices added yet." << endl;
  }

  cout << "\nPress Enter to continue...";
  cin.get();
}
