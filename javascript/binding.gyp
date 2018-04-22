{
    "targets": [{
        "includes": [
            "auto.gypi",
            "final-flags.gypi"
        ],

        "sources": [
            "sources/yoga/Utils.cpp",
            "sources/yoga/YGConfig.cpp",
            "sources/yoga/YGEnums.cpp",
            "sources/yoga/YGFloatOptional.cpp",
            "sources/yoga/YGLayout.cpp",
            "sources/yoga/YGNode.cpp",
            "sources/yoga/YGNodePrint.cpp",
            "sources/yoga/YGStyle.cpp",
            "sources/yoga/Yoga.cpp",
            "sources/Config.cc",
            "sources/Node.cc",
            "sources/global.cc",
            "sources/nbind.cc"
        ],

        "cflags": [
            "-DNBIND"
        ],

        "include_dirs": [
            "sources"
        ]
    }],

    "includes": [
        "auto-top.gypi"
    ]
}
