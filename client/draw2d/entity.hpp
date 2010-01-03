#ifndef SANGUIS_CLIENT_DRAW2D_ENTITY_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITY_HPP_INCLUDED

#include "sprite/rotation_type.hpp"
#include "sprite/point.hpp"
#include "sprite/dim.hpp"
#include "../time_type.hpp"
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{

class entity
{
	FCPPT_NONCOPYABLE(entity)
public:
	virtual void
	update(
		time_type
	) = 0;

	virtual bool
	may_be_removed() const;
	
	virtual void
	on_remove();

	virtual void
	pos(
		sprite::point const &
	) = 0;

	virtual void
	dim(
		sprite::dim const &
	) = 0;

	virtual void
	orientation(
		sprite::rotation_type
	) = 0;

	virtual void
	visible(
		bool
	) = 0;

	virtual ~entity();
protected:
	entity();

	virtual funit
	orientation() const;
private:
	static fcppt::log::object &
	log();

	bool may_be_removed_;
};

}
}
}

#endif
