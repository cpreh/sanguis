#include <sanguis/gui/impl/draw_image.hpp>
#include <sanguis/gui/impl/draw_sprite.hpp>
#include <sanguis/gui/impl/image_sprite_choices.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/sprite/config/texture_coordinates.hpp>
#include <sge/texture/const_optional_part_ref.hpp>
#include <sge/texture/part_fwd.hpp>


void
sanguis::gui::impl::draw_image(
	sge::renderer::device::ffp &_renderer,
	sge::renderer::context::ffp &_context,
	sge::texture::part const &_texture,
	sge::rucksack::vector const _pos
)
{
	typedef
	sge::sprite::parameters<
		sanguis::gui::impl::image_sprite_choices<
			sge::sprite::config::texture_coordinates::automatic
		>
	>
	parameters;

	sanguis::gui::impl::draw_sprite(
		_renderer,
		_context,
		parameters()
		.pos(
			_pos
		)
		.texture(
			sge::texture::const_optional_part_ref(
				_texture
			)
		)
		.texture_size()
	);
}
