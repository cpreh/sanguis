#include <sanguis/load/model/cell_size.hpp>
#include <sanguis/load/model/part.hpp>
#include <sanguis/load/model/part_map.hpp>
#include <sanguis/load/model/part_result.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::load::model::part_result::part_result(
	sanguis::load::model::cell_size const &_cell_size,
	sanguis::load::model::part_map &&_parts
)
:
	cell_size_(
		_cell_size
	),
	parts_(
		std::move(
			_parts
		)
	)
{
}

sanguis::load::model::part_result::part_result(
	part_result &&_other
)// = default;
:
	cell_size_(
		_other.cell_size_
	),
	parts_(
		std::move(
			_other.parts_
		)
	)
{
}

sanguis::load::model::part_result::~part_result()
{
}

sanguis::load::model::cell_size const &
sanguis::load::model::part_result::cell_size() const
{
	return
		cell_size_;
}

sanguis::load::model::part_map const &
sanguis::load::model::part_result::parts() const
{
	return
		parts_;
}
