#ifndef SANGUIS_CLIENT_CONFIG_HOMEDIR_HPP_INCLUDED
#define SANGUIS_CLIENT_CONFIG_HOMEDIR_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace config
{

boost::filesystem::path const
homedir();

}
}
}

#endif
