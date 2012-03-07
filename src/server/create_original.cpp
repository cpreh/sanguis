#include <sanguis/server/create_original.hpp>
#include <sanguis/server/original_object.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::main_object_unique_ptr
sanguis::server::create_original(
	boost::program_options::variables_map const &_vm
)
{
	return
		sanguis::main_object_unique_ptr(
			fcppt::make_unique_ptr<
				server::original_object
			>(
				fcppt::cref(
					_vm
				)
			)
		);
}
