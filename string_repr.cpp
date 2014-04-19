#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct table {
    int ascii;
    int value;
};

//function to sort table<vector>
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

  //function that prints out freq vector
  void print_freq() {
    int i;
    char c;

    for(i = 0; i < table_size; i++) {
      c = freq_resized[i].ascii;
      cout << "Freq of " << c << " : " << freq_resized[i].value << endl; 
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

  //initializes each element of freq[] to 0
  for(i = 0; i < 256; i++) {
    freq[i] = 0;
  }

  //finds the frequencies of each char in input string
  for(i = 0; i < length; i++) {
    ascii = (int)s.at(i);
    freq[ascii]++;    
  }

  //finds the size for the resized vector that stores frequency data
  for(i = 0; i < 256; i++) {
    if(freq[i] > 0)
      size++;
  }

  table_size = size;

  //adds frequencies to the vector
  for(i = 0, j=0; i < 256; i++) {
    if(freq[i] > 0) {
      table f_table = {i, freq[i]};
      freq_resized.push_back(f_table);
      j++;
    }
  }

  //sorts the newly filled vector
  sort(freq_resized.begin(), freq_resized.end(), compare_table);
}
  
int main() {
  string user_input;
  char user_input_aschar;
  int user_case;
  bool still_running = true;

  //creates variable to read in from sample.txt
  ifstream sample_file("sample.txt");
  string temp;
  string sample_string;

  //reads in sample.txt and stores in sample_string
  while(getline(sample_file, temp)) {
    sample_string += temp;
  }

  sample_file.close();

  Freq_table* freq = new Freq_table(sample_string);

  //display options for prompt
  cout << "Please choose from the following:\n\n";
  cout << "1: Build the library file from sample.txt\n";
  cout << "2: Print the charater list and frequency of each char in sample.txt\n";
  cout << "3: Encode a message\n";
  cout << "4: Decode a message\n\n";

  //creates cases for each option in the prompt
  while(still_running) {
    cout << ">> ";
    cin >> user_input;
    //user_input = cin.get();
    user_input_aschar = user_input.at(0);
    
    
    //checks if user input is invalid
    if(user_input.length() != 1) {
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
      freq->print_freq();
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

  return 0;
}
