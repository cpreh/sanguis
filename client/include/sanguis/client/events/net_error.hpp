#ifndef SANGUIS_CLIENT_EVENTS_NET_ERROR_HPP_INCLUDED
#define SANGUIS_CLIENT_EVENTS_NET_ERROR_HPP_INCLUDED

#include <sanguis/client/events/net_error_fwd.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/event.hpp>
#include <boost/system/error_code.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace events
{

class net_error
:
	public boost::statechart::event<
		sanguis::client::events::net_error
	>
{
	FCPPT_NONASSIGNABLE(
		net_error
	);
public:
	net_error(
		fcppt::string const &,
		boost::system::error_code const &
	);

	fcppt::string const &
	message() const;

	boost::system::error_code const &
	code() const;
private:
	fcppt::string const message_;

	boost::system::error_code const code_;
};

}
}
}

#endif
