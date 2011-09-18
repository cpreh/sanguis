#ifndef SANGUIS_LOAD_MODEL_FIND_TEXTURE_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_FIND_TEXTURE_HPP_INCLUDED

#include <sanguis/load/model/optional_texture_identifier.hpp>
#include <sge/parse/json/member_vector.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

optional_texture_identifier const
find_texture(
	sge::parse::json::member_vector const &
);

}
}
}

#endif
