set(assignment 800B)
set(exe_name ${assignment})
set(${exe_name}_srcs
  main.cpp
  )
source_group("" FILES ${${exe_name}_srcs})
add_executable(${exe_name} ${${exe_name}_srcs})
set_property(TARGET ${exe_name} PROPERTY FOLDER ${exe_name})
install(TARGETS ${exe_name} DESTINATION .)
