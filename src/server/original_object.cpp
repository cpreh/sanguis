#include <sanguis/main_object.hpp>
#include <sanguis/server/create.hpp>
#include <sanguis/server/original_object.hpp>
#include <sge/systems/empty_list.hpp>
#include <sge/systems/make_empty_list.hpp>
#include <sge/systems/instance_impl.hpp>
#include <awl/main/exit_code.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::server::original_object::original_object(
	boost::program_options::variables_map const &_vm
)
:
	systems_(
		sge::systems::make_empty_list()
	),
	load_context_(),
	object_(
		sanguis::server::create(
			_vm,
			load_context_,
			systems_.charconv_system()
		)
	)
{
}

sanguis::server::original_object::~original_object()
{
}

awl::main::exit_code const
sanguis::server::original_object::run()
{
	return
		object_->run();
}
