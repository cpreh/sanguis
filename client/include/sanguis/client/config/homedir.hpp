#ifndef SANGUIS_CLIENT_CONFIG_HOMEDIR_HPP_INCLUDED
#define SANGUIS_CLIENT_CONFIG_HOMEDIR_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace config
{

std::filesystem::path
homedir();

}
}
}

#endif
