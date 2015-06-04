#ifndef SANGUIS_SERVER_WORLD_PLACE_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_PLACE_CALLBACK_HPP_INCLUDED

#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

template<
	typename Type
>
using
place_callback
=
std::function<
	fcppt::unique_ptr<
		Type
	> ()
>;

}
}
}

#endif
