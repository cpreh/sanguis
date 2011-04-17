#ifndef SANGUIS_SERVER_PERKS_PERK_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_PERK_HPP_INCLUDED

#include "level_diff.hpp"
#include "../entities/base_fwd.hpp"
#include "../environment/object_fwd.hpp"
#include "../level.hpp"
#include "../../time_type.hpp"
#include "../../perk_type.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace perks
{

class perk
{
	FCPPT_NONCOPYABLE(
		perk
	);
public:
	virtual void
	update(
		entities::base &,
		sanguis::time_type,
		environment::object &
	);
	
	void
	raise_level(
		entities::base &
	);
	
	perk_type::type
	type() const;

	virtual ~perk();
protected:
	explicit perk(
		perk_type::type
	);

	server::level const
	level() const;
private:
	virtual void
	change(
		entities::base &,
		perks::level_diff
	) = 0;

	perk_type::type const type_;

	server::level level_;
};

}
}
}

#endif
