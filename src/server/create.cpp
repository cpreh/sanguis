#include <sanguis/main_object_unique_ptr.hpp>
#include <sanguis/args/server_port.hpp>
#include <sanguis/server/create.hpp>
#include <sanguis/server/object.hpp>
#include <sge/charconv/system_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::main_object_unique_ptr
sanguis::server::create(
	boost::program_options::variables_map const &_vm,
	sge::charconv::system &_charconv_system
)
{
	return
		sanguis::main_object_unique_ptr(
			fcppt::make_unique_ptr<
				sanguis::server::object
			>(
				sanguis::args::server_port(
					_vm
				),
				_charconv_system
			)
		);
}
