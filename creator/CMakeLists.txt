fcppt_utils_load_source_files(creator/files.txt SANGUIS_CREATOR_FILES)

sanguis_add_library(
  creator
  "${SANGUIS_CREATOR_FILES}"
  HAS_IMPL_DIR
  DEPS
  ${sanguis_core_TARGET}
  ${fcppt_core_TARGET}
  ${fcppt_log_TARGET}
  ${sgecore_TARGET}
  ${sgeparse_TARGET}
  ${sgeparsejson_TARGET}
  sgebresenham_interface
  TRANSITIVE_DEPS
  fcppt_core_interface
  fcppt_log_interface)
