#ifndef SANGUIS_CLIENT_DRAW_BASE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW_BASE_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/client/draw_base_fwd.hpp>
#include <sanguis/client/control/environment_fwd.hpp>
#include <sanguis/messages/server/base_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{

class draw_base
{
	FCPPT_NONCOPYABLE(
		draw_base
	);
protected:
	draw_base();
public:
	virtual
	~draw_base() = 0;

	virtual
	void
	process_message(
		sanguis::messages::server::base const &
	) = 0;

	virtual
	void
	update(
		sanguis::duration const &
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

	virtual
	sanguis::client::control::environment &
	control_environment() const = 0;
};

}
}

#endif
