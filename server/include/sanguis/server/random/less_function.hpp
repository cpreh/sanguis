#ifndef SANGUIS_SERVER_RANDOM_LESS_FUNCTION_HPP_INCLUDED
#define SANGUIS_SERVER_RANDOM_LESS_FUNCTION_HPP_INCLUDED

#include <sanguis/server/random/less_function_tag.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/strong_typedef_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sanguis::server::random
{

template<
	typename Arg
>
using
less_function
=
fcppt::strong_typedef<
	fcppt::function<
		bool (
			Arg const &,
			Arg const &
		)
	>,
	sanguis::server::random::less_function_tag
>;

}

#endif
