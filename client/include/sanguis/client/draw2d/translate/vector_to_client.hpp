#ifndef SANGUIS_CLIENT_DRAW2D_TRANSLATE_VECTOR_TO_CLIENT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_TRANSLATE_VECTOR_TO_CLIENT_HPP_INCLUDED

#include <sanguis/client/draw2d/vector2_fwd.hpp>
#include <sanguis/messages/types/vector2_fwd.hpp>


namespace sanguis::client::draw2d::translate
{

sanguis::client::draw2d::vector2
vector_to_client(
	sanguis::messages::types::vector2 const &
);

}

#endif
