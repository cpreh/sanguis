#ifndef SANGUIS_SERVER_COLLISION_BODY_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_BODY_HPP_INCLUDED

#include "body_fwd.hpp"
#include "global_groups_fwd.hpp"
#include "create_parameters_fwd.hpp"
#include "ghost_reference_vector.hpp"
#include "group_vector.hpp"
#include "shape_unique_ptr.hpp"
#include "solidity_fwd.hpp"
#include "../center.hpp"
#include "../speed.hpp"
#include <sge/projectile/body/object_fwd.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

class body
{
	FCPPT_NONCOPYABLE(
		body
	);
public:
	body(
		sge::projectile::world &,
		collision::create_parameters const &,
		collision::global_groups const &
		collision::group_vector const &,
		collision::shape_unique_ptr,
		collision::solidity const &,
		collision::ghost_reference_vector const &
	);

	~body();

	void
	center(
		server::center const &
	);

	server::center const
	center() const;

	void
	speed(
		server::speed const &
	);

	server::speed const
	speed() const;
private:
	void
	on_position_change(
		sge::projectile::body::position const &
	);

	typedef fcppt::scoped_ptr<
		sge::projectile::body
	> body_scoped_ptr;

	body_scoped_ptr body_;

	ghost_reference_vector ghost_references_;
};

}
}
}

#endif

