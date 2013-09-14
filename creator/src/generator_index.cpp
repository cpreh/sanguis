#include <sanguis/creator/generator_count_type.hpp>
#include <sanguis/creator/generator_index.hpp>
#include <sanguis/creator/name.hpp>
#include <sanguis/creator/aux_/generator_map.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>


sanguis::creator::name const
sanguis::creator::generator_index(
	sanguis::creator::generator_count_type const _index
)
{
	// TODO: Maybe we should keep the generators in an array instead
	return
		std::next(
			sanguis::creator::aux_::generator_map().begin(),
			fcppt::cast::size<
				std::iterator_traits<
					sanguis::creator::aux_::generator_map_type::const_iterator
				>::difference_type
			>(
				fcppt::cast::to_signed(
					_index
				)
			)
		)->first;
}
