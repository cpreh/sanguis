#include <sanguis/creator/impl/graveyard_name.hpp>
#include <sanguis/creator/impl/maze_name.hpp>
#include <sanguis/creator/impl/normal_generator_vector.hpp>
#include <sanguis/creator/impl/normal_generator_vector_type.hpp>
#include <sanguis/creator/impl/rooms_name.hpp>


namespace
{

sanguis::creator::impl::normal_generator_vector_type const generators{
	/*
	sanguis::creator::impl::graveyard_name()
	sanguis::creator::impl::maze_name()
	*/
	sanguis::creator::impl::rooms_name()
};

}

sanguis::creator::impl::normal_generator_vector_type const &
sanguis::creator::impl::normal_generator_vector()
{
	return
		generators;
}
