#ifndef SANGUIS_LOAD_MODEL_FIND_TEXTURE_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_FIND_TEXTURE_HPP_INCLUDED

#include <sanguis/load/model/optional_texture_identifier_fwd.hpp>
#include <sge/parse/json/object_fwd.hpp>


namespace sanguis
{
namespace load
{
namespace model
{

sanguis::load::model::optional_texture_identifier
find_texture(
	sge::parse::json::object const &
);

}
}
}

#endif
