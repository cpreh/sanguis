#ifndef SANGUIS_CLIENT_STATES_RUNNING_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_RUNNING_HPP_INCLUDED

#include <sanguis/client/machine.hpp>
#include <sanguis/client/sound_manager_fwd.hpp>
#include <sanguis/client/control/environment_fwd.hpp>
#include <sanguis/client/control/input_translator_fwd.hpp>
#include <sanguis/client/control/actions/any_fwd.hpp>
#include <sanguis/client/console/object_fwd.hpp>
#include <sanguis/client/draw2d/scene/object_fwd.hpp>
#include <sanguis/client/events/message_fwd.hpp>
#include <sanguis/client/events/net_error_fwd.hpp>
#include <sanguis/client/events/render_fwd.hpp>
#include <sanguis/client/events/tick_fwd.hpp>
#include <sanguis/client/gui/hud/object_fwd.hpp>
#include <sanguis/client/states/ingame_fwd.hpp>
#include <sanguis/messages/server/add_console_command_fwd.hpp>
#include <sanguis/messages/server/base_fwd.hpp>
#include <sanguis/messages/server/change_world_fwd.hpp>
#include <sanguis/messages/server/console_print_fwd.hpp>
#include <sanguis/messages/server/experience_fwd.hpp>
#include <sanguis/messages/server/give_weapon_fwd.hpp>
#include <sanguis/messages/server/level_up_fwd.hpp>
#include <sanguis/messages/server/magazine_remaining_fwd.hpp>
#include <sanguis/messages/server/pause_fwd.hpp>
#include <sanguis/messages/server/remove_weapon_fwd.hpp>
#include <sanguis/messages/server/unpause_fwd.hpp>
#include <sge/input/cursor/activatable_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
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

class running
:
	public boost::statechart::state<
		sanguis::client::states::running,
		sanguis::client::machine,
		sanguis::client::states::ingame
	>
{
	FCPPT_NONCOPYABLE(
		running
	);
public:
	typedef boost::mpl::list4<
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
			sanguis::client::events::net_error
		>
	> reactions;

	explicit
	running(
		my_context
	);

	virtual
	~running();

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
		sanguis::client::events::net_error const &
	);

	typedef boost::statechart::result result_type;

	boost::statechart::result
	operator()(
		sanguis::messages::server::add_console_command const &
	);

	boost::statechart::result
	operator()(
		sanguis::messages::server::change_world const &
	);

	boost::statechart::result
	operator()(
		sanguis::messages::server::console_print const &
	);

	boost::statechart::result
	operator()(
		sanguis::messages::server::experience const &
	);

	boost::statechart::result
	operator()(
		sanguis::messages::server::give_weapon const &
	);

	boost::statechart::result
	operator()(
		sanguis::messages::server::level_up const &
	);

	boost::statechart::result
	operator()(
		sanguis::messages::server::magazine_remaining const &
	);

	boost::statechart::result
	operator()(
		sanguis::messages::server::pause const &
	);

	boost::statechart::result
	operator()(
		sanguis::messages::server::remove_weapon const &
	);

	boost::statechart::result
	operator()(
		sanguis::messages::server::unpause const &
	);

	sanguis::client::control::environment &
	control_environment();

	sanguis::client::console::object &
	console();

	sge::input::cursor::activatable &
	cursor();

	sanguis::client::gui::hud::object &
	hud_gui();
private:
	void
	handle_player_action(
		sanguis::client::control::actions::any const &
	);

	boost::statechart::result
	handle_default_msg(
		sanguis::messages::server::base const &
	);

	fcppt::scoped_ptr<
		sanguis::client::console::object
	> const console_;

	fcppt::scoped_ptr<
		sanguis::client::sound_manager
	> const sound_manager_;

	fcppt::scoped_ptr<
		sanguis::client::gui::hud::object
	> const hud_;

	fcppt::scoped_ptr<
		sanguis::client::draw2d::scene::object
	> const drawer_;

	fcppt::scoped_ptr<
		sanguis::client::control::input_translator
	> const input_translator_;
};

}
}
}

#endif
