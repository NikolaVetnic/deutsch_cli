./parser_ads.out "$1"
./parser_connectors.out "$1"
./parser_expressions.out "$1"
./parser_nouns.out "$1"
./parser_verbs.out "$1"

cd ../../../base

ln -s ./_complete/de/parsed/ads.csv ./de_ads.csv
ln -s ./_complete/de/parsed/connectors.csv ./de_connectors.csv
ln -s ./_complete/de/parsed/expressions.csv ./de_expressions.csv
ln -s ./_complete/de/parsed/nouns.csv ./de_nouns.csv
ln -s ./_complete/de/parsed/verbs.csv ./de_verbs.csv