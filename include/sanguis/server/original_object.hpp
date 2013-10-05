#ifndef SANGUIS_SERVER_ORIGINAL_OBJECT_HPP_INCLUDED
#define SANGUIS_SERVER_ORIGINAL_OBJECT_HPP_INCLUDED

#include <sanguis/main_object.hpp>
#include <sanguis/server/common_object.hpp>
#include <alda/net/port.hpp>
#include <awl/main/exit_code.hpp>
#include <fcppt/noncopyable.hpp>


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
		alda::net::port
	);

	~original_object();

	awl::main::exit_code const
	run();
private:
	sanguis::server::common_object impl_;
};

}
}

#endif
