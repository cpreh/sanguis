#include <sanguis/client/draw2d/entities/buffs/base.hpp>
#include <sanguis/client/draw2d/entities/buffs/slow.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/sprite/normal/color.hpp>
#include <sanguis/client/draw2d/sprite/normal/color_format.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/image/color/any/object.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/assert/pre.hpp>


sanguis::client::draw2d::entities::buffs::slow::slow()
:
	sanguis::client::draw2d::entities::buffs::base(),
	previous_color_()
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
	FCPPT_ASSERT_PRE(
		!previous_color_.has_value()
	);

	previous_color_ =
		optional_color(
			_model.color()
		);

	_model.color(
		sge::image::color::any::convert<
			sanguis::client::draw2d::sprite::normal::color_format
		>(
			sge::image::color::predef::lightblue()
		)
	);
}

void
sanguis::client::draw2d::entities::buffs::slow::remove(
	sanguis::client::draw2d::entities::model::object &_model
)
{
	_model.color(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			previous_color_
		)
	);

	previous_color_ =
		optional_color();
}
