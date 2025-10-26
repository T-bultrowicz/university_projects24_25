tests=0
while [ 1 ]; do
    tests=$(($tests+1))
    echo -n "Test #$tests.. "
    echo "$(($tests+69420)) $1" | ./gen.e >p.in
    ./test.e <p.in >p1.out
    ./solve.e <p.in >p2.out
    check=`diff -w -q p1.out p2.out`

    if [ "$check" != "" ]; then
        echo "failed"
        cat p1.out
        echo ""
        cat p2.out
        exit
    fi
    echo " OK "
    cat p1.out
done
