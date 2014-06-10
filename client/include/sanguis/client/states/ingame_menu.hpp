#ifndef SANGUIS_CLIENT_STATES_INGAME_MENU_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_INGAME_MENU_HPP_INCLUDED

#include <sanguis/client/states/ingame_menu_fwd.hpp>
#include <sanguis/client/states/has_player.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/result.hpp>
#include <boost/statechart/state.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace states
{

class ingame_menu
:
	public boost::statechart::state<
		sanguis::client::states::ingame_menu,
		sanguis::client::states::has_player
	>
{
	FCPPT_NONCOPYABLE(
		ingame_menu
	);
public:
	explicit
	ingame_menu(
		my_context
	);

	~ingame_menu()
	override;
};

}
}
}

#endif
