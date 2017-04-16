#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/impl/perimeter_to_coords.hpp>
#include <fcppt/assert/error.hpp>


sanguis::creator::grid::pos
sanguis::creator::impl::perimeter_to_coords(
	sanguis::creator::grid::dim const &_dim,
	unsigned const &_t)
{
	unsigned w2 = static_cast<unsigned>(_dim.w() - 2);
	unsigned h2 = static_cast<unsigned>(_dim.h() - 2);

	FCPPT_ASSERT_ERROR(
		w2 > 0);

	FCPPT_ASSERT_ERROR(
		h2 > 0);

	FCPPT_ASSERT_ERROR(
		_t < 2 * w2 + 2 * h2);

	if (_t < w2)
		return sanguis::creator::grid::pos(
			_t + 1u,
			0u);

	if (_t < w2 + h2)
		return sanguis::creator::grid::pos(
			w2 + 1u,
			_t - w2 + 1u);

	if (_t < 2u * w2 + h2)
		return sanguis::creator::grid::pos(
			w2 - (_t - w2 - h2),
			h2 + 1u);

	return sanguis::creator::grid::pos(
		0u,
		h2 - (_t - 2u * w2 - h2));
}
