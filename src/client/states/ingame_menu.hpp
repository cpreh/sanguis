#ifndef SANGUIS_CLIENT_STATES_INGAME_MENU_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_INGAME_MENU_HPP_INCLUDED

#include "has_player.hpp"
#include <fcppt/noncopyable.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/result.hpp>
#include <boost/mpl/list.hpp>

namespace sanguis
{
namespace client
{
namespace states
{

class ingame_menu
:
	public boost::statechart::state<
		ingame_menu,
		has_player
	>
{
	FCPPT_NONCOPYABLE(
		ingame_menu
	);
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
