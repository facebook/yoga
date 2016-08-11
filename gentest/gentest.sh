rm $(dirname $0)/test.html
$EDITOR $(dirname $0)/test.html
export TEST=$(cat test.html)
printf "$(cat $(dirname $0)/test-template.html)" "$(cat $(dirname $0)/test.html)" > $(dirname $0)/test.html
open $(dirname $0)/test.html
