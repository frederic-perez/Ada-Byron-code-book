# -- 

project(Ada-Byron-code-book)

set(CTEST_PROJECT_NAME "${PROJECT_NAME}")
set(CTEST_DROP_METHOD "http")
option(USE_ALMA_LOCAL_CDASH "Use Alma's local CDash" OFF)
if(USE_ALMA_LOCAL_CDASH)
	set(CTEST_DROP_SITE "172.26.0.117")
	set(CTEST_DROP_LOCATION "/CDash/submit.php?project=Bone-segmenter")
else()
	set(CTEST_DROP_SITE "my.cdash.org")
	set(CTEST_DROP_LOCATION "/submit.php?project=${PROJECT_NAME}")
endif()
set(CTEST_DROP_SITE_CDASH TRUE)

# -- eof
