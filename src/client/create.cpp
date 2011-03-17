#include "create.hpp"
#include "object.hpp"
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>

sanguis::main_object_unique_ptr
sanguis::client::create(
	sge::systems::instance &_sys,
	boost::program_options::variables_map const &_vm
)
{
	return
		main_object_unique_ptr(
			fcppt::make_unique_ptr<
				object
			>(
				fcppt::ref(
					_sys
				),
				_vm
			)
		);
}
