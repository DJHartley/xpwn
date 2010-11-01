add_executable(hfstool hfstool.c)
target_link_libraries (hfstool hfs)
install(TARGETS hfstool DESTINATION .)

add_executable(dmgtool dmgtool.c)
target_link_libraries (dmgtool dmg)
install(TARGETS dmgtool DESTINATION .)

add_executable(ipswtool ipswtool.c)
target_link_libraries(ipswtool ipsw)
install(TARGETS ipswtool DESTINATION .)

add_executable(xpwntool xpwntool.c)
target_link_libraries(xpwntool ipsw)
install(TARGETS xpwntool DESTINATION .)

add_executable(imagetool imagetool.c)
target_link_libraries(imagetool ipsw)
install(TARGETS imagetool DESTINATION .)

