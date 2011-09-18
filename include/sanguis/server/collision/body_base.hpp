#ifndef SANGUIS_SERVER_COLLISION_BODY_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_BODY_BASE_HPP_INCLUDED

#include <sanguis/server/collision/body_base_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool_fwd.hpp>
#include <fcppt/config/external_end.hpp>

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
	) const = 0;

	virtual void
	collision(
		collision::body_base &
	) = 0;
};

}
}
}

#endif
