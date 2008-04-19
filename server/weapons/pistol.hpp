#ifndef SANGUIS_SERVER_WEAPONS_PISTOL_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_PISTOL_HPP_INCLUDED

#include "weapon.hpp"
#include "../../messages/types.hpp"

namespace sanguis
{
namespace server
{
namespace weapons
{

class pistol : public weapon {
public:
	pistol(
		time_type base_cooldown);
private:
	void do_attack(
		entity const &from,
		messages::pos_type const& to);
};

}
}
}

#endif
