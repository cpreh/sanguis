#include <sanguis/main_object_unique_ptr.hpp>
#include <sanguis/client/create.hpp>
#include <sanguis/client/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::main_object_unique_ptr
sanguis::client::create(
	boost::program_options::variables_map const &_vm
)
{
	return
		sanguis::main_object_unique_ptr(
			fcppt::make_unique_ptr<
				sanguis::client::object
			>(
				_vm
			)
		);
}
