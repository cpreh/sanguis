#ifndef SANGUIS_CLIENT_STATES_RUNNING_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_RUNNING_HPP_INCLUDED

#include "ingame_fwd.hpp"
#include "../machine.hpp"
#include "../perk_chooser.hpp"
#include "../music_handler.hpp"
#include "../perk_container.hpp"
#include "../level_type.hpp"
#include "../daytime_settings.hpp"
#include "../events/message_fwd.hpp"
#include "../control/logic_fwd.hpp"
#include "../control/input_handler_fwd.hpp"
#include "../draw2d/scene/object_fwd.hpp"
#include "../draw2d/sprite/point.hpp"
#include "../events/tick_fwd.hpp"
#include "../../perk_type.hpp"
#include "../../messages/base.hpp"
#include "../../messages/add_own_player.hpp"
#include "../../messages/highscore.hpp"
#include "../../messages/remove_id.hpp"
#include "../../messages/disconnect.hpp"
#include "../../messages/give_weapon.hpp"
#include "../../messages/available_perks.hpp"
#include "../../messages/level_up.hpp"
#include "../../messages/console_print.hpp"
#include "../../messages/add_console_command.hpp"
#include "../../messages/pause.hpp"
#include "../../messages/unpause.hpp"
#include "../../entity_id.hpp"
#include <sge/renderer/state/scoped.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/transition.hpp>
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
		messages::add_own_player const &
	);

	boost::statechart::result
	operator()(
		messages::remove_id const &
	);

	boost::statechart::result
	operator()(
		messages::disconnect const &
	);

	boost::statechart::result
	operator()(
		messages::give_weapon const &
	);

	boost::statechart::result
	operator()(
		messages::highscore const &
	);

	boost::statechart::result
	operator()(
		messages::available_perks const &
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

	perk_container const &
	perks() const;
	
	level_type
	levels_left() const;
	
	void
	consume_level();

	entity_id
	player_id() const;

	client::perk_chooser &
	perk_chooser();
private:
	boost::statechart::result
	handle_default_msg(
		messages::base const &
	);

	void
	send_message(
		messages::auto_ptr
	);

	void
	send_perk_choose(
		perk_type::type
	);

	void
	cursor_pos(
		draw2d::sprite::point const & // FIXME!
	);

	void
	cursor_show(
		bool show
	);

	void
	on_escape();

	sge::renderer::state::scoped renderer_state_;

	music_handler music_;

	client::daytime_settings daytime_settings_;

	fcppt::scoped_ptr<
		draw2d::scene::object
	> drawer_;

	fcppt::scoped_ptr<
		control::logic
	> logic_;

	fcppt::scoped_ptr<
		control::input_handler
	> player_input_;

	fcppt::signal::scoped_connection const esc_connection_;

	client::perk_chooser perk_chooser_;

	entity_id const cursor_id_;

	fcppt::signal::scoped_connection const
		cursor_pos_conn_,
		cursor_show_conn_;
};

}
}
}

#endif
