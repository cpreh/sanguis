#include <sanguis/creator/generator_count_type.hpp>
#include <sanguis/creator/generator_index.hpp>
#include <sanguis/creator/name.hpp>
#include <sanguis/creator/aux_/normal_generator_vector.hpp>


sanguis::creator::name
sanguis::creator::generator_index(
	sanguis::creator::generator_count_type const _index
)
{
	return
		sanguis::creator::aux_::normal_generator_vector()[
			_index
		];
}
