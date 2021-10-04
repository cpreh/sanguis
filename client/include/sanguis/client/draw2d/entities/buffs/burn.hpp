#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_BUFFS_BURN_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_BUFFS_BURN_HPP_INCLUDED

#include <sanguis/diff_clock_cref.hpp>
#include <sanguis/client/draw2d/entities/buffs/base.hpp>
#include <sanguis/client/draw2d/entities/model/object_fwd.hpp>
#include <sanguis/client/draw2d/sprite/animation/texture.hpp>
#include <sanguis/client/draw2d/sprite/normal/object_decl.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_ref.hpp>
#include <sanguis/client/load/model/collection_cref.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::client::draw2d::entities::buffs
{

class burn
:
	public sanguis::client::draw2d::entities::buffs::base
{
	FCPPT_NONMOVABLE(
		burn
	);
public:
	burn(
		sanguis::diff_clock_cref,
		sanguis::client::draw2d::sprite::normal::system_ref,
		sanguis::client::load::model::collection_cref,
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

#endif
