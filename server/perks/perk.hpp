#ifndef SANGUIS_SERVER_PERKS_PERK_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_PERK_HPP_INCLUDED

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
	virtual void bind(entity &);
	virtual void activate() = 0;
	virtual void deactivate() = 0;
	virtual bool can_raise_level() const = 0;
	void raise_level();
	virtual ~perk();
protected:
	typedef unsigned level_type;
	level_type level() const;
	entity &get_entity() const;
private:
	entity    *entity_;
	level_type level_;
};

}
}
}

#endif
