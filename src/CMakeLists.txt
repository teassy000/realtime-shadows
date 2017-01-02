# add projects
add_subdirectory(baseShadowApp)

# set all projects' subsystem to Windows
set_target_properties(baseShadowApp PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
