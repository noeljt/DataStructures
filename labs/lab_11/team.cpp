#include <cassert>
#include <list>
#include "superhero.h"
#include "team.h"
#include <algorithm>

bool isvowel(char c) {
  if (!isalpha(c)) return false;
  char c2 = tolower(c);
  return (c2 == 'a' || c2 == 'e' || c2 == 'i' || c2 == 'o' || c2 == 'u');
}

bool isconsonant(char c) {
  return (isalpha(c) && !isvowel(c));
}

std::string Team::getName() const {
  if (superheroes.size() == 0) 
    return "";
  std::string answer;
  std::list<Superhero>::const_iterator itr;
  for (itr = superheroes.begin(); itr != superheroes.end(); itr++) {
    char first_consonant = ' ';
    char first_vowel = ' ';
    std::string true_identity = itr->getTrueIdentity();
    for (int j = 0; j < true_identity.size(); j++) {
      if (first_consonant == ' ' && isconsonant(true_identity[j]))
        first_consonant = tolower(true_identity[j]);
      if (first_vowel == ' ' && isvowel(true_identity[j]))
        first_vowel = tolower(true_identity[j]);
    }
    answer.push_back(first_consonant);
    answer.push_back(first_vowel);
  }

  answer[0] = toupper(answer[0]);
  return answer;
}

Team& Team::operator+=(const Superhero & a) {
  superheroes.push_back(a);
  return *this;
}
Team& Team::operator-=(const Superhero & a) {
  std::list<Superhero>::iterator it = std::find(superheroes.begin(),superheroes.end(),a);
  if (it!=superheroes.end()) {
    superheroes.erase(it);
    return *this;
  }
  return *this;
}

Team operator+(const Team & a, const Team & b) {
  Team t;
  std::list<Superhero>::const_iterator it = a.superheroes.begin();
  for (;it!=a.superheroes.end();it++) {
    t.superheroes.push_back(*it);
  }
  for (it=b.superheroes.begin();it!=b.superheroes.end();it++) {
    t.superheroes.push_back(*it);
  }
  return t;
}
Team operator+(const Team &a, const Superhero &b) {
  Team t;
  std::list<Superhero>::const_iterator it = a.superheroes.begin();
  for (;it!=a.superheroes.end();it++) {
    t.superheroes.push_back(*it);
  }
  t.superheroes.push_back(b);
  return t;
}

Team operator+(const Superhero & a, const Superhero & b) {
  Team t;
  t+=a;
  t+=b;
  return t;
}