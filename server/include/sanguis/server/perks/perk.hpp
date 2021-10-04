#ifndef SANGUIS_SERVER_PERKS_PERK_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_PERK_HPP_INCLUDED

#include <sanguis/perk_type.hpp>
#include <sanguis/server/level.hpp>
#include <sanguis/server/entities/with_perks_fwd.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <sanguis/server/perks/level_diff.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::server::perks
{

class perk
{
	FCPPT_NONMOVABLE(
		perk
	);
public:
	virtual
	void
	update(
		sanguis::server::entities::with_perks &, // NOLINT(google-runtime-references)
		sanguis::server::environment::object & // NOLINT(google-runtime-references)
	); // NOLINT(google-runtime-references)

	void
	raise_level(
		sanguis::server::entities::with_perks & // NOLINT(google-runtime-references)
	); // NOLINT(google-runtime-references)

	[[nodiscard]]
	sanguis::perk_type
	type() const;

	virtual
	~perk();
protected:
	explicit
	perk(
		sanguis::perk_type
	);

	[[nodiscard]]
	sanguis::server::level
	level() const;
private:
	virtual
	void
	change(
		sanguis::server::entities::with_perks &, // NOLINT(google-runtime-references)
		sanguis::server::perks::level_diff
	) = 0;

	sanguis::perk_type const type_;

	sanguis::server::level level_;
};

}

#endif
