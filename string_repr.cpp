#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

struct table {
  int ascii;
  int frequency; //value;
};

struct library {
  int ascii;
  string bit_string;
};

struct node {
  node * left;
  node * right;
  int frequency;
  int bit_value;
  int ascii;
  string bit_string;
};

//function to sort table<vector>
bool compare_table(const table& a, const table& b) {
    return a.frequency < b.frequency;
}


class String_repr {
private:
  vector<table> freq;
  vector<library> lib;
  vector<node*> trees;
  int table_size;
  double compression;
  int tree_size;
  node * root;

  void set_bit_value_private(node * root) {
    if(root != NULL) {
      if(root->left != NULL) {
	root->left->bit_value = 0;
	set_bit_value_private(root->left);
      }
      if(root->right != NULL) {
	root->right->bit_value = 1;
	set_bit_value_private(root->right);
      } 
    }
  }

  void build_bit_strings_private(node * root) {
    string s;
    int i;

    std::ostringstream ss;
    
    if(root != NULL) {
      if(root->left != NULL) {
	i = root->left->bit_value;
	ss << i;
	s = ss.str();
	root->left->bit_string = root->bit_string;
	root->left->bit_string += s; 
	build_bit_strings_private(root->left);
      }
      
      if(root->ascii != -1) {
        library l = {root->ascii,root->bit_string};
	lib.push_back(l);
      }
      
      if(root->right != NULL) {
	i = root->right->bit_value;
	ss << i;
	s = ss.str();
	root->right->bit_string = root->bit_string;
	root->right->bit_string += s; 
	build_bit_strings_private(root->right);
      }
    }
    else {
      cout << "Tree is empty\n";
    }
  }
  
public:
  String_repr();
  String_repr(vector<table> t, int size);

  double get_compression() {
    return compression;
  }

  void init_nodes() {
    int i;
    node * n;
    
    for(i = 0; i < table_size; i++) {
      n = new node;
      n->left = NULL;
      n->right = NULL;
      n->frequency = freq[i].frequency;
      n->bit_value = 0;
      n->ascii = freq[i].ascii;
      trees.push_back(n);
    }
    tree_size = trees.size();
  }

  void build_tree() {
    int vector_size = tree_size;
    int sum;
    int i;
    node * n;

    while(vector_size > 1) {
      sum = trees[0]->frequency + trees[1]->frequency;
      n = new node;

      if((trees[0]->ascii == -1) && (trees[1]->ascii == -1)) {
	n->left = trees[1];
	n->right = trees[0];
      }
      else if(trees[0]->ascii == -1) {
	n->left = trees[1];
	n->right = trees[0];
      }
      else if(trees[1]->ascii == -1) {
	n->left = trees[0];
	n->right = trees[1];
      }
      else {
	n->left = trees[1];
	n->right = trees[0];
      }

      n->frequency = sum;
      n->bit_value = 0;
      n->ascii = -1;

      trees.erase(trees.begin(),trees.begin()+2);

      vector_size--;

      i = 0;
      while((trees[i]->frequency) < (n->frequency)) {
	i++;
	if(i >= vector_size)
	  break;
      }
      

      if(i >= vector_size) 
	trees.push_back(n);
      else
	trees.insert(trees.begin()+i,n);
      
      root = n;
    }    
  }

  void makeCode() {
    int i;
    ofstream library_file;
    
    library_file.open("library.txt");

    for(i = 0; i < table_size; i++) {
      library_file << lib[i].ascii << " " << lib[i].bit_string << endl;
    }

    library_file.close();
  }

  string encode(string s) {
    int i,j;
    int ascii;
    int length = s.length();
    double uncompressed = length * 8;
    double compressed;
    string bit_string;
    double comp_ratio;

    for(i = 0; i < length; i++) {
      ascii = (int)s.at(i);
      for(j = 0; j < table_size; j++) {
	if(ascii == lib[j].ascii) {
	  bit_string += lib[j].bit_string;
	  break;
	}
      }
    }

   compressed = bit_string.length();
   comp_ratio = uncompressed/compressed;

    compression = comp_ratio;
    
    return bit_string;
  }

  string decode(string s) {
    string substr;
    string decoded;
    int i; 
    int delim;
    char c;

    delim = s.find(" ");

    if(delim >= 0) {
      cout << "Has spaces\n";
      while((delim = s.find(" ")) != -1) {
	substr = s.substr(0, delim);
	cout << "substr: " << substr << endl;
	cout << "Delim: " << delim << endl;
	for(i = 0; i < table_size; i++) {
	  if(substr == lib[i].bit_string) {
	    c = lib[i].ascii;
	    decoded += c;
	    break;
	  }
	}
	s = s.substr(delim+1);
      }
      for(i = 0; i < table_size; i++) {
	if(substr == lib[i].bit_string) {
	  c = lib[i].ascii;
	  decoded += c;
	  break;
	}
      }
    }
    else {
      cout << "Does not have spaces\n";
      for(i = 0; i < table_size; i++) {
	if(s == lib[i].bit_string) {
	  c = lib[i].ascii;
	  decoded += c;
	  break;
	}
      }
    }
    return decoded;
  }
  
  void set_bit_value() {
    set_bit_value_private(root);
  }

  void build_bit_strings() {
    build_bit_strings_private(root);
  }
};

String_repr::String_repr(vector<table> t, int size) {
  freq = t;
  table_size = size;
  root = NULL;
}

class Freq_table {
private:  
  int freq[256];
  vector<table> freq_resized;
  int table_size;

public:
  Freq_table();
  Freq_table(string s);

  //function that prppints out freq vector
  void print_freq() {
    int i;
    char c;

    for(i = 0; i < table_size; i++) {
      c = freq_resized[i].ascii;
      cout << "Freq of " << c << " : " << freq_resized[i].frequency << endl; 
    }
  }

  int get_table_size() {
    return table_size;
  }

  //returns the freq_resized vector
  vector<table> get_freq() {
    return freq_resized;
  }
  
  /*
  void delete_freq_resized() {
    delete [] freq_resized;
    }*/
};

//initializer for Freq_table
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
  string output;
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
  String_repr* repr = new String_repr(freq->get_freq(), freq->get_table_size());

  repr->init_nodes();

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
    cin.ignore();
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

    repr->build_tree();
    repr->set_bit_value();
    repr->build_bit_strings();
    
    switch (user_case) {
    case 1:
      repr->makeCode();
      still_running = false;
      break;

    case 2:
      freq->print_freq();
      still_running = false;
      break;
      
    case 3:
      cout << "Please enter the text to be encoded: \n";
      //cin.clear();
      cin >> user_input;
      cin.ignore();
      
      output = repr->encode(user_input);
      cout << "The encoded text is: " << output << endl;
      cout << "The compression ratio is: " << repr->get_compression() << endl;
      still_running = false;
      break;
      
    case 4:
      cout << "Please enter an encoded message:\n";
      //cin >> noskipws >> user_input;
      //cin.ignore();
      cin.clear();
      std::getline(std::cin, user_input);
      output = repr->decode(user_input);
      cout << "The decoded text is: " << output << endl;
      still_running = false;
      break;
      
    default:
      cout << "Invalid input.  Please enter a numerical value 1-4\n";
      break;
    }
  
  }

  return 0;
}
