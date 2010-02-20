#include "create.hpp"
#include "object.hpp"
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_auto_ptr.hpp>

sanguis::main_object_auto_ptr
sanguis::client::create(
	sge::systems::instance &sys,
	boost::program_options::variables_map const &vm
)
{
	main_object_auto_ptr ret(
		fcppt::make_auto_ptr<
			object
		>(
			std::tr1::ref(
				sys
			),
			vm
		)
	);

	return ret;
}
