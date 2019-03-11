mkdir encrypted
for i in `ls *.pdf`; do
  pdftk $i output encrypted/$i.encrypt.pdf owner_pw "$2" user_pw "$3"
done
