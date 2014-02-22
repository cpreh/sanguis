#include <sanguis/model/cell_size.hpp>
#include <sanguis/model/exception.hpp>
#include <sanguis/model/object.hpp>
#include <sanguis/model/optional_animation_delay.hpp>
#include <sanguis/model/part_fwd.hpp>
#include <sanguis/model/part_map.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::model::object::object(
	sanguis::model::cell_size const _cell_size,
	sanguis::model::optional_animation_delay const _animation_delay,
	sanguis::model::part_map &&_parts
)
:
	cell_size_{
		_cell_size
	},
	animation_delay_{
		_animation_delay
	},
	parts_(
		std::move(
			_parts
		)
	)
{
}

sanguis::model::object::object(
	object &&
) = default;

sanguis::model::object &
sanguis::model::object::operator=(
	object &&
) = default;

sanguis::model::object::~object()
{
}

sanguis::model::optional_animation_delay const
sanguis::model::object::animation_delay() const
{
	return
		animation_delay_;
}

void
sanguis::model::object::animation_delay(
	sanguis::model::optional_animation_delay const _animation_delay
)
{
	animation_delay_ =
		_animation_delay;
}

sanguis::model::part &
sanguis::model::object::part(
	fcppt::string const &_name
)
{
	sanguis::model::part_map::iterator const it{
		parts_.find(
			_name
		)
	};

	if(
		it
		==
		parts_.end()
	)
		throw
			sanguis::model::exception{
				FCPPT_TEXT("No part named ")
				+
				_name
			};

	return
		it->second;
}

sanguis::model::part_map const &
sanguis::model::object::parts() const
{
	return
		parts_;
}

sanguis::model::cell_size const
sanguis::model::object::cell_size() const
{
	return
		cell_size_;
}
