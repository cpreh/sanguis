#include "create.hpp"
#include "object.hpp"
#include <fcppt/make_auto_ptr.hpp>

sanguis::main_object_auto_ptr
sanguis::server::create(
	sge::systems::instance const &sys,
	boost::program_options::variables_map const &vm,
	load::model::context const *const context
)
{
	main_object_auto_ptr ret(
		fcppt::make_auto_ptr<
			object
		>(
			sys,
			vm,
			context
		)
	);

	return ret;
}
