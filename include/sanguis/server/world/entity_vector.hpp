#ifndef SANGUIS_SERVER_WORLD_ENTITY_VECTOR_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_ENTITY_VECTOR_HPP_INCLUDED

#include <sanguis/server/entities/base_fwd.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

class entity_vector
{
	FCPPT_NONCOPYABLE(
		entity_vector
	);

	typedef boost::ptr_vector<
		sanguis::server::entities::base
	> impl;
public:
	typedef impl::iterator iterator;

	typedef impl::const_iterator const_iterator;

	entity_vector();

	~entity_vector();

	void
	push_back(
		sanguis::server::entities::unique_ptr &&
	);

	sanguis::server::entities::base &
	back();

	iterator
	begin();

	iterator
	end();

	iterator
	erase(
		iterator
	);
private:
	impl impl_;
};

}
}
}

#endif
