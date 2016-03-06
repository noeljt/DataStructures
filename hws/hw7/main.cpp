// -----------------------------------------------------------------
// HOMEWORK 7 WORD FREQUENCY MAPS
//
// You may use all of, some of, or none of the provided code below.
// You may edit it as you like (provided you follow the homework
// instructions).
// -----------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <cstdlib>
#include <cassert>

#include "mtrand.h"



// ASSIGNMENT: FILL IN YOUR OWN MAP STRUCTURE
typedef  std::map<std::string,std::map<std::string,std::map<std::string,int> > > MY_3_MAP;
typedef  std::map<std::string,std::map<std::string,std::map<std::string,int> > >::iterator it_3;
typedef  std::map<std::string,std::map<std::string,int> >  MY_MAP;
typedef  std::map<std::string,std::map<std::string,int> >::iterator it_1;
typedef  std::map<std::string,int>::iterator it_2;




// Custom helper function that reads the input stream looking for
// double quotes (a special case delimiter needed below), and white
// space.  Contiguous blocks of alphabetic characters are lowercased &
// packed into the word.
bool ReadNextWord(std::istream &istr, std::string &word) {
  char c;
  word.clear();
  while (istr) {
    // just "peek" at the next character in the stream
    c = istr.peek();
    if (isspace(c)) {
      // skip whitespace before a word starts
      istr.get(c);
      if (word != "") {
	// break words at whitespace
	return true;
      }
    } else if (c == '"') {
      // double quotes are a delimiter and a special "word"
      if (word == "") {
	istr.get(c);
	word.push_back(c);
      }
      return true;
    } else if (isalpha(c)) {
      // this a an alphabetic word character
      istr.get(c);
      word.push_back(tolower(c));
    } else {
      // ignore this character (probably punctuation)
      istr.get(c);
    }
  }
  return false;
}


// Custom helper function that reads the input stream looking a
// sequence of words inside a pair of double quotes.  The words are
// separated by white space, but the double quotes might not have
// space between them and the neighboring word.  Punctuation is
// ignored and words are lowercased.
std::vector<std::string> ReadQuotedWords(std::istream &istr) {
  // returns A STRING
  std::vector<std::string> answer;
  std::string word;
  bool open_quote = false;
  while (ReadNextWord(istr,word)) {
    if (word == "\"") {
      if (open_quote == false) { open_quote=true; }
      else { break; }
    } else {
      // add each word to the string
      answer.push_back(word);
    }
  }
  return answer;
}



// Loads the sample text from the file, storing it in the map data
// structure Window specifies the width of the context (>= 2) of the
// sequencing stored in the map.  parse_method is a placeholder for
// optional extra credit extensions that use punctuation.
void LoadSampleText(MY_MAP &data, const std::string &filename, int window, const std::string &parse_method) {
  // open the file stream
  std::ifstream istr(filename.c_str());
  if (!istr) { 
    std::cerr << "ERROR cannot open file: " << filename << std::endl; 
    exit(1);
  } 
  // verify the window parameter is appropriate
  if (window < 2) {
    std::cerr << "ERROR window size must be >= 2:" << window << std::endl;
  }
  // verify that the parse method is appropriate
  bool ignore_punctuation = false;
  if (parse_method == "ignore_punctuation") {
    ignore_punctuation = true;
  } else {
    std::cerr << "ERROR unknown parse method: " << parse_method << std::endl;
    exit(1);
  }



  //
  std::string word;
  std::string next_word;
  std::ifstream istr_2(filename.c_str());
  ReadNextWord(istr_2,word);
  if (ignore_punctuation==true and window==2) {
    while (ReadNextWord(istr,word)) {
      ReadNextWord(istr_2,next_word);
      if (word == "\"") {
        continue;
      }
      else {
        ++data[word][next_word];
      }
    }
  }
  //
}
void LoadSampleText(MY_3_MAP &data, const std::string &filename, int window, const std::string &parse_method) {
  // open the file stream
  std::ifstream istr(filename.c_str());
  if (!istr) { 
    std::cerr << "ERROR cannot open file: " << filename << std::endl; 
    exit(1);
  } 
  // verify the window parameter is appropriate
  if (window < 2) {
    std::cerr << "ERROR window size must be >= 2:" << window << std::endl;
  }
  // verify that the parse method is appropriate
  bool ignore_punctuation = false;
  if (parse_method == "ignore_punctuation") {
    ignore_punctuation = true;
  } else {
    std::cerr << "ERROR unknown parse method: " << parse_method << std::endl;
    exit(1);
  }



  //
  std::string word;
  std::string next_word;
  std::ifstream istr_2(filename.c_str());
  ReadNextWord(istr_2,word);
  if (ignore_punctuation==true and window==3) {
    std::string third_word;
    std::ifstream istr_3(filename.c_str());
    ReadNextWord(istr_3,third_word);
    ReadNextWord(istr_3,third_word);
    while (ReadNextWord(istr,word)) {
      ReadNextWord(istr_2,next_word);
      ReadNextWord(istr_3,third_word);
      if (word == "\"") {
        continue;
      }
      else {
        ++data[word][next_word][third_word];
      }
    }
  }
  //
}



int main () {

  // ASSIGNMENT: THE MAIN DATA STRUCTURE
  MY_MAP data;
  MY_3_MAP data_3;
  // Parse each command
  std::string command;    
  std::string filename;
  int window;
  while (std::cin >> command) {

    // load the sample text file
    if (command == "load") {
      std::string parse_method;
      std::cin >> filename >> window >> parse_method;      

      // pretty straightforward... load the file
      if (window==2) {
        LoadSampleText(data, filename, window, parse_method);
      }
      else if (window==3) {
        MY_3_MAP data;
        LoadSampleText(data_3,filename,window,parse_method);
      }
      std::cout << "Loaded " << filename << " with window = " << window << " and parse method = "
                << parse_method << std::endl;
    } 

    // print the portion of the map structure with the choices for the
    // next word given a particular sequence.
    else if (command == "print") {
      std::cout<<std::endl;
      std::vector<std::string> sentence = ReadQuotedWords(std::cin);
      int total;

      //
      if (window==2) {
        it_1 it = data.find(sentence[0]); //find correct word in data
        if (it!=data.end()) {
          total=0;
          for (it_2 iter = it->second.begin();iter!=it->second.end();iter++) {
            total+=iter->second; //total occurences
          }
          std::cout << sentence[0] << " (" << total << ")" << std::endl;
          for (it_2 iter = it->second.begin();iter!=it->second.end();iter++) { //print following words
            if (iter->first=="") continue;
            std::cout << sentence[0] << " " << iter->first << " (" << iter->second << ")" << std::endl;
          }
        }
        else {
          std::cout << "Word not found." << std::endl;
        }
      }
      else if (window==3) {
        int total_2;
        if (sentence.size()==1) {
          it_3 it = data_3.find(sentence[0]); //find correct word in data
          if (it!=data_3.end()) {
            total=0;
            for (it_1 iter = it->second.begin();iter!=it->second.end();iter++) { //find oc
              for (it_2 iterator = iter->second.begin();iterator!=iter->second.end();iterator++) {
                total+=iterator->second;
              }
            }
            std::cout << sentence[0] << " (" << total << ")" << std::endl;
            for (it_1 iter = it->second.begin();iter!=it->second.end();iter++) { //print following words
              if (iter->first=="") continue;
              total_2=0;
              for (it_2 iterator = iter->second.begin();iterator!=iter->second.end();iterator++) {
                total_2+=iterator->second;
              }
              std::cout << sentence[0] << " " << iter->first << " (" << total_2 << ")" << std::endl;
            }
          }
          else {
            std::cout << "Word not found." << std::endl;
          }
        }
          else if (sentence.size()==2) {
          it_3 it = data_3.find(sentence[0]);
          if (it!=data_3.end()) {
            it_1 iter= it->second.find(sentence[1]);
            if (iter!=it->second.end()) {
              total=0;
              for (it_2 iterator = iter->second.begin();iterator!=iter->second.end();iterator++) {
                total+=iterator->second;
              }
              std::cout << sentence[0] << " " << sentence[1] << " (" << total << ")" << std::endl;
              for (it_2 iterator = iter->second.begin();iterator!=iter->second.end();iterator++) {
                if (iter->first=="") continue;
                std::cout << sentence[0] << " " << sentence[1] << " " << iterator->first
                          << " (" << iterator->second << ")" << std::endl;
              }
            }
            else {
              std::cout << "Word combination not found." << std::endl;
            }
          }
          else {
            std::cout << "First word not found." << std::endl;
          }
        }
      }
    }

    // generate the specified number of words 
    else if (command == "generate") {
      std::cout<<std::endl;
      std::vector<std::string> sentence = ReadQuotedWords(std::cin);
      // how many additional words to generate
      int length;
      std::cin >> length;
      std::string selection_method;
      std::cin >> selection_method;
      bool random_flag;
      if (selection_method == "random") {
	random_flag = true;
      } else {
	assert (selection_method == "most_common");
	random_flag = false;
      }


      //
      int max;
      if (random_flag==false) {
        if (window==2) {
          it_2 it_max;
          std::cout << sentence[0];
          for (int i=0;i<length;i++) {
            max =0;
            it_1 it = data.find(sentence[0]);
            if (it!=data.end()) {
              for (it_2 iter = it->second.begin();iter!=it->second.end();iter++) {
                if (iter->second>max) { //find most frequent word
                  max = iter->second;
                  it_max = iter;
                }
              }
              sentence[0] = it_max->first; //store for next loop
              std::cout << " " << sentence[0]; //print it
            }
          }
          std::cout<<std::endl; //because it looks nicer
        }
        else if (window==3) {
          if (sentence.size()==1) {
            int total;
            it_1 it_max_1;
            it_3 it = data_3.find(sentence[0]);
            if (it!=data_3.end()) {
              std::cout << sentence[0];
              max=0;
              for (it_1 iter = it->second.begin();iter!=it->second.end();iter++) {
                total=0;
                for (it_2 iterator=iter->second.begin();iterator!=iter->second.end();iterator++) {
                  total+=iterator->second;
                }
                if (total>max) {
                  max = total;
                  it_max_1 = iter;
                }
              }
              sentence.push_back(it_max_1->first);
              std::cout << " " << sentence[1];
              it_2 it_max;
              for (int i=1;i<length;i++) {
                max=0;
                it_3 it = data_3.find(sentence[0]);
                if (it!=data_3.end()) {
                  it_1 iter = it->second.find(sentence[1]);
                  if (iter!=it->second.end()) {
                    for (it_2 iterator = iter->second.begin();iterator!=iter->second.end();iterator++) {
                      if (iterator->second>max) {
                        max = iterator->second;
                        it_max = iterator;
                      }
                    }
                    sentence[0] = sentence[1];
                    sentence[1] = it_max->first;
                    std::cout << " " << sentence[1];
                  }
                }
              }
              std::cout<<std::endl;             
            }
          }
          else if (sentence.size()==2) {
            it_2 it_max;
            std::cout << sentence[0] << " " << sentence[1];
            for (int i=0;i<length;i++) {
              max=0;
              it_3 it = data_3.find(sentence[0]);
              if (it!=data_3.end()) {
                it_1 iter = it->second.find(sentence[1]);
                if (iter!=it->second.end()) {
                  for (it_2 iterator = iter->second.begin();iterator!=iter->second.end();iterator++) {
                    if (iterator->second>max) {
                      max = iterator->second;
                      it_max = iterator;
                    }
                  }
                  sentence[0] = sentence[1];
                  sentence[1] = it_max->first;
                  std::cout << " " << sentence[1];
                }
              }
            }
            std::cout<<std::endl;
          }
        }
      }
      else {
        if (window==2) {
          std::cout << sentence[0];
          std::vector<std::string> chance;
          MTRand mtrand;
          for (int i=0;i<length;i++) {
            it_1 it = data.find(sentence[0]);
            if (it!=data.end()) {
              for (it_2 iter = it->second.begin();iter!=it->second.end();iter++) {
                for (int x=0;x<iter->second;x++) {
                  chance.push_back(iter->first);
                }
              }
              int n = mtrand.randInt(chance.size()-1);
              sentence[0] = chance[n]; //store for next loop
              std::cout << " " << sentence[0]; //print it
              chance.clear();
            }
          }
          std::cout<<std::endl; //because it looks nicer
        }
        else if (window==3) {
          if (sentence.size()==1) {
            int total;
            std::cout << sentence[0];
            std::vector<std::string> chance;
            MTRand mtrand;
            it_3 it = data_3.find(sentence[0]);
            if (it!=data_3.end()) {
              for (it_1 iter = it->second.begin();iter!=it->second.end();iter++) {
                total =0;
                for (it_2 iterator=iter->second.begin();iterator!=iter->second.end();iterator++) {
                  total+=iterator->second;
                }
                for (int i=0;i<total;i++) {
                  chance.push_back(iter->first);
                }
              }
              int n = mtrand.randInt(chance.size()-1);
              sentence.push_back(chance[n]);
              std::cout << " " << sentence[1];
              chance.clear();
              for (int i=1;i<length;i++) {
                it = data_3.find(sentence[0]);
                if (it!=data_3.end()) {
                  it_1 iter = it->second.find(sentence[1]);
                  if (iter!=it->second.end()) {
                    for (it_2 iterator=iter->second.begin();iterator!=iter->second.end();iterator++) {
                      for (int x=0;x<iterator->second;x++) {
                        chance.push_back(iterator->first);
                      }
                    }
                    n = mtrand.randInt(chance.size()-1);
                    sentence[0] = sentence[1];
                    sentence[1] = chance[n];
                    std::cout << " " << sentence[1];
                    chance.clear();
                  }
                }
              }
              std::cout<<std::endl;
              }          
          }
          else if (sentence.size()==2) {
            std::cout << sentence[0] << " " << sentence[1];
            std::vector<std::string> chance;
            MTRand mtrand;
            for (int i=0;i<length;i++) {
              it_3 it = data_3.find(sentence[0]);
              if (it!=data_3.end()) {
                it_1 iter = it->second.find(sentence[1]);
                if (iter!=it->second.end()) {
                  for (it_2 iterator=iter->second.begin();iterator!=iter->second.end();iterator++) {
                    for (int x=0;x<iterator->second;x++) {
                      chance.push_back(iterator->first);
                    }
                  }
                  int n = mtrand.randInt(chance.size()-1);
                  sentence[0] = sentence[1];
                  sentence[1] = chance[n];
                  std::cout << " " << sentence[1];
                }
              }
            }
            std::cout<<std::endl;
          }
        }
      }
    } else if (command == "quit") {
      std::cout<<std::endl;
      break;
    } else {
      std::cout << "WARNING: Unknown command: " << command << std::endl;
    }
  }
}
