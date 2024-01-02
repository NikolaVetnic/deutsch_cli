gcc main.c \
    ./tests/global.h            ./tests/global.c            \
    ./tests/de/a_test.h         ./tests/de/a_test.c         \
    ./tests/de/c_test.h         ./tests/de/c_test.c         \
    ./tests/de/e_test.h         ./tests/de/e_test.c         \
    ./tests/de/n_test.h         ./tests/de/n_test.c         \
    ./tests/de/v_test.h         ./tests/de/v_test.c         \
    ./tests/hu/n_test_hu.h      ./tests/hu/n_test_hu.c      \
    ./tests/hu/v_test_hu.h      ./tests/hu/v_test_hu.c      \
    ./utils/help.h              ./utils/help.c              \
    ./utils/utils.h             ./utils/utils.c             \
    ./utils/params.h            ./utils/params.c            \
    ./words/de/ads.h            ./words/de/ads.c            \
    ./words/de/connectors.h     ./words/de/connectors.c     \
    ./words/de/expressions.h    ./words/de/expressions.c    \
    ./words/de/nouns.h          ./words/de/nouns.c          \
    ./words/de/verbs.h          ./words/de/verbs.c          \
    ./words/hu/nouns_hu.h       ./words/hu/nouns_hu.c       \
    ./words/hu/verbs_hu.h       ./words/hu/verbs_hu.c     
mv a.out run_test.out

gcc main_rndw.c \
    ./tests/global.h            ./tests/global.c            \
    ./tests/de/a_test.h         ./tests/de/a_test.c         \
    ./tests/de/c_test.h         ./tests/de/c_test.c         \
    ./tests/de/e_test.h         ./tests/de/e_test.c         \
    ./tests/de/n_test.h         ./tests/de/n_test.c         \
    ./tests/de/v_test.h         ./tests/de/v_test.c         \
    ./utils/help.h              ./utils/help.c              \
    ./utils/utils.h             ./utils/utils.c             \
    ./utils/params.h            ./utils/params.c            \
    ./words/de/ads.h            ./words/de/ads.c            \
    ./words/de/connectors.h     ./words/de/connectors.c     \
    ./words/de/expressions.h    ./words/de/expressions.c    \
    ./words/de/nouns.h          ./words/de/nouns.c          \
    ./words/de/verbs.h          ./words/de/verbs.c          
mv a.out print_rndw.out

./run_test.out $1 $2 $3 $4 $5 $6 $7 $8 $9
