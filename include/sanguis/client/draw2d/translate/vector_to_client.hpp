#ifndef SANGUIS_CLIENT_DRAW2D_TRANSLATE_VECTOR_TO_CLIENT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_TRANSLATE_VECTOR_TO_CLIENT_HPP_INCLUDED

#include <sanguis/client/draw2d/vector2.hpp>
#include <sanguis/messages/types/vector2.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace translate
{

draw2d::vector2 const
vector_to_client(
	messages::types::vector2 const &
);

}
}
}
}

#endif
