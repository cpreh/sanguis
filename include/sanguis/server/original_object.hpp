#ifndef SANGUIS_SERVER_ORIGINAL_OBJECT_HPP_INCLUDED
#define SANGUIS_SERVER_ORIGINAL_OBJECT_HPP_INCLUDED

#include <sanguis/main_object.hpp>
#include <sanguis/main_object_scoped_ptr.hpp>
#include <sanguis/load/server_context.hpp>
#include <sge/systems/instance.hpp>
#include <awl/main/exit_code.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{

class original_object
:
	public sanguis::main_object
{
	FCPPT_NONCOPYABLE(
		original_object
	);
public:
	explicit
	original_object(
		boost::program_options::variables_map const &
	);

	~original_object();

	awl::main::exit_code const
	run();
private:
	sge::systems::instance systems_;

	sanguis::load::server_context load_context_;

	sanguis::main_object_scoped_ptr const object_;
};

}
}

#endif
