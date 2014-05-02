#ifndef SANGUIS_SERVER_WORLD_ENTITY_MAP_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_ENTITY_MAP_HPP_INCLUDED

#include <sanguis/entity_id.hpp>
#include <sanguis/server/entities/with_id_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

class entity_map
{
	FCPPT_NONCOPYABLE(
		entity_map
	);

	typedef
	std::map<
		sanguis::entity_id,
		sanguis::server::entities::with_id_unique_ptr
	>
	impl;
public:
	typedef impl::iterator iterator;

	typedef impl::const_iterator const_iterator;

	entity_map();

	~entity_map();

	typedef
	std::pair<
		iterator,
		bool
	>
	insert_return_type;

	insert_return_type const
	insert(
		sanguis::entity_id,
		sanguis::server::entities::with_id_unique_ptr &&
	);

	iterator
	begin();

	iterator
	end();

	iterator
	find(
		sanguis::entity_id
	);

	const_iterator
	find(
		sanguis::entity_id
	) const;

	void
	erase(
		iterator
	);

	sanguis::server::entities::with_id_unique_ptr
	release(
		iterator
	);
private:
	impl impl_;
};

}
}
}

#endif
