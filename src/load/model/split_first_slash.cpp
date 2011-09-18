#include <sanguis/load/model/split_first_slash.hpp>
#include <sanguis/exception.hpp>
#include <fcppt/text.hpp>

sanguis::load::model::split_pair const
sanguis::load::model::split_first_slash(
	fcppt::string const &_string
)
{
	fcppt::string::size_type const sz(
		_string.find(
			FCPPT_TEXT('/')
		)
	);

	if(
		sz == fcppt::string::npos
	)
		throw sanguis::exception(
			FCPPT_TEXT("No / found in ")
			+ _string
		);

	return
		model::split_pair(
			fcppt::string(
				_string.substr(
					0,
					sz
				)
			),
			fcppt::string(
				_string.substr(
					sz + 1
				)
			)
		);
}
