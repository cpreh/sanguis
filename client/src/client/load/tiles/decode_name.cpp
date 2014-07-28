#include <sanguis/client/load/tiles/decode_name.hpp>
#include <sanguis/client/load/tiles/direction.hpp>
#include <sanguis/client/load/tiles/optional_orientation.hpp>
#include <sanguis/client/load/tiles/orientation.hpp>
#include <fcppt/char_type.hpp>
#include <fcppt/enum_size.hpp>
#include <fcppt/make_enum_range.hpp>
#include <fcppt/optional_bind.hpp>
#include <fcppt/optional_bind_construct.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/cast/enum_to_int.hpp>


sanguis::client::load::tiles::optional_orientation const
sanguis::client::load::tiles::decode_name(
	fcppt::string const &_name
)
{
	return
		_name.size()
		!=
		fcppt::enum_size<
			sanguis::client::load::tiles::direction
		>::value
		?
			sanguis::client::load::tiles::optional_orientation()
		:
			fcppt::algorithm::fold(
				fcppt::make_enum_range<
					sanguis::client::load::tiles::direction
				>(),
				sanguis::client::load::tiles::optional_orientation(
					sanguis::client::load::tiles::orientation::null()
				),
				[
					&_name
				](
					sanguis::client::load::tiles::direction const _dir,
					sanguis::client::load::tiles::optional_orientation const _state
				)
				{
					return
						fcppt::optional_bind(
							_state,
							[
								_dir,
								&_name
							](
								sanguis::client::load::tiles::orientation const _orientation
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
									fcppt::optional_bind_construct(
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
										-> sanguis::client::load::tiles::orientation
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
