# Copyright (c) 2016-2024 Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

{
  "targets": [
    {
      "target_name": "<(module_name)",
      'product_dir': '<(module_path)',

      "sources": [ "src/kth-native.cpp",
                   "src/node.cpp",

                   "src/string_list.cpp",
                   "src/chain/chain.cpp",
                   "src/chain/header.cpp",
                   "src/chain/block.cpp",
                   "src/chain/merkle_block.cpp",
                   "src/chain/point.cpp",
                   "src/chain/transaction.cpp",
                   "src/chain/input.cpp",
                   "src/chain/output.cpp",
                   "src/chain/output_point.cpp",
                   "src/chain/tools.cpp",
                   "src/chain/script.cpp",
                   "src/chain/input_list.cpp",
                   "src/chain/output_list.cpp",
                   "src/chain/transaction_list.cpp",
                   "src/chain/block_list.cpp",
                   "src/chain/history_compact_list.cpp",
                   "src/chain/history_compact.cpp",
                   "src/chain/stealth_compact.cpp",
                   "src/chain/stealth_compact_list.cpp",

                   "src/config/authority.cpp",
                   "src/config/blockchain_settings.cpp",
                   "src/config/checkpoint.cpp",
                   "src/config/database_settings.cpp",
                   "src/config/endpoint.cpp",
                   "src/config/network_settings.cpp",
                   "src/config/node_settings.cpp",
                   "src/config/settings.cpp",

                   "src/wallet/ec_private.cpp",
                   "src/wallet/ec_public.cpp",
                   "src/wallet/elliptic_curve.cpp",
                   "src/wallet/hd_private.cpp",
                   "src/wallet/hd_public.cpp",
                   "src/wallet/payment_address.cpp",
                   "src/wallet/wallet.cpp",

      ],

      'variables': {
        'install_py': '<(DEPTH)/install.py',
        'deployment_target%': '<!(echo $MACOSX_DEPLOYMENT_TARGET)'
      },

      "xcode_settings": {
        'MACOSX_DEPLOYMENT_TARGET': '<(deployment_target)',
        'OTHER_CFLAGS': [
          "-std=c++2b",
        ],
      },

      'actions': [
        {
          'action_name': 'Install',
          'inputs': [
            '>(install_py)',
          ],
          'outputs': [''],
          # 'action': ['<!(node -p "process.env.npm_config_python || \\"python\\"")','>@(_inputs)', '<(DEPTH)', "<(target_arch)"]
          'action': ['<!(node -p "process.env.npm_config_python || \\"python3\\"")','>@(_inputs)', '<(DEPTH)']
        },
      ],

      'defines': [
          'KTH_LIB_STATIC',
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
                'AdditionalOptions': [ '/std:c++23' ]
            },
         },
        },
        'Release': {
          'msvs_settings': {
            'VCCLCompilerTool': {
              'RuntimeLibrary': '0', # /MT
              # 'RuntimeLibrary': '2', # /MD
              'AdditionalOptions': [ '/std:c++23' ]
            },
          },
        },
      },

      'conditions': [
        ['OS=="linux"', {

          "include_dirs": ["<!(node -e \"require('nan')\")", "./deps/include", "../deps/include", "./include", "../include"],

          "cflags": [
            "-std=c++23",
            "-Wno-deprecated-declarations",
            "-Wno-unused-result",
            "-Wno-cast-function-type",
            ""
          ],

          "cflags_cc": [
            "-std=c++23",
            "-Wno-deprecated-declarations",
            "-Wno-unused-result",
            "-Wno-cast-function-type",
            ""
          ],


          'libraries': [
            "-L<(module_root_dir)/deps/lib/",

            '-lc-api',
            '-lnode',
            '-lblockchain',
            '-lnetwork',
            '-lconsensus',
            '-ldatabase',
            '-ldomain',
            '-linfrastructure',

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
            "-std=2b",
            ""
          ],

          "cflags_cc": [
            "-std=c++2b",
            ""
          ],

          "include_dirs": ["<!(node -e \"require('nan')\")", "./deps/include", "../deps/include", "./include", "../include"],

          'libraries': [
            "-L<(module_root_dir)/deps/lib/",

            '-lc-api',
            '-lnode',
            '-lblockchain',
            '-lnetwork',
            '-lconsensus',
            '-ldatabase',
            '-ldomain',
            '-linfrastructure',

            '-llmdb',

            # '-llmdbd',

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
        ['OS=="win"', {
          "include_dirs": ["<!(node -e \"require('nan')\")", "<(module_root_dir)/deps/include", "<(module_root_dir)/include"],

          'libraries': [
            '<(module_root_dir)/deps/lib/c-api.lib',
            '<(module_root_dir)/deps/lib/node.lib',
            '<(module_root_dir)/deps/lib/blockchain.lib',
            '<(module_root_dir)/deps/lib/network.lib',
            '<(module_root_dir)/deps/lib/consensus.lib',
            '<(module_root_dir)/deps/lib/database.lib',
            '<(module_root_dir)/deps/lib/domain.lib',
            '<(module_root_dir)/deps/lib/infrastructure.lib',
            '<(module_root_dir)/deps/lib/lmdb.lib',
            '<(module_root_dir)/deps/lib/libboost_date_time.lib',
            '<(module_root_dir)/deps/lib/libboost_iostreams.lib',
            '<(module_root_dir)/deps/lib/libboost_locale.lib',
            '<(module_root_dir)/deps/lib/libboost_program_options.lib',
            '<(module_root_dir)/deps/lib/libboost_system.lib',
            '<(module_root_dir)/deps/lib/libboost_thread.lib',
            '<(module_root_dir)/deps/lib/secp256k1.lib',
            '<(module_root_dir)/deps/lib/mpir.lib',
          ]
        }]
      ],

    }
  ]
}
