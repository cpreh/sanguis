#ifndef SANGUIS_CLIENT_EVENTS_OVERLAY_HPP_INCLUDED
#define SANGUIS_CLIENT_EVENTS_OVERLAY_HPP_INCLUDED

#include <sanguis/client/events/overlay_fwd.hpp>
#include <sge/renderer/context/object_fwd.hpp>
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

class overlay
:
	public boost::statechart::event<
		overlay
	>
{
	FCPPT_NONASSIGNABLE(
		overlay
	);
public:
	explicit
	overlay(
		sge::renderer::context::object &
	);

	sge::renderer::context::object &
	context() const;
private:
	sge::renderer::context::object &context_;

};

}
}
}

#endif
