gcc main.c ./tests/v_test.h ./tests/v_test.c ./utils/help.h ./utils/help.c ./utils/params.h ./utils/params.c ./words/verbs.h ./words/verbs.c
mv a.out run_test.out
./run_test.out $1 $2 $3 $4
