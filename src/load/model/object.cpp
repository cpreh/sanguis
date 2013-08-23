#include <sanguis/exception.hpp>
#include <sanguis/random_generator.hpp>
#include <sanguis/load/log.hpp>
#include <sanguis/load/model/cell_size.hpp>
#include <sanguis/load/model/make_parts.hpp>
#include <sanguis/load/model/object.hpp>
#include <sanguis/load/model/part.hpp>
#include <sanguis/load/resource/context_fwd.hpp>
#include <sge/exception.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/random/variate.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_int.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>


sanguis::load::model::object::object(
	boost::filesystem::path const &_path,
	sanguis::load::resource::context const &_context
)
try
:
	path_(
		_path
	),
	part_result_(
		sanguis::load::model::make_parts(
			_path,
			_context
		)
	),
	random_part_()
{
	FCPPT_LOG_DEBUG(
		sanguis::load::log(),
		fcppt::log::_
			<< FCPPT_TEXT("Entering ")
			<< fcppt::filesystem::path_to_string(
				_path
			)
	);
}
catch(
	sge::exception const &_error
)
{
	FCPPT_LOG_ERROR(
		sanguis::load::log(),
		fcppt::log::_
			<< FCPPT_TEXT("model \"")
			<< fcppt::filesystem::path_to_string(
				_path
			)
			<< FCPPT_TEXT("\": \"")
			<< _error.string()
			<< FCPPT_TEXT('"')
	);

	throw;
}

sanguis::load::model::object::~object()
{
}

sanguis::load::model::part const &
sanguis::load::model::object::operator[](
	fcppt::string const &_name
) const
{
	sanguis::load::model::part_map::const_iterator const it(
		this->parts().find(
			_name
		)
	);

	if(
		it
		==
		this->parts().end()
	)
		throw sanguis::exception(
			FCPPT_TEXT("Category \"")
			+
			_name
			+
			FCPPT_TEXT("\" not found in ")
			+
			fcppt::filesystem::path_to_string(
				path_
			)
		);

	return
		*it->second;
}

sanguis::load::model::part const &
sanguis::load::model::object::random_part(
	sanguis::random_generator &_random_generator
) const
{
	if(
		!random_part_
	)
		random_part_.take(
			fcppt::make_unique_ptr<
				part_rand
			>(
				_random_generator,
				part_map_distribution(
					part_map_distribution::param_type::min(
						0u
					),
					part_map_distribution::param_type::max(
						this->parts().size() - 1u
					)
				)
			)
		);

	return
		*std::next(
			this->parts().begin(),
			static_cast<
				sanguis::load::model::part_map::difference_type
			>(
				(
					*random_part_
				)()
			)
		)->second;
}

sanguis::load::model::object::size_type
sanguis::load::model::object::size() const
{
	return
		this->parts().size();
}

sanguis::load::model::object::const_iterator
sanguis::load::model::object::begin() const
{
	return
		this->parts().begin();
}

sanguis::load::model::object::const_iterator
sanguis::load::model::object::end() const
{
	return
		this->parts().end();
}

sanguis::load::model::cell_size const
sanguis::load::model::object::cell_size() const
{
	return
		part_result_.cell_size();
}

sanguis::load::model::part_map const &
sanguis::load::model::object::parts() const
{
	return
		part_result_.parts();
}
