#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

typedef std::unordered_map<std::string,int> wf;


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
void LoadSampleText(wf &data, const std::string &filename) {
  // open the file stream
  std::ifstream istr(filename.c_str());
  if (!istr) { 
    std::cerr << "ERROR cannot open file: " << filename << std::endl; 
    exit(1);
  } 
  std::string word;
  std::string next_word;
  std::ifstream istr_2(filename.c_str());
  ReadNextWord(istr_2,word);
	while (ReadNextWord(istr,word)) {
	  ReadNextWord(istr_2,next_word);
	  if (word == "\"") {
	    continue;
	  }
	  else {
	    ++data[word];
	  }
	}
}

int main(int argc, char* argv[]) {
	if (argc!=2) {
		std::cout << "Invalid arguments" << std::endl;
		return 1;
	}
	wf data;
	std::string filename(argv[1]);
	LoadSampleText(data,filename);
	std::cout << "Unique Words: " << data.size() << std::endl;
}