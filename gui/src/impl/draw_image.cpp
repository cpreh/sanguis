#include <sanguis/gui/impl/draw_image.hpp>
#include <sanguis/gui/impl/draw_sprite.hpp>
#include <sanguis/gui/impl/image_sprite_choices.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/config/texture_coordinates.hpp>
#include <sge/sprite/config/texture_size_option.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/texture0.hpp>
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
	sanguis::gui::impl::draw_sprite(
		_renderer,
		_context,
		sge::sprite::object<
			sanguis::gui::impl::image_sprite_choices<
				sge::sprite::config::texture_coordinates::automatic,
				sge::sprite::config::texture_size_option::always
			>
		>(
			sge::sprite::roles::pos{} =
				_pos,
			sge::sprite::roles::texture0{} =
				sge::texture::const_optional_part_ref(
					_texture
				)
		)
	);
}
