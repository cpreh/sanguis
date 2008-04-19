#ifndef SANGUIS_SERVER_WEAPONS_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_WEAPON_HPP_INCLUDED

#include "../../time_type.hpp"
#include "../../messages/types.hpp"

namespace sanguis
{
namespace server
{

class entity;

namespace weapons
{

class weapon {
public:
	weapon(
		messages::space_unit range,
		time_type base_cooldown);
	messages::space_unit range() const;
	time_type base_cooldown() const;
	virtual bool attack(
		entity const &from,
		messages::pos_type const& to) = 0;
private:
	messages::space_unit range_;
	time_type            base_cooldown_;
};

}
}
}

#endif
