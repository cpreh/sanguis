#ifndef SANGUIS_CLIENT_CONTROL_ACTION_TYPE_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_ACTION_TYPE_HPP_INCLUDED

namespace sanguis
{
namespace client
{
namespace control
{

namespace action_type
{
enum type
{
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
}

}
}
}

#endif
