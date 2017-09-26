{
  "targets": [
    {
      "target_name": "bitprim",
      "sources": [ "bitprim_addon.cc" ],

      # # Linux OLD
      # "include_dirs": ["/home/fernando/dev/bitprim/bitprim-node-cint/include"],
      # "libraries": [ "-lbitprim-node-cint", "-L/home/fernando/dev/bitprim/bitprim-node-cint/cmake-build-debug" ]

      # # Windows OLD
      # "include_dirs": ["C:\\development\\bitprim\\bitprim-node-cint\\include", "C:\\development\\bitprim\\bitprim-core\\include"],
      # "libraries": [ "C:\\development\\bitprim\\bitprim-node-cint\\build\\bitprim-node-cint.lib"]
      # # "libraries": [ "-LC:\\development\\bitprim\\bitprim-node-cint\\build", "-lbitprim-node-cint"  ]

      "include_dirs": ["deps/include/"],

      'conditions': [
        ['OS=="linux"', {
          'libraries': [
            '-L../deps/lib/', 
            '-lbitprim-node-cint',
            '-lbitprim-node-cint', 
            '-lbitprim-node', 
            '-lbitprim-blockchain', 
            '-lbitprim-network', 
            '-lbitprim-consensus', 
            '-lbitprim-database', 
            '-lbitprim-core',
            '-lboost_atomic', 
            '-lboost_chrono', 
            '-lboost_date_time', 
            '-lboost_filesystem', 
            '-lboost_iostreams', 
            '-lboost_locale', 
            '-lboost_log', 
            '-lboost_log_setup', 
            '-lboost_program_options', 
            '-lboost_random', 
            '-lboost_regex', 
            '-lboost_system', 
            '-lboost_unit_test_framework', 
            '-lboost_prg_exec_monitor', 
            '-lboost_test_exec_monitor', 
            '-lboost_thread', 
            '-lboost_timer', 
            '-lsecp256k1', 
            '-lbz2', 
            '-lgmp', 
            '-lz',
          ],
        }],
        ['OS=="mac"', {
          'libraries': [
          ],
        }],
        # ['OS=="linux"', {
        #   'cflags': [
        #     '<!@(pkg-config --cflags QtCore QtGui QtTest)'
        #   ],
        #   'ldflags': [
        #     '<!@(pkg-config --libs-only-L --libs-only-other QtCore QtGui QtTest)'
        #   ],
        #   'libraries': [
        #     '<!@(pkg-config --libs-only-l QtCore QtGui QtTest)'
        #   ]
        # }],
        ['OS=="win"', {
          'libraries': [
              # '../deps/qt-4.8.0/win32/ia32/lib/QtCore4.lib',
              # '../deps/qt-4.8.0/win32/ia32/lib/QtGui4.lib',
              # '../deps/qt-4.8.0/win32/ia32/lib/QtTest4.lib'
          ]
        }]
      ],

    }
  ]
}
