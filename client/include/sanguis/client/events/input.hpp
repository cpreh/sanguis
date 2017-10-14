#ifndef SANGUIS_CLIENT_EVENTS_INPUT_HPP_INCLUDED
#define SANGUIS_CLIENT_EVENTS_INPUT_HPP_INCLUDED

#include <sanguis/client/events/input_fwd.hpp>
#include <sge/input/event_base_fwd.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/event.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace events
{

class input
:
	public boost::statechart::event<
		sanguis::client::events::input
	>
{
public:
	explicit
	input(
		sge::input::event_base const &
	);

	sge::input::event_base const &
	get() const;
private:
	fcppt::reference<
		sge::input::event_base const
	> const event_;
};

}
}
}

#endif
