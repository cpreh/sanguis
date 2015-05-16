#include <sanguis/creator/signed_rect.hpp>
#include <sanguis/creator/impl/overlap.hpp>

bool
sanguis::creator::impl::overlap(
	sanguis::creator::signed_rect const &_a,
	sanguis::creator::signed_rect const &_b
)
{
	return
		_a.left() <= _b.right() &&
		_a.top() <= _b.bottom() &&
		_a.right() >= _b.left() &&
		_a.bottom() >= _b.top();
}
