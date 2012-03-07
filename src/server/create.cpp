#include <sanguis/server/create.hpp>
#include <sanguis/server/object.hpp>
#include <sanguis/args/server_port.hpp>
#include <sge/charconv/system_fwd.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>


sanguis::main_object_unique_ptr
sanguis::server::create(
	boost::program_options::variables_map const &_vm,
	load::context_base const &_context,
	sge::charconv::system &_charconv_system
)
{
	return
		sanguis::main_object_unique_ptr(
			fcppt::make_unique_ptr<
				server::object
			>(
				args::server_port(
					_vm
				),
				fcppt::cref(
					_context
				),
				fcppt::ref(
					_charconv_system
				)
			)
		);
}
