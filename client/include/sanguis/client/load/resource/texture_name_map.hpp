#ifndef SANGUIS_CLIENT_LOAD_RESOURCE_TEXTURE_NAME_MAP_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_RESOURCE_TEXTURE_NAME_MAP_HPP_INCLUDED

#include <sanguis/client/load/resource/texture_identifier.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sanguis::client::load::resource
{

using
texture_name_map
=
std::unordered_map<
	sanguis::client::load::resource::texture_identifier,
	std::filesystem::path
>;

}

#endif
