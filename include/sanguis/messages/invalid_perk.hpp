#ifndef SANGUIS_MESSAGES_INVALID_PERK_HPP_INCLUDED
#define SANGUIS_MESSAGES_INVALID_PERK_HPP_INCLUDED

#include <sanguis/perk_type.hpp>
#include <sanguis/messages/types/enum.hpp>
#include <fcppt/enum_size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{

typedef
std::integral_constant<
	sanguis::messages::types::enum_,
	static_cast<
		sanguis::messages::types::enum_
	>(
		fcppt::enum_size<
			sanguis::perk_type
		>::value
	)
>
invalid_perk;

}
}

#endif
