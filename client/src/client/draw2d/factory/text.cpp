#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/own.hpp>
#include <sanguis/client/draw2d/entities/own_unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/text.hpp>
#include <sanguis/client/draw2d/factory/text.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/normal/color.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_fwd.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sanguis::client::draw2d::entities::own_unique_ptr
sanguis::client::draw2d::factory::text(
	sanguis::diff_clock const &_diff_clock,
	sanguis::client::draw2d::sprite::normal::system &_normal_system,
	sge::font::object &_font,
	sge::font::string const &_text,
	sanguis::client::draw2d::sprite::center const _center,
	sanguis::client::draw2d::sprite::normal::color const _color
)
{
	return
		fcppt::unique_ptr_to_base<
			sanguis::client::draw2d::entities::own
		>(
			fcppt::make_unique_ptr_fcppt<
				sanguis::client::draw2d::entities::text
			>(
				_diff_clock,
				_normal_system,
				_font,
				_text,
				sanguis::client::draw2d::z_ordering::flare,
				_center,
				_color
			)
		);
}
