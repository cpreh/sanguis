#ifndef SANGUIS_SERVER_AI_SIMPLE_HPP_INCLUDED
#define SANGUIS_SERVER_AI_SIMPLE_HPP_INCLUDED

#include "base.hpp"
#include "../entities/fwd.hpp"
#include "../entities/auto_weak_link.hpp"

namespace sanguis
{
namespace server
{
namespace ai
{

class simple : public base {
public:
	simple();
private:
	void bind(
		entities::entity_with_weapon &me);
	
	void update(
		time_type,
		entities::container &);

	entities::entity_with_weapon *me_;
	entities::auto_weak_link target;
};

}
}
}

#endif
