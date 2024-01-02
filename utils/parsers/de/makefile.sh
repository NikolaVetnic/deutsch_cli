gcc parser_nouns.c \
    ../../utils.h                       ../../utils.c                       \
    ../../../words/de/nouns.h           ../../../words/de/nouns.c           \
    ../../../tests/global.h             ../../../tests/global.c             \
    ../../../words/w_sym.h
mv a.out parser_nouns.out

gcc parser_verbs.c \
    ../../utils.h                       ../../utils.c                       \
    ../../../words/de/verbs.h           ../../../words/de/verbs.c           \
    ../../../tests/global.h             ../../../tests/global.c             \
    ../../../words/w_sym.h
mv a.out parser_verbs.out

gcc parser_ads.c \
    ../../utils.h                       ../../utils.c                       \
    ../../../words/de/ads.h             ../../../words/de/ads.c             \
    ../../../tests/global.h             ../../../tests/global.c             \
    ../../../words/w_sym.h  
mv a.out parser_ads.out

gcc parser_connectors.c \
    ../../utils.h                       ../../utils.c                       \
    ../../../words/de/connectors.h      ../../../words/de/connectors.c      \
    ../../../tests/global.h             ../../../tests/global.c             \
    ../../../words/w_sym.h
mv a.out parser_connectors.out

gcc parser_expressions.c \
    ../../utils.h                       ../../utils.c                       \
    ../../../words/de/expressions.h     ../../../words/de/expressions.c     \
    ../../../tests/global.h             ../../../tests/global.c             \
    ../../../words/w_sym.h
mv a.out parser_expressions.out