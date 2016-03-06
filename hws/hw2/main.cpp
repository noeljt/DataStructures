#include <iostream>
#include "player.h"
#include "match.h"
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <set>
#include <iterator>
#include <sstream>


void parse_set(std::string &aSet, int &games_won, int &games_lost) 
{
	int i = aSet.find('-');
	games_won = std::atoi(aSet.substr(0,i).c_str());
	games_lost = std::atoi(aSet.substr(i+1,aSet.size()-i-1).c_str());
}


//turn file into vector of match classes
int parse_file(char* f_name, std::vector<Match> & match_results)
{
	std::ifstream myfile (f_name);

	if (!myfile.good())
	{
		std::cerr << "Can't open " << f_name << " to read.\n" << std::endl;
		return 1;
	}

	std::string winner;
	std::string loser;
	std::vector<std::string> sets;
	std::string set;
	std::string line;
	unsigned int i, n, n_sets;

	int games_won;
	int games_lost;
	int tie_break = 0;

	int w_gamesWon, w_gamesLost, w_setsWon, w_setsLost;
	int l_gamesWon, l_gamesLost, l_setsWon, l_setsLost;

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			//make sure values aren't carried over
			games_won = 0;
			games_lost = 0;
			w_gamesWon = 0;
			w_gamesLost = 0;
			w_setsWon = 0;
			w_setsLost = 0;
			l_setsWon = 0;
			l_setsLost = 0;
			l_gamesWon = 0;
			l_gamesLost = 0;
			if (line.find("  ") != std::string::npos)
			{
				i = line.find("  ");
				line.replace(i,1,"");
			}

			//get names of winner and loser
			i = line.find(' ');
			i = line.find(' ', (i+1));
			winner = line.substr(0,i);
			n = line.find(' ',(i+4));
			n = line.find(' ',(n+1));
			loser = line.substr((i+4),(n-i-4));
			//separate sets from names
			set = line.substr(n);
			n_sets = set.size()/4; //space + 2 numbers + '-'
			if (set.size()%4!=0)
			{
				tie_break = set.size()%4;
			}
			for (i=0;i<set.size();i+=4)
			{
				
				if (i+6>=(set.size()-1))
				{
					sets.push_back(set.substr(i+1));
				}
				else
				{
				sets.push_back(set.substr(i+1,3));
				}
			}
			//generate stats for the match from sets
			for (i=0;i<n_sets;i++)
			{
				parse_set(sets[i],games_won,games_lost);
				w_gamesWon += games_won;
				w_gamesLost += games_lost;
				l_gamesWon += games_lost;
				l_gamesLost += games_won;
				if (games_won>games_lost)
				{
					w_setsWon++;
					l_setsLost++;
				}
				else
				{
					w_setsLost++;
					l_setsWon++;
				}

			}
			//store match results in a match class
			match_results.push_back(Match(winner,loser,w_setsWon,w_setsLost,w_gamesWon,w_gamesLost,
									l_setsWon,l_setsLost,l_gamesWon,l_gamesLost));
			//clear sets vector
			sets.erase(sets.begin(),sets.end());
		}
	}
	return 0;
}

void create_players(std::vector<Player> & players, std::vector<Match> & match_results, unsigned int &longest)
{
	unsigned int i;
	unsigned int n;
	bool matchResult;
	std::set<std::string> player_names;
	//create a set of unique player names
	for (i=0;i<match_results.size();i++)
	{
		player_names.insert(match_results[i].getWinner());
		player_names.insert(match_results[i].getLoser());
	}
	//turn player names in vector of player classes
	for (std::set<std::string>::iterator it=player_names.begin();it!=player_names.end();it++)
	{
		players.push_back(Player(*it));
	}
	//find longest name for formatting grid
	for (i=0;i<players.size();i++)
	{
		if (players[i].getName().size()>longest)
		{
			longest = players[i].getName().size();
		}
	}
	//add match data to each player
	for (i=0;i<players.size();i++)
	{
		for (n=0;n<match_results.size();n++)
		{
			if (players[i].getName()==match_results[n].getWinner()) //if they won the match    
			{
				matchResult = true;
				players[i].addMatch(matchResult,
									match_results[n].getWinnerSetWins(),
								    match_results[n].getWinnerSetLosses(),
								    match_results[n].getWinnerGameWins(),
								    match_results[n].getWinnerGameLosses());
			}
			else if (players[i].getName()==match_results[n].getLoser()) //if they lost the match
			{
				matchResult = false;
				players[i].addMatch(matchResult,
									match_results[n].getLoserSetWins(),
								    match_results[n].getLoserSetLosses(),
								    match_results[n].getLoserGameWins(),
								    match_results[n].getLoserGameLosses());
			}
		}
	}

}

int save_file(std::vector<Player> & players, char* out_file, unsigned int &longest)
{
	std::ofstream file;
	file.open(out_file);
	if (!file.good())
	{
		std::cerr << "Can't open " << out_file << " to write. \n";
		return 1;
	}

	file << "MATCH STATISTICS\n"
		 << std::left << std::setw(longest) << "Player" 
		 << std::right << std::setw(5) << "W"
		 << std::right << std::setw(5) << "L"
		 << std::right << std::setw(13) << "percentage" << std::endl;
	sort(players.begin(), players.end(), compare_matches);
	for (unsigned int i = 0;i<players.size();i++)
	{
		file << players[i].printMatch(longest);
	}
	file << "\nGAME STATISTICS\n"
		 << std::left << std::setw(longest) << "Player" 
		 << std::right << std::setw(5) << "W"
		 << std::right << std::setw(5) << "L"
		 << std::right << std::setw(13) << "percentage" << std::endl;
	sort(players.begin(), players.end(), compare_games);
	for (unsigned int i = 0;i<players.size();i++)
	{
		file << players[i].printGame(longest);
	}
	file << "\nMOST WASTED EFFORT\n"
	     << std::left << std::setw(longest) << "Player" 
		 << std::right << std::setw(8) << "Games"
		 << std::right << std::setw(9) << "Matches"
		 << std::right << std::setw(9) << "Ratio" << std::endl;
	file << std::right << std::setw(longest+8) << "Played"
		 << std::right << std::setw(9) << "Won" << std::endl;
	sort(players.begin(), players.end(), compare_effort);
	for (unsigned int i = 0;i<players.size();i++)
	{
		file << players[i].printEffort(longest);
	}
	file.close();
	return 0;

}


int main(int argc, char* argv[])
{
	char* in_file = argv[1];
	char* out_file = argv[2];
	unsigned int longest = 16;
	std::vector<Match> match_results;
	std::vector<Player> players;
	parse_file(in_file, match_results);
	create_players(players, match_results, longest);
	save_file(players, out_file, longest);
	return 0;
}