cmake_minimum_required(VERSION 3.2)

PROJECT(log4cpp)

# Policy to address @foo@ variable expansion
if(POLICY CMP0053)
  cmake_policy(SET CMP0053 NEW)
endif()

include_directories ( include )
include_directories ( . )
add_library(log4cpp SHARED 
  src/Appender.cpp
  src/AppenderSkeleton.cpp
  src/AppendersFactory.cpp
  src/BufferingAppender.cpp
  src/FactoryParams.cpp
  src/LayoutsFactory.cpp
  src/LevelEvaluator.cpp
  src/Localtime.cpp
  src/PassThroughLayout.cpp
  src/TriggeringEventEvaluatorFactory.cpp
  src/LayoutAppender.cpp
  src/FileAppender.cpp
  src/DailyRollingFileAppender.cpp
  src/RollingFileAppender.cpp
  src/FixedContextCategory.cpp
  src/IdsaAppender.cpp
  src/OstreamAppender.cpp
  src/StringQueueAppender.cpp
  src/SyslogAppender.cpp
  src/RemoteSyslogAppender.cpp
  src/SimpleLayout.cpp
  src/BasicLayout.cpp
  src/PatternLayout.cpp
  src/Category.cpp
  src/CategoryStream.cpp
  src/HierarchyMaintainer.cpp
  src/Configurator.cpp
  src/BasicConfigurator.cpp
  src/SimpleConfigurator.cpp
  src/PropertyConfigurator.cpp
  src/PropertyConfiguratorImpl.cpp
  src/LoggingEvent.cpp
  src/Priority.cpp
  src/NDC.cpp
  src/Filter.cpp
  src/TimeStamp.cpp
  src/StringUtil.cpp
  src/Properties.cpp
  src/Win32DebugAppender.cpp
  src/NTEventLogAppender.cpp
  src/DllMain.cpp
  src/DummyThreads.cpp
  src/MSThreads.cpp
  src/OmniThreads.cpp
  src/PThreads.cpp
  src/PortabilityImpl.cpp
  src/AbortAppender.cpp
)
# Preprocessor Definitions
if (WIN32)
  set(FLAGS)
  set(FLAGS "${FLAGS} -D LOG4CPP_HAS_DLL")
  set(FLAGS "${FLAGS} -D LOG4CPP_BUILD_DLL")
  set(FLAGS "${FLAGS} -D _CRT_SECURE_NO_WARNINGS")
#  MESSAGE(${FLAGS})
  set_target_properties(log4cpp PROPERTIES COMPILE_FLAGS "${FLAGS}" PREFIX "")
  target_link_libraries(log4cpp ws2_32 advapi32)
#  set_target_properties(log4cpp PROPERTIES LINK_FLAGS /NODEFAULTLIB:msvcrt )
else (WIN32)
  if (APPLE)
    add_definitions ( -DNDEBUG -DLOG4CPP_HAVE_SSTREAM )
    set_target_properties(log4cpp PROPERTIES MACOSX_RPATH ON)
  else (APPLE)
    add_definitions ( -pthread -DNDEBUG -DLOG4CPP_HAVE_SSTREAM )
  endif (APPLE)
endif (WIN32)

install (
  DIRECTORY include/log4cpp
  DESTINATION include
  PATTERN ".svn" EXCLUDE
  PATTERN "*.am" EXCLUDE
  PATTERN "*.in" EXCLUDE
  )

install (TARGETS log4cpp
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)
  
