#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_NORMAL_CHOICES_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_NORMAL_CHOICES_FWD_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/type_choices_fwd.hpp>
#include <sanguis/client/draw2d/sprite/normal/color_format.hpp>
#include <sge/sprite/config/choices_fwd.hpp>
#include <sge/sprite/config/intrusive_fwd.hpp>
#include <sge/sprite/config/normal_size_fwd.hpp>
#include <sge/sprite/config/pos_fwd.hpp>
#include <sge/sprite/config/pos_option.hpp>
#include <sge/sprite/config/texture_coordinates.hpp>
#include <sge/sprite/config/texture_level_count_fwd.hpp>
#include <sge/sprite/config/texture_ownership.hpp>
#include <sge/sprite/config/texture_size_option.hpp>
#include <sge/sprite/config/with_color_fwd.hpp>
#include <sge/sprite/config/with_rotation_fwd.hpp>
#include <sge/sprite/config/with_texture_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal/list/list.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sprite
{
namespace normal
{

typedef
sge::sprite::config::choices<
	sanguis::client::draw2d::sprite::type_choices,
	sge::sprite::config::pos<
		sge::sprite::config::pos_option::center
	>,
	sge::sprite::config::normal_size<
		sge::sprite::config::texture_size_option::maybe
	>,
	metal::list<
		sge::sprite::config::with_rotation,
		sge::sprite::config::with_texture<
			sge::sprite::config::texture_level_count<
				1u
			>,
			sge::sprite::config::texture_coordinates::automatic,
			sge::sprite::config::texture_ownership::reference
		>,
		sge::sprite::config::with_color<
			sanguis::client::draw2d::sprite::normal::color_format
		>,
		sge::sprite::config::intrusive
	>
>
choices;

}
}
}
}
}

#endif
