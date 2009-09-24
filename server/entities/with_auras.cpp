sanguis::server::entities::with_auras::with_auras(
	base_parameters const &param_
)
:
	base(
		param_
	),
	auras_()
{}

void
sanguis::server::entities::with_auras::add_aura(
	auras::auto_ptr a)
{
	auras_.push_back(a);

	auras::aura &ref(
		auras_.back()
	);

	ref.owner(
		id()
	);
}

void
sanguis::server::entities::with_auras::center()
{
	BOOST_FOREACH(
		aura_container::reference r,
		auras_
	)
		r.center(
			_center
		);
}

void
sanguis::server::entities::with_auras::on_destroy()
{
	BOOST_FOREACH(
		aura_container::reference aura_,
		auras_
	)
		aura_.destroy();
}

void
sanguis::server::entities::with_auras::recreate(
)
{
	BOOST_FOREACH(
		aura_container::reference aura_,
		auras_
	)
		aura_.recreate(
			environment_->collision_world(),
			collision_groups_,
			create_param
		);
}
