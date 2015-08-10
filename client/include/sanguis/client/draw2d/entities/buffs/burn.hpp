#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_BUFFS_BURN_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_BUFFS_BURN_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/client/draw2d/entities/buffs/base.hpp>
#include <sanguis/client/draw2d/entities/model/object_fwd.hpp>
#include <sanguis/client/draw2d/sprite/animation/texture.hpp>
#include <sanguis/client/draw2d/sprite/normal/object_decl.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_fwd.hpp>
#include <sanguis/client/load/model/collection_fwd.hpp>
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
	burn(
		sanguis::diff_clock const &,
		sanguis::client::draw2d::sprite::normal::system &,
		sanguis::client::load::model::collection const &,
		sanguis::client::draw2d::entities::model::object const &
	);

	~burn()
	override;
private:
	void
	update(
		sanguis::client::draw2d::entities::model::object const &
	)
	override;

	sanguis::client::draw2d::sprite::animation::texture animation_;

	sanguis::client::draw2d::sprite::normal::object sprite_;
};

}
}
}
}
}

#endif
