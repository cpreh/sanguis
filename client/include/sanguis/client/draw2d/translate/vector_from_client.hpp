#ifndef SANGUIS_CLIENT_DRAW2D_TRANSLATE_VECTOR_FROM_CLIENT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_TRANSLATE_VECTOR_FROM_CLIENT_HPP_INCLUDED

#include <sanguis/client/draw2d/vector2_fwd.hpp>
#include <sanguis/messages/types/vector2_fwd.hpp>


namespace sanguis::client::draw2d::translate
{

sanguis::messages::types::vector2
vector_from_client(
	sanguis::client::draw2d::vector2 const &
);

}

#endif
