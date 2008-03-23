#ifndef SANGUIS_PLAYER_STATE_HPP_INCLUDED
#define SANGUIS_PLAYER_STATE_HPP_INCLUDED

#include "weapon_type.hpp"
#include <boost/cstdint.hpp>

namespace sanguis
{
struct player_state
{
	weapon_type::type weapon;
	boost::uint32_t ammo;

	player_state() {}
	player_state(const weapon_type::type weapon,const boost::uint32_t ammo) 
		: weapon(weapon),ammo(ammo) {}
};

template<class Archive> 
inline void serialize(Archive &ar,player_state &p,const unsigned) 
{
	ar & p.ammo & p.weapon;
}
}

#endif
