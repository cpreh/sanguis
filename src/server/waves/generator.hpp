#ifndef SANGUIS_SERVER_WAVES_GENERATOR_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_GENERATOR_HPP_INCLUDED

#include "wave.hpp"
#include "../environment/object_fwd.hpp"
#include "../environment/load_context_fwd.hpp"
#include "../console_fwd.hpp"
#include "../../diff_clock_fwd.hpp"
#include <sge/console/arg_list.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>
#include <boost/ptr_container/ptr_list.hpp>

namespace sanguis
{
namespace server
{
namespace waves
{

class generator
{
	FCPPT_NONCOPYABLE(
		generator
	);
public:
	generator(
		sanguis::diff_clock const &,
		server::console &
	);

	~generator();

	void
	process(
		environment::object &,
		environment::load_context &
	);
private:
	void
	spawn(
		sge::console::arg_list const &
	);

	void
	spawn_all();

	sanguis::diff_clock const &diff_clock_;

	server::console &console_;

	fcppt::signal::scoped_connection const spawn_connection_;

	typedef boost::ptr_list<
		waves::wave
	> wave_list;

	wave_list waves_;
};

}
}
}

#endif
