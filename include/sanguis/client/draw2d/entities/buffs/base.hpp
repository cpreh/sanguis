#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_BUFFS_BASE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_BUFFS_BASE_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/buffs/base_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{
namespace buffs
{

class base
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	base();
public:
	virtual
	~base() = 0;

	virtual
	void
	apply(
		sanguis::client::draw2d::entities::model::object &
	);

	virtual
	void
	remove(
		sanguis::client::draw2d::entities::model::object &
	);

	virtual
	void
	update(
		sanguis::client::draw2d::entities::model::object const &
	);
};

}
}
}
}
}

#endif
