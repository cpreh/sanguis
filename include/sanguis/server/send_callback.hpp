#ifndef SANGUIS_SERVER_SEND_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_SEND_CALLBACK_HPP_INCLUDED

#include <sanguis/messages/base_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{

typedef std::function<
	void(
		sanguis::messages::base const &
	)
> send_callback;

}
}

#endif
