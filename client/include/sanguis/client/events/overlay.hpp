#ifndef SANGUIS_CLIENT_EVENTS_OVERLAY_HPP_INCLUDED
#define SANGUIS_CLIENT_EVENTS_OVERLAY_HPP_INCLUDED

#include <sanguis/client/events/overlay_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
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

class overlay
:
	public boost::statechart::event<
		sanguis::client::events::overlay
	>
{
public:
	explicit
	overlay(
		sge::renderer::context::ffp &
	);

	overlay(
		overlay &&
	);

	overlay(
		overlay const &
	);

	overlay &
	operator=(
		overlay &&
	);

	overlay &
	operator=(
		overlay const &
	);

	~overlay()
	override;

	sge::renderer::context::ffp &
	context() const;
private:
	fcppt::reference<
		sge::renderer::context::ffp
	> context_;
};

}
}
}

#endif
