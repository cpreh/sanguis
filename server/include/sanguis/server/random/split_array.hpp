#ifndef SANGUIS_SERVER_RANDOM_SPLIT_ARRAY_HPP_INCLUDED
#define SANGUIS_SERVER_RANDOM_SPLIT_ARRAY_HPP_INCLUDED

#include <sanguis/server/random/amount.hpp>
#include <fcppt/array/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server::random
{

template <std::size_t Size>
using split_array = fcppt::array::object<sanguis::server::random::amount, Size>;

}

#endif
