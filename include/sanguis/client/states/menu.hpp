#ifndef SANGUIS_CLIENT_STATES_MENU_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_MENU_HPP_INCLUDED

#include <sanguis/client/machine.hpp>
#include <sanguis/client/events/connected_fwd.hpp>
#include <sanguis/client/events/message_fwd.hpp>
#include <sanguis/client/events/net_error_fwd.hpp>
#include <sanguis/client/events/render_fwd.hpp>
#include <sanguis/client/events/tick_fwd.hpp>
#include <sanguis/client/gui/menu/object.hpp>
#include <sanguis/client/states/menu_fwd.hpp>
#include <sanguis/messages/server/base_fwd.hpp>
#include <sanguis/messages/server/connected_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/list/list10.hpp>
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

class menu
:
	public boost::statechart::state<
		sanguis::client::states::menu,
		sanguis::client::machine
	>
{
	FCPPT_NONCOPYABLE(
		menu
	);
public:
	typedef boost::mpl::list5<
		boost::statechart::custom_reaction<
			sanguis::client::events::tick
		>,
		boost::statechart::custom_reaction<
			sanguis::client::events::render
		>,
		boost::statechart::custom_reaction<
			sanguis::client::events::message
		>,
		boost::statechart::custom_reaction<
			sanguis::client::events::connected
		>,
		boost::statechart::custom_reaction<
			sanguis::client::events::net_error
		>
	> reactions;

	explicit
	menu(
		my_context
	);

	virtual
	~menu();

	typedef boost::statechart::result result_type;

	boost::statechart::result
	react(
		sanguis::client::events::tick const &
	);

	boost::statechart::result
	react(
		sanguis::client::events::render const &
	);

	boost::statechart::result
	react(
		sanguis::client::events::message const &
	);

	boost::statechart::result
	react(
		sanguis::client::events::connected const &
	);

	boost::statechart::result
	react(
		sanguis::client::events::net_error const &
	);

	result_type
	operator()(
		sanguis::messages::server::connected const &
	);
private:
	boost::statechart::result
	handle_default_msg(
		sanguis::messages::server::base const &
	);

	sanguis::client::gui::menu::object menu_;
};

}
}
}

#endif
