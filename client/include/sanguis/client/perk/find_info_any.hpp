#ifndef SANGUIS_CLIENT_PERK_FIND_INFO_ANY_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_FIND_INFO_ANY_HPP_INCLUDED

#include <sanguis/exception.hpp>
#include <sanguis/perk_type.hpp>
#include <sanguis/client/perk/compare.hpp>
#include <sanguis/client/perk/info.hpp>
#include <sanguis/client/perk/to_string.hpp>
#include <fcppt/optional_to_exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/find_if_opt.hpp>
#include <fcppt/container/tree/pre_order.hpp>


namespace sanguis
{
namespace client
{
namespace perk
{

template<
	typename Tree
>
Tree &
find_info_any(
	sanguis::perk_type const _type,
	Tree &_tree
)
{
	return
		*
		fcppt::optional_to_exception(
			fcppt::algorithm::find_if_opt(
				fcppt::container::tree::pre_order<
					Tree
				>(
					_tree
				),
				sanguis::client::perk::compare(
					_type
				)
			),
			[
				_type
			]{
				return
					sanguis::exception{
						FCPPT_TEXT("Can't find perk type ")
						+
						sanguis::client::perk::to_string(
							_type
						)
					};
			}
		);
}

}
}
}

#endif
