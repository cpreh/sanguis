#ifndef SANGUIS_SERVER_PERKS_PERK_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_PERK_HPP_INCLUDED

#include <memory>

namespace sanguis
{
namespace server
{

class entity;

namespace perks
{

class perk {
public:
	perk();
	void activate(entity &);
	void deactivate();
	virtual bool can_raise_level() const = 0;
	void raise_level();
	virtual ~perk();
protected:
	typedef unsigned level_type;
	level_type level() const;
	entity &get_entity() const;
private:
	virtual void do_activate() = 0;
	virtual void do_deactivate() = 0;

	entity    *entity_;
	level_type level_;
};
typedef std::auto_ptr<perk> perk_auto_ptr;

}
}
}

#endif
