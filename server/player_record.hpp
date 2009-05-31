#ifndef SANGUIS_SERVER_PLAYER_RECORD_HPP_INCLUDED
#define SANGUIS_SERVER_PLAYER_RECORD_HPP_INCLUDED

#include "player_record_fwd.hpp"
#include "exp_type.hpp"
#include <sge/string.hpp>

namespace sanguis
{
namespace server
{

class player_record {
public:
	player_record(
		sge::string const &name,
		exp_type);
	
	sge::string const &name() const;
	exp_type exp() const;
private:
	sge::string name_;
	exp_type exp_;
};

}
}

#endif
