# Copyright (c) 2016-2021 Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

{
  "targets": [
    {
      # "target_name": "kth",
      "target_name": "<(module_name)",

      'product_dir': '<(module_path)',

      "sources": [ "src/kth-native.cpp", "src/node.cpp",
                   "src/string_list.cpp",
                   "src/chain/chain.cpp", "src/chain/header.cpp", "src/chain/block.cpp", 
                   "src/chain/merkle_block.cpp", "src/chain/point.cpp", 
                   "src/chain/transaction.cpp", "src/chain/input.cpp", "src/chain/output.cpp", "src/chain/output_point.cpp", 
                   "src/chain/tools.cpp",
                   "src/chain/script.cpp", "src/chain/input_list.cpp", "src/chain/output_list.cpp", "src/chain/transaction_list.cpp",
                   "src/chain/block_list.cpp",
                   "src/chain/history_compact_list.cpp",
                   "src/chain/history_compact.cpp",
                   "src/chain/payment_address.cpp",
                   "src/chain/stealth_compact.cpp",
                   "src/chain/stealth_compact_list.cpp",
      ],
      
      'variables': {
        'setup_py': '<(DEPTH)/setup.py',
        'install_py': '<(DEPTH)/install.py',
      },

      "xcode_settings": {
        'OTHER_CFLAGS': [
          "-std=c++17",
          # "-stdlib=libc++"
        ],
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
          'KTH_LOG_LIBRARY_SPDLOG',
          'KTH_CURRENCY_BCH',
      ],
 
      #  https://docs.microsoft.com/en-us/dotnet/api/microsoft.visualstudio.vcprojectengine.runtimelibraryoption?view=visualstudiosdk-2019
      'configurations': {
        'Debug': {
          'msvs_settings': {
            'VCCLCompilerTool': {
                'RuntimeLibrary': '1', # /MTd
                # 'RuntimeLibrary': '3', # /MDd
                'AdditionalOptions': [ '/std:c++17' ]
            },
         },
        },
        'Release': {
          'msvs_settings': {
            'VCCLCompilerTool': {
              'RuntimeLibrary': '0', # /MT
              # 'RuntimeLibrary': '2', # /MD
              'AdditionalOptions': [ '/std:c++17' ]
            },
          },
        },
      },

      'conditions': [
        ['OS=="linux"', {

          "include_dirs": ["<!(node -e \"require('nan')\")", "./deps/include", "../deps/include", "./include", "../include"],

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
            "-L<(module_root_dir)/deps/lib/",

            '-lkth-c-api',
            '-lkth-node', 
            '-lkth-blockchain', 
            '-lkth-network', 
            '-lkth-consensus', 
            '-lkth-database', 
            '-lkth-domain',
            '-lkth-infrastructure',

            '-llmdb', 
            '-lboost_date_time', 
            '-lboost_iostreams', 
            '-lboost_locale', 
            '-lboost_program_options', 
            '-lboost_system', 
            '-lboost_thread', 
            '-lsecp256k1', 
            '-lbz2', 
            '-lgmp', 
            '-lz',
          ],
        }],
        ['OS=="mac"', {

          "cflags": [
            "-std=c++17",
            ""
          ],

          "cflags_cc": [
            "-std=c++17",
            ""
          ],

          "include_dirs": ["<!(node -e \"require('nan')\")", "./deps/include", "../deps/include", "./include", "../include"],
          
          'libraries': [
            "-L<(module_root_dir)/deps/lib/",

            '-lkth-c-api', 
            '-lkth-node', 
            '-lkth-blockchain', 
            '-lkth-network', 
            '-lkth-consensus', 
            '-lkth-database', 
            '-lkth-domain',
            # '-lboost_chrono', 
            '-lboost_date_time', 
            '-lboost_iostreams', 
            '-lboost_locale', 
            '-lboost_program_options', 
            '-lboost_system', 
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
       
          # "cflags": [
          #   "/std:c++17",
          #   ""
          # ],

          # "cflags_cc": [
          #   "/std:c++17",
          #   ""
          # ],
          
          "include_dirs": ["<!(node -e \"require('nan')\")", "<(module_root_dir)/deps/include", "<(module_root_dir)/include"],
          
          'libraries': [
            '<(module_root_dir)/deps/lib/kth-c-api.lib', 
            '<(module_root_dir)/deps/lib/kth-node.lib', 
            '<(module_root_dir)/deps/lib/kth-blockchain.lib', 
            '<(module_root_dir)/deps/lib/kth-network.lib', 
            '<(module_root_dir)/deps/lib/kth-consensus.lib', 
            '<(module_root_dir)/deps/lib/kth-database.lib', 
            '<(module_root_dir)/deps/lib/kth-domain.lib',
            '<(module_root_dir)/deps/lib/kth-infrastructure.lib',
            '<(module_root_dir)/deps/lib/lmdb.lib',
            '<(module_root_dir)/deps/lib/boost_date_time.lib', 
            '<(module_root_dir)/deps/lib/boost_iostreams.lib', 
            '<(module_root_dir)/deps/lib/boost_locale.lib', 
            '<(module_root_dir)/deps/lib/boost_program_options.lib', 
            '<(module_root_dir)/deps/lib/boost_system.lib', 
            '<(module_root_dir)/deps/lib/boost_thread.lib', 
            '<(module_root_dir)/deps/lib/secp256k1.lib', 
            '<(module_root_dir)/deps/lib/mpir.lib', 
            # '<(module_root_dir)/deps/lib/libbz2', 
            # '<(module_root_dir)/deps/lib/libgmp', 
            # '<(module_root_dir)/deps/lib/libz',
          ]

# LastWriteTime         Length Name                                                                  
# ----                -------------         ------ ----                                                                  
# -a----        2/19/2021   3:01 PM         323658 boost_chrono.lib                                                      
# -a----        2/19/2021   3:01 PM           1290 boost_date_time.lib                                                   
# -a----        2/19/2021   3:01 PM         411396 boost_iostreams.lib                                                   
# -a----        2/19/2021   3:01 PM        6104276 boost_locale.lib                                                      
# -a----        2/19/2021   3:01 PM        3879060 boost_program_options.lib                                             
# -a----        2/19/2021   3:01 PM           1224 boost_system.lib                                                      
# -a----        2/19/2021   3:01 PM         452724 boost_thread.lib                                                      
# -a----        2/19/2021   3:01 PM       15126924 kth-blockchain.lib                                                    
# -a----        2/19/2021   3:01 PM       15908386 kth-c-api.lib                                                         
# -a----        2/19/2021   3:01 PM        1968980 kth-consensus-clone.lib                                               
# -a----        2/19/2021   3:01 PM        2123428 kth-consensus.lib                                                     
# -a----        2/19/2021   3:01 PM        6325546 kth-database.lib                                                      
# -a----        2/19/2021   3:01 PM       33330086 kth-domain.lib                                                        
# -a----        2/19/2021   3:01 PM       21823762 kth-infrastructure.lib                                                
# -a----        2/19/2021   3:01 PM       48329588 kth-network.lib                                                       
# -a----        2/19/2021   3:01 PM       36773980 kth-node.lib                                                          
# -a----        2/19/2021   3:00 PM         167696 lmdb.lib                                                              
# -a----        2/19/2021   3:00 PM        2972834 mpir.lib                                                              
# -a----        2/19/2021   3:00 PM        1405270 mpirxx.lib                                                            
# -a----        2/19/2021   3:01 PM         162894 secp256k1.lib                                                         
# -a----        2/19/2021   3:00 PM           1104 sicudt.lib                                                            
# -a----        2/19/2021   3:00 PM       22085728 sicuin.lib                                                            
# -a----        2/19/2021   3:00 PM         386992 sicuio.lib                                                            
# -a----        2/19/2021   3:00 PM         257144 sicutest.lib                                                          
# -a----        2/19/2021   3:00 PM        2264194 sicutu.lib                                                            
# -a----        2/19/2021   3:00 PM        8713778 sicuuc.lib            
        }]
      ],

    }
  ]
}
