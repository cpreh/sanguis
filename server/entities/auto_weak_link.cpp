#include "auto_weak_link.hpp"
#include "entity.hpp"
#include "../../exception.hpp"
#include <sge/text.hpp>

sanguis::server::entities::auto_weak_link::auto_weak_link()
:
	ref(0)
{}

sanguis::server::entities::auto_weak_link::auto_weak_link(
	entity &ref)
:
	ref(&ref)
{
	add_me();
}

sanguis::server::entities::auto_weak_link::auto_weak_link(
	auto_weak_link const &old)
:
	auto_hook_type(old),
	ref(old.ref)
{
	if(old.is_linked())
		add_me();
}

sanguis::server::entities::auto_weak_link::~auto_weak_link()
{}

sanguis::server::entities::auto_weak_link &
sanguis::server::entities::auto_weak_link::operator=(
	auto_weak_link const &old)
{
	unlink();
	auto_hook_type::operator=(old);	
	ref = old.ref;

	if(old.is_linked())
		add_me();
	return *this;
}

void sanguis::server::entities::auto_weak_link::unlink()
{
	auto_hook_type::unlink();
	ref = 0;
}

sanguis::server::entities::auto_weak_link::operator
sanguis::server::entities::auto_weak_link::unspecified *() const
{
	static unspecified unspec;
	return is_linked()
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

sanguis::server::entities::entity &
sanguis::server::entities::auto_weak_link::checked_ref() const
{
	if(!ref)
		throw exception(
			SGE_TEXT("Tried to dereference a weak link that is dead!")
		);
	return *ref;
}

void
sanguis::server::entities::auto_weak_link::add_me()
{
	if(!ref)
		return;

	ref->insert_link(
		*this
	);
}
