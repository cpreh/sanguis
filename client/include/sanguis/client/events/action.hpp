#ifndef SANGUIS_CLIENT_EVENTS_ACTION_HPP_INCLUDED
#define SANGUIS_CLIENT_EVENTS_ACTION_HPP_INCLUDED

#include <sanguis/client/control/actions/any.hpp>
#include <sanguis/client/events/action_fwd.hpp>
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
		sanguis::client::events::action
	>
{
	FCPPT_NONASSIGNABLE(
		action
	);
public:
	explicit
	action(
		sanguis::client::control::actions::any const &
	);

	sanguis::client::control::actions::any const &
	value() const;
private:
	sanguis::client::control::actions::any const value_;
};

}
}
}

#endif
