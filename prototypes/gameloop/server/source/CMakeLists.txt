# 
# External dependencies
# 

find_package(Qt5Core     5.9 REQUIRED)
find_package(Qt5Gui      5.9 REQUIRED)


#
# Targets
#

add_subdirectory(server)
add_subdirectory(serverlib)
