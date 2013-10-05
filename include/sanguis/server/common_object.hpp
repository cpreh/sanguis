#ifndef SANGUIS_SERVER_COMMON_OBJECT_HPP_INCLUDED
#define SANGUIS_SERVER_COMMON_OBJECT_HPP_INCLUDED

#include <sanguis/io_service.hpp>
#include <sanguis/server/machine.hpp>
#include <alda/net/port.hpp>
#include <awl/main/exit_code.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_state_machine.hpp>


namespace sanguis
{
namespace server
{

class common_object
{
	FCPPT_NONCOPYABLE(
		common_object
	);
public:
	explicit
	common_object(
		alda::net::port
	);

	~common_object();

	void
	run();

	void
	stop();
private:
	sanguis::io_service io_service_;

	sanguis::server::machine machine_;

	typedef fcppt::scoped_state_machine<
		sanguis::server::machine
	> scoped_machine;

	scoped_machine scoped_machine_;
};

}
}

#endif
