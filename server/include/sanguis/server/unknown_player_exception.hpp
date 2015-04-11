#ifndef SANGUIS_SERVER_UNKNOWN_PLAYER_EXCEPTION_HPP_INCLUDED
#define SANGUIS_SERVER_UNKNOWN_PLAYER_EXCEPTION_HPP_INCLUDED

#include <sanguis/exception.hpp>


namespace sanguis
{
namespace server
{

class unknown_player_exception
:
	public sanguis::exception
{
public:
	unknown_player_exception();
};

}
}

#endif
