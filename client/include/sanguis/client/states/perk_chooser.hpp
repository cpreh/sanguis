#ifndef SANGUIS_CLIENT_STATES_PERK_CHOOSER_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_PERK_CHOOSER_HPP_INCLUDED

#include <sanguis/client/scoped_pause.hpp>
#include <sanguis/client/events/action_fwd.hpp>
#include <sanguis/client/events/input_fwd.hpp>
#include <sanguis/client/events/overlay_fwd.hpp>
#include <sanguis/client/events/tick_fwd.hpp>
#include <sanguis/client/gui/hud/scoped_details.hpp>
#include <sanguis/client/gui/perk/chooser.hpp>
#include <sanguis/client/states/has_player.hpp>
#include <fcppt/noncopyable.hpp>
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

class perk_chooser
:
	public boost::statechart::state<
		sanguis::client::states::perk_chooser,
		sanguis::client::states::has_player
	>
{
	FCPPT_NONCOPYABLE(
		perk_chooser
	);
public:
	using
	reactions
	=
	boost::mpl::list4<
		boost::statechart::custom_reaction<
			sanguis::client::events::action
		>,
		boost::statechart::custom_reaction<
			sanguis::client::events::overlay
		>,
		boost::statechart::custom_reaction<
			sanguis::client::events::tick
		>,
		boost::statechart::custom_reaction<
			sanguis::client::events::input
		>
	>;

	explicit
	perk_chooser(
		my_context
	);

	~perk_chooser();

	boost::statechart::result
	react(
		sanguis::client::events::action const &
	);

	boost::statechart::result
	react(
		sanguis::client::events::overlay const &
	);

	boost::statechart::result
	react(
		sanguis::client::events::tick const &
	);

	boost::statechart::result
	react(
		sanguis::client::events::input const &
	);
private:
	sanguis::client::scoped_pause const pause_;

	sanguis::client::gui::perk::chooser perk_chooser_gui_;

	sanguis::client::gui::hud::scoped_details const hud_details_;
};

FCPPT_PP_POP_WARNING

}
}
}

#endif
