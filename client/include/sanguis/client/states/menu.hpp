#ifndef SANGUIS_CLIENT_STATES_MENU_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_MENU_HPP_INCLUDED

#include <sanguis/client/machine.hpp>
#include <sanguis/client/events/connected_fwd.hpp>
#include <sanguis/client/events/input_fwd.hpp>
#include <sanguis/client/events/message_fwd.hpp>
#include <sanguis/client/events/net_error_fwd.hpp>
#include <sanguis/client/events/render_fwd.hpp>
#include <sanguis/client/events/tick_fwd.hpp>
#include <sanguis/client/gui/menu/object.hpp>
#include <sanguis/client/states/menu_fwd.hpp>
#include <sanguis/messages/call/result_fwd.hpp>
#include <sanguis/messages/server/connected_fwd.hpp>
#include <fcppt/noncopyable.hpp>
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
	typedef boost::mpl::list6<
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
		>,
		boost::statechart::custom_reaction<
			sanguis::client::events::input
		>
	> reactions;

	explicit
	menu(
		my_context
	);

	~menu();

	typedef
	sanguis::messages::call::result
	result_type;

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

	boost::statechart::result
	react(
		sanguis::client::events::input const &
	);

	sanguis::messages::call::result
	operator()(
		sanguis::messages::server::connected const &
	);
private:
	fcppt::log::object log_;

	sanguis::client::gui::menu::object menu_;
};

FCPPT_PP_POP_WARNING

}
}
}

#endif
