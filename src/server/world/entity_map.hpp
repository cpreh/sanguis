#ifndef SANGUIS_SERVER_WORLD_ENTITY_MAP_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_ENTITY_MAP_HPP_INCLUDED

#include "../../entity_id.hpp"
#include "../entities/base_fwd.hpp"
#include "../entities/unique_ptr.hpp"
#include <fcppt/noncopyable.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <utility>

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

	typedef boost::ptr_map<
		sanguis::entity_id,
		entities::base
	> impl;
public:
	typedef impl::iterator iterator;

	typedef impl::const_iterator const_iterator;

	entity_map();

	~entity_map();

	typedef std::pair<
		iterator,
		bool
	> insert_return_type;

	insert_return_type const
	insert(
		sanguis::entity_id,
		entities::unique_ptr
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

	entities::unique_ptr
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
