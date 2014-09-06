#include <sanguis/enemy_kind.hpp>
#include <sanguis/client/draw2d/entities/enemy_color.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::image::color::any::object
sanguis::client::draw2d::entities::enemy_color(
	sanguis::enemy_kind const _kind
)
{
	switch(
		_kind
	)
	{
	case sanguis::enemy_kind::normal:
		return
			sge::image::color::predef::white();
	case sanguis::enemy_kind::champion:
		return
			sge::image::color::predef::blue();
	case sanguis::enemy_kind::unique:
		return
			sge::image::color::predef::gold();
	}

	FCPPT_ASSERT_UNREACHABLE;
}
