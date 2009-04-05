#ifndef SANGUIS_CLIENT_STATES_PAUSED_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_PAUSED_HPP_INCLUDED

#include "running.hpp"
#include "../message_event.hpp"
#include "../../messages/fwd.hpp"
#include "../../tick_event.hpp"
#include <sge/gui/widgets/buttons/image.hpp>
#include <sge/gui/manager.hpp>
#include <sge/gui/widgets/backdrop.hpp>
#include <sge/gui/widgets/label.hpp>
#include <sge/signal/connection_manager.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/result.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/mpl/list.hpp>
#include <boost/array.hpp>

namespace sanguis
{
namespace client
{
namespace states
{
class paused
	: public boost::statechart::state<paused,running>
{
	public:
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<tick_event>,
		boost::statechart::custom_reaction<message_event>
		> reactions;

	paused(my_context);

	boost::statechart::result react(tick_event const &);
	boost::statechart::result react(message_event const &);

	boost::statechart::result operator()(messages::unpause const &);
	boost::statechart::result operator()(messages::available_perks const &);
	private:
	typedef boost::ptr_vector<sge::gui::widgets::buttons::image> button_container;

	boost::statechart::result handle_default_msg(messages::base const &);

	sge::gui::manager m_;
	sge::gui::widgets::backdrop background_;
	sge::gui::widgets::label perks_left_;
	button_container buttons_;
	sge::signal::connection_manager connections_;

	void regenerate_widgets();
	void perk_callback(perk_type::type);
};
}
}
}

#endif
