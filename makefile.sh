gcc main.c ./tests/global.h ./tests/global.c ./tests/n_test.h ./tests/n_test.c ./tests/v_test.h ./tests/v_test.c ./utils/help.h ./utils/help.c ./utils/utils.h ./utils/utils.c ./utils/params.h ./utils/params.c ./words/nouns.h ./words/nouns.c ./words/verbs.h ./words/verbs.c
mv a.out run_test.out
gcc main_rndw.c ./tests/global.h ./tests/global.c ./tests/n_test.h ./tests/n_test.c ./tests/v_test.h ./tests/v_test.c ./utils/help.h ./utils/help.c ./utils/utils.h ./utils/utils.c ./utils/params.h ./utils/params.c ./words/nouns.h ./words/nouns.c ./words/verbs.h ./words/verbs.c
mv a.out print_rndw.out
./run_test.out $1 $2 $3 $4
