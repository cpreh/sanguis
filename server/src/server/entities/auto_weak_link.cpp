#include <sanguis/server/entities/auto_weak_hook.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_comparison.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/optional/comparison.hpp>
#include <fcppt/optional/maybe_void.hpp>


sanguis::server::entities::auto_weak_link::auto_weak_link()
:
	ref_()
{
}

sanguis::server::entities::auto_weak_link::auto_weak_link(
	sanguis::server::entities::with_links &_ref
)
:
	ref_(
		fcppt::make_ref(
			_ref
		)
	)
{
	this->add_me();
}

sanguis::server::entities::auto_weak_link::auto_weak_link(
	auto_weak_link const &_old
)
:
	sanguis::server::entities::auto_weak_hook(
		_old
	),
	ref_(
		_old.ref_
	)
{
	if(
		_old.is_linked()
	)
	{
		this->add_me();
	}
}

sanguis::server::entities::auto_weak_link::~auto_weak_link()
= default;

sanguis::server::entities::auto_weak_link &
sanguis::server::entities::auto_weak_link::operator=(
	auto_weak_link const &_old
)
{
	if(
		this
		==
		&_old
	)
	{
		return
			*this;
	}

	this->unlink();

	sanguis::server::entities::auto_weak_hook::operator=(
		_old
	);

	ref_ =
		_old.ref_;

	if(
		_old.is_linked()
	)
	{
		this->add_me();
	}

	return
		*this;
}

void
sanguis::server::entities::auto_weak_link::unlink()
{
	sanguis::server::entities::auto_weak_hook::unlink();

	ref_ =
		optional_with_links_ref();
}

sanguis::server::entities::auto_weak_link::optional_with_links_ref
sanguis::server::entities::auto_weak_link::get() const
{
	return
		this->is_linked()
		?
			ref_
		:
			optional_with_links_ref()
		;
}

bool
sanguis::server::entities::auto_weak_link::operator==(
	sanguis::server::entities::auto_weak_link const &_link
) const
{
	return
		this->is_linked()
		==
		_link.is_linked()
		&&
		ref_
		==
		_link.ref_;
}

sanguis::server::entities::with_links &
sanguis::server::entities::auto_weak_link::checked_ref() const
{
	return
		FCPPT_ASSERT_OPTIONAL_ERROR(
			this->get()
		).get();
}

void
sanguis::server::entities::auto_weak_link::add_me()
{
	fcppt::optional::maybe_void(
		ref_,
		[
			this
		](
			fcppt::reference<
				sanguis::server::entities::with_links
			> const _ref
		)
		{
			_ref.get().insert_link(
				*this
			);
		}
	);
}

bool
sanguis::server::entities::operator!=(
	sanguis::server::entities::auto_weak_link const &_left,
	sanguis::server::entities::auto_weak_link const &_right
)
{
	return
		!(
			_left
			==
			_right
		);
}
