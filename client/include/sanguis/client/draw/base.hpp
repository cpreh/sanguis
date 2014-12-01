#ifndef SANGUIS_CLIENT_DRAW_BASE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW_BASE_HPP_INCLUDED

#include <sanguis/client/slowed_duration_fwd.hpp>
#include <sanguis/client/control/environment.hpp>
#include <sanguis/client/control/optional_cursor_position_fwd.hpp>
#include <sanguis/client/draw/base_fwd.hpp>
#include <sanguis/messages/server/base_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace draw
{

class base
:
	public sanguis::client::control::environment
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	base();
public:
	~base()
	override;

	virtual
	void
	process_message(
		sanguis::messages::server::base const &
	) = 0;

	virtual
	void
	update(
		sanguis::client::slowed_duration,
		sanguis::client::control::optional_cursor_position const &
	) = 0;

	virtual
	void
	draw(
		sge::renderer::context::ffp &
	) = 0;

	virtual
	void
	overlay(
		sge::renderer::context::ffp &
	) = 0;

	virtual
	void
	pause(
		bool
	) = 0;
};

}
}
}

#endif
