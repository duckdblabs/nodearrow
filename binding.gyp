{
    "targets": [
        {
            "target_name": "<(module_name)",
            "sources": [
                "src/nodearrow.cpp"
            ],
            "include_dirs": [
                "<!@(node -p \"require('node-addon-api').include\")",
                '$(ARROW_INCLUDE)'
            ],
            'defines': [
                'NAPI_DISABLE_CPP_EXCEPTIONS=1',
                "NAPI_VERSION=5"
            ],
            "cflags_cc": [
                "-frtti",
                "-fexceptions",
                "-Wno-redundant-move",
            ],
            "cflags_cc!": [
                "-fno-rrti",
                "-fno-exceptions",
            ],
            "cflags": [
                "-frtti",
                "-fexceptions",
                "-Wno-redundant-move",
            ],
            "cflags!": [
                "-fno-rrti",
                "-fno-exceptions",
            ],
            "xcode_settings": {
                "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
                "GCC_ENABLE_CPP_RTTI": "YES",
                "CLANG_CXX_LIBRARY": "libc++",
                "MACOSX_DEPLOYMENT_TARGET": "10.15",
                'CLANG_CXX_LANGUAGE_STANDARD':'c++11',
                'OTHER_CFLAGS' : ['-fexceptions', '-frtti', '-Wno-redundant-move']

            },
            "msvs_settings": {
                "VCCLCompilerTool": {
                    "ExceptionHandling": 1,
                    "AdditionalOptions": [
                        "/bigobj"
                    ]
                }
            },
            # "conditions": [
            #     [
            #         'OS=="win"',
            #         {
            #             "defines": [
            #                 "DUCKDB_BUILD_LIBRARY"
            #             ]
            #         },
            #     ],  # OS=="win"
            # ],  # conditions
            "libraries": [
                '$(ARROW_STATIC_LIB)'
            ]

        },
        {
            "target_name": "action_after_build",
            "type": "none",
            "dependencies": [
                "<(module_name)"
            ],
            "copies": [
                {
                    "files": [ "<(PRODUCT_DIR)/<(module_name).node" ],
                    "destination": "<(module_path)"
                }
            ]
        }
    ]
}
