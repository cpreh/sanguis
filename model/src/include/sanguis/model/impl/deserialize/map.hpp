#ifndef SANGUIS_MODEL_IMPL_DESERIALIZE_MAP_HPP_INCLUDED
#define SANGUIS_MODEL_IMPL_DESERIALIZE_MAP_HPP_INCLUDED

#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/string.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace model
{
namespace impl
{
namespace deserialize
{

template<
	typename Result
>
Result
map(
	sge::parse::json::object const &_object,
	sge::parse::json::string const &_name,
	typename
	Result::mapped_type (
		*_deserialize_inner
	)(
		sge::parse::json::object const &
	)
)
{
	return
		fcppt::algorithm::map<
			Result
		>(
			sge::parse::json::find_member_exn<
				sge::parse::json::object
			>(
				_object.members,
				_name
			).members,
			[
				_deserialize_inner
			](
				sge::parse::json::member const &_member
			)
			{
				return
					std::make_pair(
						typename
						Result::key_type(
							_member.first
						),
						_deserialize_inner(
							_member.second.get<
								sge::parse::json::object
							>()
						)
					);
			}
		);
}

}
}
}
}

#endif
