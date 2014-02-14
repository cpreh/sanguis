#include <sanguis/creator/aux_/graveyard_name.hpp>
#include <sanguis/creator/aux_/maze_name.hpp>
#include <sanguis/creator/aux_/normal_generator_vector.hpp>
#include <sanguis/creator/aux_/normal_generator_vector_type.hpp>


namespace
{

sanguis::creator::aux_::normal_generator_vector_type const generators{
	sanguis::creator::aux_::graveyard_name(),
	sanguis::creator::aux_::maze_name()
};

}

sanguis::creator::aux_::normal_generator_vector_type const &
sanguis::creator::aux_::normal_generator_vector()
{
	return
		generators;
}
