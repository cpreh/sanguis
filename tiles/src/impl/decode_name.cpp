#include <sanguis/tiles/direction.hpp>
#include <sanguis/tiles/orientation.hpp>
#include <sanguis/tiles/impl/decode_name.hpp>
#include <sanguis/tiles/impl/optional_orientation.hpp>
#include <fcppt/char_type.hpp>
#include <fcppt/enum_size.hpp>
#include <fcppt/make_enum_range.hpp>
#include <fcppt/optional_bind.hpp>
#include <fcppt/optional_map.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/cast/enum_to_int.hpp>
#include <fcppt/container/bitfield/operators.hpp>


sanguis::tiles::impl::optional_orientation
sanguis::tiles::impl::decode_name(
	fcppt::string const &_name
)
{
	return
		_name.size()
		!=
		fcppt::enum_size<
			sanguis::tiles::direction
		>::value
		?
			sanguis::tiles::impl::optional_orientation()
		:
			fcppt::algorithm::fold(
				fcppt::make_enum_range<
					sanguis::tiles::direction
				>(),
				sanguis::tiles::impl::optional_orientation(
					sanguis::tiles::orientation::null()
				),
				[
					&_name
				](
					sanguis::tiles::direction const _dir,
					sanguis::tiles::impl::optional_orientation const _state
				)
				{
					return
						fcppt::optional_bind(
							_state,
							[
								_dir,
								&_name
							](
								sanguis::tiles::orientation const _orientation
							)
							{
								typedef
								fcppt::optional<
									bool
								>
								optional_bool;

								auto const char_to_bool(
									[](
										fcppt::char_type const _value
									)
									-> optional_bool
									{
										switch(
											_value
										)
										{
										case FCPPT_TEXT('0'):
											return
												optional_bool(
													true
												);
										case FCPPT_TEXT('1'):
											return
												optional_bool(
													false
												);
										}

										return
											optional_bool();
									}
								);

								return
									fcppt::optional_map(
										char_to_bool(
											_name[
												fcppt::cast::enum_to_int<
													fcppt::string::size_type
												>(
													_dir
												)
											]
										),
										[
											_orientation,
											_dir
										](
											bool const _value
										)
										-> sanguis::tiles::orientation
										{
											return
												_value
												?
													_orientation
													|
													_dir
												:
													_orientation
												;
										}
									);
							}
						);
				}
			);
}
