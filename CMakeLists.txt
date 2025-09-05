add_library(ImGuiDebugUI SHARED)

# Sources
file(GLOB_RECURSE INCL CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Include/*.*")
file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.*")
file(GLOB_RECURSE META CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.meta")
target_sources(ImGuiDebugUI PRIVATE ${SRCS} ${INCL} ${META})

# Expose include dirs to dependents (build & install time)
target_include_directories(ImGuiDebugUI
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
    $<INSTALL_INTERFACE:Include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Source
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# C++20
set_target_properties(ImGuiDebugUI PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)

# Links
target_link_libraries(ImGuiDebugUI PUBLIC
  Tbx::Engine
  imgui
  SDL3-shared
)

# Copy plugin meta file to build dir
add_custom_command(TARGET ImGuiDebugUI POST_BUILD
  COMMENT "Copying plugin meta file to build dir"
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
          "${CMAKE_CURRENT_SOURCE_DIR}/ImGuiDebugUI.meta"
          "$<TARGET_FILE_DIR:ImGuiDebugUI>/ImGuiDebugUI.meta")

# Namespaced alias for consumers
add_library(Tbx::Plugin::ImGuiDebugUI ALIAS ImGuiDebugUI)