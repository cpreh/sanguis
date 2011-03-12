#include "create.hpp"
#include "object.hpp"
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_unique_ptr.hpp>

sanguis::main_object_unique_ptr
sanguis::client::create(
	sge::systems::instance &sys,
	boost::program_options::variables_map const &vm
)
{
	return
		main_object_unique_ptr(
			fcppt::make_unique_ptr<
				object
			>(
				std::tr1::ref(
					sys
				),
				vm
			)
		);
}
