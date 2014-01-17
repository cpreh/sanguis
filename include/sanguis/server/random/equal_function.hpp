#ifndef SANGUIS_SERVER_RANDOM_EQUAL_FUNCTION_HPP_INCLUDED
#define SANGUIS_SERVER_RANDOM_EQUAL_FUNCTION_HPP_INCLUDED

#include <sanguis/server/random/equal_function_tag.hpp>
#include <fcppt/strong_typedef_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace random
{

template<
	typename Arg
>
using
equal_function
=
fcppt::strong_typedef<
	std::function<
		bool (
			Arg const &,
			Arg const &
		)
	>,
	sanguis::server::random::equal_function_tag
>;

}
}
}

#endif
