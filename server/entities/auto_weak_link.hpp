#ifndef SANGUIS_SERVER_ENTITIES_AUTO_WEAK_LINK_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_AUTO_WEAK_LINK_HPP_INCLUDED

#include "entity_fwd.hpp"
#include "weak_link_pair.hpp"
#include "auto_weak_link_ref.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{
class auto_weak_link {
public:
	auto_weak_link();
	auto_weak_link(
		entity &me,
		entity &ref);
	auto_weak_link(
		auto_weak_link &);
	~auto_weak_link();
	auto_weak_link &
	operator=(
		auto_weak_link &);
	void unlink();
	void swap(
		auto_weak_link &);
	
	// std::auto_ptr semantics
	operator auto_weak_link_ref();
	auto_weak_link(
		auto_weak_link_ref);
	auto_weak_link &
	operator=(
		auto_weak_link_ref);
private:
	struct unspecified {};
public:
	operator unspecified *() const;
	entity &operator*() const;
	entity *operator->() const;
private:
	entity *real_ref() const;
	entity &checked_ref() const;
	weak_link_pair const release();

	weak_link_pair data;
};

}
}
}

#endif
