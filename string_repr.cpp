#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct table {
    int ascii;
    int value;
};

bool compare_table(const table& a, const table& b) {
    return a.value > b.value;
}

class String_repr {
private:
  
public:
};

class Freq_table {
private:  
  int freq[256];
  vector<table> freq_resized;
  int table_size;

public:
  Freq_table();
  Freq_table(string s);

  void print_freq() {
    int i;

    for(i = 0; i < table_size; i++) {
      cout << "Freq of " << freq_resized[i].ascii << " : " << freq_resized[i].value << endl; 
    }
  }
  
  /*
  void delete_freq_resized() {
    delete [] freq_resized;
    }*/
};

Freq_table::Freq_table(string s) {
  int i,j;
  int ascii;
  int length = s.length();
  int size = 0;

  
  for(i = 0; i < 256; i++) {
    freq[i] = 0;
  }
 
  for(i = 0; i < length; i++) {
    ascii = (int)s.at(i);
    freq[ascii]++;    
  }

  for(i = 0; i < 256; i++) {
    if(freq[i] > 0)
      size++;
  }

  table_size = size;
  
  for(i = 0, j=0; i < 256; i++) {
    if(freq[i] > 0) {
      table f_table = {i, freq[i]};
      freq_resized.push_back(f_table);
      j++;
    }
  }

  sort(freq_resized.begin(), freq_resized.end(), compare_table);
}
  
int main() {
  string user_input;
  char user_input_aschar;
  int user_case;
  bool still_running = true;

  ifstream sample_file("sample.txt");
  string temp;
  string sample_string;
    
  while(getline(sample_file, temp)) {
    sample_string += temp;
  }

  sample_file.close();

  Freq_table* freq = new Freq_table(sample_string);
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

  //freq->delete_freq_resized();

  cout << user_input << endl;
  return 0;
}
