#include <iostream>
using namespace std;

class string_repr {
private:
  
public:
};

int main() {
  string user_input;
  bool still_running = true;;

  cout << "Please choose from the following:\n\n";
  cout << "1: Build the library file from sample.txt\n";
  cout << "2: Print the charater list and frequency of each char in sample.txt\n";
  cout << "3: Encode a message\n";
  cout << "4: Decode a message\n\n";

  while(still_running) {
    cout << ">> ";
    user_input = cin.get();
    
  }

  cout << user_input << endl;
  return 0;
}
