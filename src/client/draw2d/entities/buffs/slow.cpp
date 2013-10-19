#include <sanguis/client/draw2d/entities/buffs/base.hpp>
#include <sanguis/client/draw2d/entities/buffs/slow.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/sprite/normal/color.hpp>
#include <sanguis/client/draw2d/sprite/normal/color_format.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/image/color/any/object.hpp>


sanguis::client::draw2d::entities::buffs::slow::slow()
:
	sanguis::client::draw2d::entities::buffs::base()
{
}

sanguis::client::draw2d::entities::buffs::slow::~slow()
{
}

void
sanguis::client::draw2d::entities::buffs::slow::apply(
	sanguis::client::draw2d::entities::model::object &_model
)
{
	_model.color(
		sge::image::color::any::convert<
			sanguis::client::draw2d::sprite::normal::color_format
		>(
			sge::image::color::predef::blue()
		)
	);
}

void
sanguis::client::draw2d::entities::buffs::slow::remove(
	sanguis::client::draw2d::entities::model::object &_model
)
{
	// TODO: We should restore the previous color
	_model.color(
		sge::image::color::any::convert<
			sanguis::client::draw2d::sprite::normal::color_format
		>(
			sge::image::color::predef::white()
		)
	);
}
