#ifndef SANGUIS_CLIENT_CONTROL_PLAYER_ACTION_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_PLAYER_ACTION_HPP_INCLUDED

#include "player_action_fwd.hpp"
#include "action_type.hpp"
#include "key_scale.hpp"

namespace sanguis
{
namespace client
{
namespace control
{

class player_action
{
public:
	player_action(
		action_type::type,
		key_scale
	);

	action_type::type
	type() const;

	key_scale
	scale() const;
private:
	action_type::type type_;

	key_scale scale_;
};

}
}
}

#endif
