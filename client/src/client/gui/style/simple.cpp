#include <sanguis/client/gui/style/simple.hpp>
#include <sanguis/client/load/resource/texture_identifier.hpp>
#include <sanguis/gui/fill_level.hpp>
#include <sanguis/gui/text_color.hpp>
#include <sanguis/client/gui/style/background_color.hpp>
#include <sanguis/client/gui/style/border_color.hpp>
#include <sanguis/client/gui/style/inner_border.hpp>
#include <sanguis/client/gui/style/outer_border.hpp>
#include <sanguis/client/gui/style/spacing.hpp>
#include <sanguis/client/gui/style/text_color.hpp>
#include <sanguis/gui/fill_color.hpp>
#include <sanguis/gui/renderer/base.hpp>
#include <sanguis/gui/style/base.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/padding.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/cast/enum_to_int.hpp>
#include <fcppt/cast/float_to_int.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/math/box/shrink.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/vector/arithmetic.hpp>

sanguis::client::gui::style::simple::simple(
	sanguis::client::load::resource::textures const &_textures
)
:
	sanguis::gui::style::base(),
	textures_(
		_textures)
{
}

sanguis::client::gui::style::simple::~simple()
{
}

sge::rucksack::dim const
sanguis::client::gui::style::simple::button_spacing() const
{
	return
		this->spacing();
}

void
sanguis::client::gui::style::simple::draw_button(
	sanguis::gui::renderer::base &_renderer,
	sge::renderer::context::ffp &_context,
	sge::rucksack::rect const _area
) const
{
	const sge::rucksack::rect::value_type tilesize{12};

	for (auto const &tile :
		{
			std::make_pair<>(sge::rucksack::vector{0,0}, FCPPT_TEXT("hud_frame_transparent_nw")),
			std::make_pair<>(sge::rucksack::vector{_area.size().w() - tilesize,0}, FCPPT_TEXT("hud_frame_transparent_ne")),
			std::make_pair<>(sge::rucksack::vector{_area.size().w() - tilesize,_area.size().h() - tilesize}, FCPPT_TEXT("hud_frame_transparent_se")),
			std::make_pair<>(sge::rucksack::vector{0,_area.size().h() - tilesize}, FCPPT_TEXT("hud_frame_transparent_sw"))
		}
	)
	{
		sge::texture::const_part_shared_ptr part{
			textures_.load(
				sanguis::client::load::resource::texture_identifier{
					tile.second
				}
			)
		};

		_renderer.draw_image(
				_context,
				*part,
				_area.pos() + tile.first
		);
	}

	sge::texture::const_part_shared_ptr part_v{
		textures_.load(
			sanguis::client::load::resource::texture_identifier{
				FCPPT_TEXT("hud_frame_transparent_v")
			}
		)
	};

	sge::texture::const_part_shared_ptr part_h{
		textures_.load(
			sanguis::client::load::resource::texture_identifier{
				FCPPT_TEXT("hud_frame_transparent_h")
			}
		)
	};

	_renderer.draw_image_repeat(
			_context,
			*part_v,
			sge::rucksack::rect{
				sge::rucksack::rect::vector{
					_area.pos() + sge::rucksack::vector{_area.size().w() - tilesize, tilesize}
				},
				sge::rucksack::rect::dim{
					tilesize,
					_area.size().h() - 2 * tilesize
				}
			}
	);

	_renderer.draw_image_repeat(
			_context,
			*part_v,
			sge::rucksack::rect{
				sge::rucksack::rect::vector{
					_area.pos() + sge::rucksack::vector{0,tilesize}
				},
				sge::rucksack::rect::dim{
					tilesize,
					_area.size().h() - 2 * tilesize
				}
			}
	);

	_renderer.draw_image_repeat(
			_context,
			*part_h,
			sge::rucksack::rect{
				sge::rucksack::rect::vector{
					_area.pos() + sge::rucksack::vector{tilesize,0}
				},
				sge::rucksack::rect::dim{
					_area.size().w() - 2 * tilesize,
					tilesize
				}
			}
	);

	_renderer.draw_image_repeat(
			_context,
			*part_h,
			sge::rucksack::rect{
				sge::rucksack::rect::vector{
					_area.pos() + sge::rucksack::vector{tilesize,_area.size().h() - tilesize}
				},
				sge::rucksack::rect::dim{
					_area.size().w() - 2 * tilesize,
					tilesize
				}
			}
	);

}

void
sanguis::client::gui::style::simple::draw_bar(
	sanguis::gui::renderer::base &_renderer,
	sge::renderer::context::ffp &_context,
	sge::rucksack::rect const _area,
	sge::rucksack::axis const _axis,
	sanguis::gui::fill_level const _fill_level,
	sanguis::gui::fill_color const &_fill_color
) const
{
	_renderer.fill_rect(
		_context,
		_area,
		sanguis::client::gui::style::border_color()
	);

	sge::rucksack::rect const inner_rect(
		fcppt::math::box::shrink(
			_area,
			sge::rucksack::vector(
				sanguis::client::gui::style::outer_border::value,
				sanguis::client::gui::style::outer_border::value
			)
		)
	);

	_renderer.fill_rect(
		_context,
		inner_rect,
		sanguis::client::gui::style::background_color()
	);

	sge::rucksack::scalar const fill_size(
		fcppt::cast::float_to_int<
			sge::rucksack::scalar
		>(
			fcppt::cast::int_to_float<
				sanguis::gui::fill_level::value_type
			>(
				inner_rect.size()[
					// TODO: Make a function in rucksack for this
					fcppt::cast::enum_to_int<
						fcppt::math::size_type
					>(
						_axis
					)
				]
			)
			*
			_fill_level.get()
		)
	);

	_renderer.fill_rect(
		_context,
		sge::rucksack::rect(
			_axis
			==
			sge::rucksack::axis::y
			?
				sge::rucksack::vector(
					inner_rect.pos().x(),
					inner_rect.pos().y()
					+
					inner_rect.h()
					-
					fill_size
				)
			:
				inner_rect.pos()
			,
			sge::rucksack::dim(
				_axis
				==
				sge::rucksack::axis::x
				?
					fill_size
				:
					inner_rect.w()
				,
				_axis
				==
				sge::rucksack::axis::y
				?
					fill_size
				:
					inner_rect.h()
			)
		),
		_fill_color.get()
	);

}

sge::rucksack::padding const
sanguis::client::gui::style::simple::frame_padding() const
{
	return
		sge::rucksack::padding{
			10
		};
}

void
sanguis::client::gui::style::simple::draw_frame(
	sanguis::gui::renderer::base &_renderer,
	sge::renderer::context::ffp &_context,
	sge::rucksack::rect const _area,
	sge::rucksack::padding const _padding
) const
{
	sge::rucksack::scalar const border_size(
		_padding.get()
		/
		2
	);


	_renderer.fill_rect(
		_context,
		sge::rucksack::rect(
			_area.pos(),
			sge::rucksack::dim(
				_area.w(),
				border_size
			)
		),
		sanguis::client::gui::style::border_color()
	);

	_renderer.fill_rect(
		_context,
		sge::rucksack::rect(
			_area.pos(),
			sge::rucksack::dim(
				border_size,
				_area.h()
			)
		),
		sanguis::client::gui::style::border_color()
	);

	_renderer.fill_rect(
		_context,
		sge::rucksack::rect(
			_area.pos()
			+
			sge::rucksack::dim(
				_area.w()
				-
				border_size,
				0
			),
			sge::rucksack::dim(
				border_size,
				_area.h()
			)
		),
		sanguis::client::gui::style::border_color()
	);

	_renderer.fill_rect(
		_context,
		sge::rucksack::rect(
			_area.pos()
			+
			sge::rucksack::dim(
				0,
				_area.h()
				-
				border_size
			),
			sge::rucksack::dim(
				_area.w(),
				border_size
			)
		),
		sanguis::client::gui::style::border_color()
	);
}

sge::rucksack::dim const
sanguis::client::gui::style::simple::edit_spacing() const
{
	return
		this->spacing();
}

void
sanguis::client::gui::style::simple::draw_edit(
	sanguis::gui::renderer::base &_renderer,
	sge::renderer::context::ffp &_context,
	sge::rucksack::rect const _area
) const
{
	_renderer.fill_rect(
		_context,
		_area,
		sanguis::client::gui::style::border_color()
	);

	_renderer.fill_rect(
		_context,
		sge::rucksack::rect(
			_area.pos()
			+
			sanguis::client::gui::style::outer_border::value,
			_area.size()
			-
			2
			*
			sanguis::client::gui::style::outer_border::value
		),
		sanguis::client::gui::style::background_color()
	);
}

sge::rucksack::dim const
sanguis::client::gui::style::simple::image_spacing() const
{
	return
		sge::rucksack::dim::null();
}

sge::rucksack::dim const
sanguis::client::gui::style::simple::text_spacing() const
{
	return
		sge::rucksack::dim::null();
}

void
sanguis::client::gui::style::simple::draw_image(
	sanguis::gui::renderer::base &,
	sge::renderer::context::ffp &,
	sge::rucksack::rect
) const
{
}

void
sanguis::client::gui::style::simple::draw_text(
	sanguis::gui::renderer::base &,
	sge::renderer::context::ffp &,
	sge::rucksack::rect
) const
{
}

sanguis::gui::text_color
sanguis::client::gui::style::simple::text_color() const
{
	return
		sanguis::gui::text_color(
			sanguis::client::gui::style::text_color()
		);
}

sge::rucksack::dim const
sanguis::client::gui::style::simple::spacing() const
{
	return
		fcppt::math::dim::fill<
			sge::rucksack::dim::dim_wrapper::value
		>(
			sanguis::client::gui::style::spacing::value
		);
}