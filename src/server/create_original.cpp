#include <sanguis/main_object_unique_ptr.hpp>
#include <sanguis/server/create_original.hpp>
#include <sanguis/server/original_object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::main_object_unique_ptr
sanguis::server::create_original(
	boost::program_options::variables_map const &_vm
)
{
	return
		sanguis::main_object_unique_ptr(
			fcppt::make_unique_ptr<
				sanguis::server::original_object
			>(
				_vm
			)
		);
}
