#ifndef SANGUIS_SERVER_COLLISION_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_BASE_HPP_INCLUDED

#include <sge/collision/objects/base_fwd.hpp>
#include <sge/noncopyable.hpp>
#include <boost/logic/tribool_fwd.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

class base {
	SGE_NONCOPYABLE(base)
protected:
	explicit base(
		sge::collision::objects::base_ptr
	);

	sge::collision::objects::base_ptr const
	collision_object();

	sge::collision::objects::const_base_ptr const
	collision_object() const;
public:
	virtual ~base();

	virtual boost::logic::tribool const
	can_collide_with(
		collision::base const &
	) const;

	virtual void
	collision(
		collision::base &
	);
private:
	sge::collision::objects::base_ptr const base_;
};

}
}
}

#endif
