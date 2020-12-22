#ifndef SANGUIS_TOOLS_ANIMATIONS_QTUTIL_STRING_TO_OPTIONAL_HPP_INCLUDED
#define SANGUIS_TOOLS_ANIMATIONS_QTUTIL_STRING_TO_OPTIONAL_HPP_INCLUDED

#include <sanguis/tools/animations/qtutil/to_fcppt_string.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <QString>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace tools
{
namespace animations
{
namespace qtutil
{

template<
	typename Result
>
fcppt::optional::object<
	Result
>
string_to_optional(
	QString const &_string
)
{
	using
	result_type
	=
	fcppt::optional::object<
		Result
	>;

	return
		_string.isEmpty()
		?
			result_type()
		:
			result_type(
				Result(
					sanguis::tools::animations::qtutil::to_fcppt_string(
						_string
					)
				)
			)
		;
}

}
}
}
}

#endif
