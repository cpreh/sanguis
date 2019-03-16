#ifndef SANGUIS_MODEL_IMPL_DESERIALIZE_MAP_HPP_INCLUDED
#define SANGUIS_MODEL_IMPL_DESERIALIZE_MAP_HPP_INCLUDED

#include <sanguis/model/exception.hpp>
#include <sge/charconv/utf8_string.hpp>
#include <sge/charconv/utf8_string_to_fcppt.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/get_exn.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/optional/to_exception.hpp>
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
	sge::charconv::utf8_string const &_name,
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
							fcppt::optional::to_exception(
								sge::charconv::utf8_string_to_fcppt(
									_member.first
								),
								[]{
									return
										sanguis::model::exception{
											FCPPT_TEXT("Failed to convert animation name")
										};
								}
							)
						),
						_deserialize_inner(
							sge::parse::json::get_exn<
								sge::parse::json::object
							>(
								_member.second.get()
							)
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
