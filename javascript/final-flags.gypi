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
                "-s", "TOTAL_MEMORY=134217728"
            ],

	    "xcode_settings": {
		"OTHER_LDFLAGS": [ "<@(_ldflags)" ]
	    }

        } ]

    ]
}
