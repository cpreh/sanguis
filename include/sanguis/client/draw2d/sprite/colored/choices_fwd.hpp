#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_COLORED_CHOICES_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_COLORED_CHOICES_FWD_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/type_choices_fwd.hpp>
#include <sanguis/client/draw2d/sprite/colored/color_format.hpp>
#include <sge/sprite/config/choices_fwd.hpp>
#include <sge/sprite/config/intrusive_fwd.hpp>
#include <sge/sprite/config/normal_size_fwd.hpp>
#include <sge/sprite/config/with_color_fwd.hpp>
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
namespace colored
{

typedef sge::sprite::config::choices<
	sanguis::client::draw2d::sprite::type_choices,
	sge::sprite::config::normal_size,
	boost::mpl::vector2<
		sge::sprite::config::with_color<
			sanguis::client::draw2d::sprite::colored::color_format
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
