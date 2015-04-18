#ifndef SANGUIS_GUI_IMPL_IMAGE_SPRITE_CHOICES_HPP_INCLUDED
#define SANGUIS_GUI_IMPL_IMAGE_SPRITE_CHOICES_HPP_INCLUDED

#include <sanguis/gui/impl/sprite_type_choices.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <sge/sprite/config/pos.hpp>
#include <sge/sprite/config/pos_option.hpp>
#include <sge/sprite/config/texture_coordinates.hpp>
#include <sge/sprite/config/texture_level_count.hpp>
#include <sge/sprite/config/texture_ownership.hpp>
#include <sge/sprite/config/texture_size_option.hpp>
#include <sge/sprite/config/with_texture.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>



namespace sanguis
{
namespace gui
{
namespace impl
{

template<
	sge::sprite::config::texture_coordinates TextureCoordinates,
	sge::sprite::config::texture_size_option TextureSize
>
using
image_sprite_choices
=
sge::sprite::config::choices<
	sanguis::gui::impl::sprite_type_choices,
	sge::sprite::config::pos<
		sge::sprite::config::pos_option::pos
	>,
	sge::sprite::config::normal_size<
		TextureSize
	>,
	boost::mpl::vector1<
		sge::sprite::config::with_texture<
			sge::sprite::config::texture_level_count<
				1u
			>,
			TextureCoordinates,
			sge::sprite::config::texture_ownership::reference
		>
	>
>;

}
}
}

#endif
