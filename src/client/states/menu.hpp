#ifndef SANGUIS_CLIENT_STATES_MENU_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_MENU_HPP_INCLUDED

#include "menu_fwd.hpp"
#include "../machine.hpp"
#include "../events/message_fwd.hpp"
#include "../events/tick_fwd.hpp"
#include "../gui/menu/object.hpp"
#include "../../messages/net_error.hpp"
#include "../../messages/connect.hpp"
#include "../../messages/disconnect.hpp"
#include "../../messages/connect_state.hpp"
#include "../../connect_state.hpp"
#include <sge/renderer/state/scoped.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/mpl/list.hpp>

namespace sanguis
{
namespace client
{
namespace states
{

class menu
:
	public boost::statechart::state<
		menu,
		machine
	>
{
	FCPPT_NONCOPYABLE(
		menu
	);
public:
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<
			events::tick
		>,
		boost::statechart::custom_reaction<
			events::message
		>
	> reactions;

	explicit menu(
		my_context
	);

	~menu();

	typedef boost::statechart::result result_type;

	boost::statechart::result
	react(
		events::tick const &
	);

	boost::statechart::result
	react(
		events::message const &
	);

	boost::statechart::result
	handle_default_msg(
		messages::base const &
	);

	result_type
	operator()(
		messages::net_error const &
	);

	result_type
	operator()(
		messages::connect const &
	);

	result_type
	operator()(
		messages::disconnect const &
	);

	result_type
	operator()(
		messages::connect_state const &
	);
private:
	fcppt::log::object &
	log();

	client::gui::menu::object menu_;

	connect_state::type connect_state_;

	sge::renderer::state::scoped const renderer_state_;
	
	void
	connect(
		fcppt::string const &,
		fcppt::string const &
	);

	void
	quickstart();

	void
	cancel_connect();
};

}
}
}

#endif
