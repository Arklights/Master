
set (AUTOTOOL_FILES "autom4te.cache;m4;configure.ac;Makefile.am")

set (CPACK_GENERATOR TGZ)
set (CPACK_PACKAGE_NAME "snort")
set (CPACK_PACKAGE_VENDOR "Cisco")
set (CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
set (CPACK_PACKAGE_VERSION_PATCH "${VERSION_BUILD}-${VERSION_RELEASE}")
set (CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/doc/images/snort.png")
set (CPACK_PACKAGE_INSTALL_DIRECTORY "snort")
set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set (CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")
set (CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
set (CPACK_SOURCE_IGNORE_FILES "tools/snort2lua/tests/;\\\\.git/;\\\\.gitignore;extra/;${AUTOTOOL_FILES}")
set (CPACK_SOURCE_GENERATOR TGZ)

include(CPack)
