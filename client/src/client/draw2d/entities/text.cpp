#include <sanguis/diff_clock_cref.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/client/draw2d/font_color_format.hpp>
#include <sanguis/client/draw2d/funit.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/own.hpp>
#include <sanguis/client/draw2d/entities/text.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/point.hpp>
#include <sanguis/client/draw2d/sprite/size_or_texture_size.hpp>
#include <sanguis/client/draw2d/sprite/unit.hpp>
#include <sanguis/client/draw2d/sprite/normal/color.hpp>
#include <sanguis/client/draw2d/sprite/normal/no_rotation.hpp>
#include <sanguis/client/draw2d/sprite/normal/object.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_decl.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_ref.hpp>
#include <sge/font/object.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/text_unique_ptr.hpp>
#include <sge/font/align_h/left.hpp>
#include <sge/font/align_h/variant.hpp>
#include <sge/font/draw/create_texture.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/sprite/intrusive/connection.hpp>
#include <sge/sprite/roles/center.hpp>
#include <sge/sprite/roles/color.hpp>
#include <sge/sprite/roles/connection.hpp>
#include <sge/sprite/roles/rotation.hpp>
#include <sge/sprite/roles/size_or_texture_size.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <sge/sprite/types/texture_size.hpp>
#include <sge/texture/const_part_ref.hpp>
#include <sge/texture/part.hpp>
#include <sge/timer/elapsed_fractional.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/unique_ptr_to_const.hpp>
#include <fcppt/cast/float_to_int.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


sanguis::client::draw2d::entities::text::text(
	sanguis::diff_clock_cref const _diff_clock,
	sanguis::client::draw2d::sprite::normal::system_ref const _sprite_system,
	sge::font::object &_font,
	sge::font::string const &_text,
	sanguis::client::draw2d::z_ordering const _z_ordering,
	sanguis::client::draw2d::sprite::center const &_center,
	sanguis::client::draw2d::sprite::normal::color const _color
)
:
	sanguis::client::draw2d::entities::text::text(
		_diff_clock,
		_sprite_system,
		_font.create_text(
			_text,
			sge::font::text_parameters{
				sge::font::align_h::variant{
					sge::font::align_h::left{}
				}
			}
		),
		_z_ordering,
		_center,
		_color
	)
{
}

sanguis::client::draw2d::entities::text::~text()
= default;

sanguis::client::draw2d::entities::text::text(
	sanguis::diff_clock_cref const _diff_clock,
	sanguis::client::draw2d::sprite::normal::system_ref const _sprite_system,
	sge::font::text_unique_ptr &&_text,
	sanguis::client::draw2d::z_ordering const _z_ordering,
	sanguis::client::draw2d::sprite::center const &_center,
	sanguis::client::draw2d::sprite::normal::color const _color
)
:
	sanguis::client::draw2d::entities::own(),
	life_time_(
		sanguis::diff_timer::parameters{
			_diff_clock,
			sanguis::duration_second(
				1.F
			)
		}
	),
	texture_(
		fcppt::unique_ptr_to_const(
			sge::font::draw::create_texture(
				fcppt::make_ref(
					_sprite_system->renderer()
				),
				*_text,
				sanguis::client::draw2d::font_color_format(),
				sge::renderer::texture::emulate_srgb::no
			)
		)
	),
	sprite_(
		sge::sprite::roles::connection{} =
			_sprite_system->connection(
				_z_ordering
			),
		sge::sprite::roles::center{} =
			_center.get()
			-
			fcppt::math::vector::structure_cast<
				sanguis::client::draw2d::sprite::point,
				fcppt::cast::size_fun
			>(
				_text->rect().pos()
			),
		sge::sprite::roles::color{} =
			_color,
		sge::sprite::roles::rotation{} =
			sanguis::client::draw2d::sprite::normal::no_rotation().get(),
		sge::sprite::roles::size_or_texture_size{} =
			sanguis::client::draw2d::sprite::size_or_texture_size{
				sge::sprite::types::texture_size()
			},
		sge::sprite::roles::texture0{} =
			sge::texture::const_part_ref{
				*texture_
			}
	),
	origin_(
		sprite_.center()
	)
{
}

void
sanguis::client::draw2d::entities::text::update()
{
	sprite_.center(
		origin_.get()
		-
		sanguis::client::draw2d::sprite::point{
			fcppt::literal<
				sanguis::client::draw2d::sprite::unit
			>(
				0
			),
			fcppt::cast::float_to_int<
				sanguis::client::draw2d::sprite::unit
			>(
				sge::timer::elapsed_fractional<
					sanguis::client::draw2d::funit
				>(
					life_time_
				)
				*
				fcppt::literal<
					sanguis::client::draw2d::funit
				>(
					100.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
				)
			)
		}
	);
}

bool
sanguis::client::draw2d::entities::text::may_be_removed() const
{
	return
		life_time_.expired();
}
