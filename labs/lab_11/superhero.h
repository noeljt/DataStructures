#include <string>
#include <iostream>
#include <vector>

#ifndef superhero_h_
#define superhero_h_
class Superhero {
public:
	
	Superhero(std::string name_, std::string identity_, std::string power_) : name(name_), identity(identity_), power(power_), good(1)	{}
	// ACCESSORS
	const std::string getName()	    {return name;}
	const std::string getPower()	{return power;}
	const bool isGood()	            {return (good == 1);}
	
	
	const bool operator==(const std::string otherName)	{return (identity == otherName);}
	const bool operator==(const Superhero & other) 	    {return (name==other.name);     }
	const bool operator!=(const std::string otherName)	{return (identity != otherName);}
	Superhero &operator-()	{
		good = (-1)*(good);
		return *this;
	}
	bool operator>(Superhero const& rhs)	{
		if (power == "Fire")	{
			if (rhs.power == "Wood")	{
				return true;
			}else if (rhs.power == "Water")	{
				return false;
			}else if (rhs.power == "Laser")	{
				return false;
			}else if (rhs.power == "Speed")	{
				return false;
			}else if (rhs.power == "Flying")	{
				return true;
			}else if (rhs.power == "Invisible")	{
				return true;
			}else if (rhs.power == "Flexible")	{
				return true;
			}
		}else if (power == "Wood")	{
			if (rhs.power == "Fire")	{
				return false;
			}else if (rhs.power == "Water")	{
				return true;
			}else if (rhs.power == "Laser")	{
				return false;
			}else if (rhs.power == "Speed")	{
				return true;
			}else if (rhs.power == "Flying")	{
				return false;
			}else if (rhs.power == "Invisible")	{
				return true;
			}else if (rhs.power == "Flexible")	{
				return false;
			}
		}else if (power == "Water")	{
			if (rhs.power == "Fire")	{
				return true;
			}else if (rhs.power == "Wood")	{
				return false;
			}else if (rhs.power == "Laser")	{
				return true;
			}else if (rhs.power == "Speed")	{
				return false;
			}else if (rhs.power == "Flying")	{
				return false;
			}else if (rhs.power == "Invisible")	{
				return true;
			}else if (rhs.power == "Flexible")	{
				return false;
			}
		}else if (power == "Laser")	{
			if (rhs.power == "Fire")	{
				return true;
			}else if (rhs.power == "Wood")	{
				return true;
			}else if (rhs.power == "Water")	{
				return false;
			}else if (rhs.power == "Speed")	{
				return true;
			}else if (rhs.power == "Flying")	{
				return true;
			}else if (rhs.power == "Invisible")	{
				return false;
			}else if (rhs.power == "Flexible")	{
				return false;
			}
		}else if (power == "Speed")	{
			if (rhs.power == "Fire")	{
				return false;
			}else if (rhs.power == "Wood")	{
				return false;
			}else if (rhs.power == "Water")	{
				return true;
			}else if (rhs.power == "Laser")	{
				return true;
			}else if (rhs.power == "Flying")	{
				return false;
			}else if (rhs.power == "Invisible")	{
				return true;
			}else if (rhs.power == "Flexible")	{
				return false;
			}
		}else if (power == "Flying")	{
			if (rhs.power == "Fire")	{
				return false;
			}else if (rhs.power == "Wood")	{
				return true;
			}else if (rhs.power == "Water")	{
				return false;
			}else if (rhs.power == "Speed")	{
				return true;
			}else if (rhs.power == "Flying")	{
				return true;
			}else if (rhs.power == "Invisible")	{
				return false;
			}else if (rhs.power == "Flexible")	{
				return false;
			}
		}else if (power == "Invisible")	{
			if (rhs.power == "Fire")	{
				return false;
			}else if (rhs.power == "Wood")	{
				return true;
			}else if (rhs.power == "Water")	{
				return false;
			}else if (rhs.power == "Speed")	{
				return true;
			}else if (rhs.power == "Flying")	{
				return true;
			}else if (rhs.power == "Invisible")	{
				return false;
			}else if (rhs.power == "Flexible")	{
				return false;
			}
		}else if (power == "Flexible")	{
			if (rhs.power == "Fire")	{
				return false;
			}else if (rhs.power == "Wood")	{
				return true;
			}else if (rhs.power == "Water")	{
				return false;
			}else if (rhs.power == "Speed")	{
				return true;
			}else if (rhs.power == "Flying")	{
				return true;
			}else if (rhs.power == "Invisible")	{
				return false;
			}else if (rhs.power == "Flexible")	{
				return false;
			}
		}
		return false;
	}
	friend class Team;
	
	
private:
	
	std::string getTrueIdentity() const	{
		return (*this).identity;
	}	
	
	const std::string name;
	const std::string identity;
	const std::string power;
	int good;
};

inline std::ostream& operator<< (std::ostream & ostr, Superhero & c)	{
	std::string allegience;
	if (c.isGood()) {allegience="Superhero ";}
	else {allegience="Supervillain ";}
	ostr << allegience << c.getName() << " has power " << c.getPower() << std::endl;
	return ostr;
}
#endif