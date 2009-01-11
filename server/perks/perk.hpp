#ifndef SANGUIS_SERVER_PERKS_PERK_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_PERK_HPP_INCLUDED

#include <sge/noncopyable.hpp>

namespace sanguis
{
namespace server
{

namespace entities
{
class entity;
}

namespace perks
{

class perk {
	SGE_NONCOPYABLE(perk)
public:
	perk();
	void apply(entities::entity &);
	virtual bool can_raise_level() const = 0;
	void raise_level();
	virtual ~perk();
protected:
	typedef unsigned level_type;
	level_type level() const;
private:
	virtual void do_apply(entities::entity &) = 0;

	level_type level_;
};

}
}
}

#endif
