project('strptime', 'c',
  version : '1.0.0',
  default_options : ['warning_level=3'])

strptime = static_library('strptime',
    files(
      'src/LibOb_strptime.c',
      'src/strptime.c'
    ),
    include_directories: ['include'],
    install: true
  )

shared_library('ob',
    files(),
    link_with: [strptime],
    install: true
  )

install_headers(
    files(
      'include/strptime.h'
    ),
    subdir: 'libob'
  )
