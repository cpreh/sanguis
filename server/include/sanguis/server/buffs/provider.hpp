#ifndef SANGUIS_SERVER_BUFFS_PROVIDER_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_PROVIDER_HPP_INCLUDED

#include <sanguis/server/buffs/provider_fwd.hpp>
#include <sanguis/server/buffs/unique_ptr.hpp>
#include <sanguis/server/entities/with_buffs_fwd.hpp>
#include <sanguis/server/entities/with_buffs_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_decl.hpp>
#include <fcppt/reference_std_hash.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sanguis::server::buffs
{

class provider
{
	FCPPT_NONMOVABLE(
		provider
	);
public:
	provider();

	~provider();

	void
	add(
		sanguis::server::entities::with_buffs_ref,
		sanguis::server::buffs::unique_ptr &&
	);

	void
	remove(
		sanguis::server::entities::with_buffs & // NOLINT(google-runtime-references)
	); // NOLINT(google-runtime-references)
private:
	using
	buff_reference
	=
	fcppt::reference<
		sanguis::server::buffs::buff
	>;

	using
	buff_map
	=
	std::unordered_map<
		sanguis::server::entities::with_buffs_ref,
		buff_reference
	>;

	buff_map buffs_;
};

}

#endif
