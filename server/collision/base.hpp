#ifndef SANGUIS_SERVER_COLLISION_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_BASE_HPP_INCLUDED

#include <sge/collision/objects/circle_fwd.hpp>
#include <sge/noncopyable.hpp>

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
		sge::collision::objects::circle_ptr);
public:
	virtual ~base();
private:
	sge::collision::objects::circle_ptr const circle_;
};

}
}
}

#endif
