#ifndef SANGUIS_CLIENT_STATES_PAUSED_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_PAUSED_HPP_INCLUDED

#include "running.hpp"
#include "../perk_chooser.hpp"
#include "../message_event.hpp"
#include "../../messages/unpause.hpp"
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
	private:
	boost::statechart::result handle_default_msg(messages::base const &);

	perk_chooser::activation chooser_activation_;
};
}
}
}

#endif
