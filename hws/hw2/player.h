//File: player.h
//Purpose: Header file with the declaration of the (tennis) player class.

#ifndef __player_h_
#define __player_h_

#include <string>

class Player
{
public:
	Player(std::string aName);

	//ACCESSORS
	std::string getName() const;
	int getMatchesWon() const;
	int getMatchesLost() const;
	int getSetsWon() const;
	int getSetsLost() const;
	int getWins() const;
	int getLosses() const;

	//Modifiers
	void addMatch(bool match_outcome, int setsWon_, int setsLost_, int gamesWon_, int gamesLost_);

	//Other Member Functions
	std::string printMatch(unsigned int &longest) const;
	std::string printEffort(unsigned int &longest) const;
	std::string printGame(unsigned int &longest) const;
	float matchPercentage() const;
	float effort() const;
	float gamePercentage() const;

private:
	std::string name;
	int matchesWon;
	int matchesLost;
	int setsWon;
	int setsLost;
	int wins;
	int losses;

};

bool compare_matches(const Player & p1, const Player & p2);
bool compare_effort(const Player & p1, const Player & p2);
bool compare_games(const Player & p1, const Player & p2);
#endif