#ifndef SANGUIS_SERVER_RANDOM_CREATE_FUNCTION_HPP_INCLUDED
#define SANGUIS_SERVER_RANDOM_CREATE_FUNCTION_HPP_INCLUDED

#include <sanguis/server/random/create_function_tag.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/strong_typedef_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server::random
{

template <typename Result, typename Arg>
using create_function = fcppt::strong_typedef<
    fcppt::function<Result(Arg const &)>,
    sanguis::server::random::create_function_tag>;

}

#endif
