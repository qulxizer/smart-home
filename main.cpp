#include <ctime>
#include <iostream>
using namespace std;

int MainMenu();
bool Authenticate_User();
int SettingsMenu();
int InitializeMenu();
int ModeSelectionMenu();
void App() {
  int choice = MainMenu();
  if (choice < 1 || choice > 4) {
    cout << "Please select a choice between 1-4" << endl;
  }
  if (choice == 1) {
    if (Authenticate_User() == false) {
      cout << "Unable to authenticate credentials This is possibly due to "
              "incorrect entry of password";
      App();
    }
    choice = SettingsMenu();
    if (choice == 1 || choice == 2) {
      choice = InitializeMenu();
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

int InitializeMenu() {
  int choice = 0;
  cout << "Mode Initialize Menu" << endl;
  cout << "Press" << endl;
  cout << "1. Add number of rooms" << endl;
  cout << "2. Add device" << endl;
  cout << "3. Exit" << endl;
  cin >> choice;
  return choice;
}
