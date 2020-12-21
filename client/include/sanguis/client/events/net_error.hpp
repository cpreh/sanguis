#ifndef SANGUIS_CLIENT_EVENTS_NET_ERROR_HPP_INCLUDED
#define SANGUIS_CLIENT_EVENTS_NET_ERROR_HPP_INCLUDED

#include <sanguis/client/events/net_error_fwd.hpp>
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
public:
	net_error(
		fcppt::string &&,
		boost::system::error_code const &
	);

	net_error(
		net_error &&
	)
	noexcept;

	net_error(
		net_error const &
	);

	net_error &
	operator=(
		net_error &&
	)
	noexcept;

	net_error &
	operator=(
		net_error const &
	);

	~net_error()
	override;

	[[nodiscard]]
	fcppt::string const &
	message() const;

	[[nodiscard]]
	boost::system::error_code const &
	code() const;
private:
	fcppt::string message_;

	boost::system::error_code code_;
};

}
}
}

#endif
