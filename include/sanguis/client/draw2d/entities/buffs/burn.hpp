#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_BUFFS_BURN_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_BUFFS_BURN_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/buffs/base.hpp>
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

class burn
:
	public sanguis::client::draw2d::entities::buffs::base
{
	FCPPT_NONCOPYABLE(
		burn
	);
public:
	burn();

	~burn();
private:
	void
	update(
		sanguis::client::draw2d::entities::model::object const &
	)
	override;
};

}
}
}
}
}

#endif
