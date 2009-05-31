#ifndef SANGUIS_SERVER_COLLISION_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_BASE_HPP_INCLUDED

#include "../pos_type.hpp"
#include "../space_unit.hpp"
#include <sge/collision/objects/circle_fwd.hpp>
#include <sge/collision/world_fwd.hpp>
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
		sge::collision::world_ptr const collision_,
		pos_type const &center,
		pos_type const &speed,
		space_unit const radius);
	
	/*
	sge::collision::objects::circle_ptr const
	circle();

	sge::collision::objects::const_circle_ptr const
	circle() const;
	*/
	sge::collision::objects::circle_ptr const
	circle() { return circle_; }

	sge::collision::objects::const_circle_ptr const
	circle() const { return circle_; }
public:
	virtual ~base();

	virtual boost::logic::tribool const
	can_collide_with(
		collision::base const &) const;

	virtual void
	collision(
		collision::base &);
private:
	sge::collision::objects::circle_ptr const circle_;
};

}
}
}

#endif
