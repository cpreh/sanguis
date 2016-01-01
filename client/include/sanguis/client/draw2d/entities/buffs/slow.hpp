#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_BUFFS_SLOW_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_BUFFS_SLOW_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/buffs/base.hpp>
#include <sanguis/client/draw2d/entities/model/object_fwd.hpp>
#include <sanguis/client/draw2d/sprite/normal/color.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional/object_decl.hpp>


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

class slow
:
	public sanguis::client::draw2d::entities::buffs::base
{
	FCPPT_NONCOPYABLE(
		slow
	);
public:
	slow();

	~slow()
	override;
private:
	void
	apply(
		sanguis::client::draw2d::entities::model::object &
	)
	override;

	void
	remove(
		sanguis::client::draw2d::entities::model::object &
	)
	override;

	typedef
	fcppt::optional::object<
		sanguis::client::draw2d::sprite::normal::color
	>
	optional_color;

	optional_color previous_color_;
};

}
}
}
}
}

#endif
