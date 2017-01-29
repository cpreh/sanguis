#ifndef SANGUIS_CLIENT_ARGS_PARSER_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_ARGS_PARSER_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/client/args/result_fwd.hpp>
#include <fcppt/options/base_unique_ptr.hpp>


namespace sanguis
{
namespace client
{
namespace args
{

typedef
fcppt::options::base_unique_ptr<
	sanguis::client::args::result
>
parser_unique_ptr;

}
}
}

#endif
