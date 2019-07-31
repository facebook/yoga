{
    "targets": [{
    	"includes": [
    	    "auto.gypi",
            "final-flags.gypi"
    	],

    	"sources": [
            "<!@(ls -1 sources/yoga/*.cpp)",
            "<!@(ls -1 sources/yoga/*/*.cpp)",
            "sources/Config.cc",
            "sources/Node.cc",
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
