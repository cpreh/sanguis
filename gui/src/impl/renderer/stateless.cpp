#include <sanguis/gui/impl/draw_image.hpp>
#include <sanguis/gui/impl/draw_image_repeat.hpp>
#include <sanguis/gui/impl/fill_rect.hpp>
#include <sanguis/gui/impl/renderer/stateless.hpp>
#include <sanguis/gui/renderer/base.hpp>
#include <sge/font/draw/set_matrices.hpp>
#include <sge/font/draw/set_states.hpp>
#include <sge/font/draw/static_text.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/texture/part_fwd.hpp>


sanguis::gui::impl::renderer::stateless::stateless(
	sge::renderer::device::ffp &_renderer
)
:
	sanguis::gui::renderer::base(),
	renderer_(
		_renderer
	)
{
}

sanguis::gui::impl::renderer::stateless::~stateless()
{
}

void
sanguis::gui::impl::renderer::stateless::fill_rect(
	sge::renderer::context::ffp &_context,
	sge::rucksack::rect const _rect,
	sge::image::color::any::object const &_color
)
{
	sanguis::gui::impl::fill_rect(
		renderer_,
		_context,
		_rect,
		_color
	);
}

void
sanguis::gui::impl::renderer::stateless::draw_image(
	sge::renderer::context::ffp &_context,
	sge::texture::part const &_texture,
	sge::rucksack::vector const _pos
)
{
	sanguis::gui::impl::draw_image(
		renderer_,
		_context,
		_texture,
		_pos
	);
}

void
sanguis::gui::impl::renderer::stateless::draw_image_repeat(
	sge::renderer::context::ffp &_context,
	sge::texture::part const &_texture,
	sge::rucksack::rect const _area
)
{
	sanguis::gui::impl::draw_image_repeat(
		renderer_,
		_context,
		_texture,
		_area
	);
}

void
sanguis::gui::impl::renderer::stateless::draw_static_text(
	sge::renderer::context::ffp &_context,
	sge::font::draw::static_text const &_static_text
)
{
	_static_text.draw_advanced(
		_context,
		sge::font::draw::set_matrices(
			false
		),
		sge::font::draw::set_states(
			false
		)
	);
}
