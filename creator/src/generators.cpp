#include <sanguis/creator/generator_vector.hpp>
#include <sanguis/creator/generators.hpp>
#include <sanguis/creator/impl/graveyard_name.hpp>
#include <sanguis/creator/impl/maze_name.hpp>
#include <sanguis/creator/impl/rooms_name.hpp>


namespace
{

sanguis::creator::generator_vector const global_generators{
	sanguis::creator::impl::graveyard_name(),
//	sanguis::creator::impl::maze_name(),
	sanguis::creator::impl::rooms_name()
};

}

sanguis::creator::generator_vector const &
sanguis::creator::generators()
{
	return
		global_generators;
}
