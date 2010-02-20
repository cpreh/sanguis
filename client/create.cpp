#include "create.hpp"
#include "object.hpp"
#include <fcppt/make_auto_ptr.hpp>

sanguis::main_object_auto_ptr
sanguis::client::create(
	sge::systems::instance const &sys,
	boost::program_options::variables_map const &vm
)
{
	return
		fcppt::make_auto_ptr<
			object
		>(
			sys,
			vm
		);
}
