#ifndef SANGUIS_CREATOR_IMPL_GENERATOR_MAP_TYPE_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_GENERATOR_MAP_TYPE_HPP_INCLUDED

#include <sanguis/creator/name.hpp>
#include <sanguis/creator/impl/generator_function.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace creator
{
namespace impl
{

using
generator_map_type
=
std::unordered_map<
	sanguis::creator::name,
	sanguis::creator::impl::generator_function
>;

}
}
}

#endif
