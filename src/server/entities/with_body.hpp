#ifndef SANGUIS_SERVER_ENTITIES_WITH_BODY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_BODY_HPP_INCLUDED

#include "base.hpp"
#include "../collision/body_fwd.hpp"
#include "../../time_type.hpp"
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
	public entities::with_ghosts
{
	FCPPT_NONCOPYABLE(
		with_body
	);
public:
	with_body();

	~with_body();

	// entities::base overridden functions
	void
	on_update(
		sanguis::time_type
	);
prviate:
	void
	on_transfer(
		collision::global_groups const &,
		collision::create_parameters const &
	);

	virtual void
	on_center(
		server::pos const &
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
