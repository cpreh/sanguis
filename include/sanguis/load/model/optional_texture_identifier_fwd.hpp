#ifndef SANGUIS_LOAD_MODEL_OPTIONAL_TEXTURE_IDENTIFIER_FWD_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_OPTIONAL_TEXTURE_IDENTIFIER_FWD_HPP_INCLUDED

#include <sanguis/load/resource/texture_identifier.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{
namespace load
{
namespace model
{

typedef fcppt::optional<
	sanguis::load::resource::texture_identifier
> optional_texture_identifier;

}
}
}

#endif
