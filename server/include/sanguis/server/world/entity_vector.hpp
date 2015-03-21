#ifndef SANGUIS_SERVER_WORLD_ENTITY_VECTOR_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_ENTITY_VECTOR_HPP_INCLUDED

#include <sanguis/server/world/entity_vector_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

template<
	typename Type
>
class entity_vector
{
	FCPPT_NONCOPYABLE(
		entity_vector
	);

	typedef
	std::unique_ptr<
		Type
	>
	entity_unique_ptr;

	typedef
	std::vector<
		entity_unique_ptr
	>
	impl;
public:
	typedef
	typename
	impl::iterator
	iterator;

	entity_vector();

	~entity_vector();

	void
	push_back(
		entity_unique_ptr &&
	);

	void
	pop_back();

	Type &
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
