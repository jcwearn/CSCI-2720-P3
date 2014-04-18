#include <iostream>
#include <fstream>
using namespace std;

class String_repr {
private:
  
public:
};

class Freq_table {
private:
  int freq[256];

public:
  Freq_table();
  Freq_table(string s);

  void print_freq() {
    int i;

    for(i = 0; i < 256; i++) {
      if(freq[i] != 0)
	cout << "Freq " << i << " " << freq[i] << endl;
    }
  }
};

Freq_table::Freq_table(string s) {
  int i;
  int ascii;
  int length = s.length();
  
  for(i = 0; i < length; i++) {
    freq[i] = 0;
  }

  for(i = 0; i < length; i++) {
    ascii = (int)s.at(i);
    freq[ascii]++;
  }
  
}
  
int main() {
  string user_input;
  char user_input_aschar;
  int user_case;
  bool still_running = true;

  Freq_table* freq = new Freq_table("This is a test");
  freq->print_freq();

  cout << "Please choose from the following:\n\n";
  cout << "1: Build the library file from sample.txt\n";
  cout << "2: Print the charater list and frequency of each char in sample.txt\n";
  cout << "3: Encode a message\n";
  cout << "4: Decode a message\n\n";

  while(still_running) {
    cout << ">> ";
    cin >> user_input;
    //user_input = cin.get();
    user_input_aschar = user_input.at(0);
    
    
    //checks if user input is invalid
    if(user_input.length() != 1) {
      
      cout << user_input.length() << endl;
      user_case = -1;
    }
    
    else {
      if(isdigit(user_input_aschar)) {
	user_case =  user_input_aschar - '0';
      }
    }
    
    switch (user_case) {
    case 1:

      
      
      still_running = false;
      break;
    case 2:
      still_running = false;
      break;
    case 3:
      still_running = false;
      break;
    case 4:
      still_running = false;
      break;
    default:
      cout << "Invalid input.  Please enter a numerical value 1-4\n";
      break;
    }
  
  }

  cout << user_input << endl;
  return 0;
}
