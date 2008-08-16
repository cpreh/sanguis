#ifndef SANGUIS_SERVER_WEAPONS_DELAYED_ATTACK_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_DELAYED_ATTACK_HPP_INCLUDED

#include "../teams.hpp"
#include "../../messages/types.hpp"

namespace sanguis
{
namespace server
{
namespace weapons
{

class delayed_attack {
public:
	delayed_attack(
		messages::pos_type const &spawn_point,
		messages::space_unit angle,
		team::type team_,
		messages::pos_type const &dest);

	messages::pos_type const &spawn_point() const;
	messages::space_unit angle() const;
	team::type team() const;
	messages::pos_type const &dest() const;
private:
	messages::pos_type   spawn_point_;
	messages::space_unit angle_;
	team::type           team_;
	messages::pos_type   dest_;
};

}
}
}

#endif
