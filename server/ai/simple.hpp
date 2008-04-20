#ifndef SANGUIS_SERVER_AI_SIMPLE_HPP_INCLUDED
#define SANGUIS_SERVER_AI_SIMPLE_HPP_INCLUDED

#include "base.hpp"

namespace sanguis
{
namespace server
{
namespace ai
{

class simple : public base {
public:
	simple(
		entity& me);
private:
	void update(
		time_type,
		entity_container const &);

	entity &me;
	entity const *target;
};

}
}
}

#endif
