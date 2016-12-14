RED='\033[1;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color


for i in $(seq 0 19); do
  printf "TEST $i\t"
  cp dataset/input/input$i.txt input.txt
  #time
   ./lich >/dev/null

  if diff output.txt dataset/output/output$i.txt > /dev/null ; then
    echo "------------> ${GREEN}OUTPUT CORRETTO${NC}"
  else
    echo "------------> ${RED}OUTPUT SBAGLIATO${NC}"
fi
done
