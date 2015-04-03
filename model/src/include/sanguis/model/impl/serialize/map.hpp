#ifndef SANGUIS_MODEL_IMPL_SERIALIZE_MAP_HPP_INCLUDED
#define SANGUIS_MODEL_IMPL_SERIALIZE_MAP_HPP_INCLUDED

#include <sge/parse/json/member.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/string.hpp>
#include <fcppt/algorithm/map.hpp>


namespace sanguis
{
namespace model
{
namespace impl
{
namespace serialize
{

template<
	typename Map
>
sge::parse::json::member
map(
	Map const &_map,
	sge::parse::json::string const &_name,
	sge::parse::json::object (
		*_serialize_inner
	)(
		typename Map::mapped_type const &
	)
)
{
	return
		sge::parse::json::member(
			_name,
			sge::parse::json::object(
				fcppt::algorithm::map<
					sge::parse::json::member_map
				>(
					_map,
					[
						_serialize_inner
					](
						typename Map::value_type const &_pair
					)
					{
						return
							sge::parse::json::member(
								_pair.first.get(),
								_serialize_inner(
									_pair.second
								)
							);
					}
				)
			)
		);
}

}
}
}
}

#endif
