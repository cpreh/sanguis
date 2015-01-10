#include <sanguis/gui/aux_/draw_image_repeat.hpp>
#include <sanguis/gui/aux_/draw_sprite.hpp>
#include <sanguis/gui/aux_/image_sprite_choices.hpp>
#include <sanguis/gui/aux_/sprite_type_choices.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/sprite/config/texture_coordinates.hpp>
#include <sge/sprite/types/repetition.hpp>
#include <sge/texture/const_optional_part_ref.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/cast/int_to_float_fun.hpp>
#include <fcppt/math/dim/to_vector.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


void
sanguis::gui::aux_::draw_image_repeat(
	sge::renderer::device::ffp &_renderer,
	sge::renderer::context::ffp &_context,
	sge::texture::part const &_texture,
	sge::rucksack::rect const _rect
)
{
	typedef
	sge::sprite::parameters<
		sanguis::gui::aux_::image_sprite_choices<
			sge::sprite::config::texture_coordinates::repetition
		>
	>
	parameters;

	typedef
	sge::sprite::types::repetition<
		sanguis::gui::aux_::sprite_type_choices
	>
	repetition_type;

	sanguis::gui::aux_::draw_sprite(
		_renderer,
		_context,
		parameters()
		.pos(
			_rect.pos()
		)
		.texture(
			sge::texture::const_optional_part_ref(
				_texture
			)
		)
		.repetition(
			fcppt::math::vector::structure_cast<
				repetition_type,
				fcppt::cast::int_to_float_fun
			>(
				fcppt::math::dim::to_vector(
					_rect.size()
				)
			)
			/
			fcppt::math::vector::structure_cast<
				repetition_type,
				fcppt::cast::int_to_float_fun
			>(
				fcppt::math::dim::to_vector(
					_texture.size()
				)
			)
		)
		.size(
			_rect.size()
		)
	);
}
