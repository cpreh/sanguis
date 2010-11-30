#include "auto_weak_link.hpp"
#include "base.hpp"
#include "../../exception.hpp"
#include <fcppt/text.hpp>

sanguis::server::entities::auto_weak_link::auto_weak_link()
:
	ref_(0)
{}

sanguis::server::entities::auto_weak_link::auto_weak_link(
	base &_ref
)
:
	ref_(&_ref)
{
	add_me();
}

sanguis::server::entities::auto_weak_link::auto_weak_link(
	auto_weak_link const &_old
)
:
	auto_hook_type(_old),
	ref_(_old.ref_)
{
	if(_old.is_linked())
		add_me();
}

sanguis::server::entities::auto_weak_link::~auto_weak_link()
{}

sanguis::server::entities::auto_weak_link &
sanguis::server::entities::auto_weak_link::operator=(
	auto_weak_link const &_old
)
{
	unlink();
	auto_hook_type::operator=(_old);	
	ref_ = _old.ref_;

	if(_old.is_linked())
		add_me();
	return *this;
}

void
sanguis::server::entities::auto_weak_link::unlink()
{
	auto_hook_type::unlink();
	ref_ = 0;
}

sanguis::server::entities::auto_weak_link::operator
sanguis::server::entities::auto_weak_link::unspecified *() const
{
	static unspecified unspec;
	return is_linked()
		? &unspec
		: 0;
}

sanguis::server::entities::base &
sanguis::server::entities::auto_weak_link::operator*() const
{
	return checked_ref();
}

sanguis::server::entities::base *
sanguis::server::entities::auto_weak_link::operator->() const
{
	return get();
}

sanguis::server::entities::base *
sanguis::server::entities::auto_weak_link::get() const
{
	return &checked_ref();
}

sanguis::server::entities::base &
sanguis::server::entities::auto_weak_link::checked_ref() const
{
	if(!ref_)
		throw exception(
			FCPPT_TEXT("Tried to dereference a weak link that is dead!")
		);
	return *ref_;
}

void
sanguis::server::entities::auto_weak_link::add_me()
{
	if(!ref_)
		return;

	ref_->insert_link(
		*this
	);
}
