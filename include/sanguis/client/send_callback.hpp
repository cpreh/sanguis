#ifndef SANGUIS_CLIENT_SEND_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_SEND_CALLBACK_HPP_INCLUDED

#include <sanguis/messages/base_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{

typedef std::function<
	void(
		sanguis::messages::base const &
	)
> send_callback;

}
}

#endif
