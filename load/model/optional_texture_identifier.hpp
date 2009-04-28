#ifndef SANGUIS_LOAD_MODEL_OPTIONAL_TEXTURE_IDENTIFIER_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_OPTIONAL_TEXTURE_IDENTIFIER_HPP_INCLUDED

#include "../resource/texture_identifier.hpp"
#include <sge/optional_fwd.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

typedef sge::optional<
	resource::texture_identifier
> optional_texture_identifier;

}
}
}

#endif
