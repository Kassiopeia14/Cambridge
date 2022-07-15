{
 "targets": [
  {
   "target_name": "sha256Generator",
   "sources": ["SHA256GeneratorWrap_Node.cpp", "SHA256GeneratorWrap.cpp"],
   "cflags_cc": [
        "-std=c++17"
      ],
   "defines": [
        "UNICODE"
      ],
    "libraries": [
        "../../x64/Release/modSHA256Generator.lib"
    ],

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
  }
 ]
}