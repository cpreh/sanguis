#ifndef SANGUIS_CLIENT_EVENTS_ACTION_HPP_INCLUDED
#define SANGUIS_CLIENT_EVENTS_ACTION_HPP_INCLUDED

#include <sanguis/client/events/action_fwd.hpp>
#include <sanguis/client/control/actions/any.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/event.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace client
{
namespace events
{

class action
:
	public boost::statechart::event<
		action
	>
{
	FCPPT_NONASSIGNABLE(
		action
	);
public:
	explicit action(
		client::control::actions::any const &
	);

	client::control::actions::any const
	value() const;
private:
	client::control::actions::any const value_;
};

}
}
}

#endif
