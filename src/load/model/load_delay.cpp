#include <sanguis/load/model/load_delay.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/chrono/duration.hpp>
#include <fcppt/config/external_end.hpp>

sanguis::load::model::optional_delay const
sanguis::load::model::load_delay(
	sge::parse::json::member_map const &_entries
)
{
	typedef fcppt::optional<
		int const &
	> optional_int_ref;

	optional_int_ref const ret(
		sge::parse::json::find_member<
			int
		>(
			_entries,
			FCPPT_TEXT("delay")
		)
	);

	return
		ret
		?
			model::optional_delay(
				boost::chrono::duration_cast<
					sanguis::duration
				>(
					// FIXME: we shouldn't tell multiple times that these are milliseconds!
					boost::chrono::milliseconds(
						*ret
					)
				)
			)
		:
			model::optional_delay()
		;
}
