#include <sanguis/client/create.hpp>
#include <sanguis/client/object.hpp>
#include <fcppt/make_unique_ptr.hpp>

sanguis::main_object_unique_ptr
sanguis::client::create(
	boost::program_options::variables_map const &_vm
)
{
	return
		main_object_unique_ptr(
			fcppt::make_unique_ptr<
				object
			>(
				_vm
			)
		);
}
