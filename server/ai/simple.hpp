#ifndef SANGUIS_SERVER_AI_SIMPLE_HPP_INCLUDED
#define SANGUIS_SERVER_AI_SIMPLE_HPP_INCLUDED

#include "base.hpp"
#include "../entities/fwd.hpp"

namespace sanguis
{
namespace server
{
namespace ai
{

class simple : public base {
public:
	simple(
		entities::enemy& me);
private:
	void update(
		time_type,
		entities::container const &);

	entities::enemy &me;
	entities::entity const *target;
};

}
}
}

#endif
