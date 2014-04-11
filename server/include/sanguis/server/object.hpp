#ifndef SANGUIS_SERVER_OBJECT_HPP_INCLUDED
#define SANGUIS_SERVER_OBJECT_HPP_INCLUDED

#include <sanguis/io_service.hpp>
#include <sanguis/server/machine.hpp>
#include <sanguis/server/object_base.hpp>
#include <sanguis/server/object_fwd.hpp>
#include <sanguis/server/symbol.hpp>
#include <alda/net/port.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_state_machine.hpp>


namespace sanguis
{
namespace server
{

class object
:
	public sanguis::server::object_base
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	SANGUIS_SERVER_SYMBOL
	explicit
	object(
		alda::net::port
	);

	SANGUIS_SERVER_SYMBOL
	~object();

	SANGUIS_SERVER_SYMBOL
	void
	run();

	SANGUIS_SERVER_SYMBOL
	void
	stop();
private:
	sanguis::io_service io_service_;

	sanguis::server::machine machine_;

	typedef
	fcppt::scoped_state_machine<
		sanguis::server::machine
	>
	scoped_machine;

	scoped_machine scoped_machine_;
};

}
}

#endif
