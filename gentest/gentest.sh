rm $(dirname $0)/test.html
$EDITOR $(dirname $0)/test.html

GENERIC_TEST="$(cat $(dirname $0)/test.html)"
LTR_TEST="$(cat $(dirname $0)/test.html)"
RTL_TEST="$(cat $(dirname $0)/test.html)"

LTR_TEST=${LTR_TEST//start/left}
LTR_TEST=${LTR_TEST//end/right}

RTL_TEST=${RTL_TEST//start/right}
RTL_TEST=${RTL_TEST//end/left}

printf "$(cat $(dirname $0)/test-template.html)" "$LTR_TEST" "$RTL_TEST" "$GENERIC_TEST" > $(dirname $0)/test.html
open $(dirname $0)/test.html
