#include "weak_link.hpp"
#include "entity.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>

sanguis::server::entities::auto_weak_link::auto_weak_link(
	entity &me,
	entity &ref)
:
	me(&me),
	ref(&ref)
{}

sanguis::server::entities::auto_weak_link::auto_weak_link(
	auto_weak_link &old)
:
	me(old.me),
	ref(old.ref)
{
	old.release();
}

sanguis::server::entities::auto_weak_link::~auto_weak_link()
{
	unlink();
}

sanguis::server::entities::auto_weak_link &
sanguis::server::entities::auto_weak_link::operator=(
	auto_weak_link &old)
{
	release();
	me = old.me;
	ref = old.ref;
	old.release();
	return *this;
}

void sanguis::server::entities::auto_weak_link::unlink()
{
	if(me && ref)
		me->unlink(ref);
}

sanguis::server::entities::auto_weak_link::operator sanguis::server::entities::auto_weak_link::unspecified *() const
{
	static unspecified unspec;
	return real_ref()
		? &unspec
		: 0;
}

sanguis::server::entities::entity &
sanguis::server::entities::auto_weak_link::operator->() const
{
	entity *const r(
		real_ref());
	if(!r)
		throw sge::exception(
			SGE_TEXT("Tried to dereference a weak link that is dead!"));
	return *r;
}

sanguis::server::entities::entity *
sanguis::server::entities::auto_weak_link::real_ref() const
{
	return me && me->has_ref(ref)
		? ref
		: 0;
}

void sanguis::server::entities::auto_weak_link::release()
{
	me = 0;
	ref = 0;
}
