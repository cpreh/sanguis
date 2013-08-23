#ifndef SANGUIS_LOAD_RESOURCE_TEXTURE_NAME_MAP_HPP_INCLUDED
#define SANGUIS_LOAD_RESOURCE_TEXTURE_NAME_MAP_HPP_INCLUDED

#include <sanguis/load/resource/texture_identifier.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace load
{
namespace resource
{

typedef std::unordered_map<
	sanguis::load::resource::texture_identifier,
	fcppt::string
> texture_name_map;

}
}
}

#endif
