#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_PARTICLE_CHOICES_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_PARTICLE_CHOICES_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/type_choices.hpp>
#include <sanguis/client/draw2d/sprite/particle/color_format.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/custom_center.hpp>
#include <sge/sprite/config/intrusive.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <sge/sprite/config/texture_coordinates.hpp>
#include <sge/sprite/config/texture_level_count.hpp>
#include <sge/sprite/config/texture_ownership.hpp>
#include <sge/sprite/config/with_color.hpp>
#include <sge/sprite/config/with_depth.hpp>
#include <sge/sprite/config/with_rotation.hpp>
#include <sge/sprite/config/with_texture.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sprite
{
namespace particle
{

typedef sge::sprite::config::choices<
	sprite::type_choices,
	sge::sprite::config::normal_size,
	boost::mpl::vector5<
		sge::sprite::config::with_rotation<
			sge::sprite::config::custom_center<
				false
			>
		>,
		sge::sprite::config::with_texture<
			sge::sprite::config::texture_level_count<
				1u
			>,
			sge::sprite::config::texture_coordinates::automatic,
			sge::sprite::config::texture_ownership::shared
		>,
		sge::sprite::config::with_depth,
		sge::sprite::config::with_color<
			sprite::particle::color_format
		>,
		sge::sprite::config::intrusive
	>
> choices;

}
}
}
}
}

#endif
