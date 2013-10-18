#include <sanguis/aura_type.hpp>
#include <sanguis/load/aura_name.hpp>
#include <sanguis/load/auras/lookup_name.hpp>
#include <fcppt/enum_size.hpp>
#include <fcppt/string.hpp>
#include <fcppt/algorithm/array_fold.hpp>
#include <fcppt/algorithm/find_exn.hpp>
#include <fcppt/cast/int_to_enum.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <cstddef>
#include <iterator>
#include <fcppt/config/external_end.hpp>


// TODO: Generalize this code!
namespace
{

typedef std::array<
	fcppt::string,
	fcppt::enum_size<
		sanguis::aura_type
	>::value
> aura_type_array;

aura_type_array const aura_types(
	fcppt::algorithm::array_fold<
		aura_type_array
	>(
		[](
			std::size_t const _index
		)
		{
			return
				sanguis::load::aura_name(
					fcppt::cast::int_to_enum<
						sanguis::aura_type
					>(
						_index
					)
				);
		}
	)
);

}

sanguis::aura_type
sanguis::load::auras::lookup_name(
	fcppt::string const &_str
)
{
	return
		fcppt::cast::int_to_enum<
			sanguis::aura_type
		>(
			std::distance(
				aura_types.begin(),
				fcppt::algorithm::find_exn(
					aura_types.begin(),
					aura_types.end(),
					_str
				)
			)
		);

}
