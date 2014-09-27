#ifndef SANGUIS_CLIENT_LOAD_RESOURCE_TEXTURE_NAME_MAP_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_RESOURCE_TEXTURE_NAME_MAP_HPP_INCLUDED

#include <sanguis/client/load/resource/texture_identifier.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace resource
{

typedef
std::unordered_map<
	sanguis::client::load::resource::texture_identifier,
	boost::filesystem::path
>
texture_name_map;

}
}
}
}

#endif
