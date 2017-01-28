#ifndef SANGUIS_SERVER_ARGS_PARSER_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_ARGS_PARSER_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/args/result_fwd.hpp>
#include <fcppt/options/base_unique_ptr.hpp>


namespace sanguis
{
namespace server
{
namespace args
{

typedef
fcppt::options::base_unique_ptr<
	sanguis::server::args::result
>
parser_unique_ptr;

}
}
}

#endif
