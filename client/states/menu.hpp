#ifndef SANGUIS_CLIENT_STATES_MENU_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_MENU_HPP_INCLUDED

#include "../../connect_state.hpp"
#include "../machine.hpp"
#include "../message_event_fwd.hpp"
#include "../menu/object.hpp"
#include "../../messages/net_error.hpp"
#include "../../messages/connect.hpp"
#include "../../messages/disconnect.hpp"
#include "../../messages/assign_id.hpp"
#include "../../tick_event_fwd.hpp"
#include <sge/log/object_fwd.hpp>
#include <sge/renderer/state/scoped.hpp>
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
	: public boost::statechart::state<menu,machine>
{
public:
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<tick_event>,
		boost::statechart::custom_reaction<message_event>
	> reactions;

	explicit menu(my_context); 

	typedef boost::statechart::result result_type;

	boost::statechart::result react(
		tick_event const &);
	boost::statechart::result react(
		message_event const &);
	boost::statechart::result handle_default_msg(
		messages::base const &);
	boost::statechart::result operator()(
		messages::net_error const &);
	boost::statechart::result operator()(
		messages::connect const &);
	boost::statechart::result operator()(
		messages::disconnect const &);
	boost::statechart::result operator()(
		messages::assign_id const &);
private:
	sge::log::object &log();

	client::menu::object menu_;
	connect_state::type connect_state_;
	sge::renderer::state::scoped const renderer_state_;
	
	void connect(
		sge::string const &,
		sge::string const &);
	void start_server();
	void cancel_connect();
};
}
}
}

#endif
