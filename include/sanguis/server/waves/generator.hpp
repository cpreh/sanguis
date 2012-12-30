#ifndef SANGUIS_SERVER_WAVES_GENERATOR_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_GENERATOR_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/console_fwd.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <sanguis/server/waves/wave.hpp>
#include <sge/console/arg_list.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <fcppt/config/external_end.hpp>


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
		sanguis::random_generator &,
		sanguis::server::console &
	);

	~generator();

	void
	process(
		sanguis::server::environment::object &,
		sanguis::server::environment::load_context &
	);
private:
	void
	spawn(
		sge::console::arg_list const &
	);

	void
	spawn_all();

	sanguis::diff_clock const &diff_clock_;

	sanguis::random_generator &random_generator_;

	sanguis::server::console &console_;

	fcppt::signal::scoped_connection const spawn_connection_;

	typedef boost::ptr_list<
		sanguis::server::waves::wave
	> wave_list;

	wave_list waves_;
};

}
}
}

#endif
