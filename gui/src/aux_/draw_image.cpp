#include <sanguis/gui/aux_/draw_image.hpp>
#include <sanguis/gui/aux_/draw_sprite.hpp>
#include <sanguis/gui/aux_/sprite_type_choices.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <sge/sprite/config/texture_coordinates.hpp>
#include <sge/sprite/config/texture_level_count.hpp>
#include <sge/sprite/config/texture_ownership.hpp>
#include <sge/sprite/config/with_texture.hpp>
#include <sge/texture/const_optional_part_ref.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


void
sanguis::gui::aux_::draw_image(
	sge::renderer::device::ffp &_renderer,
	sge::renderer::context::ffp &_context,
	sge::texture::part const &_texture,
	sge::rucksack::vector const _pos
)
{
	typedef
	sge::sprite::config::choices<
		sanguis::gui::aux_::sprite_type_choices,
		sge::sprite::config::normal_size,
		boost::mpl::vector1<
			sge::sprite::config::with_texture<
				sge::sprite::config::texture_level_count<
					1u
				>,
				sge::sprite::config::texture_coordinates::automatic,
				sge::sprite::config::texture_ownership::reference
			>
		>
	>
	choices;

	typedef
	sge::sprite::parameters<
		choices
	>
	parameters;

	sanguis::gui::aux_::draw_sprite(
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
