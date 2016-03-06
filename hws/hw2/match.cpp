//File: match.cpp
//Purpose: (tennis) match class implementation

#include <iostream>
#include "match.h"
#include <string>

Match::Match(std::string playerW, std::string playerL,
			 int w_setWins, int w_setLosses, int w_gameWins, int w_gameLosses,
			 int l_setWins, int l_setLosses, int l_gameWins, int l_gameLosses)
{
	winner = playerW;
	loser = playerL;
	winnerSetWins = w_setWins;
	winnerSetLosses = w_setLosses;
	winnerGameWins = w_gameWins;
	winnerGameLosses = w_gameLosses;
	loserSetWins = l_setWins;
	loserSetLosses = l_setLosses;
	loserGameWins = l_gameWins;
	loserGameLosses = l_gameLosses;
}

std::string Match::getWinner() const
{
	return winner;
}
std::string Match::getLoser() const
{
	return loser;
}
int Match::getWinnerSetWins() const
{
	return winnerSetWins;
}
int Match::getWinnerSetLosses() const
{
	return winnerSetLosses;
}
int Match::getWinnerGameWins() const
{
	return winnerGameWins;
}
int Match::getWinnerGameLosses() const
{
	return winnerGameLosses;
}
int Match::getLoserSetWins() const
{
	return loserSetWins;
}
int Match::getLoserSetLosses() const
{
	return loserSetLosses;
}
int Match::getLoserGameWins() const
{
	return loserGameWins;
}
int Match::getLoserGameLosses() const
{
	return loserGameLosses;
}