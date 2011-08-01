#include "load_delay.hpp"
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/chrono/duration_cast.hpp>
#include <fcppt/chrono/milliseconds.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>

sanguis::load::model::optional_delay const
sanguis::load::model::load_delay(
	sge::parse::json::member_vector const &entries
)
{
	int const *const ret(
		sge::parse::json::find_member<
			int
		>(
			entries,
			FCPPT_TEXT("delay")
		)
	);

	return
		ret
		?
			optional_delay(
				fcppt::chrono::duration_cast<
					sanguis::duration
				>(
					// FIXME: we shouldn't tell multiple times that these are milliseconds!
					fcppt::chrono::milliseconds(
						*ret
					)
				)
			)
		:
			optional_delay();
}
