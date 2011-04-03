#ifndef SANGUIS_SERVER_ENTITIES_WITH_BODY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_BODY_HPP_INCLUDED

#include "with_body_fwd.hpp"
#include "with_ghosts.hpp"
#include "../collision/body_base.hpp"
#include "../collision/body_fwd.hpp"
#include "../collision/create_parameters_fwd.hpp"
#include "../center.hpp"
#include "../speed.hpp"
#include <sge/projectile/shape/shared_base_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <boost/logic/tribool_fwd.hpp>

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

	void
	speed(
		server::speed const &
	);
protected:
	void
	on_transfer(
		collision::create_parameters const &
	);
private:
	void
	on_position_change(
		server::center const &
	);

	boost::logic::tribool const
	can_collide_with(
		collision::body_base const &
	) const;

	void
	collide(
		collision::body_base &
	);

	virtual boost::logic::tribool const
	can_collide_with_body(
		entities::with_body const &
	) const;

	virtual void
	collision_with_body(
		entities::with_body &
	);

	// own virtual functions
	
	virtual server::speed const
	initial_direction() const;

	virtual sge::projectile::shape::shared_base_ptr const
	recreate_shape() = 0;

	typedef fcppt::scoped_ptr<
		collision::body
	> body_scoped_ptr;

	body_scoped_ptr collision_body_;
};

}
}
}

#endif
