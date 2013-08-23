#ifndef SANGUIS_CLIENT_CONSOLE_ACTIVATION_HPP_INCLUDED
#define SANGUIS_CLIENT_CONSOLE_ACTIVATION_HPP_INCLUDED

#include <sanguis/client/console/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace console
{

class activation
{
	FCPPT_NONCOPYABLE(
		activation
	);
public:
	explicit
	activation(
		sanguis::client::console::object &
	);

	~activation();
private:
	sanguis::client::console::object &console_;
};

}
}
}

#endif
