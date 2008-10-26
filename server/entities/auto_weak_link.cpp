#include "auto_weak_link.hpp"
#include "entity.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>

sanguis::server::entities::auto_weak_link::auto_weak_link()
:
	data(
		0,
		0)
{}

sanguis::server::entities::auto_weak_link::auto_weak_link(
	entity &me,
	entity &ref)
:
	data(
		&me,
		&ref)
{}

sanguis::server::entities::auto_weak_link::auto_weak_link(
	auto_weak_link &old)
:
	data(
		0,
		0)
{
	old.swap(*this);
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
	old.swap(*this);
	return *this;
}

void sanguis::server::entities::auto_weak_link::unlink()
{
	if(data.me && data.ref)
		data.me->unlink(data.ref);
}

void sanguis::server::entities::auto_weak_link::swap(
	auto_weak_link &r)
{
	data.swap(r.data);
}

sanguis::server::entities::auto_weak_link::operator sanguis::server::entities::auto_weak_link_ref()
{
	return auto_weak_link_ref(
		release());
}

sanguis::server::entities::auto_weak_link::auto_weak_link(
	auto_weak_link_ref const r)
:
	data(r.data)
{}

sanguis::server::entities::auto_weak_link &
sanguis::server::entities::auto_weak_link::operator=(
	auto_weak_link_ref const r)
{
	unlink();
	data = r.data;
	return *this;
}

sanguis::server::entities::auto_weak_link::operator sanguis::server::entities::auto_weak_link::unspecified *() const
{
	static unspecified unspec;
	return real_ref()
		? &unspec
		: 0;
}

sanguis::server::entities::entity &
sanguis::server::entities::auto_weak_link::operator*() const
{
	return checked_ref();
}

sanguis::server::entities::entity *
sanguis::server::entities::auto_weak_link::operator->() const
{
	return &checked_ref();
}

sanguis::server::entities::entity *
sanguis::server::entities::auto_weak_link::real_ref() const
{
	return data.me && data.me->has_ref(data.ref)
		? data.ref
		: 0;
}

sanguis::server::entities::entity &
sanguis::server::entities::auto_weak_link::checked_ref() const
{
	entity *const r(
		real_ref());
	if(!r)
		throw sge::exception(
			SGE_TEXT("Tried to dereference a weak link that is dead!"));
	return *r;

}

sanguis::server::entities::weak_link_pair const
sanguis::server::entities::auto_weak_link::release()
{
	weak_link_pair const ret(
		data);
	data.me = 0;
	data.ref = 0;
	return ret;
}
