#ifndef SANGUIS_SERVER_COLLISION_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_BASE_HPP_INCLUDED

#include "base_fwd.hpp"
#include <fcppt/noncopyable.hpp>
#include <boost/logic/tribool_fwd.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

class base
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	base();
public:
	virtual ~base();

	virtual boost::logic::tribool const
	can_collide_with(
		collision::base const &
	) const;

	virtual void
	collision_begin(
		collision::base &
	) = 0;

	virtual void
	collision_end(
		collision::base &
	) = 0;
};

}
}
}

#endif
