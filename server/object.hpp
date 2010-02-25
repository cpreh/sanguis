#ifndef SANGUIS_SERVER_OBJECT_HPP_INCLUDED
#define SANGUIS_SERVER_OBJECT_HPP_INCLUDED

#include "machine.hpp"
#include "object_fwd.hpp"
#include "../load/context_base_fwd.hpp"
#include "../main_object.hpp"
#include <sge/systems/instance_fwd.hpp>
#include <fcppt/thread/object.hpp>
#include <fcppt/noncopyable.hpp>
#include <boost/program_options/variables_map.hpp>

namespace sanguis
{
namespace server
{

class object
:
	public main_object
{
	FCPPT_NONCOPYABLE(object)
public:
	explicit object(
		sge::systems::instance const &,
		boost::program_options::variables_map const &,
		load::context_base const &
	);

	void
	quit();

	int
	run();

	~object();
private:
	void
	mainloop();

	server::machine machine_;

	fcppt::thread::object server_thread_;

	bool running_;
};

}
}

#endif
