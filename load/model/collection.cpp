#include "collection.hpp"
#include "make_path.hpp"
#include "object.hpp"
#include <fcppt/auto_ptr.hpp>
#include <fcppt/make_auto_ptr.hpp>

sanguis::load::model::object const &
sanguis::load::model::collection::operator[](
	fcppt::string const &name
) const
{
	boost::mutex::scoped_lock const lock_(
		mutex_
	);

	model_map::const_iterator it(
		models.find(
			name
		)
	);

	if(
		it == models.end()
	)
	{
		fcppt::auto_ptr<
			object
		>
		to_insert(
			fcppt::make_auto_ptr<
				object
			>(
				make_path(
					name
				),
				ctx
			)
		);
			
		it = models.insert(
			name,
			to_insert
		).first;
	}

	return *it->second;	
}

sanguis::load::model::collection::~collection()
{
}

sanguis::load::model::collection::collection(
	resource::context const &ctx
)
:
	ctx(ctx),
	models(),
	mutex_()
{}
