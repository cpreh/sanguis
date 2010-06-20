#ifndef SANGUIS_SERVER_WAVES_GENERATOR_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_GENERATOR_HPP_INCLUDED

#include "wave.hpp"
#include "../environment/object_ptr.hpp"
#include "../environment/load_context_ptr.hpp"
#include "../console_fwd.hpp"
#include "../../time_type.hpp"
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
	FCPPT_NONCOPYABLE(generator)
public:
	explicit generator(
		server::console &
	);

	~generator();

	void
	process(
		time_type,
		environment::object_ptr,
		environment::load_context_ptr
	);
private:
	void
	spawn(
		sge::console::arg_list const &
	);

	void
	spawn_all();

	server::console &console_;

	fcppt::signal::scoped_connection spawn_connection;

	typedef boost::ptr_list<
		wave
	> wave_list;

	wave_list waves;
};

}
}
}

#endif
