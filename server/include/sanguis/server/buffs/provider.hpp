#ifndef SANGUIS_SERVER_BUFFS_PROVIDER_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_PROVIDER_HPP_INCLUDED

#include <sanguis/server/buffs/provider_fwd.hpp>
#include <sanguis/server/buffs/unique_ptr.hpp>
#include <sanguis/server/entities/with_buffs_fwd.hpp>
#include <fcppt/reference_wrapper_decl.hpp>
#include <fcppt/reference_wrapper_std_hash.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace buffs
{

class provider
{
	FCPPT_NONCOPYABLE(
		provider
	);
public:
	provider();

	~provider();

	void
	add(
		sanguis::server::entities::with_buffs &,
		sanguis::server::buffs::unique_ptr &&
	);

	void
	remove(
		sanguis::server::entities::with_buffs &
	);
private:
	typedef
	fcppt::reference_wrapper<
		sanguis::server::buffs::buff
	>
	buff_reference;

	typedef
	fcppt::reference_wrapper<
		sanguis::server::entities::with_buffs
	>
	with_buffs_reference;

	typedef
	std::unordered_map<
		with_buffs_reference,
		buff_reference
	>
	buff_map;

	buff_map buffs_;
};

}
}
}

#endif
