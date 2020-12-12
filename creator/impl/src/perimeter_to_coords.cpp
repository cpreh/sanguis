#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/impl/perimeter_to_coords.hpp>
#include <fcppt/assert/error.hpp>


sanguis::creator::grid::pos
sanguis::creator::impl::perimeter_to_coords(
	sanguis::creator::grid::dim const &_dim,
	unsigned const &_t)
{
	auto const w2 = static_cast<unsigned>(_dim.w() - 2);
	auto const h2 = static_cast<unsigned>(_dim.h() - 2);

	FCPPT_ASSERT_ERROR(
		w2 > 0);

	FCPPT_ASSERT_ERROR(
		h2 > 0);

	FCPPT_ASSERT_ERROR(
		_t < 2 * w2 + 2 * h2);

	if (_t < w2)
	{
		return sanguis::creator::grid::pos(
			_t + 1U,
			0U);
	}

	if (_t < w2 + h2)
	{
		return sanguis::creator::grid::pos(
			w2 + 1U,
			_t - w2 + 1U);
	}

	if (_t < 2U * w2 + h2)
	{
		return sanguis::creator::grid::pos(
			w2 - (_t - w2 - h2),
			h2 + 1U);
	}

	return sanguis::creator::grid::pos(
		0U,
		h2 - (_t - 2U * w2 - h2));
}
