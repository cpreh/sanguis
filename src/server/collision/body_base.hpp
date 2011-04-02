#ifndef SANGUIS_SERVER_COLLISION_BODY_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_BODY_BASE_HPP_INCLUDED

#include "body_base_fwd.hpp"
#include <boost/logic/tribool_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

class body_base
{
	FCPPT_NONCOPYABLE(
		body_base
	);
protected:
	body_base();
public:
	virtual ~body_base();

	virtual boost::logic::tribool const
	can_collide_with(
		collision::body_base const &
	) const;

	virtual void
	collision(
		collision::body_base &
	);
};

}
}
}

#endif
