{
    "conditions": [

        [ "1==1", {

            "cflags_cc": [
                "-std=c++14",
                "-DNBIND_DUPLICATE_POINTERS"
            ],

	    "xcode_settings": {
		"OTHER_CPLUSPLUSFLAGS": [ "<@(_cflags_cc)" ]
	    }

        } ],

        [ "asmjs==1", {

            "ldflags": [
                "--memory-init-file", "0",
                "-s", "PRECISE_F32=1",
                "-s", "ALLOW_MEMORY_GROWTH=1"
            ],

	    "xcode_settings": {
		"OTHER_LDFLAGS": [ "<@(_ldflags)" ]
	    }

        } ]

    ]
}
