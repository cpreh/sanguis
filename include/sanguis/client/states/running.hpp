#ifndef SANGUIS_CLIENT_STATES_RUNNING_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_RUNNING_HPP_INCLUDED

#include <sanguis/client/states/ingame_fwd.hpp>
#include <sanguis/client/machine.hpp>
#include <sanguis/client/music_handler_fwd.hpp>
#include <sanguis/client/daytime_settings_fwd.hpp>
#include <sanguis/client/control/environment_fwd.hpp>
#include <sanguis/client/console/object_fwd.hpp>
#include <sanguis/client/draw2d/scene/object_fwd.hpp>
#include <sanguis/client/events/message_fwd.hpp>
#include <sanguis/client/events/net_error_fwd.hpp>
#include <sanguis/client/events/render_fwd.hpp>
#include <sanguis/client/events/tick_fwd.hpp>
#include <sanguis/messages/base.hpp>
#include <sanguis/messages/add_own_player.hpp>
#include <sanguis/messages/console_print.hpp>
#include <sanguis/messages/add_console_command.hpp>
#include <sanguis/messages/pause.hpp>
#include <sanguis/messages/unpause.hpp>
#include <sanguis/messages/level_up.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/list/list10.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/result.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace client
{
namespace states
{

class running
:
	public boost::statechart::state<
		running,
		machine,
		ingame
	>
{
	FCPPT_NONCOPYABLE(
		running
	);
public:
	typedef boost::mpl::list4<
		boost::statechart::custom_reaction<
			events::tick
		>,
		boost::statechart::custom_reaction<
			events::render
		>,
		boost::statechart::custom_reaction<
			events::message
		>,
		boost::statechart::custom_reaction<
			events::net_error
		>
	> reactions;

	explicit running(
		my_context
	);

	~running();

	boost::statechart::result
	react(
		events::tick const &
	);

	boost::statechart::result
	react(
		events::render const &
	);

	boost::statechart::result
	react(
		events::message const &
	);

	boost::statechart::result
	react(
		events::net_error const &
	);

	typedef boost::statechart::result result_type;

	boost::statechart::result
	operator()(
		messages::level_up const &
	);

	boost::statechart::result
	operator()(
		messages::console_print const &
	);

	boost::statechart::result
	operator()(
		messages::add_console_command const &
	);

	boost::statechart::result
	operator()(
		messages::pause const &
	);

	boost::statechart::result
	operator()(
		messages::unpause const &
	);

	control::environment &
	control_environment();

	client::console::object &
	console();
private:
	boost::statechart::result
	handle_default_msg(
		messages::base const &
	);

	sge::renderer::state::scoped const renderer_state_;

	fcppt::scoped_ptr<
		client::console::object
	> console_;

	fcppt::scoped_ptr<
		client::daytime_settings
	> daytime_settings_;

	fcppt::scoped_ptr<
		draw2d::scene::object
	> drawer_;

	fcppt::scoped_ptr<
		client::music_handler
	> music_;
};

}
}
}

#endif
