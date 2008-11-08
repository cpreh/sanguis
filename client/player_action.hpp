#ifndef SANGUIS_CLIENT_PLAYER_ACTION_HPP_INCLUDED
#define SANGUIS_CLIENT_PLAYER_ACTION_HPP_INCLUDED

#include "../messages/types.hpp"
#include <boost/statechart/event.hpp>

namespace sanguis
{
namespace client
{

typedef messages::space_unit key_scale;

struct player_action {
	enum action_type {
		horizontal_move,
		vertical_move,
		horizontal_look,
		vertical_look,
		shoot,
		switch_weapon_forwards,
		switch_weapon_backwards,
		pause_unpause
		// TODO: more
	};

	player_action(
		action_type type_,
		key_scale scale);

	action_type type() const;
	key_scale scale() const;
private:
	action_type         type_;
	key_scale           scale_;
};

}
}

#endif
