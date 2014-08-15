#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_BUFFERS_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_BUFFERS_FWD_HPP_INCLUDED

#include <sge/sprite/buffers/single_fwd.hpp>
#include <sge/sprite/buffers/with_declaration_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sprite
{

template<
	typename Choices
>
using buffers
=
sge::sprite::buffers::with_declaration<
	sge::sprite::buffers::single<
		Choices
	>
>;

}
}
}
}

#endif
