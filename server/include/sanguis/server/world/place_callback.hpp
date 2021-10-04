#ifndef SANGUIS_SERVER_WORLD_PLACE_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_PLACE_CALLBACK_HPP_INCLUDED

#include <fcppt/function_impl.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis::server::world
{

template<
	typename Type
>
using
place_callback
=
fcppt::function<
	fcppt::unique_ptr<
		Type
	> ()
>;

}

#endif
