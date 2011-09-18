#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/exception.hpp>
#include <fcppt/text.hpp>

sanguis::server::entities::auto_weak_link::auto_weak_link()
:
	ref_(0)
{
}

sanguis::server::entities::auto_weak_link::auto_weak_link(
	base &_ref
)
:
	ref_(&_ref)
{
	this->add_me();
}

sanguis::server::entities::auto_weak_link::auto_weak_link(
	auto_weak_link const &_old
)
:
	auto_weak_hook(_old),
	ref_(_old.ref_)
{
	if(
		_old.is_linked()
	)
		this->add_me();
}

sanguis::server::entities::auto_weak_link::~auto_weak_link()
{
}

sanguis::server::entities::auto_weak_link &
sanguis::server::entities::auto_weak_link::operator=(
	auto_weak_link const &_old
)
{
	this->unlink();

	auto_weak_hook::operator=(
		_old
	);

	ref_ = _old.ref_;

	if(
		_old.is_linked()
	)
		this->add_me();

	return *this;
}

void
sanguis::server::entities::auto_weak_link::unlink()
{
	auto_weak_hook::unlink();

	ref_ = 0;
}

sanguis::server::entities::base &
sanguis::server::entities::auto_weak_link::operator*() const
{
	return this->checked_ref();
}

sanguis::server::entities::base *
sanguis::server::entities::auto_weak_link::operator->() const
{
	return this->get();
}

sanguis::server::entities::base *
sanguis::server::entities::auto_weak_link::get() const
{
	return &this->checked_ref();
}

sanguis::server::entities::base &
sanguis::server::entities::auto_weak_link::checked_ref() const
{
	if(
		!ref_
	)
		throw sanguis::exception(
			FCPPT_TEXT("Tried to dereference a weak link that is dead!")
		);

	return *ref_;
}

void
sanguis::server::entities::auto_weak_link::add_me()
{
	if(
		!ref_
	)
		return;

	ref_->insert_link(
		*this
	);
}

bool
sanguis::server::entities::auto_weak_link::boolean_test() const
{
	return this->is_linked();
}
