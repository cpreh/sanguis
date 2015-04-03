#ifndef SANGUIS_CREATOR_IMPL_GENERATOR_MAP_TYPE_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_GENERATOR_MAP_TYPE_HPP_INCLUDED

#include <sanguis/creator/name.hpp>
#include <sanguis/creator/impl/generator_function.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace creator
{
namespace impl
{

typedef
std::map<
	sanguis::creator::name,
	sanguis::creator::impl::generator_function
>
generator_map_type;

}
}
}

#endif
