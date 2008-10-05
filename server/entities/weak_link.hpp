#ifndef SANGUIS_SERVER_ENTITIES_WEAK_LINK_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WEAK_LINK_HPP_INCLUDED

namespace sanguis
{
namespace server
{
namespace entities
{

class entity;

class auto_weak_link {
public:
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
private:
	struct unspecified {};
public:
	operator unspecified *() const;
	entity &operator->() const;
private:
	entity *real_ref() const;
	void release();
	entity *me,
	       *ref;
};

}
}
}

#endif
