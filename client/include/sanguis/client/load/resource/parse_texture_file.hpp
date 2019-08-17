#ifndef SANGUIS_CLIENT_LOAD_RESOURCE_PARSE_TEXTURE_FILE_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_RESOURCE_PARSE_TEXTURE_FILE_HPP_INCLUDED

#include <sanguis/client/load/resource/texture_name_map.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace resource
{

sanguis::client::load::resource::texture_name_map
parse_texture_file(
	fcppt::log::object &,
	std::filesystem::path const &,
	sanguis::client::load::resource::texture_name_map &&
);

}
}
}
}

#endif
