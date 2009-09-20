#ifndef SANGUIS_SERVER_PERKS_PERK_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_PERK_HPP_INCLUDED

#include "../entities/entity_fwd.hpp"
#include "../environment/object_ptr.hpp"
#include "../environment/load_context_ptr.hpp"
#include "../../time_type.hpp"
#include "../../perk_type.hpp"
#include <sge/noncopyable.hpp>

namespace sanguis
{
namespace server
{

namespace perks
{

class perk {
	SGE_NONCOPYABLE(perk)
public:
	void
	apply(
		entities::entity &,
		time_type,
		environment::object_ptr,
		environment::load_context_ptr
	);
	
	virtual bool
	can_raise_level() const = 0;
	
	void raise_level();
	
	perk_type::type
	type() const;

	virtual ~perk();
protected:
	explicit perk(
		perk_type::type
	);

	typedef unsigned level_type;

	level_type
	level() const;
private:
	virtual void
	do_apply(
		entities::entity &,
		time_type,
		environment::object_ptr,
		environment::load_context_ptr
	) = 0;

	perk_type::type const type_;
	level_type level_;
};

}
}
}

#endif
