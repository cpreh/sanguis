#ifndef SANGUIS_CLIENT_STATES_RUNNING_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_RUNNING_HPP_INCLUDED

#include "ingame_fwd.hpp"
#include "../machine.hpp"
#include "../music_handler.hpp"
#include "../daytime_settings_fwd.hpp"
#include "../control/environment_fwd.hpp"
#include "../draw2d/scene/object_fwd.hpp"
#include "../events/tick_fwd.hpp"
#include "../events/message_fwd.hpp"
#include "../gui/perk/chooser_fwd.hpp"
#include "../../messages/base.hpp"
#include "../../messages/add_own_player.hpp"
#include "../../messages/disconnect.hpp"
#include "../../messages/console_print.hpp"
#include "../../messages/add_console_command.hpp"
#include "../../messages/pause.hpp"
#include "../../messages/unpause.hpp"
#include "../../messages/available_perks.hpp"
#include "../../messages/level_up.hpp"
#include "../../perk_type.hpp"
#include <sge/renderer/state/scoped.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/result.hpp>
#include <boost/mpl/list/list10.hpp>

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
	typedef boost::mpl::list2<
		boost::statechart::custom_reaction<
			events::tick
		>,
		boost::statechart::custom_reaction<
			events::message
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
		events::message const &
	);
	
	typedef boost::statechart::result result_type;

	boost::statechart::result
	operator()(
		messages::disconnect const &
	);

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

	result_type
	operator()(
		messages::available_perks const &
	);

	control::environment &
	control_environment();

	client::gui::perk::chooser &
	perk_chooser();
private:
	boost::statechart::result
	handle_default_msg(
		messages::base const &
	);

	void
	send_perk_choose(
		perk_type::type
	);

	sge::renderer::state::scoped const renderer_state_;

	music_handler music_;

	fcppt::scoped_ptr<
		client::gui::perk::chooser
	> perk_chooser_;

	fcppt::scoped_ptr<
		client::daytime_settings
	> daytime_settings_;

	fcppt::scoped_ptr<
		draw2d::scene::object
	> drawer_;
};

}
}
}

#endif
