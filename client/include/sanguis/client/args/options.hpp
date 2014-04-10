#ifndef SANGUIS_CLIENT_ARGS_OPTIONS_HPP_INCLUDED
#define SANGUIS_CLIENT_ARGS_OPTIONS_HPP_INCLUDED

#include <sanguis/client/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/options_description.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace args
{

SANGUIS_CLIENT_SYMBOL
boost::program_options::options_description
options();

}
}
}

#endif
