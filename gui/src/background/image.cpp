#include <sanguis/gui/aux_/draw_image_stretched.hpp>
#include <sanguis/gui/background/base.hpp>
#include <sanguis/gui/background/image.hpp>
#include <sanguis/gui/main_area/base_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/rect.hpp>


sanguis::gui::background::image::image(
	sge::renderer::device::ffp &_renderer,
	sanguis::gui::main_area::base &_main_area,
	sge::texture::const_part_shared_ptr const _texture
)
:
	sanguis::gui::background::base(
		_main_area
	),
	renderer_(
		_renderer
	),
	texture_(
		_texture
	)
{
}

sanguis::gui::background::image::~image()
{
}

void
sanguis::gui::background::image::on_draw(
	sge::renderer::context::ffp &_context,
	sge::rucksack::rect const _area
)
{
	sanguis::gui::aux_::draw_image_stretched(
		renderer_,
		_context,
		*texture_,
		_area
	);
}
