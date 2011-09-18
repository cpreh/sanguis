#ifndef SANGUIS_SERVER_PERKS_PERK_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_PERK_HPP_INCLUDED

#include <sanguis/server/perks/level_diff.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <sanguis/server/level.hpp>
#include <sanguis/perk_type.hpp>
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
