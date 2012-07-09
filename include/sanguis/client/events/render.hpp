#ifndef SANGUIS_CLIENT_EVENTS_RENDER_HPP_INCLUDED
#define SANGUIS_CLIENT_EVENTS_RENDER_HPP_INCLUDED

#include <sanguis/client/events/render_fwd.hpp>
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

class render
:
	public boost::statechart::event<
		render
	>
{
	FCPPT_NONASSIGNABLE(
		render
	);
public:
	explicit
	render(
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
