#include <sanguis/client/create.hpp>
#include <sanguis/client/object.hpp>
#include <sanguis/client/object_base.hpp>
#include <sanguis/client/object_base_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::client::object_base_unique_ptr
sanguis::client::create(
	boost::program_options::variables_map const &_vm
)
{
	return
		fcppt::unique_ptr_to_base<
			sanguis::client::object_base
		>(
			fcppt::make_unique_ptr<
				sanguis::client::object
			>(
				_vm
			)
		);
}
