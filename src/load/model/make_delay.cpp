#include <sanguis/duration.hpp>
#include <sanguis/exception.hpp>
#include <sanguis/load/model/make_delay.hpp>
#include <sanguis/load/model/optional_delay.hpp>
#include <sge/parse/json/find_member.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>


sanguis::duration const
sanguis::load::model::make_delay(
	sge::parse::json::object const &_object,
	sanguis::load::model::optional_delay const &_opt_delay
)
{
	typedef fcppt::optional<
		sge::parse::json::int_type
	> optional_int;

	optional_int const opt_value(
		sge::parse::json::find_member<
			sge::parse::json::int_type
		>(
			_object.members,
			FCPPT_TEXT("delay")
		)
	);

	if(
		opt_value
	)
		return
			std::chrono::duration_cast<
				sanguis::duration
			>(
				std::chrono::milliseconds(
					*opt_value
				)
			);

	if(
		_opt_delay
	)
		return
			*_opt_delay;

	throw
		sanguis::exception(
			FCPPT_TEXT("delay not in header but not in specified leaf TODO either!")
		);
}
