#ifndef SANGUIS_CLIENT_STATES_RUNNING_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_RUNNING_HPP_INCLUDED

#include <sanguis/slowdown.hpp>
#include <sanguis/client/machine.hpp>
#include <sanguis/client/sound_manager_fwd.hpp>
#include <sanguis/client/console/object_fwd.hpp>
#include <sanguis/client/control/environment_fwd.hpp>
#include <sanguis/client/control/input_translator_fwd.hpp>
#include <sanguis/client/control/optional_cursor_position_fwd.hpp>
#include <sanguis/client/control/actions/any_fwd.hpp>
#include <sanguis/client/draw/base_unique_ptr.hpp>
#include <sanguis/client/events/input_fwd.hpp>
#include <sanguis/client/events/message_fwd.hpp>
#include <sanguis/client/events/net_error_fwd.hpp>
#include <sanguis/client/events/overlay_fwd.hpp>
#include <sanguis/client/events/render_fwd.hpp>
#include <sanguis/client/events/tick_fwd.hpp>
#include <sanguis/client/gui/hud/object_fwd.hpp>
#include <sanguis/client/load/hud/context.hpp>
#include <sanguis/client/states/ingame_fwd.hpp>
#include <sanguis/messages/call/result_fwd.hpp>
#include <sanguis/messages/server/add_console_command_fwd.hpp>
#include <sanguis/messages/server/add_own_player_fwd.hpp>
#include <sanguis/messages/server/change_world_fwd.hpp>
#include <sanguis/messages/server/console_print_fwd.hpp>
#include <sanguis/messages/server/experience_fwd.hpp>
#include <sanguis/messages/server/give_weapon_fwd.hpp>
#include <sanguis/messages/server/level_up_fwd.hpp>
#include <sanguis/messages/server/magazine_remaining_fwd.hpp>
#include <sanguis/messages/server/pause_fwd.hpp>
#include <sanguis/messages/server/reload_fwd.hpp>
#include <sanguis/messages/server/remove_weapon_fwd.hpp>
#include <sanguis/messages/server/slowdown_fwd.hpp>
#include <sanguis/messages/server/unpause_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
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

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4265)

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
	using
	reactions
	=
	boost::mpl::list6<
		boost::statechart::custom_reaction<
			sanguis::client::events::tick
		>,
		boost::statechart::custom_reaction<
			sanguis::client::events::render
		>,
		boost::statechart::custom_reaction<
			sanguis::client::events::overlay
		>,
		boost::statechart::custom_reaction<
			sanguis::client::events::message
		>,
		boost::statechart::custom_reaction<
			sanguis::client::events::net_error
		>,
		boost::statechart::custom_reaction<
			sanguis::client::events::input
		>
	>;

	explicit
	running(
		my_context
	);

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
		sanguis::client::events::overlay const &
	);

	boost::statechart::result
	react(
		sanguis::client::events::message const &
	);

	boost::statechart::result
	react(
		sanguis::client::events::net_error const &
	);

	boost::statechart::result
	react(
		sanguis::client::events::input const &
	);

	using
	result_type
	=
	sanguis::messages::call::result;

	sanguis::messages::call::result
	operator()(
		sanguis::messages::server::add_console_command const &
	);

	sanguis::messages::call::result
	operator()(
		sanguis::messages::server::add_own_player const &
	);

	sanguis::messages::call::result
	operator()(
		sanguis::messages::server::change_world const &
	);

	sanguis::messages::call::result
	operator()(
		sanguis::messages::server::console_print const &
	);

	sanguis::messages::call::result
	operator()(
		sanguis::messages::server::experience const &
	);

	sanguis::messages::call::result
	operator()(
		sanguis::messages::server::give_weapon const &
	);

	sanguis::messages::call::result
	operator()(
		sanguis::messages::server::level_up const &
	);

	sanguis::messages::call::result
	operator()(
		sanguis::messages::server::magazine_remaining const &
	);

	sanguis::messages::call::result
	operator()(
		sanguis::messages::server::pause const &
	);

	sanguis::messages::call::result
	operator()(
		sanguis::messages::server::reload const &
	);

	sanguis::messages::call::result
	operator()(
		sanguis::messages::server::remove_weapon const &
	);

	sanguis::messages::call::result
	operator()(
		sanguis::messages::server::slowdown const &
	);

	sanguis::messages::call::result
	operator()(
		sanguis::messages::server::unpause const &
	);

	sanguis::client::console::object &
	console();

	sanguis::client::gui::hud::object &
	hud_gui();

	sanguis::client::control::environment const &
	control_environment() const;

	void
	update(
		sanguis::client::events::tick const &,
		sanguis::client::control::optional_cursor_position const &
	);
private:
	void
	handle_player_action(
		sanguis::client::control::actions::any const &
	);

	void
	do_pause(
		bool
	);

	fcppt::log::object log_;

	sanguis::client::load::hud::context hud_resources_;

	fcppt::unique_ptr<
		sanguis::client::console::object
	> const console_;

	fcppt::unique_ptr<
		sanguis::client::sound_manager
	> const sound_manager_;

	fcppt::unique_ptr<
		sanguis::client::gui::hud::object
	> const hud_;

	sanguis::client::draw::base_unique_ptr const drawer_;

	fcppt::unique_ptr<
		sanguis::client::control::input_translator
	> const input_translator_;

	sanguis::slowdown slowdown_;
};

FCPPT_PP_POP_WARNING

}
}
}

#endif
