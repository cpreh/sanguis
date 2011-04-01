#ifndef SANGUIS_SERVER_ENTITIES_WITH_BODY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_BODY_HPP_INCLUDED

#include "base.hpp"
#include "with_ghosts.hpp"
#include "../collision/body_base.hpp"
#include "../collision/body_fwd.hpp"
#include "../collision/create_parameters_fwd.hpp"
#include "../center.hpp"
#include <sge/projectile/shapes/base_ptr.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

class with_body
:
	public entities::with_ghosts,
	public collision::body_base
{
	FCPPT_NONCOPYABLE(
		with_body
	);
public:
	with_body();

	~with_body();

	// entities::base overridden functions
	server::center const
	center() const;

	void
	center(
		server::center const &
	);
prviate:
	void
	on_transfer(
		collision::create_parameters const &
	);

	void
	on_position_change(
		server::center const &
	);

	// own virtual functions
	virtual sge::projectile::shapes::base_ptr const
	recreate_shape(
		sge::collision::world &
	) = 0;

	typedef fcppt::scoped_ptr<
		collision::body
	> body_scoped_ptr;

	body_scoped_ptr collision_body_;
};

}
}
}

#endif
