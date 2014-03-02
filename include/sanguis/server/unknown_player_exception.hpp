#ifndef SANGUIS_SERVER_UNKNOWN_PLAYER_EXCEPTION_HPP_INCLUDED
#define SANGUIS_SERVER_UNKNOWN_PLAYER_EXCEPTION_HPP_INCLUDED

#include <sanguis/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/assert/information_fwd.hpp>


namespace sanguis
{
namespace server
{

class unknown_player_exception
:
	public sanguis::exception
{
public:
	explicit
	unknown_player_exception(
		fcppt::string const &
	);

	explicit
	unknown_player_exception(
		fcppt::assert_::information const &
	);
};

}
}

#endif
