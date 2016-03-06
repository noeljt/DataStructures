//File: match.h
//Purpose: Header File with declaration of the (tennis) match class.

#ifndef __match_h_
#define __match_h_

#include <string>

class Match
{
public:
	Match(std::string playerW, std::string playerL,
		  int w_setWins, int w_setLosses, int w_gameWins, int w_gameLosses,
		  int l_setWins, int l_setLosses, int l_gameWins, int l_gameLosses);

	//ACCESSORS
	std::string getWinner() const;
	std::string getLoser() const;
	int getWinnerSetWins() const;
	int getWinnerSetLosses() const;
	int getWinnerGameWins() const;
	int getWinnerGameLosses() const;
	int getLoserSetWins() const;
	int getLoserSetLosses() const;
	int getLoserGameWins() const;
	int getLoserGameLosses() const;

private:
	std::string winner;
	std::string loser;
	int winnerSetWins;
	int winnerSetLosses;
	int winnerGameWins;
	int winnerGameLosses;
	int loserSetWins;
	int loserSetLosses;
	int loserGameWins;
	int loserGameLosses;
};

#endif