#ifndef SANGUIS_TILES_IMPL_ERROR_MESSAGE_FUNCTION_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_ERROR_MESSAGE_FUNCTION_HPP_INCLUDED

#include <fcppt/function_impl.hpp>
#include <fcppt/string.hpp>


namespace sanguis::tiles::impl
{

using
error_message_function
=
fcppt::function<
	fcppt::string ()
>;

}

#endif
