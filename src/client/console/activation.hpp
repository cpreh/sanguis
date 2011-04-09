#ifndef SANGUIS_CLIENT_CONSOLE_ACTIVATION_HPP_INCLUDED
#define SANGUIS_CLIENT_CONSOLE_ACTIVATION_HPP_INCLUDED

#include "object_fwd.hpp"
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
	explicit activation(
		console::object &
	);

	~activation();
private:
	console::object &console_;
};

}
}
}

#endif
