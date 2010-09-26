#ifndef SANGUIS_CLIENT_STATES_INGAME_MENU_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_INGAME_MENU_HPP_INCLUDED

#include "ingame_menu_fwd.hpp"

namespace sanguis
{
namespace client
{
namespace states
{

class ingame_menu
:
	public boost::statechart::state<
		ingame_menu
	>
{
public:
	explicit ingame_menu(
		my_context
	);

	~ingame_menu();
};

}
}
}

#endif
