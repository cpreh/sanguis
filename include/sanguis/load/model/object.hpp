#ifndef SANGUIS_LOAD_MODEL_OBJECT_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_OBJECT_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/load/model/cell_size.hpp>
#include <sanguis/load/model/object_fwd.hpp>
#include <sanguis/load/model/part_fwd.hpp>
#include <sanguis/load/model/part_map.hpp>
#include <sanguis/load/model/part_result.hpp>
#include <sanguis/load/resource/context_fwd.hpp>
#include <fcppt/random/variate_fwd.hpp>
#include <fcppt/random/distribution/basic_fwd.hpp>
#include <fcppt/random/distribution/parameters/uniform_int_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace load
{
namespace model
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	typedef sanguis::load::model::part_map::const_iterator const_iterator;

	typedef sanguis::load::model::part_map::size_type size_type;

	object(
		boost::filesystem::path const &,
		sanguis::load::resource::context const &
	);

	~object();

	sanguis::load::model::part const &
	operator[](
		fcppt::string const &
	) const;

	sanguis::load::model::part const &
	random_part(
		sanguis::random_generator &
	) const;

	size_type
	size() const;

	const_iterator
	begin() const;

	const_iterator
	end() const;

	sanguis::load::model::cell_size const
	cell_size() const;
private:
	sanguis::load::model::part_map const &
	parts() const;

	boost::filesystem::path const path_;

	sanguis::load::model::part_result const part_result_;

	typedef fcppt::random::distribution::basic<
		fcppt::random::distribution::parameters::uniform_int<
			sanguis::load::model::part_map::size_type
		>
	> part_map_distribution;

	typedef fcppt::random::variate<
		sanguis::random_generator,
		part_map_distribution
	> part_rand;

	mutable fcppt::scoped_ptr<
		part_rand
	> random_part_;
};

}
}
}

#endif
