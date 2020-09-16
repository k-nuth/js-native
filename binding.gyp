# Copyright (c) 2016-2020 Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

{
  "targets": [
    {
      # "target_name": "kth",
      "target_name": "<(module_name)",

      'product_dir': '<(module_path)',

      "sources": [ "kth_addon.cpp", "chain/chain.cpp", "chain/header.cpp", "chain/block.cpp", 
                   "chain/merkle_block.cpp", "chain/point.cpp", 
                   "chain/transaction.cpp", "chain/input.cpp", "chain/output.cpp", "chain/output_point.cpp", 
                   "chain/tools.cpp",
                   "chain/script.cpp", "chain/input_list.cpp", "chain/output_list.cpp", "chain/transaction_list.cpp",
                   "chain/block_list.cpp",
                   "chain/history_compact_list.cpp",
                   "chain/history_compact.cpp",
                   "chain/payment_address.cpp",
                   "chain/stealth_compact.cpp",
                   "chain/stealth_compact_list.cpp",
                   "wallet/word_list.cpp",
                ],
      
      'variables': {
        'setup_py': '<(DEPTH)/setup.py',
        'install_py': '<(DEPTH)/install.py',
      },

      # 'actions': [
      #   {
      #       'action_name': 'build_ftgl',
      #       'message': 'Building FTGL...',
      #       'inputs': ['ftgl/src/FTGL/ftgl.h'],
      #       'outputs': ['ftgl/src/.libs/libftgl.a'],
      #       'action': [''eval', 'cd ftgl && ./configure --with-pic && make -C src''],
      #   },
      # ],

      # 'actions': [
      #   {
      #     'variables': {
      #       'core_library_files': [
      #         'src/runtime.js',
      #         'src/v8natives.js',
      #         'src/macros.py',
      #       ],
      #     },
      #     'action_name': 'js2c',
      #     'inputs': [
      #       'tools/js2c.py',
      #       '<@(core_library_files)',
      #     ],
      #     'outputs': [
      #       '<(INTERMEDIATE_DIR)/libraries.cpp',
      #       '<(INTERMEDIATE_DIR)/libraries-empty.cpp',
      #     ],
      #     'action': ['python', 'tools/js2c.py', '<@(_outputs)', 'CORE', '<@(core_library_files)'],
      #   },
      # ],


      'actions': [
        # {
        #     'action_name': 'installconan',
        #     'message': 'Install Conan',
        #     'inputs': [''],
        #     'outputs': [''],
        #     'action': ['python', '-m pip install conan'],
        #     # 'action': ['python', '--version'],
        # },
        # {
        #     'action_name': 'runconan',
        #     'message': 'run Conan',
        #     'inputs': [''],
        #     'outputs': [''],
        #     'action': ['python', '-m conans.conan', 'install ..'],
        # },
        # {
        #     'action_name': 'movedir',
        #     'message': 'Move Dirs',
        #     'inputs': [''],
        #     'outputs': [''],
        #     # 'action': ['python', '../setup.py'],
        #     'action': ['python', '-c "\\texec(\\"import os \\nprint(os.getcwd()) \\")"'],
        # },

        {
          'action_name': 'Install',
          'inputs': [
            '>(install_py)',
          ],
          # 'outputs': ['>(nmf_pnacl)'],
          'outputs': [''],
          'action': [
            'python',
            '>@(_inputs)', 
          ],
        },
        {
          'action_name': 'Setup',
          'inputs': [
            '>(setup_py)',
          ],
          # 'outputs': ['>(nmf_pnacl)'],
          'outputs': [''],
          'action': [
            'python',
            '>@(_inputs)', 
          ],
        },
      ],


      'defines': [
          'KTH_LIB_STATIC',
          'KTH_DB_NEW_FULL',
      ],
      # # Linux OLD
      # "include_dirs": ["/home/fernando/dev/k-nuth/node-cint/include"],
      # "libraries": [ "-lkth-c-api", "-L/home/fernando/dev/k-nuth/node-cint/cmake-build-debug" ]

      # # Windows OLD
      # "include_dirs": ["C:\\development\\kth\\c-api\\include", "C:\\development\\kth\\kth-domain\\include"],
      # "libraries": [ "C:\\development\\kth\\c-api\\build\\c-api.lib"]
      # # "libraries": [ "-LC:\\development\\kth\\c-api\\build", "-lkth-c-api"  ]

      

      'configurations': {
        'Debug': {
          'msvs_settings': {
            'VCCLCompilerTool': {
                'RuntimeLibrary': '3' # /MDd
            },
          },
        },
        'Release': {
          'msvs_settings': {
            'VCCLCompilerTool': {
              'RuntimeLibrary': '2' # /MD
            },
          },
        },
      },

      'conditions': [
        ['OS=="linux"', {

          "include_dirs": ["<!(node -e \"require('nan')\")", "./deps/include", "../deps/include"],
          # "include_dirs": ["/home/fernando/dev/c-api/include"],

          "cflags": [
            "-std=c++17",
            "-Wno-deprecated-declarations",
            "-Wno-unused-result",
            "-Wno-cast-function-type",
            ""
          ],

          "cflags_cc": [
            "-std=c++17",
            "-Wno-deprecated-declarations",
            "-Wno-unused-result",
            "-Wno-cast-function-type",
            ""
          ],
          

          'libraries': [
            '-L./deps/lib/', 
            '-L../deps/lib/',
            # '-L/home/fernando/dev/c-api/build/lib', 

            '-lkth-c-api', 
            '-lkth-node', 
            '-lkth-blockchain', 
            '-lkth-network', 
            '-lkth-consensus', 
            '-lkth-database', 
            '-lkth-domain',
            # '-lboost_atomic', 
            # '-lboost_chrono', 
            '-lboost_date_time', 
            # '-lboost_filesystem', 
            '-lboost_iostreams', 
            '-lboost_locale', 
            '-lboost_log', 
            '-lboost_log_setup', 
            '-lboost_program_options', 
            '-lboost_regex', 
            '-lboost_system', 
            # '-lboost_unit_test_framework', 
            # '-lboost_prg_exec_monitor', 
            # '-lboost_test_exec_monitor', 
            # '-lboost_thread', 
            '-lsecp256k1', 
            '-lbz2', 
            '-lgmp', 
            '-lz',
          ],
        }],
        ['OS=="mac"', {

          "cflags": [
            "-std=c++11",
          ],
          "include_dirs": ["<!(node -e \"require('nan')\")", "./deps/include", "../deps/include"],
          # "include_dirs": ["/home/fernando/dev/c-api/include"],
          
          'libraries': [
            '-L./deps/lib/', 
            '-L../deps/lib/',
            # '-L/home/fernando/dev/c-api/build/lib', 

            '-lkth-c-api', 
            '-lkth-node', 
            '-lkth-blockchain', 
            '-lkth-network', 
            '-lkth-consensus', 
            '-lkth-database', 
            '-lkth-domain',
            '-lboost_atomic', 
            '-lboost_chrono', 
            '-lboost_date_time', 
            '-lboost_filesystem', 
            '-lboost_iostreams', 
            '-lboost_locale', 
            '-lboost_log', 
            '-lboost_log_setup', 
            '-lboost_program_options', 
            '-lboost_regex', 
            '-lboost_system', 
            '-lboost_unit_test_framework', 
            '-lboost_prg_exec_monitor', 
            '-lboost_test_exec_monitor', 
            '-lboost_thread', 
            '-lsecp256k1', 
            '-lbz2', 
            '-lgmp', 
            '-lz',
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
          "include_dirs": ["<!(node -e \"require('nan')\")", "deps/include"],
          'libraries': [
            '../deps/lib/kth-c-api.lib', 
            '../deps/lib/kth-node.lib', 
            '../deps/lib/kth-blockchain.lib', 
            '../deps/lib/kth-network.lib', 
            '../deps/lib/kth-consensus.lib', 
            '../deps/lib/kth-database.lib', 
            '../deps/lib/kth-domain.lib',
            '../deps/lib/kth-infrastructure.lib',
            '../deps/lib/libboost_atomic.lib', 
            '../deps/lib/libboost_chrono.lib', 
            '../deps/lib/libboost_date_time.lib', 
            '../deps/lib/libboost_filesystem.lib', 
            '../deps/lib/libboost_iostreams.lib', 
            '../deps/lib/libboost_locale.lib', 
            '../deps/lib/libboost_log.lib', 
            '../deps/lib/libboost_log_setup.lib', 
            '../deps/lib/libboost_program_options.lib', 
            '../deps/lib/libboost_regex.lib', 
            '../deps/lib/libboost_system.lib', 
            '../deps/lib/libboost_unit_test_framework.lib', 
            '../deps/lib/libboost_prg_exec_monitor.lib', 
            '../deps/lib/libboost_test_exec_monitor.lib', 
            '../deps/lib/libboost_thread.lib', 
            '../deps/lib/secp256k1.lib', 
            '../deps/lib/mpir.lib', 
            # '../deps/lib/libbz2', 
            # '../deps/lib/libgmp', 
            # '../deps/lib/libz',
          ]
        }]
      ],

    }
  ]
}
