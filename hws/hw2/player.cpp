//File: player.cpp
//Purpose: (tennis) player class implementaion
#include <iostream>
#include "player.h"
#include <string>
#include <iomanip>
#include <sstream>

Player::Player(std::string aName) //constructor
{
	name = aName;
	matchesWon = 0;
	matchesLost = 0;
	setsWon = 0;
	setsLost = 0;
	wins = 0;
	losses = 0;
}

std::string Player::getName() const
{
	return name;
}
int Player::getMatchesWon() const
{
	return matchesWon;
}
int Player::getMatchesLost() const
{
	return matchesLost;
}
int Player::getSetsWon() const
{
	return setsWon;
}
int Player::getSetsLost() const
{
	return setsLost;
}
int Player::getWins() const
{
	return wins;
}
int Player::getLosses() const
{
	return losses;
}

void Player::addMatch(bool match_outcome, int setsWon_, int setsLost_, int gamesWon_, int gamesLost_)
{
	if (match_outcome==true)
	{
		matchesWon++;
	}
	else if (match_outcome==false)
	{
		matchesLost++;
	}
	setsWon += setsWon_;
	setsLost += setsLost_;
	wins += gamesWon_;
	losses += gamesLost_;
}

std::string Player::printMatch(unsigned int &longest) const
{
	std::stringstream buffer;
	buffer << std::left << std::setw(longest) << name << std::right << std::setw(5) 
		   << matchesWon << std::setw(5) << matchesLost << std::setw(13) 
		   << std::fixed << std::setprecision(3) << ((matchesWon/((float)matchesWon+matchesLost))) 
		   << std::endl;
	std::string str_out = buffer.str();
	return str_out;
}
std::string Player::printEffort(unsigned int &longest) const
{
	std::stringstream buffer;
	buffer << std::left << std::setw(longest) << name << std::right << std::setw(8) 
		   << (wins+losses) << std::setw(8) << matchesWon << std::setw(10) 
		   << std::fixed << std::setprecision(3) << (effort()) 
		   << std::endl;
	std::string str_out = buffer.str();
	return str_out;
}

std::string Player::printGame(unsigned int &longest) const
{
	std::stringstream buffer;
	buffer << std::left << std::setw(longest) << name << std::right << std::setw(5) 
		   << wins << std::setw(5) << losses << std::setw(13) 
		   << std::fixed << std::setprecision(3) << ((wins/((float)wins+losses))) 
		   << std::endl;
	std::string str_out = buffer.str();
	return str_out;
}
float Player::matchPercentage() const
{
	return (matchesWon/((float)matchesWon+matchesLost));
}
float Player::effort() const
{
	return (matchesWon/((float)(wins+losses)));
}
float Player::gamePercentage() const
{
	return (wins/((float)wins+losses));
}

bool compare_matches(const Player &p1, const Player &p2)
{
	if (p1.matchPercentage()==p2.matchPercentage())
	{
		int i = p1.getName().find(' ');
		int n = p2.getName().find(' ');
		return p1.getName().substr(i)<p2.getName().substr(n);
	}
	else
	{
		return p1.matchPercentage()>p2.matchPercentage();
	}
}
bool compare_effort(const Player &p1, const Player &p2)
{
	if (p1.effort()==p2.effort())
	{
		if ((p1.getWins()+p1.getLosses())==(p2.getWins()+p2.getLosses()))
		{
			int i = p1.getName().find(' ');
			int n = p2.getName().find(' ');
			return p1.getName().substr(i)<p2.getName().substr(n);
		}
		else
		{
			return (p1.getWins()+p1.getLosses())>(p2.getWins()+p2.getLosses());
		}
	}
	else
	{
		return p1.effort()<p2.effort();
	}
}
bool compare_games(const Player &p1, const Player &p2)
{
	if (p1.gamePercentage()==p2.gamePercentage())
	{
		int i = p1.getName().find(' ');
		int n = p2.getName().find(' ');
		return p1.getName().substr(i)<p2.getName().substr(n);
	}
	else
	{
		return p1.gamePercentage()>p2.gamePercentage();
	}
}