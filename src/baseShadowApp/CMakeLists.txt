set(RESOURCE_DIR ../../res)
set(UTIL_DIR ../common)
set(EXTERN_DIR ../../libs/external)

# add link dir
link_directories(G:/projects/realtime-shadows/libs/external/DirectXTK/Bin/Desktop_2015/x64)

# add files
aux_source_directory(. DIR_SRCS)

# shaders
file(GLOB VS_SHADERS
"${RESOURCE_DIR}/shaders/base.vs.hlsl"
)
file(GLOB PS_SHADERS
"${RESOURCE_DIR}/shaders/base.ps.hlsl"
)

set_source_files_properties( ${PS_SHADERS} PROPERTIES VS_SHADER_TYPE Pixel VS_SHADER_MODEL 5.0 VS_SHADER_ENTRYPOINT main )
set_source_files_properties( ${VS_SHADERS} PROPERTIES VS_SHADER_TYPE Vertex VS_SHADER_MODEL 5.0 VS_SHADER_ENTRYPOINT main )

source_group("shaders" FILES ${VS_SHADERS} ${PS_SHADERS})

# add header directory
include_directories(${UTIL_DIR} ${EXTERN_DIR}/DirectXTK/Inc)

# add the executable
add_executable( baseShadowApp ${DIR_SRCS} ${VS_SHADERS} ${PS_SHADERS})

# add liberarys
target_link_libraries ( baseShadowApp DirectXTK)

# set project's subsystem to Windows
set_target_properties( baseShadowApp PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")