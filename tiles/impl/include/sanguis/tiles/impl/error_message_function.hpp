#ifndef SANGUIS_TILES_IMPL_ERROR_MESSAGE_FUNCTION_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_ERROR_MESSAGE_FUNCTION_HPP_INCLUDED

#include <fcppt/function_impl.hpp>
#include <fcppt/string.hpp>


namespace sanguis
{
namespace tiles
{
namespace impl
{

typedef
fcppt::function<
	fcppt::string ()
>
error_message_function;

}
}
}

#endif
